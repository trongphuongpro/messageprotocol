/** 
 * @file uart_message.h
 * @brief Function prototypes for message protocol
 *  
 * This library is used to create Data Link Layer for existed Physical Layers,
 * such as UART, SPI, I2C,...

 * This file contains the prototypes, struct, enum and extern variable
 * that you will need, in order to use this library.

 * @author Nguyen Trong Phuong (aka trongphuongpro)
 * @date 2019 Dec 28
 */


#ifndef __MESSAGE__
#define __MESSAGE__

#ifdef __cplusplus
extern "C" {
#endif

#include "crc32.h"


/** 
 * massage preamble size
 */	
#define MESSAGE_PREAMBLE_SIZE		4


/** 
 * maximum payload size
 */		
#define MESSAGE_MAX_PAYLOAD_SIZE	100


/** 
 * @brief enum contains code for each step of transmitting/receiving procedure
 */  
typedef enum  {	parsingPreamble=0, /**< 0 */
				parsingAddress, /**< 1 */
				parsingSize, /**< 2 */
				parsingPayload, /**< 3 */
				parsingChecksum, /**< 4 */
				idle /**< 5 */ 
} steps;


/** 
 * @brief Struct contains message packet
 */  
typedef struct {
	uint8_t preamble[MESSAGE_PREAMBLE_SIZE]; /**< preamble of message packet */
	uint8_t address[2]; /**< destination and source address: 2 bytes*/
	uint8_t payloadSize; /**< size of payload: 1 byte */
	uint8_t payload[MESSAGE_MAX_PAYLOAD_SIZE]; /**< payload */
	crc32_t checksum; /**< CRC-32 checksum: 4 bytes */
} __attribute__((__packed__)) MessagePacket;


/** 
 * @brief global variable contains current state of procedure
 */
extern volatile steps currentStep;


/** 
 * @brief Initialize message transmitting/receiving procedure
 * 
 * Open UART bus, initialize crc32 checksum, enable interrupt.
 *
 * @param baudrate UART baudrate.
 * @return pointer to received MessagePacket.
 */
volatile MessagePacket* uart_message_init(uint32_t baudrate);


/** 
 * @brief Send message packet
 *
 * @param baudrate UART baudrate.
 * @param destination Receiver's address.
 * @param source Transmitter's address.
 * @param payload message need to be sent.
 * @param len length of message. 
 * @return nothing.
 */
void message_send(const void* preamble, 
						uint8_t destination, 
						uint8_t source, 
						const void* payload, 
						uint8_t len);


/** 
 * @brief Check the integrity of the data
 *
 * @return 0: OK
 * @return -1: Error
 */
int message_verifyChecksum(void);

#ifdef __cplusplus
}
#endif

#endif