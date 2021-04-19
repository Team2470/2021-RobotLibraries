#pragma once

#include "CommandBase.h"

class WaitCmd : public CommandBase {

  private:

    unsigned long start_cmd_ = 0;
    unsigned long stop_ms_ = 10000;

  public:
  
    WaitCmd(int stop_ms);

    void initialize() override;

    void execute() override;

    bool isFinished() override;

    void end(bool interrupted);

};
