#include "DSProtocol.h"
#include <stdio.h>

// Libraries need to include Arduino.h or WProgram.h to use Serial
#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

/*************************************************************
 ********************* Local Defines *************************
 *************************************************************/

#define SOF1 0x24
#define SOF2 0x70
#define HEADER_LENGTH   2
#define CHECKSUM_LENGTH 1




//
// DS -> Robot Packets
//

// Control Packet 
// [0xAA][0x55]
// [CONTROL][BTN1][BTN2][AXIS0][AXIS1][AXIS2][AXIS3][AXIS4][AXIS5]
// [CKSUM]
#define DS_CONTROL_LENGTH 12
#define DS_PAYLOAD_LENGTH DS_CONTROL_LENGTH - HEADER_LENGTH - CHECKSUM_LENGTH

#define HEADER1_INDEX 0
#define HEADER2_INDEX 1
#define DS_CONTROL_CONTROL_INDEX         2 // [control byte]
#define DS_CONTROL_BUTTON_BYTE1_INDEX    3
#define DS_CONTROL_BUTTON_BYTE2_INDEX    4
#define DS_CONTROL_LEFT_X_AXIS_INDEX     5
#define DS_CONTROL_LEFT_Y_AXIS_INDEX     6
#define DS_CONTROL_RIGHT_X_AXIS_INDEX    7
#define DS_CONTROL_RIGHT_Y_AXIS_INDEX    8
#define DS_CONTROL_TRIGGER_X_AXIS_INDEX  9
#define DS_CONTROL_TRIGGER_Y_AXIS_INDEX  10
#define CHECKSUM_INDEX 11

// Whole 
#define MSDG

//
// Robot -> DS Packets
//

// None yet

// Log Message Packet - Any line that does not start with !S

#define MAX_PKT_LEN DS_CONTROL_LENGTH + HEADER_LENGTH + CHECKSUM_LENGTH;


/*************************************************************
 ******************** Public Functions ***********************
 *************************************************************/

bool DSProtocol::process() {
	// If we find a new packet, inform the caller
	bool new_packets = false;

	// Read all available characters and feed it into the parser one at a time
	while ( Serial.available() > 0 ) {
		char c = Serial.read();

		switch(state_)
		{
			default:
			case DECODE_RESET:
			{
				state_++;
				// fall through
			}
			case DECODE_START:
			{
				clearData();
				state_++;
				// fall through
			}
			case DECODE_SOF1:
			{
				pushData(c);
				state_++;
				break;
			}
			case DECODE_SOF2:
			{
				pushData(c);
				if(buffer_[HEADER1_INDEX] == SOF1 
				   && buffer_[HEADER2_INDEX] == SOF2) 
				{
					// Match, parse the next state
					state_++;
				}
				else
				{
					// Roll buffers back one byte so that we can look
					// for the start of frame again
					popData();
				}
				break;
			}
			case DECODE_PAY:
			{
				pushData(c);
				if (buffer_pos_ > (DS_PAYLOAD_LENGTH + HEADER_LENGTH)) 
				{
					state_++;
				}
				break;
			}
			case DECODE_CRC:
			{
				pushData(c);
				new_packets |= decodeDSControlPacket(buffer_, buffer_pos_ - 1);
				state_ = DECODE_START;
			}
		}
	}

	return new_packets;
}

DriverStation DSProtocol::getStatus() {
	return ds;
}


/*************************************************************
 ******************* Private Functions ***********************
 *************************************************************/
  
bool DSProtocol::decodeDSControlPacket(uint8_t buffer[], int buffer_len) {
	if (buffer_len < DS_CONTROL_LENGTH) return false;
	
	if (buffer[0] == SOF1  && buffer[1] == SOF2) {
		if(!verifyChecksum(buffer, buffer_len, CHECKSUM_INDEX)) {
			//Serial.println("BAD CHECKSUM");
			return false;
		}

		// Data
		uint8_t controlWord = &buffer[DS_CONTROL_CONTROL_INDEX];

		ds.mode      = controlWord & 0x0f;         // Bits 0->4
		ds.enabled   = (controlWord & (1<< 4)) > 0;  // Bit 5
		ds.estopped  = (controlWord & (1<< 5)) > 0;  // Bit 6

		// Data
		ds.gamepad.buttonState  = buffer[DS_CONTROL_BUTTON_BYTE1_INDEX];
		ds.gamepad.buttonState += buffer[DS_CONTROL_BUTTON_BYTE2_INDEX] << 8;
		ds.gamepad.axis[0] = buffer[DS_CONTROL_LEFT_X_AXIS_INDEX];
		ds.gamepad.axis[1] = buffer[DS_CONTROL_LEFT_Y_AXIS_INDEX];
		ds.gamepad.axis[2] = buffer[DS_CONTROL_RIGHT_X_AXIS_INDEX];
		ds.gamepad.axis[3] = buffer[DS_CONTROL_RIGHT_Y_AXIS_INDEX];
		ds.gamepad.axis[4] = buffer[DS_CONTROL_TRIGGER_X_AXIS_INDEX];
		ds.gamepad.axis[5] = buffer[DS_CONTROL_TRIGGER_Y_AXIS_INDEX];

		return true;
	}	

	return false;
}

bool DSProtocol::verifyChecksum(uint8_t buffer[], int buffer_len, int content_length ) {
	// Calculate Checksum
	unsigned char checksum = 0;
	for ( int i = 0; i < content_length; i++ )
	{
		checksum += buffer[i];
	}

	// Decode Checksum
	unsigned char decoded_checksum = buffer[content_length];

	// Serial.print("Expected: ");
	// Serial.print(decoded_checksum);
	// Serial.print(" Got: ");
	// Serial.println(checksum);

	return ( checksum == decoded_checksum );
}

void DSProtocol::pushData( char data ) {
	if (buffer_pos_ < sizeof(buffer_)) {
		buffer_[buffer_pos_] = data;
		buffer_pos_++;
	}
}

void DSProtocol::popData() {
	for (uint8_t i = 1; i < buffer_pos_; i++) {
		buffer_[i-1] = buffer_[i];
	}
	buffer_pos_--;
}

void DSProtocol::clearData() {
	buffer_pos_ = 0;
}
