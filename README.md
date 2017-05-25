PWM dimmed leds strip in function of the distance between your hand and the sensor.
The sensor and the aluminium profile containing the strips are sticked under the upper cabinet of the kitchen.
- If the distance is lower than 5cm (2") light is full and an orange led is on as well.
- If the distance is between 5cm and 18cm, light is dimmed from 100% to 0% and the orange led is blinking.
- If the distance is between 18cm and 23cm, light is off and the orange led as well.
- Distances higher than 23cm are ignored.

Actually, even if the system globally works, there are still changes in the lighting due to a kind of "rebounds" when my hand is under the sensor. So the code needs improvements : it decrements a counter when the distance is constant and, when the counter reaches zero, the code works with the measured value which is supposed to be stable. If the distance changes before the counter reaches zero, the counter is reinitialized. 
I planned to make an average of the measures to obtain something stable. In fact, I don't get time to work on it actually as I'm on another project.
