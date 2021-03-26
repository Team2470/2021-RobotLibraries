#pragma once

#include "CommandBase.h"
#include "LEDSubsystem.h"

class BlinkLEDCmd : public CommandBase {

  public:

    unsigned long start_cmd_ = 0;
    unsigned long last_blink_ = 0;

  public:
  
    BlinkLEDCmd(LEDSubsystem& led);

    void initialize() override;

    void execute() override;

    bool isFinished() override;

    void end(bool interrupted);

  private:
    LEDSubsystem& led_;

};
