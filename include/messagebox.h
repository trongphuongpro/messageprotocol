/** 
 * @file messagebox.h
 * @brief Function prototypes for creating ring buffer for embedded systems
 * @author Nguyen Trong Phuong (aka trongphuongpro)
 * @date January 6, 2020
 */


#ifndef __RINGBUFFER__
#define __RINGBUFFER__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include "message.h"

/** 
 * @brief Struct contains FIFO buffer containing received messages.
 */ 
typedef struct MessageBox {
	Message *data; /**< @brief Array of pointers to messages */
	uint8_t readPoint; /**< @brief Reading point */
	uint8_t writePoint; /**< @brief Writting point */
	uint8_t capacity; /**< @brief The capacity of FIFO buffer */
	bool isFull; /**< @brief State of buffer, full or not */
} __attribute__((packed)) MessageBox;


/**
 * @brief Create new ring buffer.
 * @param box pointer to MessageBox instance
 * @param data pointer to array containing data
 * @param num max number of element in buffer.
 * @return new ring buffer instance.
 */
void messagebox_create(MessageBox* box, Message *data, uint8_t num);


/**
 * @brief Destroy a ring buffer.
 *
 * Free all allocated memory for this buffer.
 * @param buffer ring buffer instance.
 * @return nothing.
 */
void messagebox_destroy(MessageBox* buffer);


/**
 * @brief Reset existed ring buffer.
 * @param buffer ring buffer instance.
 * @return nothing.
 */
void messagebox_clear(MessageBox* buffer);


/**
 * @brief Check if ring buffer is empty
 * @param buffer ring buffer instance.
 * @return state of ring buffer.
 */
bool messagebox_isEmpty(MessageBox* buffer);


/**
 * @brief Check if new data is available
 * @param buffer ring buffer instance.
 * @return state of ring buffer.
 */
bool messagebox_isAvailable(MessageBox* buffer);


/**
 * @brief Check if ring buffer is full
 * @param buffer ring buffer instance.
 * @return state of ring buffer.
 */
bool messagebox_isFull(MessageBox* buffer);


/**
 * @brief Check the capacity of ring buffer
 * @param buffer ring buffer instance.
 * @return the capacity of buffer
 */
uint8_t messagebox_getCapacity(MessageBox* buffer);


/**
 * @brief Get the used space of ring buffer
 * @param buffer ring buffer instance.
 * @return the number of used space of buffer
 */
uint8_t messagebox_getUsedSpace(MessageBox* buffer);


/**
 * @brief Get the free space of ring buffer
 * @param buffer ring buffer instance.
 * @return the number of free space of buffer
 */
uint8_t messagebox_getFreeSpace(MessageBox* buffer);


/**
 * @brief Push new message to ring buffer
 * @param buffer ring buffer instance.
 * @param message message instance.
 * @return the number of free space of buffer
 */
void messagebox_push(MessageBox* buffer, Message message);


/**
 * @brief Pop a message from ring buffer
 * @param buffer ring buffer instance.
 * @param message message instance.
 * @return 0: success, -1: failed due buffer is empty.
 */
int messagebox_pop(MessageBox* buffer, Message *message);


#ifdef __cplusplus
}
#endif

#endif