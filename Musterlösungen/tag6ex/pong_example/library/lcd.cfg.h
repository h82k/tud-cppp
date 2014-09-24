/*! \file lcd.cfg.h */
//*****************************************************************************
// Author		: Christian Illy
// Created		: 20.04.2009
// Revised		: 04.06.2009
// Version		: 0.1
// Target MCU	: Fujitsu MB96300 series
//
///	\ingroup lcd
///	\defgroup lcd_configuration Internal configurations (lcd.cfg.h)
///	\par Overview
///		This library provides hardware definitions for the LCD routines.
///
//*****************************************************************************
//@{
#ifndef LCD_CFG_H_
#define LCD_CFG_H_

/// 1 = Use local framebuffer in RAM and copy to LCD on call to lcd_flush().<br>0 = Directly manipulate LCD ram contents.
#define LCD_FRAMEBUFFER_MODE	0

/// Port where the data pins of the display are connected
#define LCD_DATA_PORT	PDR01
/// Direction register of the data pins port
#define LCD_DATA_DDR	DDR01
/// Input enable register of the data pins port
#define LCD_DATA_PIER	PIER01

/// Port where the control lines of the display are connected
#define LCD_CTRL_PORT	PDR02
/// Direction register of the control pins port
#define LCD_CTRL_DDR	DDR02
/// Input enable register of the control pins port
#define LCD_CTRL_PIER	PIER02
/// Data/Instruction pin
#define LCD_CTRL_DI		0
/// Read/Write pin
#define LCD_CTRL_RW		1
/// Enable pin
#define LCD_CTRL_E		2
/// Chip 1 select pin
#define LCD_CTRL_CS1	3
/// Chip 2 select pin
#define LCD_CTRL_CS2	4
/// Reset pint
#define LCD_CTRL_RESET	5


/** @name LCD commands
 *  Defines command values for the display.
 */
//@{

/// Display on
#define LCD_CMD_ON 0x3f
/// Display off
#define LCD_CMD_OFF 0x3e
/// Set address
#define LCD_CMD_SETADDRESS 0x40
/// Set page
#define LCD_CMD_SETPAGE 0xb8
/// Set startline
#define LCD_CMD_STARTLINE 0xc0

//@}


/// LCD width
#define LCD_WIDTH 128
/// LCD height
#define LCD_HEIGHT 64

#endif /* LCD_CFG_H_ */
//@}
