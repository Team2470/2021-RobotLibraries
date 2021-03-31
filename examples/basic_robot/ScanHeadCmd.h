#pragma once

#include "CommandBase.h"
#include "HeadSubsystem.h"

class ScanHeadCmd : public CommandBase {

  private:
    HeadSubsystem& head_;
    unsigned long sweep_start_ = 0;
    unsigned long sweep_ms_ = 2000;
    
    int left_limit_ = 0;
    int right_limit_ = 180;
    
    int ms_per_deg_ = 0;
    bool scan_forward_ = true;

  public:
  
    ScanHeadCmd(HeadSubsystem& head, int sweep_ms, int left_limit, int right_limit);

    void initialize() override;

    void execute() override;

    bool isFinished() override;

    void end(bool interrupted);

};
