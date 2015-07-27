/*! \file lcd.h */
//*****************************************************************************
// Author		: Christian Illy
// Created		: 09.04.2009
// Revised		: 06.06.2009
// Version		: 0.1
// Target MCU	: Fujitsu MB96300 series
//
///	\defgroup lcd LCD (lcd.h)
///	\code #include "lcd.h" \endcode
///	\par Overview
///		Routines to access an AV12864 pixelmatrix display.
///
//*****************************************************************************
//@{
#ifndef LCD_H_
#define LCD_H_

#include "inttypes.h"
#include "lcd.cfg.h"

#define LCD_COLOR_BLACK				(1)
#define LCD_COLOR_WHITE				(0)

#define LCD_ALIGNMENT_LEFT			(0)
#define LCD_ALIGNMENT_CENTER		(1)
#define LCD_ALIGNMENT_RIGHT			(2)

#define LCD_ALIGNMENT_TOP			(0)
#define LCD_ALIGNMENT_MIDDLE		(4)
#define LCD_ALIGNMENT_BOTTOM		(8)

#define LCD_ORIENTATION_0			(0)
#define LCD_ORIENTATION_90			(16)
#define LCD_ORIENTATION_180			(32)
#define LCD_ORIENTATION_270			(64)

/**
 * Initializes I/Os for display usage and display's controllers
 */
extern void lcd_init(void);

/**
 * Clears the display contents
 * \param color Clear to all black (1) or all white (0)
 */
extern void lcd_clear(uint8_t color);

/**
 * Draws a single page (1*8 pixel) onto the display.
 * \param x X coordinate of the page (0 - 127)
 * \param page Page (0 - 7)
 * \param data Contents of the page. LSB is the topmost pixel
 */
extern void lcd_drawPage(uint8_t x, uint8_t page, uint8_t data);

/**
 * Read the state of a single pixel.
 * \param x X coordinate (0 - 127)
 * \param y Y coordinate (0 - 63)
 * \return 1 = active, 0 = inactive, -1 = x or y outside display area
 */
extern int8_t lcd_getPixel(int16_t x, int16_t y);

/**
 * Draws a single pixel onto the display, preserving the state of all other pixels in the same page.
 * \param x X coordinate (0 - 127)
 * \param y Y coordinate (0 - 63)
 * \param color 1 = active, 0 = inactive
 */
extern void lcd_drawPixel(int16_t x, int16_t y, uint8_t color);

/**
 * Draws a (non-filled) circle onto the display.
 * \param x X coordinate of the center of the circle (0 - 127)
 * \param y Y coordinate of the center of the circle (0 - 63)
 * \param r Radius of the circle
 * \param color 1 = pixels of circle will be active, 0 = inactive
 * \param filled 1 = circle will be completely filled, 0 = only borderline
 */
extern void lcd_drawCircle(int16_t x, int16_t y, uint8_t r, uint8_t color, uint8_t filled);

/**
 * Draws a (filled) rectangle on the display.
 * \param x X coordinate of the upper left corner of the rectangle (0 - 127)
 * \param y Y coordinate of the upper left corner of the rectangle (0 - 63)
 * \param w Width of the rectangle (0 - 128)
 * \param h Height of the rectangle (0 - 64)
 * \param color 1 = contents will be active, 0 = inactive
 * \param filled 1 = rectangle will be completely filled, 0 = only borderline
 */
extern void lcd_drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint8_t color, uint8_t filled);

/**
 * Draws a line on the display.
 * \param x1 X coordinate of the start of the line (0 - 127)
 * \param y1 Y coordinate of the start of the line (0 - 63)
 * \param x2 X coordinate of the end of the line (0 - 127)
 * \param y2 Y coordinate of the end of the line (0 - 63)
 * \param color 1 = line will be painted with active pixels, 0 = inactive pixels
 */
extern void lcd_drawLine(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint8_t color);

/**
 * Draws a single character on screen
 * \param x X position to write to (0 - 127)
 * \param page Page to write to (0 - 7)
 * \param ascii ASCII value of character to write (0 - 127)
 * \param color 1 = Character's pixels will be black, 0 = white
 * \param overlay 1 = pixels not on character's position will not be changed,
 * 					0 = the whole 5 pages for each character will be overwritten
 * \return X coordinate for next character
 */
extern uint8_t lcd_drawCharacter(uint8_t x, uint8_t page, char ascii, uint8_t color, uint8_t overlay);

/**
 * Draws a string on screen, including line wrapping (if enabled) and delay between characters
 * \param x1 X coordinate of area start (0 - 127)
 * \param page1 Page of area start (0 - 7)
 * \param x2 X coordinate of area end, set 0 to ignore (0 - 127)
 * \param page2 Page of area end (only used if wrap=1) (0 - 7)
 * \param wrap String will be wrapped to next line if set to 1
 * \param delay Wait for specified amount of time between each character (in ms)
 * \param firstChar Pointer to first character of null-terminated string
 * \param color 1 = Character's pixels will be black, 0 = white
 * \param overlay 1 = pixels not on character's position will not be changed,
 * 					0 = the whole 5 pages for each character will be overwritten
 * \return X coordinate for next character
 */
extern uint8_t lcd_drawString(uint8_t x1, uint8_t page1, uint8_t x2, uint8_t page2, uint8_t wrap,
        uint16_t delay, char* firstChar, uint8_t color, uint8_t overlay);

/**
 * Draws a single character on screen (pixel precise but slower)
 * \param x X position to write to (0 - 127)
 * \param y Y position to write to (0 - 63)
 * \param ascii ASCII value of character to write (0 - 127)
 * \param color 1 = Character's pixels will be black, 0 = white
 * \param orientation 1 = vertical, 0 = horizontal
 * \param font selects the font to use (0=default)
 * \return X or Y coordinate for next character (depending on orientation
 */
extern int16_t lcd_drawCharacterPrecise(int16_t x, int16_t y, char ascii, uint8_t color, uint8_t orientation, uint8_t font);

/**
 * Draws a string on screen using pixel-precise methods
 * \param x X coordinate to write to (0 - 127)
 * \param y Y coordinate to write to (0 - 63)
 * \param firstChar Pointer to first character of null-terminated string
 * \param color 1 = Character's pixels will be black, 0 = white
 * \param settings bitmasked settings
 * \param font selects the font to use (0=default)
 * \return X coordinate for next character
 */
extern int16_t lcd_drawStringPrecise(int16_t x, int16_t y, char* firstChar, uint8_t color, uint8_t settings, uint8_t font);

/**
 * Copies the local buffer to the LCD RAM. (Only needed if #LCD_FRAMEBUFFER_MODE is set to 1)
 */
extern void lcd_flush(void);

/** @name LCD size
 *  Defines LCD horizontal/vertical size
 *  \anchor lcd_size
 */
//@{

/**
 * Horizontal size of display in pixel
 */
#define LCD_WIDTH 128
/**
 * Vertical size of display in pixel
 */
#define LCD_HEIGHT 64
//@}

#endif /* LCD_H_ */
//@}
