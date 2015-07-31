#include "mb96348hs.h"

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

// wait a specified amount of cycles
void wait(long cycle) {
	long i;
	for (i = 0; i < cycle; ++i)
		__wait_nop();
}

// trigger lcd read
void lcd_sendEnable(void) {
	LCD_PIN_E = 1;
	wait(LCD_T);
	LCD_PIN_E = 0;
	wait(LCD_T);
}

// turn one or both parts of the on or off
// cs1 --> chip select 1 (left part)
// cs2 --> chip select 2 (right part)
void lcd_on_off(int DB0, int cs1, int cs2) {
	if (DB0)
		DB0 = 1;
	LCD_PORT_DB = 0x3E + DB0;
	if (cs1)
		LCD_PIN_CS1 = 1;
	if (cs2)
		LCD_PIN_CS2 = 1;
	lcd_sendEnable();
}

// write one byte to every cell of every activated lcd parts
void lcd_write(int data) {
	int x;
	int y;
	// reduce input to one byte (more cannot be written in one step)
	data = data % 256;
	for (x = 0; x < 8; ++x) {
		// set input to receive instructions
		LCD_PIN_DI = 0;
		// set y address
		LCD_PORT_DB = 0xB8 + y;
		lcd_sendEnable();
		// set x address;
		LCD_PORT_DB = 0x40;
		lcd_sendEnable();
		for (y = 0; y < 64; ++y) {
			// send 8 Bit (set input to receive data)
			LCD_PIN_DI = 1;
			LCD_PORT_DB = data;
			lcd_sendEnable();
		}
	}
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

void main(void) {
	// init buttons and seven-segment displays
	initIO();
	// init LCD
	initLCD();
	
	lcd_on_off(1,1,0);		// turn on the left part of the lcd
	lcd_write(0xaa);		// write the pattern 0xaa = 0b10101010
	
	for (;;) {
		__wait_nop();
	}
}
