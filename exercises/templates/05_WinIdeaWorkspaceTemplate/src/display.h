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

uint16_t color565(uint8_t r, uint8_t g, uint8_t b);

/**
 * Prints a chess pattern on the display.
 */
void printPattern(uint16_t color);

/**
 * Initializes cursor properties.
 */
void initCursor();

/**
 * Sets the textwriter cursor.
 */
void setCursor(int16_t x, int16_t y);

/**
 * Sets the color of the font in RGB-565 format.
 */
void setTextColor(uint16_t c);

/**
 * Sets the size of the font.
 */
void setTextSize(uint8_t s);

/**
 * Sets the color of the font background.
 */
void setBackgroundColor(int bg);

/**
 * Draws a char c on (x,y).
 */
void drawChar(int x, int y,  char c,  int color,  int bg, char size);


/**
 * Draws a char c on the actual cursor position and updates the cursor afterwards.
 */
void writeAuto(char c);

/**
 * Draws a strings on the display with automated cursor update.
 */
void writeText(char *text);

/**
 * Draws a string on the display with automated cursor update and linebreak.
 */
void writeTextln(char *text);

/**
 *    Write a 16 bit variable on the display.
 */
void writeNumberOnDisplay(uint16_t *value);
