#pragma once

#include <stdint.h>

class SubsystemBase {
  public:
  char name_[16] = "unnamed";

  public:
  
  // User overridable functions
  SubsystemBase();
  SubsystemBase(char name[]);

  /**
   * For now, set equality equal to the same object (address space)
   */
  bool operator==(const SubsystemBase& a) { return this == &a; }
  
  virtual void setup() {};
  virtual void periodic() {};

  char* getName();
};
