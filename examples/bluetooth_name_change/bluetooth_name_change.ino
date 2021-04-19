/*
 * This program changes the name advertized by the Bluetooth module.
 * You only need to run this once.  The module will remember the name.
 * 
 * Instructions:
 *  1. Replace the your_name_here with up to 18 charcters in the AROBOT_NAME line.
 *  2. Download the code to your robot.
 *  3. Unplug the USB port, pug in your RF module and then power up.
 *  4. Wait several seconds then power back down.
 *  5. Repeat the power up and power down process, it can take 2 boots to write both registers properly
 *  6. The name change will be written on the first power up,
 *     But it will show up every time you power up after that.
 *  7. Unplug the bluetooth module, hook up the USB and load your normal code.
 *  
 *  This program only needs to be run once.
 *  The RF module will remember the name you give it.
 *  
 */

// ****** MODIFY YOUR NAME HERE ******
char ROBOT_NAME[] = "your_name_here";

/*
 * Do not modify this function
 */
void setup() {
  // Change the Bluetooth advertising name.
  Serial.begin(9600);
  while(!Serial);
  delay(500);

  // Flush any spurious command data
  Serial.print("\r\n");
  
  Serial.print("AT+NAME");
  Serial.print(ROBOT_NAME);
  Serial.print("\r\n");
  delay(500);
  
  Serial.print("AT+BAUD=4\r\n");
  Serial.flush();
  delay(500);
  Serial.end();

  // In case they just want to change the name, also function if the baud is set to 115200
  Serial.begin(115200);
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
