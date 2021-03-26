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
  // TODO: Handle interruptible
  Serial.println("Add cmd");
  scheduled_commands_.Append(command);
  command.initialize();

}

void CommandScheduler::schedule(CommandBase& command) {
  schedule(false, command);
}

void CommandScheduler::run() {
  
  // Run any of the subsystem execute commands
  if(subsystems_.moveToStart()) {
    do {
      subsystems_.getCurrent().periodic();
    } while (subsystems_.next());
  }

  // Run any of the subsystem execute commands
  if(scheduled_commands_.moveToStart()) {
    do {

      auto& command = scheduled_commands_.getCurrent();
      
      // Run execute.  We don't have other actions to check
      command.execute();

      if (command.isFinished()) {
        command.end(false);
        
        // TODO: Remove from list of active requirements (also, track requirements)

        // Delete the current item, then continue to skip calling next
        scheduled_commands_.DeleteCurrent();
        
        // We modified the list, so use continue to read the next or break out
        if (scheduled_commands_.getLength() == 0) {
          break;
        } else {
          continue;
        }
      }

    } while (scheduled_commands_.next());
  }
  
}

void CommandScheduler::registerSubsystem(SubsystemBase& subsystem) {
  subsystems_.Append(subsystem);
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
