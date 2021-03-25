/*
 * This program changes the name advertized by the Bluetooth module.
 * You only need to run this once.  The module will remember the name.
 * 
 * Instructions:
 *  1. Replace the your name here with up to 18 charcters in the AT+NAMEyour name here\r\n line.
 *  2. Download the code to your robot.
 *  3. Unplug the USB port, pug in your RF module and then power up.
 *  4. Wait several seconds then power back down.
 *  4. The name change will be written on the first power up,
 *     But it will show up every time you power up after that.
 *  5. Unplug the bluetooth module, hook up the USB and load your normal code.
 *  
 *  This program only needs to be run once.
 *  The RF module will remember the name you give it.
 *  
 */ 
void setup() {
  // Change thg Bluetooth advertising name.
  Serial.begin(9600);
  delay(1000);
  Serial.print("AT+NAMEyournamehere\r\n");
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:

}
