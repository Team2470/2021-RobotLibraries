#include "CommandBase.h"

bool CommandBase::requires(SubsystemBase& requirement) {
  bool requires = false;

  // Looks for an exact instance match in address space
  // This should verify the exact same object is used
  if(requirements_.moveToStart()) {
    do {
      if (requirements_.getCurrent() == requirement) {
        return true;
      }
    } while (requirements_.next());
  }

  return false;
}

bool CommandBase::addRequirement(SubsystemBase& requirement) {

  if (!requires(requirement)) {
    requirements_.Append(requirement);
    return true;
  }

  return false;
}

bool CommandBase::addRequirements(LinkedList<SubsystemBase&> requires) {
  if(requires.moveToStart()) {
    do {
      addRequirement(requires.getCurrent());
    } while (requires.next());
  }
}

LinkedList<SubsystemBase&>& CommandBase::getRequirements() {
  return requirements_;
}
