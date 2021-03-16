#include <DSProtocol.h>
#include <DSState.h>
#include <Drivetrain.h>


/*************************************************************
 ****************** Modules / Libraries **********************
 *************************************************************/
DSProtocol comms;
Drivetrain drive;

/*************************************************************
 ********************* Hardware Setup ************************
 *************************************************************/
#define DO_LM_PWM  5   // Left Motor Speed
#define DO_RM_PWM  6   // Right Motor Speed
#define DO_LM_REV  7   // Left Motor - Reverse
#define DO_LM_FWD  8   // Left Motor - Forward
#define DO_RM_REV  9   // Right Motor - Reverse
#define DO_RM_FWD 11   // Right Motor - Forward


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
  Serial.begin(57600);
  while (!Serial); // wait for Leonardo enumeration, others continue immediately
  Serial.println("Ready");

  //
  // Hardware initailization
  //
  drive.setup(DO_LM_FWD, DO_LM_REV, DO_LM_PWM,
              DO_RM_FWD, DO_RM_REV, DO_RM_PWM);

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
    
  	float forward  = dsStatus.gamepad1.getAxisFloat(GamepadAxis::LeftY);
  	float turn = dsStatus.gamepad1.getAxisFloat(GamepadAxis::RightX); 

  	// Pass axes to arcade drive
    drive.arcade(forward, turn, true);
  
  } 
  else 
  {
    //Serial.println("No new data received, waiting...");
    delay(50);
  }

  
}
