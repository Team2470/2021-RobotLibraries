#pragma once

#include "CommandBase.h"
#include "LinkedList.hpp"

/**
 * The scheduler responsible for running Commands.  A Command-based robot should
 * call Run() on the singleton instance in its periodic block in order to run
 * commands synchronously from the main loop.  Subsystems should be registered
 * with the scheduler using RegisterSubsystem() in order for their Periodic()
 * methods to be called and for their default commands to be scheduled.
 */
class CommandScheduler final {

  public:

  LinkedList<SubsystemBase&> subsystems_;
  LinkedList<CommandBase&> scheduled_commands_;
  
  public:
  /**
   * Returns the Scheduler instance.
   *
   * @return the instance
   */
  static CommandScheduler& getInstance();

  /**
   * Changes the period of the loop overrun watchdog. This should be kept in
   * sync with the TimedRobot period.
   */
  void setPeriod(unsigned int period);

  /**
   * Schedules a command for execution.  Does nothing if the command is already
   * scheduled. If a command's requirements are not available, it will only be
   * started if all the commands currently using those requirements have been
   * scheduled as interruptible.  If this is the case, they will be interrupted
   * and the command will be scheduled.
   *
   * @param interruptible whether this command can be interrupted
   * @param command       the command to schedule
   */
  void schedule(bool interruptible, CommandBase& command);

  /**
   * Schedules a command for execution, with interruptible defaulted to true.
   * Does nothing if the command is already scheduled.
   *
   * @param command the command to schedule
   */
  void schedule(CommandBase& command);

  /**
   * Runs a single iteration of the scheduler.  The execution occurs in the
   * following order:
   *
   * <p>Subsystem periodic methods are called.
   *
   * <p>Button bindings are polled, and new commands are scheduled from them.
   *
   * <p>Currently-scheduled commands are executed.
   *
   * <p>End conditions are checked on currently-scheduled commands, and commands
   * that are finished have their end methods called and are removed.
   *
   * <p>Any subsystems not being used as requirements have their default methods
   * started.
   */
  void run();

  /**
   * Registers subsystems with the scheduler.  This must be called for the
   * subsystem's periodic block to run when the scheduler is run, and for the
   * subsystem's default command to be scheduled.  It is recommended to call
   * this from the constructor of your subsystem implementations.
   *
   * @param subsystem the subsystem to register
   */
  void registerSubsystem(SubsystemBase& subsystem);

  /**
   * Sets the default command for a subsystem.  Registers that subsystem if it
   * is not already registered.  Default commands will run whenever there is no
   * other command currently scheduled that requires the subsystem.  Default
   * commands should be written to never end (i.e. their IsFinished() method
   * should return false), as they would simply be re-scheduled if they do.
   * Default commands must also require their subsystem.
   *
   * @param subsystem      the subsystem whose default command will be set
   * @param defaultCommand the default command to associate with the subsystem
   */
  void setDefaultCommand(SubsystemBase& subsystem, CommandBase& defaultCommand); 


  private:
  // Constructor; private as this is a singleton
  CommandScheduler();
  
};
  
  
