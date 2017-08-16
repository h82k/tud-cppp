#ifndef GFX_H
#define GFX_H

#include <stdlib.h>
#include <stdio.h>
#include "pins.h"
#include "pdl_header.h"
#include "glcdfont.h"

#define WIDTH   480
#define HEIGHT  320


void fillScreen(int color);
void drawFastHLine(int x, int y, int length, int color);
void drawFastVLine(int x, int y, int length, int color);
void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
void fillRect(int x1, int y1, int w, int h, int fillcolor);
void drawPixel(int16_t x, int16_t y, uint16_t color);
void drawCircle(int x0, int y0, int r, unsigned int color);
void drawCircleHelper( int x0, int y0, int r, char cornername, unsigned int color);
void fillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta, uint16_t color);
void fillCircle(int x0, int y0, int r, unsigned int color);
void drawRoundRect(int x, int y, int w, int h, int r, unsigned int color);
void fillRoundRect(int x, int y, int w, int h, int r, unsigned color);
void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);
void drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
void fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);


void write8BitValueOnLCD(uint8_t *value);
void write16BitValueOnLCD(uint16_t *value);
void write32BitValueOnLCD(uint32_t *value);
void write3Digits8Bit(uint8_t *number);
void write3Digits16Bit(uint16_t *number);

#endif /* LCD_H */
