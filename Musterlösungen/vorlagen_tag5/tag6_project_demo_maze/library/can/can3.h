/*! \file can3.h */
//*****************************************************************************
// Author		: Nicolas Weber
// Created		: 23.04.2010
// Revised		: 07.05.2010
// Version		: 0.1
// Target MCU	: Fujitsu MB96300 series
//
///	\ingroup can
///	\defgroup can_routinglevel Routing Level access (can3.h)
///	\par Overview
///		This library enables addressed messaging over the CAN Controller.
///
//*****************************************************************************
//@{

#ifndef CAN3_H_
#define CAN3_H_

#include "can.h"
#include "../inttypes.h"
#include "../interrupts.h"

/**
 * Initializes the CAN controller.
 * \param address Address to be used
 * \return 1 if everything went fine, 0 if there was an error
 */
uint8_t can3_init(uint8_t address);

/**
 * Sends a message over the CAN controller to the destination.
 * \param dest Destination of the message (0 - CAN3_MAX_ADDRESS)
 * \param uid Used identifier for this message
 * \param data Pointer to byte data array
 * \param len length of the data (1 - 8)
 * \param interrupt
 * \return 1 if everything went fine, 0 if there was an error, in most cased wrong input data
 */
uint8_t can3_send(uint8_t dest, uint16_t uid, uint8_t* data, uint8_t len, uint8_t interrupt);

/**
 * Opens an 'Port' to accept messages with suitable id
 * \param uid Messageid
 * \return buffer reference
 */
uint8_t can3_open(uint16_t uid);

/**
 * Opens an 'Port' to accept messages with suitable id and idMask
 * \param uid Messageid
 * \param idMask Message Mask
 * \return buffer reference
 */
uint8_t can3_maskedOpen(uint16_t uid, uint16_t idMask);

/**
 * Checks if data was received and in case returns the data
 * \param buffer Buffer to check
 * \param data Array to save data to (max 8 Byte)
 * \param source pointer to save the source of this message (1 Byte)
 * \param id pointer to save received id of this message (2 Byte)
 * \return length of data field, or 0 if there was no data
 */
uint8_t can3_getData(uint8_t buffer, uint8_t* data, uint8_t* source, uint16_t* id);

/**
 * Closes an buffer, so no data is longer received
 * \param buffer Buffer to be closed
 */
void can3_close(uint8_t buffer);

/**
 * Updates the address of the CAN Controller.
 * \param address new address
 */
void can3_setAddress(uint8_t address);

/**
 * Gets the address of the CAN Controller.
 * \return address
 */
uint8_t can3_getAddress(void);

/**
 * Adds an IRQHandler to the IRQHandler list.
 * \param handler
 * \return 1 if everything went fine
 */
uint8_t can3_registerIRQHandler(IRQHandler handler);

/**
 * Removes an IRQHandler from the IRQHandler list.
 * \param handler
 * \return 1 if everything went fine
 */
uint8_t can3_removeIRQHandler(IRQHandler handler);

/** @name CAN3 fixed values
 * Values of the implementation, that cannot be changed
 */
//@{
/**
 * Sets the maximum
 */

/**
 * Maximum of available addresses
 */
#define CAN3_MAX_ADDRESS 63

/**
 * Maximum of message length, fixed by CAN specification
 */
#define CAN3_MAX_MESSAGELENGTH 8

/**
 * Defines an address for multicast messages
 */
#define CAN3_MULTICAST 255

//@}

#endif /* CAN3_H_ */
//@}
