// ProxLevel
// Pour tout appareil controlable en PWM, intensité fonction du capteur de proximité à ultra sons
// Si la position est à moins de 5cm, l'intensité est à 100% puis elle décroît jusqu'à 17cm et plus où elle passe à 0%
//
// Ecriture programme : Raphaël OLLIER
// 08 Mars 2017 - 17 Mars 2017
// Ver. 5.2

int oldd = 0;             // ancienne distance en cm
int vol = 0;               // volume
int orange = 2;             // D2 emplacement du voyant 100%
int cpt = 7;                // valeur d'init du compteur
int vcpt = 7;               // variable compteur

int clign = 40;
int vclign = 40;

int trig = 5;              // D5 broche trigger capteur ultra sons
int echo = 6;              // D6 broche retour delai
long lecture_echo;
int d;                    // distance en cm

byte levelout = 11;        // D11 broche de sortie pwm


void setup() {             // ne joue qu'une fois a  chaque demarrage ou reset

  // initialise les entrees et sorties
  pinMode (orange, OUTPUT);
  pinMode(levelout, OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  digitalWrite(trig, LOW);

  Serial.begin(9600);          // init moniteur serie
}

void loop() {                  // tourne en boucle
  digitalWrite(trig, HIGH);    // pulse de 10µS sur trig
  delayMicroseconds(10);       //
  digitalWrite(trig, LOW);     //
  lecture_echo = pulseIn(echo, HIGH);
  d = (lecture_echo / 58) ;   // conversion en cm - distance in cm
  antirebond();               // appel vers routine d'antirebonds - call anti bounces

  if (vol >= 255) {
    (vol = 255);
    digitalWrite(orange, HIGH); // cadrage et allumage voyant - light full : orange on
  }
  if (vol <= 0) {
    (vol = 0);
    digitalWrite(orange, LOW);  // eteindre le voyant - light off : orange off
  }
  
  analogWrite(levelout, vol); // ecriture des sorties

  if ((vol > 0) && (vol < 255)) {        // voyant clignotant - light between : orange blinks
    (vclign--);
    if (vclign == 0) (vclign = clign);
    if (vclign > (clign/ 8)) {
      digitalWrite(orange, LOW);
    }
    else
    {
      digitalWrite(orange, HIGH);
    }
  }
  delay(10);                 // attente 10 milliseconde - wait
}

// routine de calcul du volume - intensity calculation
void calcul() {
  if (d <= 25) {
    if ( d >= 18 ) {
      (vol = 0);
    }
    else
    { if (d < 18) {
        (vol = (350 - (20 * d)));
      }
    }
    if (d < 5) {
      (vol = 255);
    }
  }
}

//routine supprimant les rebonds - antibounce
void antirebond() {
  if (d > 25) {
    (reset());
  }
  else
  {
    if (oldd == d) {
      if (vcpt == 0) {
        calcul();
      }
      else
      {
        (vcpt--);
      }
    }
    else {
      (oldd = d);
    }
  }
}

//routine dr reinitialisation de la variable compteur de rebonds - reset
void reset() {
  (oldd = d);
  (vcpt = cpt);
}

/*
  void impression() {
  Serial.print("vol : ");
  Serial.print(vol);
  Serial.print(" vcpt : ");
  Serial.print(vcpt);
  Serial.print(" oldd : ");
  Serial.print(oldd);
  Serial.print (" d: ");
  Serial.println(d);
  }
*/

