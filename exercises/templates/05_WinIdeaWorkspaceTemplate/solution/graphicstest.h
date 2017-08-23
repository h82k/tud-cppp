#ifndef GRAPHICSTEST
#define GRAPHICSTEST

#include <stdint.h>

void testGraphics(void);
void testRotateText(void);

void testFillScreen();
void testText(void);
void testLines(uint16_t color);
void testFastLines(uint16_t color1, uint16_t color2);
void testRects(uint16_t color);
void testFilledRects(uint16_t color1, uint16_t color2);
void testFilledCircles(uint8_t radius, uint16_t color);
void testCircles(uint8_t radius, uint16_t color);
void testTriangles(void);
void testFilledTriangles(void);
void testRoundRects(void);
void testFilledRoundRects(void);

#endif