ilib/*
 * PCA Test Bench   2/26/21
 * This program is used to test out PWM PCA boards and servos used for the Team BJORG KOP
 * Place a servo on the PWM port 1 (port 0 is the first port, port 1 is the 2nd from the left).
 * The program will move the servo back and forth in 3 steps.
 */
//Libraries
  #include <Wire.h>                       //https://www.arduino.cc/en/reference/wire
  #include <Adafruit_PWMServoDriver.h>    //https://github.com/adafruit/Adafruit-PWM-Servo-Driver-Library


//Objects
  Adafruit_PWMServoDriver pca= Adafruit_PWMServoDriver(0x40);

void setup() {
  
  pca.begin();
  pca.setPWMFreq(50);
}

void loop() {
  pca.setPin(1,150,false);   //about 10 degrees
  delay(1000);
  pca.setPin(1,300,false);   //about 90 degrees which is mid range
  delay(1000);
  pca.setPin(1,450,false);   //about 170 degres
  delay(1000);

}
