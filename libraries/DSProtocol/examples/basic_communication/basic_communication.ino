#include "DSProtocol.h"
#include "DSState.h"

//
// Driver station
//
DriverStation ds;
void driverstation_process();

//
// Hardware
//
#define ENA 5   // Left Motor Speed
#define ENB 6   // Right Motor Speed
#define IN1 7   // Left Motor - Forward
#define IN2 8   // Left Motor - Reverse
#define IN3 9   // Right Motor - Forward
#define IN4 11  // Right Motor - Reverse

void setup() {
  //
  // Driver station initialization
  //
  Serial.begin(57600);
  while (!Serial); // wait for Leonardo enumeration, others continue immediately
  Serial.println("Ready");

  //
  // Hardware initailization
  //
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);
}

void loop() {
  driverstation_process();

  // User code
  int left  = -ds.gamepad1.axis[1]; // Invert as the Y axis is inverted
  int right = -ds.gamepad1.axis[3]; // Invert as the Y axis is inverted

  // TODO Figure out arcade drive later.....

  // Set the direection for the left motor
  // TODO add a dead band
  uint8_t leftOutput = 0;
  if (left > 0) {
    // Forward
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);  
    leftOutput = map(left, 0, 128, 0, 255);
  } else {
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,HIGH);      
    leftOutput = map(left, -127, 0, 255, 0);
  }
  Serial.print("Left Out: ");
  Serial.println(leftOutput);
  analogWrite(ENA, leftOutput);

  // Set the direection for the right motor
  // TODO add a dead band
  uint8_t rightOutput = 0;
  if (right > 0) {
    // Forward
    digitalWrite(IN3,LOW);  
    digitalWrite(IN4,HIGH);
    rightOutput = map(right, 0, 128, 0, 255);
  } else {
    digitalWrite(IN3,HIGH);  
    digitalWrite(IN4,LOW);    
    rightOutput = map(right, -127, 0, 255, 0);
  }
  Serial.print("Right Out: ");
  Serial.println(rightOutput);
  analogWrite(ENB, rightOutput);  
}

//
// Motor Helper functions
//


//
// Below is the logic that communicates with the driver station
// TODO It should move it is own file, but I want to keep DSProtcol/DSState platform neutral so the unit tests can run
//

char protocol_buffer[64];

void driverstation_process() {
 // If any serial bytes are received, scan to see if a start
  // of message has been received.  Remove any bytes that precede
  // the start of a message.
  bool found_start_of_message = false;
  while ( Serial.available() > 0 ) {
    char rcv_byte = Serial.peek();
    
    if ( rcv_byte != PACKET_START_CHAR ) {
      Serial.read();
    }
    else {
      delay(2);
      found_start_of_message = true;
      Serial.println("found_start_mesesage");
      break;
    }
  }

  //
  // Determine which packet was received
  //

  // If sufficient bytes have been received, process the data and
  // if a valid message is received, handle it.
  if ( found_start_of_message && ( Serial.available() >= MIN_UART_MESSAGE_LENGTH ) ) {
    int bytes_read = 0;
    while ( Serial.available() ) {
      if ( bytes_read >= sizeof(protocol_buffer) ) {
        break;
      }
      protocol_buffer[bytes_read++] = Serial.read();
    }

    int i = 0;
    // Scan the buffer looking for valid packets
    while (i < bytes_read) {
      int bytes_remaining = bytes_read - i;
      char stream_type;
      int packet_length = 0;
      if (packet_length = DSProtocol::decodeDSControlPacket(&protocol_buffer[i], bytes_remaining, ds.estopped, ds.enabled, ds.mode, ds.switchState)) {
        // Received control packet
        Serial.println("Received DS Control Packet");
      } else if (packet_length = DSProtocol::decodeJoystick1Packet(&protocol_buffer[i], bytes_remaining, ds.gamepad1.buttonState, ds.gamepad1.axis)) {
        // Recieved joystick 1 packet
        Serial.println("Received Joystick 1 Packet");
      } else if (packet_length = DSProtocol::decodeJoystick2Packet(&protocol_buffer[i], bytes_remaining, ds.gamepad2.buttonState, ds.gamepad2.axis)) {
        // Recieved joystick 2 packet
        Serial.println("Received Joystick 2 Packet");        
      }
      
      if (packet_length > 0) {
          i += packet_length;
      } else {
          i++;
      }
    }
  }
}
