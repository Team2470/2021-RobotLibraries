#pragma once

#include "SubsystemBase.h"

class LEDSubsystem : public SubsystemBase {

  public:
    LEDSubsystem();


    void setup() override;

    void periodic() override;

    // Add Subsystem methods here

    /**
     * Turns on the LED
     */
    void turnOn();

    /**
     * Turns off the LED
     */
    void turnOff();

    /**
     * Returns true if the led is on
     */
    bool isOn();

    private:

    // Necessary subsystem classes go here

};
