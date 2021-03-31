#include "WaitCmd.h"

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

WaitCmd::WaitCmd(int stop_ms) : stop_ms_(stop_ms) { }

void WaitCmd::initialize() {
  start_cmd_ = millis();
  Serial.println("Wait Initialize!");
}

void WaitCmd::execute() {
  // Just you wait, he's a cookin up something
}

bool WaitCmd::isFinished() {
  return ((millis() - start_cmd_) > stop_ms_);
}

void WaitCmd::end(bool interupted) {
  Serial.print("Wait Done: int? ");
  Serial.println(interupted);
}
