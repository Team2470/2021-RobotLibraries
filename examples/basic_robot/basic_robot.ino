#include <DSProtocol.h>
#include <DSState.h>
#include <Drivetrain.h>
#include <CommandBasedRobot.h>

#include "Constants.h"

#include "LEDSubsystem.h"
#include "HeadSubsystem.h"

#include "BlinkLEDCmd.h"
#include "ScanHeadCmd.h"

/*************************************************************
 ****************** Modules / Libraries **********************
 *************************************************************/
DSProtocol comms;
Drivetrain drive;

LEDSubsystem led;
HeadSubsystem head;

/*************************************************************
 ************** Commands the robot will use ******************
 *************************************************************/
 
BlinkLEDCmd slow_blink(led, 500, 5000);
BlinkLEDCmd fast_blink(led, 100, 2000);
WaitCmd     wait_1s(1000);
ScanHeadCmd scan_head(head, 3500, 0, 180);

/*************************************************************
 ********* Commands Sequences the robot will use *************
 *************************************************************/
 
CommandBase *bp_cmds[] = {&fast_blink, &wait_1s, &slow_blink, &wait_1s, &fast_blink};
SequentialCommandGroup blink_pattern(SIZEOF(bp_cmds), bp_cmds);

CommandBase *sab_cmds[] {&scan_head, &blink_pattern};
ParallelCommandGroup scan_and_blink(SIZEOF(sab_cmds), sab_cmds);


/*************************************************************
 ********** Robot state tracking (Do not edit) ***************
 *************************************************************/
 
/* Used to get the last time we updated the status */
long lastStatusTime = millis();
long STATUS_UPDATE_MS = 2000;

/* Tracks the last time we received a packet */
long lastCommsTime = millis();
long COMMS_LOST_MS = 1000;

/* Button pressed tracking */
bool btn_prev_a_ = false;
bool btn_prev_b_ = false;
bool btn_prev_x_ = false;
bool btn_prev_y_ = false;
bool btn_prev_start_ = false;

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
  Serial.begin(115200);
  while (!Serial); // wait for Leonardo enumeration, others continue immediately
  Serial.println("Ready");

  //
  // Hardware initailization
  //   Sets the I/O pins and other settings used by the subsystems
  drive.setup(DO_LM_FWD, DO_LM_REV, DO_LM_PWM,
              DO_RM_FWD, DO_RM_REV, DO_RM_PWM);
              
  led.setup(DO_LED);
  head.setup(DO_NECK, ALG_US_TX, ALG_US_RX);

  // Register the subsystem periodic calls with the scheduler
  CommandScheduler::getInstance().registerSubsystem(led);
  CommandScheduler::getInstance().registerSubsystem(head);
  
  Serial.println("Setup complete!");
}

/**
 * Main Loop
 *
 * This is the main loop, it will be called repeatedly until the robot is turned off.
 * Do not perform any blocking calls or your robot will hang up and not work.
 * 
 * You should not have to modify this if you are using the driver stations.  Instead, modify the
 * teleop loop function.
 */
void loop() {

  // TODO: Change to only run the scheduler when enabled?
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

  // Delay some, otherwise we try to read/send too fast
  delay(20);

  // Check if we still have communications to the driver station
  // Disable if we lose communication
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
  if (!dsStatus.enabled) Serial.println("Robot disabled");
}

/**
 * Teleop Loop
 *
 * Place all your teleop mode code here
 */
void teleop_loop(DriverStation& dsStatus) 
{
  float forward  = dsStatus.gamepad.getAxisFloat(GamepadAxis::LeftY);
  float turn = dsStatus.gamepad.getAxisFloat(GamepadAxis::RightX); 

  bool btn_a     = dsStatus.gamepad.getButton(GamepadButton::A);
  bool btn_b     = dsStatus.gamepad.getButton(GamepadButton::B);
  bool btn_x     = dsStatus.gamepad.getButton(GamepadButton::X);
  bool btn_y     = dsStatus.gamepad.getButton(GamepadButton::Y);
  bool btn_start = dsStatus.gamepad.getButton(GamepadButton::Start);
  
  if (btn_a && btn_a != btn_prev_a_) {
    CommandScheduler::getInstance().schedule(fast_blink);
  }
  btn_prev_a_ = btn_a;

  if (btn_b && btn_b != btn_prev_b_) {
    CommandScheduler::getInstance().schedule(true, scan_head);
  }
  btn_prev_b_ = btn_b;

  if (btn_x && btn_x != btn_prev_x_) {
    CommandScheduler::getInstance().schedule(true, blink_pattern);
  }
  btn_prev_x_ = btn_x;

  if (btn_y && btn_y != btn_prev_y_) {
    CommandScheduler::getInstance().schedule(true, scan_and_blink);
  }
  btn_prev_y_ = btn_y;
  
  if (btn_start && btn_start != btn_prev_start_) {
    CommandScheduler::getInstance().cancelAll();
  }
  btn_prev_start_ = btn_start;

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
  CommandScheduler::getInstance().cancelAll();
  drive.setPower(0.0f, 0.0f);
}
