#include "SequentialCommandGroup.h"

SequentialCommandGroup::SequentialCommandGroup(int cnt, const CommandBase *commands[]) {
  addCommands(cnt, commands);
}

void SequentialCommandGroup::initialize() {
  current_command_index_ = 0;

  if (command_count_ != 0) {
    commands_[0]->initialize();
  }
}

void SequentialCommandGroup::execute() {
  if (command_count_ == 0) {
    return;
  }

  auto& current_command = commands_[current_command_index_];

  current_command->execute();
  
  if (current_command->isFinished()) {
    current_command->end(false);
    current_command_index_++;
    if (current_command_index_ < command_count_) {
      commands_[current_command_index_]->initialize();
    }
  }
}

void SequentialCommandGroup::end(bool interrupted) {
  if (interrupted && (command_count_ != 0) &&
      (current_command_index_ != invalid_index_) &&
      (current_command_index_ < command_count_)) {
    commands_[current_command_index_]->end(interrupted);
  }
  current_command_index_ = invalid_index_;
}

bool SequentialCommandGroup::isFinished() {
  return current_command_index_ == command_count_;
}

void SequentialCommandGroup::addCommands(int cnt, const CommandBase *commands[]) {
  //if (!RequireUngrouped(commands)) {
  //  return;
  //}

  if (current_command_index_ != invalid_index_) {
    Serial.println("Cannot add commands while running!");
  }

  for (int i=0; i < cnt; i++) {
    //command->SetGrouped(true);
    //m_runWhenDisabled &= command->RunsWhenDisabled();

    addRequirements(commands[i]->getRequirements());

    commands_[command_count_] = commands[i];
    command_count_++;
    if (command_count_ > SEQ_MAX_COMMANDS) {
      Serial.println("Max commands Seq Commands, skipping adding of further commands.");
      break;
    }
  }
}
