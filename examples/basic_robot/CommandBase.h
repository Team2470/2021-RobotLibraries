#pragma once

#include "SubsystemBase.h"
#include "LinkedList.hpp"

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif
    
class CommandBase {

  private:
      
  private:
    LinkedList<SubsystemBase&> requirements_;

  public:

    /**
     * The initial subroutine of the command. Called once when the command is initially scheduled.
     */
    virtual void initialize() {};

    /**
     * The main body of a command. Called repeatedly while the command is scheduled.
     */
    virtual void execute() {};

    /**
     * The action to take when the command ends.  Called when either the command
     * finished normally or when it is interrupted.
     * 
     * @param interrupted whether the command was interrupted/cancelled
     */
     virtual void end(bool interrupted) {};

    /**
     * Whether the command has finished.  Once a command finishes, the scheduler
     * will call its end() method and un-schedule it.
     *
     * @return whether the command has finished.
     */
    virtual bool isFinished() { return false; };

    /**
     * Whether the command requires a given subsystem.  
     *
     * @param requirement the subsystem to inquire about
     * @return whether the subsystem is required
     */
    bool requires(SubsystemBase& requirement);

    /**
     * Add the requiement to the command.  You can add a 
     * maximum of 8 subsystems.
     */
    bool addRequirement(SubsystemBase& requirement);

    /**
     * Returns a linked list of requriements for this submodule
     */
    LinkedList<SubsystemBase&>& getRequirements();
  
};
