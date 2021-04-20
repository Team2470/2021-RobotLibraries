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
  char buffer_[128];

  /* The number of valid bytes in the buffer (should be less than the length) */
  int buffer_pos_ = 0;


  /* Decoder state machine conditions */
  typedef enum 
  {
    DECODE_RESET,  /// Decoder reset state
    DECODE_START,  /// Decoder start condition

    DECODE_SOF1,   /// Decoder start of frame character 1
    DECODE_SOF2,   /// Decoder start of frame character 2
    DECODE_PAY,    /// Decoder Payload
    DECODE_CRC,    /// Deocder CRC step

  } DECODE_STATE_E;

  uint8_t state_ = DECODE_RESET;

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
   * Decoder for the main driver station control packet
   *
   * @param[in] buffer The buffer to try parsing as a packet
   * @param[in] buffer_len  The number of bytes in the buffer
   * @param[out] mode     The current mode of the system
   * @param[out] switchState The state of each switch
   *
   * @return True if the packet decoded successfully, false otherwise
   */
  bool decodeDSControlPacket(uint8_t buffer[], int buffer_len);

  /** 
   * Verifies the protocol checksum returning true if it passes
   *
   * @param content_length The length of the payload
   */
  bool verifyChecksum(uint8_t buffer[], int buffer_len, int content_length );

  /*************************************************************
   * Buffer Manipulation
   *************************************************************/

  /**
   * Push a new character onto the internal buffer 
   *
   * @param[in] data The character to push
   */
  void pushData(char data);

  /**
   * Remove the oldest chracter to allow reintrepretation of the buffer
   */
  void popData();

  /**
   * Reset data buffers
   */
  void clearData();

};


#endif // _DS_PROTOCOL_H_
