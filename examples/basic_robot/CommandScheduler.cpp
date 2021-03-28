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
  
  const auto& requirements = command.getRequirements();
  
  // Check against current requirements.  If nothing else required the modules,
  // then go ahead and schedule it.  If something else is using it, but interruptible,
  // then cancel the previous commands and schedule the current.
  LinkedList<Command&> intersection;
  bool is_disjoint = true;
  bool all_interruptible = true;
  
  if(requirements.moveToStart()) {
    do {
      // This is a fairly slow implementation, but should be good enough if the number
      // of commands is low.
      if(requirements_.Search(requirements.getCurrent())) {
        is_disjoint = false;

        // We have a conflict, so find the command we conflict with
        if (scheduled_commands_.moveToStart()) {
          do {
            if (scheduled_commands_.getCurrent().command.requires(requirements.getCurrent())) {
              intersection.Append(scheduled_commands_.getCurrent());
              all_interruptible &= scheduled_commands_.getCurrent().interruptible;
            }
          } while (scheduled_commands_.next());
        }
      }
    } while (requirements.next());
  }

  // If we are allowed to schedule it, go ahead
  if (is_disjoint || all_interruptible) {
    if (all_interruptible) {
      if (intersection.moveToStart()) {
        do {
          cancel(intersection.getCurrent());
        } while (intersection.next());
      }
    }

    // We either cancelled or didn't have another module using it, 
    // so go ahead and run.
    command.initialize();
    struct Command new_cmd(interruptible, command);
    scheduled_commands_.Append(new_cmd);

    if(requirements.moveToStart()) {
        do {
          requirements_.Append(requirements.getCurrent());
        } while (requirements.next());
    }
  }
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

      auto& command = scheduled_commands_.getCurrent().command;
      auto interruptible = scheduled_commands_.getCurrent().interruptible;
      
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

void CommandScheduler::cancel(Command& command) {

  // Check if the command is in the schedule
  if (!scheduled_commands_.Search(command)) {
    return;
  }

  // Finish the command
  command.command.end(true);

  // Find the command in the schedule and remove it
  scheduled_commands_.Delete(command);

  // Remove it's requirements from the list
  const auto& requirements = command.command.getRequirements();
  if (requirements.moveToStart()) {
    do {
        requirements_.Delete(requirements.getCurrent());
    } while (requirements.next());
  }
}

CommandScheduler::CommandScheduler() {
//  scheduler->enabled = [this] {
//    this->Disable();
//    this->CancelAll();
//  };
//  scheduler->disabled = [this] { this->Enable(); };
}
