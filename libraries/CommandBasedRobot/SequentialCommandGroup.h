#pragma once

#include "CommandBase.h"

#define SEQ_MAX_COMMANDS 16

/**
 * A CommandGroups that runs a list of commands in sequence.
 *
 * <p>As a rule, CommandGroups require the union of the requirements of their
 * component commands.
 */
class SequentialCommandGroup : public CommandBase {
  
 public:
  /**
   * Creates a new SequentialCommandGroup.  The given commands will be run
   * sequentially, with the CommandGroup finishing when the last command
   * finishes.
   *
   * @param commands the commands to include in this group.
   */
  SequentialCommandGroup(int cnt, const CommandBase *commands[]);

  SequentialCommandGroup();

  SequentialCommandGroup(SequentialCommandGroup&& other) = default;

  // No copy constructors for command groups
  SequentialCommandGroup(const SequentialCommandGroup&) = delete;

  // Prevent template expansion from emulating copy ctor
  SequentialCommandGroup(SequentialCommandGroup&) = delete;

  void addCommands(int cnt, const CommandBase *commands[]);

  void initialize() override;

  void execute() override;

  void end(bool interrupted) override;

  bool isFinished() override;

  //bool runsWhenDisabled() const override;

 private:

  CommandBase *commands_[SEQ_MAX_COMMANDS]{0};
  int invalid_index_{-1};
  int current_command_index_{invalid_index_};
  int command_count_{0};
};
