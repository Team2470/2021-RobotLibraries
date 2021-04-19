/*
 * This program changes the name advertized by the Bluetooth module.
 * You only need to run this once.  The module will remember the name.
 * 
 * Instructions:
 *  1. Download the code to your robot.
 *  2. Unplug the USB port, pug in your RF module and then power up.
 *  3. Wait several seconds then power back down.
 *  4. Repeat the power up and power down process, it can take 2 boots to write both registers properly
 *  5. The name change will be written on the first power up,
 *     But it will show up every time you power up after that.
 *  6. Unplug the bluetooth module, hook up the USB and load your normal code.
 *  
 *  This should reset your module back to the default settings needed for the code
 *  that shipped with the robot.
 *  
 */

// ****** DO NOT Modify - Name required by Elegoo App ******
char ROBOT_NAME[] = "ELEGOO BT16";

/*
 * Do not modify this function
 */
void setup() {
  // Change the name and restore the baud rate
  Serial.begin(115200);
  while(!Serial);
  delay(500);
  
  // Flush any spurious command data
  Serial.print("\r\n");
  
  Serial.print("AT+NAME");
  Serial.print(ROBOT_NAME);
  Serial.print("\r\n");
  delay(500);
  
  Serial.print("AT+BAUD=0\r\n");
  Serial.flush();
  delay(500);
  Serial.end();

  // In case the baud was already set, just reset the name
  Serial.begin(9600);
  while(!Serial);
  delay(500);

  // Flush any spurious command data
  Serial.print("\r\n");
  
  Serial.print("AT+NAME");
  Serial.print(ROBOT_NAME);
  Serial.print("\r\n");
  delay(500);
}

void loop() {
  // put your main code here, to run repeatedly:

}
