#include <stdlib.h>
#include <stdio.h>

#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

int16_t cursorX, cursorY;
uint16_t textColor;
uint8_t textSize;
int textBackground;

/**
 * Converts RGB-888 color to RGB-565.
 */

uint16_t color565_s(uint8_t r, uint8_t g, uint8_t b);

/**
 * Prints a chess pattern on the display.
 */
void printPattern_s();

/**
 * Initializes cursor properties.
 */
void initCursor_s();

/**
 * Sets the textwriter cursor.
 */
void setCursor_s(int16_t x, int16_t y);

/**
 * Sets the color of the font in RGB-565 format.
 */
void setTextColor_s(uint16_t c);

/**
 * Sets the size of the font.
 */
void setTextSize_s(uint8_t s);

/**
 * Sets the color of the font background.
 */
void setBackgroundColor_s(int bg);

/**
 * Draws a char c on (x,y).
 */
void drawChar_s(int x, int y,  char c,  int color,  int bg, char size);


/**
 * Draws a char c on the actual cursor position and updates the cursor afterwards.
 */
void writeAuto_s(char c);

/**
 * Draws a strings on the display with automated cursor update.
 */
void writeText_s(char *text);

/**
 * Draws a string on the display with automated cursor update and linebreak.
 */
void writeTextln_s(char *text);

/**
 *    Write a 16 bit variable on the display.
 */
void writeNumberOnDisplay_s(uint16_t *value);
