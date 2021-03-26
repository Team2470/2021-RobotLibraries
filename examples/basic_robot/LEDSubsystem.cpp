#include "LEDSubsystem.h"
#include "Constants.h"

// Libraries need to include Arduino.h or WProgram.h to use Serial
#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif


// Assign a unique name
LEDSubsystem::LEDSubsystem()
  : SubsystemBase("LED") {}

void LEDSubsystem::setup() {
  pinMode(DO_LED, OUTPUT);
}

void LEDSubsystem::periodic() {
  // Add any periodic tasks you would need here
}

void LEDSubsystem::turnOn() {
  digitalWrite(DO_LED, HIGH);
}

void LEDSubsystem::turnOff() {
  digitalWrite(DO_LED, LOW);
}

bool LEDSubsystem::isOn() {
  return digitalRead(DO_LED);
}
