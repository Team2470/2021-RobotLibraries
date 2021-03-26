#pragma once

#include "SubsystemBase.h"

class LEDSubsystem : public SubsystemBase {

  public:
    LEDSubsystem();


    void setup() override;


    // Add Subsystem methods here

    /**
     * Turns on the LED
     */
    void turnOn();

    /**
     * Turns off the LED
     */
    void turnOff();

    private:

    // Necessary subsystem classes go here

};
