#include "HeadSubsystem.h"

// Libraries need to include Arduino.h or WProgram.h to use Serial
#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif


// Assign a unique name
HeadSubsystem::HeadSubsystem()
  : SubsystemBase("Head") {}

void HeadSubsystem::setup(int servo_pin, int us_tx_pin, int us_rx_pin) {
  neck_.attach(servo_pin);
  us_tx_pin_ = us_tx_pin;
  us_rx_pin_ = us_rx_pin;
}

void HeadSubsystem::periodic() {
  // Add any periodic tasks you would need here
}

/**
 * Moves the servo to the given postion
 */
void HeadSubsystem::setAngleDeg(int deg) {
  if (deg < 0) deg = 0;
  if (deg > 180) deg = 180;
  neck_.write(deg);
}

/**
 * Gets the angle of the head
 */
int HeadSubsystem::getAngleDeg() {
  return neck_.read();
}

/**
 * Gets the distance to a target
 */
int HeadSubsystem::getDistance();
