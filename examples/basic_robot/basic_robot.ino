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
    
  	double left  = -(dsStatus.gamepad1.axis[1]) / 128.0; // Invert as the Y axis is inverted
  	double right = -(dsStatus.gamepad1.axis[3]) / 128.0; // Invert as the Y axis is inverted
    
  	// Pass axes to arcade drive
    drive.arcade(left, right, true);
  
  } 
  else 
  {
    //Serial.println("No new data received, waiting...");
    delay(50);
  }

  
}
