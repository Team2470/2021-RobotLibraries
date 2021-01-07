#include "DSProtocol.h"

char protocol_buffer[64];

void setup() {
  // initialize serial communication
  Serial.begin(57600);
  while (!Serial); // wait for Leonardo enumeration, others continue immediately
  
  // put your setup code here, to run once:
  int num_bytes = DSProtocol::encodeRobotStatus(protocol_buffer,
                                                false,  // EStopped
                                                false,  // enabled
                                                0,      // mode
                                                1      // protocol version
  );
  Serial.write((unsigned char *)protocol_buffer, num_bytes);

  num_bytes = DSProtocol::encodeRobotStatus(protocol_buffer,
                                                true,  // EStopped
                                                false,  // enabled
                                                0,      // mode
                                                1      // protocol version
  );
  Serial.write((unsigned char *)protocol_buffer, num_bytes);


  num_bytes = DSProtocol::encodeRobotStatus(protocol_buffer,
                                                false,  // EStopped
                                                true,  // enabled
                                                0,      // mode
                                                1      // protocol version
  );
  Serial.write((unsigned char *)protocol_buffer, num_bytes);


  num_bytes = DSProtocol::encodeRobotStatus(protocol_buffer,
                                                false,  // EStopped
                                                false,  // enabled
                                                2,      // mode
                                                1      // protocol version
  );
  Serial.write((unsigned char *)protocol_buffer, num_bytes);
}

void loop() {
  // put your main code here, to run repeatedly:

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
      break;
    }
  }

  // If sufficient bytes have been received, process the data and
  // if a valid message is received, handle it.
  if ( found_start_of_message && ( Serial.available() >= STREAM_CMD_MESSAGE_LENGTH ) ) {
    int bytes_read = 0;
    while ( Serial.available() ) {
      if ( bytes_read >= sizeof(protocol_buffer) ) {
        break;
      }
      protocol_buffer[bytes_read++] = Serial.read();
      ////// https://github.com/nowireless/ros_nav6/blob/master/arduino/nav6/nav6.ino#L604
    }

  }
}
