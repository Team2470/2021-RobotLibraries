#pragma once

#include <Servo.h>
#include "SubsystemBase.h"

class HeadSubsystem : public SubsystemBase {

  public:
    HeadSubsystem();

    void setup(int servo_pin, int us_tx_pin, int us_rx_pin);

    void periodic() override;

    // Add Subsystem methods here

    /**
     * Moves the servo to the given postion
     */
    void setAngleDeg(int deg);

    /**
     * Gets the angle of the head
     */
    int getAngleDeg();

    /**
     * Gets the distance to a target
     */
    int getDistance();

    private:

    // Necessary subsystem classes go here
    Servo neck_;
    int us_tx_pin_;
    int us_rx_pin_;

};
