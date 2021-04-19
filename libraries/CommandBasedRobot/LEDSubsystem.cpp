#include "LEDSubsystem.h"

// Libraries need to include Arduino.h or WProgram.h to use Serial
#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif


// Assign a unique name
LEDSubsystem::LEDSubsystem()
  : SubsystemBase("LED") {}

void LEDSubsystem::setup(int led_pin) {
    led_pin_ = led_pin;
    pinMode(led_pin_, OUTPUT);
    digitalWrite(led_pin, LOW);
}

void LEDSubsystem::periodic() {
    // Add any periodic tasks you would need here
}

void LEDSubsystem::turnOn() {
    digitalWrite(led_pin_, HIGH);
}

void LEDSubsystem::turnOff() {
    digitalWrite(led_pin_, LOW);
}

bool LEDSubsystem::isOn() {
    return digitalRead(led_pin_);
}
