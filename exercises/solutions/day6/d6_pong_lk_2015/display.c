/**
 * Author: Laurenz Kamp
 * Created: 10.09.2015
 */

#include "mb96348hs.h"

#include "display.h"
#include "io.h"

#define LCD_T 			10l
#define LCD_WIDTH		128
#define LCD_HEIGHT		64

#define LCD_PORT_DB		PDR01
#define LCD_PIN_DI		PDR02_P0
#define LCD_PIN_RW		PDR02_P1
#define LCD_PIN_E		PDR02_P2
#define LCD_PIN_CS1		PDR02_P3
#define LCD_PIN_CS2		PDR02_P4
#define LCD_PIN_RESET	PDR02_P5

static unsigned char lcd_buffer[128][8];


static void LCDenable(void)
{
	LCD_PIN_E = 1;
	wait(LCD_T);
	LCD_PIN_E = 0;
	wait(LCD_T);

	return;
}

static void LCDcommand(char command)
{
	LCD_PORT_DB = command;
	LCD_PIN_DI = 0;
	LCD_PIN_RW = 0;

	LCDenable();

	return;
}

static void LCDdata(char data)
{
	LCD_PORT_DB = data;
	LCD_PIN_DI = 1;
	LCD_PIN_RW = 0;

	LCDenable();

	return;
}

static void LCDsetX(int x)
{
	if(x < 64) {
		LCD_PIN_CS1 = 1;
		LCD_PIN_CS2 = 0;
	} else {
		LCD_PIN_CS1 = 0;
		LCD_PIN_CS2 = 1;
		x -= 64;
	}

	x = (x & ((1 << 6) - 1));
	LCDcommand((1 << 6) | x);

	return;
}

static void LCDsetY(int y)
{
	LCD_PIN_CS1 = 1;
	LCD_PIN_CS2 = 1;

	y = (y & ((1 << 3) - 1));
	LCDcommand((1 << 7) | (1 << 5) | (1 << 4) | (1 << 3) | y);

	return;
}

// init LCD
void initLCD(void) {
	PDR01 = 0x00;
	DDR01 = 0xff;
	PDR02 = 0x00;
	DDR02 = 0xff;
	LCD_PIN_RESET = 1;	// RESET must be OFF (1)
	LCD_PIN_RW = 0;		// write always

	wait(1000);

	LCD_PIN_CS1 = 1;
	LCD_PIN_CS2 = 1;
	LCDcommand((1 << 6) - 1);
}

void lcd_clear(void) {
	int x, y;

	for(x = 0; x < LCD_WIDTH; x++) {
		for(y = 0; y < LCD_HEIGHT / 8; y++) {
			lcd_buffer[x][y] = 0;
		}
	}

	return;
}

void lcd_setall(void) {
	int x, y;

	for(x = 0; x < LCD_WIDTH; x++) {
		for(y = 0; y < LCD_HEIGHT / 8; y++) {
			lcd_buffer[x][y] = 255;
		}
	}

	return;
}

void lcd_flush(void) {
	int x, y;

	for(y = 0; y < 8; y++) {
		LCDsetY(y);
		LCDsetX(0);
		for(x = 0; x < 64; x++) {
			LCDdata(lcd_buffer[x][y]);
		}
		LCDsetX(64);
		for(x = 0; x < 64; x++) {
			LCDdata(lcd_buffer[x + 64][y]);
		}
	}
}

void lcd_drawPixel(int x, int y, char black) {
	if(x >= LCD_WIDTH || y >= LCD_HEIGHT || x < 0 || y < 0) {
		return;
	}

	if(black) {
		lcd_buffer[x][y / 8] |= 1 << (y % 8);
	} else {
		lcd_buffer[x][y / 8] &= ~(1 << (y % 8));
	}

	return;
}
