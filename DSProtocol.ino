#include "DSProtocol.h"
#include "DSState.h"

#define MIN_UART_MESSAGE_LENGTH DS_CONTROL_LENGTH

char protocol_buffer[64];

DriverStation ds;

void setup() {
  // initialize serial communication
  Serial.begin(9600);
  while (!Serial); // wait for Leonardo enumeration, others continue immediately
  Serial.println("Ready");
}

int foo = 0;

void loop() {
  // put your main code here, to run repeatedly:

  foo++;
  if (foo % 10000 == 0) {
    Serial.println("Bar");
  }
  
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

  // User code

}
