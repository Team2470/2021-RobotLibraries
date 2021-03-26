#include "CommandBase.h"

bool CommandBase::requires(SubsystemBase& requirement) {
  bool requires = false;

  // Looks for an exact instance match in address space
  // This should verify the exact same object is used
  for (int i=0; i<subsystem_count_; i++) {
    requires |= (requirements_[i] == &requirement);
  }

  return requires;
}

bool CommandBase::addRequirement(const SubsystemBase& requirement) {
  if (subsystem_count_ >= 8) {
    return false;
  }

  requirements_[subsystem_count_] = &requirement;
  subsystem_count_++;
}
