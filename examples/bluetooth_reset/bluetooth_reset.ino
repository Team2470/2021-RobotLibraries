/*
 * This program changes the name advertized by the Bluetooth module.
 * You only need to run this once.  The module will remember the name.
 * 
 * Instructions:
 *  1. Download the code to your robot.
 *  2. Unplug the USB port, pug in your RF module and then power up.
 *  3. Wait for the LED on the board to blink
 *  4. Repeat the power up and power down process, it can take 2 boots to write both registers properly
 *  5. The name change will be written on the first power up,
 *     But it will show up every time you power up after that.
 *  6. Unplug the bluetooth module, hook up the USB and load your normal code.
 *  
 *  This should reset your module back to the default settings needed for the code
 *  that shipped with the robot.
 *  
 */

/*
 * Do not modify this function
 */
void setup() {
  // Change the name and restore the baud rate
  Serial.begin(115200);
  delay(500);

  // Reset the name and baud back to default
  Serial.print("AT+BAUD0\r\n");
  delay(500);
  Serial.print("AT+NAMEResetting...\r\n");
  Serial.flush();
  delay(500);
  
  // In case the baud was already set, just reset the name
  Serial.begin(9600);
  delay(500);
  Serial.print("AT+NAMEELEGOO BT16\r\n");
  delay(500);

  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
}

bool blink = false;

void loop() {
  // When setup is done, blink the LED
  blink = !blink;
  digitalWrite(13, blink ? HIGH : LOW);
  delay(500);
}
