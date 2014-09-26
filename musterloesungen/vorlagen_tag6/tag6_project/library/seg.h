/*! \file seg.h */
//*****************************************************************************
// Author		: Christian Illy
// Created		: 09.04.2009
// Revised		: 06.06.2009
// Version		: 0.1
// Target MCU	: Fujitsu MB96300 series
//
///	\defgroup seg 7-segment display (seg.h)
///	\code #include "seg.h" \endcode
///	\par Overview
///		Routines to show values in decimal or hexadecimal notation on 7 segment displays
///
//*****************************************************************************
//@{
#ifndef SEG_H_
#define SEG_H_

#include "inttypes.h"

/**
 * Initializes I/Os for both seven-segment displays
 */
extern void seg_init(void);

/**
 * Show a decimal number between 0 and 99 on the displays
 * \param num Number to display
 */
extern void seg_num(uint8_t num);

/**
 * Show a decimal digit (0 - 9) on the left display
 * \param num Number to display
 */
extern void seg_numLeft(uint8_t num);

/**
 * Show a decimal digit (0 - 9) on the right display
 * \param num Number to display
 */
extern void seg_numRight(uint8_t num);

/**
 * Show a hexadecimal number between 0 and 255 on the displays
 * \param hex Value to display
 */
extern void seg_hex(uint8_t hex);

/**
 * Show a hexadecimal digit (0 - 15) on the left display
 * \param hex Value to display
 */
extern void seg_hexLeft(uint8_t hex);

/**
 * Show a hexadecimal digit (0 - 15) on the right display
 * \param hex Value to display
 */
extern void seg_hexRight(uint8_t hex);

#endif /* SEG_H_ */
//@}
