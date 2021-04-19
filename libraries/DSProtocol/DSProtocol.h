#ifndef _DS_PROTOCOL_H_
#define _DS_PROTOCOL_H_

#include "DSState.h"
#include <stdint.h>

class DSProtocol
{

/*************************************************************
 ******************* Private Variables ***********************
 *************************************************************/
private:

  /* Holds the current driver station status */
  DriverStation ds;

 /* Holds our currently received characters */
  char buffer[128];

  /* The number of valid bytes in the buffer (should be less than the length) */
  int buffer_start = 0;

/*************************************************************
 ******************* Public Functions ***********************
 *************************************************************/
public:

 /**
  * Processes the input from the serial port and indicates
  * if a new packet was read.
  *
  * @return True if the driverstation packet was updated
  */
  bool process();

  /**
   * Returns the current driver station status packet for
   * use in the rest of the program.
   *
   * @return The driver station status
   */
  DriverStation getStatus();


/*************************************************************
 ******************* Private Functions ***********************
 *************************************************************/
private:

  /**
   * Decoder for the main driver station control packet, ignores joystick packets
   *
   * @param[out] estopped True if the estop is pressed
   * @param[out] enabled  True if enabled
   * @param[out] mode     The current mode of the system
   * @param[out] switchState The state of each switch
   *
   * @return The length of the fully decoded packet
   */
  int decodeDSControlPacket(uint8_t buffer[], uint8_t buffer_len, bool& estopped, bool& enabled, uint8_t& mode, uint8_t& switchState);

  /**
   * Decoder for the joystick packet
   * Joystick Packet - ![j/J][button word][leftXAxis][leftYAxis][rightXAxis][rightYAxis][triggerLeftAxis][triggerRightAxis][checksum][cr][lf]
   *
   * @param[in]  joystick_id The id of the joystick to parse
   * @param[out] buttonWord  Decoded button status
   * @param[out] axis[]      Decoded axis information
   * @return The length of the fully decoded packet
   */
  int decodeJoystickPacket(uint8_t buffer[], uint8_t buffer_len, uint8_t joystick_id, uint16_t& buttonWord, int8_t axis[]);

  /**
   * Encode the current robot status to send to the driver station
   *
   * @param estopped         True if the robot is estopped
   * @param enabled          True if the robot is enabled
   * @param mode             The current robot mode
   * @param protocol_version The current version of the protocol
   * @return The length of the robot status packet
   */
  int encodeRobotStatus(uint8_t buffer[], uint8_t buffer_len, bool estopped, bool enabled, uint8_t mode, uint8_t protocol_version);


  /** 
   * Encodes the termination onto the packet before sending
   *
   * @param total_length   The overall length of the packet
   * @param content_length The length of the payload
   */
  void encodeTermination(uint8_t buffer[], uint8_t buffer_len, int total_length, int content_length );
  
  /** 
   * Verifies the protocol checksum returning true if it passes
   *
   * @param content_length The length of the payload
   */
  bool verifyChecksum(uint8_t buffer[], uint8_t buffer_len, int content_length );


  /*************************************************************
   * Primative encode/decode functions
   *************************************************************/


  /**
   * Decode 16 bit value from 2 characters (1 byte)
   *
   * @param[in] data A 2 character hex string
   * @return The decoded value
   */
  uint8_t decodeUint8( char *data );

  /**
   * Decode 16 bit value from 4 characters (2 bytes)
   *
   * @param[in] data a 4 character hex string
   * @return The decoded value
   */
  uint16_t decodeUint16( char *data ); 

  /**
   * Encode 8 bit value into 8 bit ascii buffer
   *
   * @param[in]  value The number to encode
   * @param[out] buff  The buffer to put the result in (2 characters)
   */
  void encodeUint8( uint8_t value, char* buff );
  
  /**
   * Encode 16 bit value into the output buffer
   *
   * @param[in]  value The number to encode
   * @param[out] buff  The buffer to put the result in (4 characters)
   */
  void encodeUint16( uint16_t value, char* buff );

};


#endif // _DS_PROTOCOL_H_
