#include "BlinkLEDCmd.h"

BlinkLEDCmd::BlinkLEDCmd(LEDSubsystem& led) : led_(led) {
  addRequirement(led);
}

void BlinkLEDCmd::initialize() {
  led_.turnOn();
}

bool BlinkLEDCmd::isFinished() {
  return true;
}
