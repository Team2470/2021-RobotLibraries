#include "BlinkLEDCmd.h"

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif


BlinkLEDCmd::BlinkLEDCmd(LEDSubsystem& led, int rate_ms, int stop_ms) : 
  led_(led), rate_ms_(rate_ms), stop_ms_(stop_ms) {
  addRequirement(led);
}

void BlinkLEDCmd::initialize() {
  led_.turnOn();
  last_blink_ = millis();
  start_cmd_ = millis();
}

void BlinkLEDCmd::execute() {
  if (millis() - last_blink_ > rate_ms_) {
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
  return (millis() - start_cmd_ > stop_ms_);
}

void BlinkLEDCmd::end(bool interupted) {
  Serial.println("LED Done");
  led_.turnOff();
}
