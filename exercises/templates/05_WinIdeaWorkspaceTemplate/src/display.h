#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <stdint.h>

#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF


/**
 * Converts RGB-888 color to RGB-565.
 */
uint16_t color565(uint8_t r, uint8_t g, uint8_t b);
uint16_t color565_s(uint8_t r, uint8_t g, uint8_t b);

/**
 * Prints a chess pattern on the display.
 */
void printPattern(uint16_t backgroundColor, uint16_t foregroundColor);
void printPattern_s(uint16_t backgroundColor, uint16_t foregroundColor);

/**
 * Initializes cursor properties.
 */
void initCursor();
void initCursor_s();

/**
 * Sets the textwriter cursor.
 */
void setCursor(int16_t x, int16_t y);
void setCursor_s(int16_t x, int16_t y);

/**
 * Sets the color of the font in RGB-565 format.
 */
void setTextColor(uint16_t color);
void setTextColor_s(uint16_t color);

/**
 * Sets the size of the font.
 */
void setTextSize(uint8_t s);
void setTextSize_s(uint8_t s);

/**
 * Sets the color of the font background.
 */
void setBackgroundColor(int bg);
void setBackgroundColor_s(int bg);

/**
 * Draws a char c on (x,y).
 * The character is shown in color c, and its background is colored using color bg.
 */
void drawChar(int x, int y,  char c,  int color,  int bg, char size);
void drawChar_s(int x, int y,  char c,  int color,  int bg, char size);


/**
 * Draws a char c on the actual cursor position and updates the cursor afterwards.
 */
void writeAuto(char c);
void writeAuto_s(char c);

/**
 * Draws a strings on the display with automated cursor update.
 */
void writeText(char *text);
void writeText_s(char *text);

/**
 * Draws a string on the display with automated cursor update and linebreak.
 */
void writeTextln(char *text);
void writeTextln_s(char *text);

/**
 *    Write a 16 bit variable on the display.
 */
void writeNumberOnDisplay(uint16_t *value);
void writeNumberOnDisplay_s(uint16_t *value);

#endif