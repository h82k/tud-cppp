/*! \file font.h */
//*****************************************************************************
// Author		: Christian Illy
// Created		: 21.04.2009
// Revised		: 06.06.2009
// Version		: 0.1
// Target MCU	: Fujitsu MB96300 series
//
///	\ingroup lcd
///	\defgroup lcd_font Font (font.h)
/// Used by lcd.h, should not be included directly!
///	\par Overview
///		Defines fontsets for pixelmatrix LCDs.
///
//*****************************************************************************
//@{
#ifndef FONT_H_
#define FONT_H_

#include "inttypes.h"

#define FONT_REGULAR 	0
#define FONT_TINY 		1
#define FONT_NANO 		2

/**
 * Retrieves the array of pages (-> pixels) for the specified ASCII value
 * \param ascii ASCII value
 * \param font Type of font
 * \return 0 if character for value not defined, pointer to the first page for the character otherwise
 */
extern uint8_t* font_getChar(uint8_t ascii, uint8_t font);

extern uint8_t font_getWidth(uint8_t font);
extern uint8_t font_getHeight(uint8_t font);

#endif /* FONT_H_ */
//@}
