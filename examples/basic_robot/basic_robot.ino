#include <DSProtocol.h>
#include <DSState.h>
#include <Drivetrain.h>
#include "Constants.h"

#include "LEDSubsystem.h"
#include "CommandScheduler.h"
#include "BlinkLEDCmd.h"

/*************************************************************
 ****************** Modules / Libraries **********************
 *************************************************************/
DSProtocol comms;
Drivetrain drive;

LEDSubsystem led;

BlinkLEDCmd  led_blink(led);

/* Used to get the last time we updated the status */
long lastStatusTime = millis();
long STATUS_UPDATE_MS = 2000;

/* Tracks the last time we received a packet */
long lastCommsTime = millis();
long COMMS_LOST_MS = 1000;


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
  led.setup();

  CommandScheduler::getInstance().registerSubsystem(led);
  
  CommandScheduler::getInstance().schedule(led_blink);
}

/**
 * Main Loop
 *
 * This is the main loop, it will be called repeatedly until the robot is turned off.
 * Do not perform any blocking calls or your robot will hang up and not work.
 */
void loop() {

  // Temporary testing, run scheduler inside loop
  CommandScheduler::getInstance().run();


  // Only react if we have received new packets, otherwise wait
  if (comms.process()) 
  {
    DriverStation dsStatus = comms.getStatus();

    if (dsStatus.enabled) 
    {
      // For now, always run teleop mode, in the future use mode to switch
      // between teleop_loop and autonomous_loop
      teleop_loop(dsStatus);
    }
    else
    {
      disable();
    }

    /* Print updates at a slow rate to prevent flooding the serial port */
    long curStatusTime = millis();
    if ((curStatusTime - lastStatusTime) > STATUS_UPDATE_MS)
    {
      status_loop(dsStatus);
      lastStatusTime = curStatusTime;
    }

    lastCommsTime = millis();
  } 

  //Serial.println("No new data received, waiting...");
  delay(20);

  if ((millis() - lastCommsTime) > COMMS_LOST_MS) 
  {
    disable();
  }
}

/**
 * Update the printed status of the robot every 2 seconds
 *
 * Place any status update code here to prevent flooding the serial port.
 */
void status_loop(DriverStation& dsStatus) 
{
  if (!dsStatus.enabled) Serial.println("Robot disabled, waiting to enable...");
  if (dsStatus.enabled && dsStatus.mode == 0) Serial.println("Robot enabled. Teleop Mode");
}

/**
 * Teleop Loop
 *
 * Place all your teleop mode code here
 */
void teleop_loop(DriverStation& dsStatus) 
{

  float forward  = dsStatus.gamepad1.getAxisFloat(GamepadAxis::LeftY);
  float turn = dsStatus.gamepad1.getAxisFloat(GamepadAxis::RightX); 

  // Pass axes to arcade drive
  drive.arcade(forward, turn, true);
}

/**
 * Disable Robot
 * 
 * Shutdown and stop any motors here.
 * This will get called on disable, or if we lose communications
 */
void disable()
{
    //digitalWrite(DO_LED, LOW);
    drive.setPower(0.0f, 0.0f);
}
