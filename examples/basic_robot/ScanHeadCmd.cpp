#include "ScanHeadCmd.h"

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#define MIN_ANGLE 0
#define MAX_ANGLE 180

ScanHeadCmd::ScanHeadCmd(HeadSubsystem& head, int sweep_ms, int left_limit, int right_limit) : 
                   head_(head), sweep_ms_(sweep_ms) {
                    
  if (left_limit < MIN_ANGLE) left_limit_ = MIN_ANGLE;
  if (right_limit > MAX_ANGLE) right_limit_ = MAX_ANGLE;
  if (left_limit > right_limit) left_limit_ = right_limit;

  addRequirement(head);
}

void ScanHeadCmd::initialize() {
  head_.setAngleDeg(left_limit_);
  sweep_start_ = millis();
  Serial.println("Head Scan Initialize!");
  
  int range = right_limit_ - left_limit_;

  // Close enough, don't need the extra float overhead
  ms_per_deg_ = sweep_ms_ / range;
  scan_forward_ = true;
}

void ScanHeadCmd::execute() {
  int ellapsed = millis() - sweep_start_;
  int deg_offset = ellapsed / ms_per_deg_;

  int new_pos = 0;

  // If we are scanning forward, add the offset and check the limit
  // otherwise subtract and do the same.
  if (scan_forward_) {
    new_pos = left_limit_ + deg_offset;
    if (new_pos > right_limit_) {
      new_pos = right_limit_;
      scan_forward_ = false;
      sweep_start_ = millis();
    }
  } else {
    new_pos = right_limit_ - deg_offset;
    if (new_pos < left_limit_) {
      new_pos = left_limit_;
      scan_forward_ = true;
      sweep_start_ = millis();
    }
  }

  head_.setAngleDeg(new_pos);
}

bool ScanHeadCmd::isFinished() {
  // Never finish
  return false;
}

void ScanHeadCmd::end(bool interupted) {
  Serial.println("Head Scan Aborted!");
  head_.setAngleDeg(90);
}
