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
  start_cmd_ = millis();
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
  // Stop blinking after 10 seconds
  return (millis() - start_cmd_ > 10000);
}

void BlinkLEDCmd::end(bool interupted) {
  Serial.println("LED Done");
  led_.turnOff();
}
