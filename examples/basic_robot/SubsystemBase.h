#pragma once

#include <stdint.h>

class SubsystemBase {
  public:
  char name_[16] = "unnamed";

  public:
  
  // User overridable functions
  SubsystemBase();
  SubsystemBase(char name[]);
  
  virtual void setup() {};
  virtual void periodic() {};

  char* getName();
};
