/*! \file can.h */
//*****************************************************************************
// Author		: Christian Illy
// Created		: 04.05.2009
// Revised		: 05.07.2009
// Version		: 0.1
// Target MCU	: Fujitsu MB96300 series
//
///	\ingroup can
///	\defgroup can_lowlevel Low level access (can.h)
///	\code #include "can/can.h" \endcode
///	\par Overview
///		This library enables low level access to the CAN controller engine.
///
//*****************************************************************************
//@{


#ifndef CAN_H_
#define CAN_H_

#include "../inttypes.h"
#include "can.cfg.h"

/**
 * (Re)Initializes I/Os and registers of CAN controller. Defined constants CAN_BAUD_*
 * can be used for bit timing (constants.h).
 * \param prescaler Prescaler ()
 * \param propSeg Number of TQ for Propagation Segment (1 - 8)
 * \param phSeg1 Number of TQ for the Phase Segment 1 (2 - 8)
 * \param phSeg2 Number of TQ for Phase Segment 2 (2 - 8)
 * \param jumpWidth ResynchronizationJumpWidth (in TQ) (1 - 4)
 * \param interrupts If set CAN interrupts will be enabled
 * \return 1 if everything went fine, 0 if there was an error (most probably wrong input
 * values)
 */
uint8_t can_init(uint8_t prescaler, uint8_t propSeg, uint8_t phSeg1, uint8_t phSeg2,
		uint8_t jumpWidth, uint8_t interrupts);

/**
 * Configures a CAN message buffer
 * \param buffer Buffer to configure (1 - #CAN_BUFFERCOUNT)
 * \param id CAN-ID to set
 * \param options Set buffer options. See defines \ref can_bufferopts "CAN_BUF_OPT_*"
 * \param maskOptions Set mask options. See defines \ref can_maskopts "CAN_BUF_MASK_*"
 * \param idMask CAN-ID mask. Only used when #CAN_BUF_MASK_USE is given in maskOptions
 * \return 1 if everything went fine, 0 if there was an error (most probably wrong input
 * values)
 */
uint8_t can_config_buffer(uint8_t buffer, uint32_t id, uint8_t options, uint8_t maskOptions,
		uint32_t idMask);

/**
 * Enable or disable automatic replies to appropriate remote-transmit-requests.
 * \param buffer Buffer to configure (1 - #CAN_BUFFERCOUNT)
 * \param enable Enable (1) or disable (0) automatic replies for this buffer
 * \return 1 if everything went fine, 0 if there was an error (most probably wrong input
 * values)
 */
uint8_t can_set_buffer_autoreply(uint8_t buffer, uint8_t enable);

/**
 * Set data of buffer
 * \param buffer Buffer to fill data in (1 - #CAN_BUFFERCOUNT)
 * \param data Pointer to data to put in buffer
 * \param len Number of bytes to put (0 - 8)
 * \return 1 if everything went fine, 0 if there was an error (most probably wrong input
 * values)
 */
uint8_t can_set_buffer_data(uint8_t buffer, uint8_t* data, uint8_t len);

/**
 * Set data of buffer
 * \param buffer Buffer to send (1 - #CAN_BUFFERCOUNT)
 * \return 1 if everything went fine, 0 if there was an error (most probably wrong input
 * values)
 */
uint8_t can_send_buffer(uint8_t buffer);

/**
 * Set data of buffer
 * \param buffer Buffer to check for new data (1 - #CAN_BUFFERCOUNT) or 0 to check all
 * buffers
 * \return Buffer number of buffer with new data (1 - #CAN_BUFFERCOUNT), 0 if there was an
 * error (most probably wrong input values)
 */
uint8_t can_buffer_newData(uint8_t buffer);

/**
 * Get data of buffer
 * \param buffer Buffer to read data from (1 - #CAN_BUFFERCOUNT)
 * \param data Pointer to target memory for data, should be at least 8 bytes long as long
 * as you do not exactly know how many bytes there will be in the buffer
 * \param id Pointer to target memory for read CAN ID
 * \return Number of returned data bytes (0 - 8), -1 if there was an
 * error (most probably wrong input values)
 */
