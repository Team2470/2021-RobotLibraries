#pragma once

#include <stdint.h>
#include <string.h>


// Libraries need to include Arduino.h or WProgram.h to use Serial
#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif


class SubsystemBase {
  public:
  char name_[16] = "unnamed";

  public:
  
  // User overridable functions
  SubsystemBase();
  SubsystemBase(char name[]);

  /**
   * For now, set equality equal to the same name
   */
  bool operator==(const SubsystemBase& a) { return (this == &a); }
  
  virtual void periodic() {};

  char* getName();
};
