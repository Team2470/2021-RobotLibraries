#pragma once

#include "CommandBase.h"
#include "LEDSubsystem.h"

class BlinkLEDCmd : public CommandBase {

  public:
  
    BlinkLEDCmd(LEDSubsystem& led);

    void initialize() override;

    bool isFinished() override;

  private:
    LEDSubsystem& led_;

};
