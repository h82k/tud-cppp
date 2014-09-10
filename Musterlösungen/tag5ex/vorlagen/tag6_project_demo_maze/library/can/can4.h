/*! \file can4.h */
//*****************************************************************************
// Author		: Nicolas Weber
// Created		: 29.04.2010
// Revised		: 07.05.2010
// Version		: 0.1
// Target MCU	: Fujitsu MB96300 series
//
///	\ingroup can
///	\defgroup can_transferlevel Transfer Level Access (can4.h)
///	\par Overview
///		This library enables addressed messaging over the CAN Controller, with ports
///		and automatic message splitting.
///
//*****************************************************************************
//@{

#ifndef CAN4_H_
#define CAN4_H_

#include "../inttypes.h"

#define CAN4_MAX_PORT 31
#define CAN4_MAX_MSG_COUNT 31

/**
 * Initializes the CAN controller.
 * \param address Address to be used
 * \return 1 if everything went fine, 0 if there was an error
 */
uint8_t can4_init(uint8_t address);

/**
 * Opens an 'Port' to accept messages with suitable port
 * \param port Port
 * \return 1 if everything went right. 0 if there was an error.
 */
uint8_t can4_open(uint8_t port);

/**
 * Closes the given port
 * \param port the Port
 */
void can4_close(uint8_t port);

/**
 * Sends a message over the CAN controller to the destination. Automatically splits the messages.
 * \param dest Destination of the message (0 - CAN3_MAX_ADDRESS)
 * \param port Port to send the message to
 * \param data Pointer to byte data array
 * \param len length of the data (1 - 512)
 * \param interrupt
 * \return 1 if everything went fine, 0 if there was an error, in most cased wrong input data
 */
uint8_t can4_send(uint8_t dest, uint8_t port, uint8_t* data, uint8_t len, uint8_t interrupt);

/**
 * Checks if data was received and in case returns the data
 * \param port Port to be checked
 * \param data Array to save data to (max 512 Byte). If msg is longer than 8 Byte, data size of data array has to be multiple of 8!!!
 * \param source pointer to save the source of this message (1 Byte)
 * \return length of data field, or 0 if there was no data
 */
uint8_t can4_getData(uint8_t port, uint8_t* data, uint8_t* source);

#endif /* CAN4_H_ */
//@}
