#include "SubsystemBase.h"
#include "string.h"

SubsystemBase::SubsystemBase() {}

SubsystemBase::SubsystemBase(char name[]) {
  strlcpy(name_, name, strlen(name_));
}

char* SubsystemBase::getName() {
  return name_;
}
