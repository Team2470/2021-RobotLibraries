#include "CommandScheduler.h"

// Libraries need to include Arduino.h or WProgram.h to use Serial
#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

// Singleton constructor
CommandScheduler& CommandScheduler::getInstance() {
  static CommandScheduler scheduler;
  return scheduler;
}

void CommandScheduler::setPeriod(unsigned int period_ms) {
  // TODO: Implement period setting
}

void CommandScheduler::schedule(bool interruptible, CommandBase& command) {
  // TODO: Implement adding to schedule
}

void CommandScheduler::schedule(CommandBase& command) {
  schedule(false, command);
}

void CommandScheduler::run() {
  // TODO: Implement run
}

void CommandScheduler::registerSubsystem(SubsystemBase& subsystem) {
  // TODO: Save to subsystem list
}

void CommandScheduler::setDefaultCommand(SubsystemBase& subsystem, CommandBase& defaultCommand) {
  if (!defaultCommand.requires(subsystem)) {
    // Default commands require subsystems
    Serial.println("Canot set default. Command doesn't require subsystem.");
    return;
  }
  if (defaultCommand.isFinished()) {
    Serial.println("Default commands should not end!");
    return;
  }

  // TODO: Create default command array for subsystem
}

CommandScheduler::CommandScheduler() {
//  scheduler->enabled = [this] {
//    this->Disable();
//    this->CancelAll();
//  };
//  scheduler->disabled = [this] { this->Enable(); };
}
