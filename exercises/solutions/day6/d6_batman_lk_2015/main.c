/**
 * Author: Laurenz Kamp
 * Created: 10.09.2015
 */

#include "mb96348hs.h"

#include "bat.h" // Batman
//#include "fuj.h" // Fujitsu Logo
//#include "hund.h" // Hund

const char DEC7SEG[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
// definitions to increase readability
#define LCD_PORT_DB		PDR01
#define LCD_PIN_DI		PDR02_P0
#define LCD_PIN_RW		PDR02_P1
#define LCD_PIN_E		PDR02_P2
#define LCD_PIN_CS1		PDR02_P3
#define LCD_PIN_CS2		PDR02_P4
#define LCD_PIN_RESET	PDR02_P5
// LCD parameter
#define LCD_T			10l
#define LCD_WIDTH		128
#define LCD_HEIGHT		64

unsigned char lcd_buffer[128][8];

/* your functions here */
int getADCValue(int channel) {
	int result;
	ADSR = 0x6C00 + (channel << 5) + channel;	// start and end channel is channelNumber
	ADCS_STRT = 1;								// start A/D conversion
	while(ADCS_INT == 0) {} 					// wait for conversion to finish
	result = ADCRL;								// store result (1 byte)
	ADCRL = 0;									// set bit to 0 for next conversion
	return result;
}

// init A/D converter
void initADC(void) {
	ADCS_MD = 3; 		// ADC Stop Mode
	ADCS_S10 = 1;		// 8 Bit Precision
	ADER0_ADE1 = 1;		// Activate analog input AN1 + AN2
	ADER0_ADE2 = 1;		// (ADER0: Inputs AN0 - AN7)
}


// init I/O-ports
void initIO(void) {
	PDR00  = 0xff;
	DDR00  = 0xff;		// set port00 as output (right seven-segment display)
	PDR09  = 0xff;
	DDR09  = 0xff;		// set port09 as output (left seven-segment display)
	PDR07  = 0x00;
	DDR07  = 0xfc;		// set P07_0 and P07_1 as input (buttons) - 0xfc = 11111100 (bin)
	PIER07 = 0x03;		// enable input - 0x03 = 00000011 (bin)
}

// init LCD
void initLCD(void) {
	PDR01 = 0x00;
	DDR01 = 0xff;
	PDR02 = 0x00;
	DDR02 = 0xff;
	LCD_PIN_RESET = 1;	// RESET must be OFF (1)
	LCD_PIN_RW = 0;		// write always
}

void wait(long d)
{
	while(d--) {
		__wait_nop();
	}

	return;
}

void LCDenable(void)
{
	LCD_PIN_E = 1;
	wait(LCD_T);
	LCD_PIN_E = 0;
	wait(LCD_T);

	return;
}

void LCDcommand(char command)
{
	LCD_PORT_DB = command;
	LCD_PIN_DI = 0;
	LCD_PIN_RW = 0;

	LCDenable();

	return;
}

void LCDdata(char data)
{
	LCD_PORT_DB = data;
	LCD_PIN_DI = 1;
	LCD_PIN_RW = 0;

	LCDenable();

	return;
}

void LCDsetX(int x)
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

void LCDsetY(int y)
{
	LCD_PIN_CS1 = 1;
	LCD_PIN_CS2 = 1;

	y = (y & ((1 << 3) - 1));
	LCDcommand((1 << 7) | (1 << 5) | (1 << 4) | (1 << 3) | y);

	return;
}

void lcd_clear(void) {
	int x, y;

	for(x = 0; x < LCD_WIDTH; x++) {
		for(y = 0; y < LCD_HEIGHT; y++) {
			lcd_buffer[x][y] = 0;
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

void lcd_drawPixel(int x,int y, int black) {
	if(black) {
		lcd_buffer[x][y / 8] |= 1 << (y % 8);
	} else {
		lcd_buffer[x][y / 8] &= ~(1 << (y % 8));
	}

	return;
}

void main(void) {
	int x, y, a1, a2;
	
	// init buttons and seven-segment displays
	initIO();
	initADC();
	// init LCD
	initLCD();
	LCD_PIN_CS1 = 1;
	LCD_PIN_CS2 = 1;
	LCDcommand((1 << 6) - 1);
	// reset buffer at startup
	lcd_clear();
	
	while(1) {
		lcd_clear();


		for(x = 0; x < 128; x++) {
			for(y = 0; y < 64; y++) {
				lcd_drawPixel(x, y, header_data[y * 128 + x] - 1);
			}
		}

		a1 = getADCValue(1) / 3;
		a2 = getADCValue(2) / 3;
		if(a1 > 64) {
			a1 = 64;
		}
		if(a2 > 64) {
			a2 = 64;
		}

		for(x = 0; x < a2; x++) {
			for(y = 0; y < 64; y++) {
				lcd_drawPixel(x, y, 1);
			}
		}
		for(x = 0; x < a1; x++) {
			for(y = 0; y < 64; y++) {
				lcd_drawPixel(128 - x, y, 1);
			}
		}

		lcd_flush();
	}
	
	for (;;) {
		__wait_nop();
	}
}
