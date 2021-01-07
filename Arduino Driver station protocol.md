# Arduino Driver station protocol
There will be 2 modes of operation:
1. basic mode
    - Single character commands
2. Advanced mode

## Advanced mode
Packet structure
```
    - Packet type (1 byte)
    - Packet length (1 byte)
    - Packet data (N Bytes)
```

Do we want to encode the data as a 

### Control packet 0x10 (1 byte)
Control (DS to Robot)
    - estop (1 bit) (our code can estop all motors)
    - FMS Connected (1 bit) (? Give to switches)
    - Enabled (1 bit)
    - Mode (2 bits)
    - reserved (4 bits)

    - Switches (1 byte, 8 bits)
        - Generic toggle switches for uses

### Joystick packet 0x74 (Joystick 1) 0x12 (Joystick 2) (3 byte)
Joystick (DS to Robot) 
    - 6 Axis (1 byte)
        1. Left X
        2. Left Y
        3. Right X
        4. Right Y
        5. Trigger X
        6. Trigger Y
    - 16 Buttons (2 bytes) (1 bit per button)
         1. A
         2. B
         3. X
         4. Y
         5. Start
         6. Back
         7. Left Trigger
         8. Right Trigger
        10. Left Button
        11. Right Button
        12. Up 
        13. Down
        14. Right
        15. Left

### Status Packet
Status (from Robot to DS)
    - reserved (4 bits)
    - estopped (1 bit)
    - enabled (1 bit)
    - mode (2 bits) // Make this 1 bit? as we only need on/off

    - Protocol Version (1 byte)

Log message: (Robot to DS)
    - Start with 0x02 
    - Print text line
    - 0x00 (end of line)

# Code structure
## DriverStation
```
enum DSMode {
    Auto    = 1
    TeleOp  = 2
}

class DriverStation {
    estopped bool
    enabled bool
    mode DSMode

    gamepad1 Gamepad
}

enum GamepadButton {
    A               = 0x0001,
    B               = 0x0002,
    X               = 0x0004,
    Y               = 0x0008,
    Start           = 0x0010,
    Back            = 0x0020,
    LeftTrigger     = 0x0040,
    RightTrigger    = 0x0080,
    LeftButton      = 0x0100,
    RightButton     = 0x0200,
    DPadUp          = 0x0400,
    DPadDown        = 0x0800,
    DPadRight       = 0x1000,
    DPadLeft        = 0x2000,
    Reserved1       = 0x4000,
    Resverved2      = 0x8000,
}


enum GamepadAxis {
    LeftX = 0,
    LeftY = 1,
    RightX = 2,
    RightY = 3,
    TriggerX = 4,
    TriggerY = 5
}

class Gamepad {
    axis int8_t
    buttonState uint16_t
}

bool Gamepad::getButton(button GamepadButton) {
    return button & button
}

bool Gamepad::getAxis(GamepadAxis axisID) {
    return this.axis[axisID]
}

DriverStation driverStation;
```

## Setup
```
void setup() {
    // Setup Bluetooth serial
    
    // Setup DriverStation control protocol struct
    driverStation =  ...
}
```

https://github.com/nowireless/ros_nav6/blob/master/arduino/nav6/nav6.ino#L605-L611
```
last_mode = 

void loop() {
    // Read from bluebooth serial 
    header

    // Update DS struct
    driverStation.estopped = 


    // Report current mode

    mode = .....
    entering_auto = ....
    entering_teleop = ....
}
```