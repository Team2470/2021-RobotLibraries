#include <DSProtocol.h>
#include <DSState.h>


/*************************************************************
 ****************** Modules / Libraries **********************
 *************************************************************/
DSProtocol comms;


/*************************************************************
 ********************* Hardware Setup ************************
 *************************************************************/
#define DO_LM_PWM  5   // Left Motor Speed
#define DO_RM_PWM  6   // Right Motor Speed
#define DO_LM_FWD  7   // Left Motor - Forward
#define DO_LM_REV  8   // Left Motor - Reverse
#define DO_RM_FWD  9   // Right Motor - Forward
#define DO_RM_REV 11  // Right Motor - Reverse


/*************************************************************
 *********************** Main Code ***************************
 *************************************************************/

/**
 * Configuration
 *
 * This is run once when the program first starts.  Use it to
 * configure and initialize any modules or system components.
 */
void setup() {
  //
  // Driver station initialization
  //

  // This should match the serial or Bluetooth rate
  comms.begin(57600);
  

  //
  // Hardware initailization
  //
  pinMode(DO_LM_FWD, OUTPUT);
  pinMode(DO_LM_REV, OUTPUT);
  pinMode(DO_RM_FWD, OUTPUT);
  pinMode(DO_RM_REV, OUTPUT);
  pinMode(DO_LM_PWM, OUTPUT);
  pinMode(DO_RM_PWM, OUTPUT);
}

/**
 * Main Loop
 *
 * This is the main loop, it will be called repeatedly until the robot is turned off.
 * Do not perform any blocking calls or your robot will hang up and not work.
 */
void loop() {

  // Only react if we have received new packets, otherwise wait
  if (comms.process()) 
  {

  	// User code
    DriverStation dsStatus = comms.getStatus();
    
  	int left  = -(dsStatus.gamepad1.axis[1]); // Invert as the Y axis is inverted
  	int right = -(dsStatus.gamepad1.axis[3]); // Invert as the Y axis is inverted
    
  
  	// TODO Figure out arcade drive later.....
  
  	// Set the direection for the left motor
  	// TODO add a dead band
  	uint8_t leftOutput = 0;
  	if (left > 0) 
  	{
  		// Forward
  		digitalWrite(DO_LM_FWD, HIGH);
  		digitalWrite(DO_LM_REV, LOW);  
  		leftOutput = map(left, 0, 128, 0, 255);
  	} 
  	else 
  	{
  		digitalWrite(DO_LM_FWD, LOW);
  		digitalWrite(DO_LM_REV, HIGH);      
  		leftOutput = map(left, -127, 0, 255, 0);
  	}
  	Serial.print("Left Out: ");
  	Serial.println(leftOutput);
  	analogWrite(DO_LM_PWM, leftOutput);
  
  	// Set the direection for the right motor
  	// TODO add a dead band
  	uint8_t rightOutput = 0;
  	if (right > 0) 
  	{
  		// Forward
  		digitalWrite(DO_RM_FWD, LOW);  
  		digitalWrite(DO_RM_REV, HIGH);
  		rightOutput = map(right, 0, 128, 0, 255);
  	} 
  	else 
  	{
  		digitalWrite(DO_RM_FWD, HIGH);  
  		digitalWrite(DO_RM_REV, LOW);    
  		rightOutput = map(right, -127, 0, 255, 0);
  	}
  	Serial.print("Right Out: ");
  	Serial.println(rightOutput);
  	analogWrite(DO_RM_PWM, rightOutput);  
	
  } 
  else 
  {
    Serial.println("No new data received, waiting...");
  }

  
}
