#include "BlinkLEDCmd.h"

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif


BlinkLEDCmd::BlinkLEDCmd(LEDSubsystem& led) : led_(led) {
  addRequirement(led);
}

void BlinkLEDCmd::initialize() {
  led_.turnOn();
  last_blink_ = millis();
}

void BlinkLEDCmd::execute() {
  if (millis() - last_blink_ > 1000) {
    if (led_.isOn()) {
      led_.turnOff();
    } else {
      led_.turnOn();
    }
    last_blink_ = millis();
  }
}

bool BlinkLEDCmd::isFinished() {
  return false;
}
