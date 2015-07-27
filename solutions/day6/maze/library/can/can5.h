/*! \file can5.h */
//*****************************************************************************
// Author		: Nicolas Weber
// Created		: 14.05.2010
// Revised		: 14.05.2010
// Version		: 0.1
// Target MCU	: Fujitsu MB96300 series
//
///	\ingroup can
///	\defgroup can_systemservices CAN System Services (can5.h)
///	\par Overview
///		This library enables System Services.
///
//*****************************************************************************
//@{

#ifndef CAN5_H_
#define CAN5_H_

#include "../inttypes.h"

/**
 * Initializes the CAN controller. Also optains automatically an address for this controller. Interrupts are also activated.
 * \return 1 if everything went fine, 0 if there was an error
 */
uint8_t can5_init(void);

/**
 * Closes the standard system message port (port 0)
 */
void can5_close(void);

/**
 * Checks if given address is online.
 * \param address Address to be used
 * \return 1 if address is online, 0 if is offline
 */
uint8_t can5_isAlive(uint8_t address);

/**
 * Internal address to optain new address but can also be accessed from outside.
 * \return 1 if everything went fine, 0 if there was an error
 */
uint8_t can5_getNewAddress(void);

/** @name Service variables
 *
 */
//@{
	#define CAN5_PING_TIMEOUT 200000
	#define CAN5_ALIVE_TIMEOUT 20000
	#define CAN5_PORT 0
//@}

#endif
//@}