int8_t can_buffer_getData(uint8_t buffer, uint8_t* data, uint32_t* id);


/** @name CAN-ID conversions
 *  Defines macros conversion between numeric CAN-IDs and their representations in the CAN
 *  engine.
 *  \anchor canid_conversions
 */
//@{

/**
 * Converts the given ID to the format needed by the arbitration registers for standard frames
 */
#define ID_TO_STDFRAME(id) ((id & 0x000007FFL) << 18)

/**
 * Converts the given ID to the format needed by the arbitration registers for extended frames
 */
#define ID_TO_EXTFRAME(id) (id & 0x1FFFFFFFL)

/**
 * Converts the value from the format of standard frames in the arbitration registers to the respective ID
 */
#define STDFRAME_TO_ID(reg) (((reg & 0x1FFFFFFFL) >> 18) & 0x000007FFL)

/**
 * Converts the value from the format of extended frames in the arbitration registers to the respective ID
 */
#define EXTFRAME_TO_ID(reg) (reg & 0x1FFFFFFFL)
//@}


/** @name Baudrate selections
 *  Defines for standard baudrates usable with #can_init.
 *  Values are: prescaler, TQ in propagation segment,
 *  	TQ phase buffer segment 1, TQ phase buffer segment 2,
 *  	TQ resynchronization jump width
 *  \anchor can_baudrates
 */
//@{

/**
 * 50 kBaud/s, sampling point 75%
 */
#define CAN_BAUD_50K	14, 8, 6, 5, 1

/**
 * 125 kBaud/s, sampling point 75%
 */
#define CAN_BAUD_125K	7, 7, 4, 4, 1

/**
 * 1 MBaud/s, sampling point 78.6%
 */
#define CAN_BAUD_1000K	1, 7, 3, 3, 1

//@}



/** @name Buffer options
 *  Options that can be passed to #can_config_buffer as "options". Can be or'ed together.
 *  \anchor can_bufferopts
 */
//@{

/**
 * Enables the buffer for reception/transmission of frames
 * (Flag for options of #can_config_buffer)
 */
#define CAN_BUF_OPT_ENABLED	(_BV(0))

/**
 * Sets the buffer to be a transmit buffer (can respond automaticly to RTR frames if
 * enabled afterwards)
 * (Flag for options of #can_config_buffer)
 */
#define CAN_BUF_OPT_TRANSMIT	(_BV(1))

/**
 * Sets the buffer to be used for extended frames
 * (Flag for options of #can_config_buffer)
 */
#define CAN_BUF_OPT_EXTENDED	(_BV(2))

/**
 * Enables the RX interrupt for the buffer
 * (Flag for options of #can_config_buffer)
 */
#define CAN_BUF_OPT_RX_INTERRUPT	(_BV(4))

/**
 * Enables the TX interrupt for the buffer
 * (Flag for options of #can_config_buffer)
 */
#define CAN_BUF_OPT_TX_INTERRUPT	(_BV(5))

//@}


/** @name Buffer mask options
 *  Options that can be passed to #can_config_buffer as "maskOptions". Can be or'ed
 *  together.
 *  \anchor can_maskopts
 */
//@{

/**
 * Enables the masks for the buffer acceptance filtering (otherwise always the whole
 * header is used for arbitration)
 * (Flag for maskOptions of #can_config_buffer)
 */
#define CAN_BUF_MASK_USE	(_BV(0))

/**
 * Selects the extended bit to be checked for acceptance filtering. Only used if
 * #CAN_BUF_MASK_USE is also given
 * (Flag for maskOptions of #can_config_buffer)
 */
#define CAN_BUF_MASK_EXTENDED	(_BV(1))

/**
 * Selects the direction bit to be checked for acceptance filtering. Only used if
 * #CAN_BUF_MASK_USE is also given
 * (Flag for maskOptions of #can_config_buffer)
 */
#define CAN_BUF_MASK_DIRECTION	(_BV(2))

//@}


#endif /* CAN_H_ */
//@}
