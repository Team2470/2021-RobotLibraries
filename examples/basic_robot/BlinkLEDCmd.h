#pragma once

#include "CommandBase.h"
#include "LEDSubsystem.h"

class BlinkLEDCmd : public CommandBase {

  private:
    LEDSubsystem& led_;
    
    unsigned long start_cmd_ = 0;
    unsigned long last_blink_ = 0;

    unsigned long rate_ms_ = 1000;
    unsigned long stop_ms_ = 10000;

  public:
  
    BlinkLEDCmd(LEDSubsystem& led, int rate_ms, int stop_ms);

    void initialize() override;

    void execute() override;

    bool isFinished() override;

    void end(bool interrupted);

};
