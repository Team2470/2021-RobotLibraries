#include "ParallelCommandGroup.h"

ParallelCommandGroup::ParallelCommandGroup(int cnt, const CommandBase *commands[]) {
  addCommands(cnt, commands);
}

void ParallelCommandGroup::initialize() {
  for (int i=0; i < command_count_; i++) {
    commands_[i].cmd->initialize();
    commands_[i].is_running = true;
  }

  is_running_ = true;
}

void ParallelCommandGroup::execute() {
  if (command_count_ == 0) {
    return;
  }

  for (int i=0; i < command_count_; i++) {
    if (!commands_[i].is_running) {
      continue;
    }
    
    commands_[i].cmd->execute();
    if (commands_[i].cmd->isFinished()) {
      commands_[i].cmd->end(false);
      commands_[i].is_running = false;
    }
  }

}

void ParallelCommandGroup::end(bool interrupted) {
  if (interrupted) {
    for (int i=0; i < command_count_; i++) {
      if (commands_[i].is_running) {
        commands_[i].cmd->end(true);
      }
    }
  }
  is_running_ = false;
}

bool ParallelCommandGroup::isFinished() {
  for (int i=0; i < command_count_; i++) {
    if (commands_[i].is_running) {
      return false;
    }
  }
  return true;
}

void ParallelCommandGroup::addCommands(int cnt, const CommandBase *commands[]) {
  //if (!RequireUngrouped(commands)) {
  //  return;
  //}

  if (is_running_) {
    Serial.println("Cannot add commands while running!");
  }

  for (int i=0; i < cnt; i++) {
    //command->SetGrouped(true);
    //m_runWhenDisabled &= command->RunsWhenDisabled();

    addRequirements(commands[i]->getRequirements());

    commands_[command_count_].cmd = commands[i];
    commands_[command_count_].is_running = false;
    
    command_count_++;
    if (command_count_ > PAR_MAX_COMMANDS) {
      Serial.println("Max commands Seq Commands, skipping adding of further commands.");
      break;
    }
  }
}
