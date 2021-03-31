#pragma once

#include "CommandBase.h"

#define PAR_MAX_COMMANDS 16

/**
 * A CommandGroup that runs a set of commands in parallel, ending when the last
 * command ends.
 *
 * <p>As a rule, CommandGroups require the union of the requirements of their
 * component commands.
 */
class ParallelCommandGroup : public CommandBase {

 public:

   /*
    * Tracks if a parallel command has completed
    */
  struct ParallelCommand {
    CommandBase* cmd{0};
    bool is_running{false};
  };

 
 public:
   /**
   * Creates a new ParallelCommandGroup.  The given commands will be executed
   * simultaneously. The command group will finish when the last command
   * finishes.  If the CommandGroup is interrupted, only the commands that are
   * still running will be interrupted.
   *
   * @param commands the commands to include in this group.
   */
  ParallelCommandGroup(int cnt, const CommandBase *commands[]);

  ParallelCommandGroup();

  ParallelCommandGroup(ParallelCommandGroup&& other) = default;

  // No copy constructors for command groups
  ParallelCommandGroup(const ParallelCommandGroup&) = delete;

  // Prevent template expansion from emulating copy ctor
  ParallelCommandGroup(ParallelCommandGroup&) = delete;

  void addCommands(int cnt, const CommandBase *commands[]);

  void initialize() override;

  void execute() override;

  void end(bool interrupted) override;

  bool isFinished() override;

  //bool runsWhenDisabled() const override;

 private:

  ParallelCommand commands_[PAR_MAX_COMMANDS];
  bool is_running_ = false;
  int command_count_{0};
};
