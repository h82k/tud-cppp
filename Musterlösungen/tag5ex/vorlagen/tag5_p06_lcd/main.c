#include "mb96348hs.h"

const char DEC7SEG[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};

#define LCD_PORT_DB     PDR01
#define LCD_PIN_DI      PDR02_P0
#define LCD_PIN_RW      PDR02_P1
#define LCD_PIN_E       PDR02_P2
#define LCD_PIN_CS1     PDR02_P3
#define LCD_PIN_CS2     PDR02_P4
#define LCD_PIN_RESET   PDR02_P5

#define LCD_T 10l
#define LCD_WIDTH 128
#define LCD_HEIGHT 64

unsigned char lcd_buffer[128][8];



/* your functions here */
void lcd_clear(void) {

}

void lcd_flush(void) {

}

void lcd_drawPixel(int x,int y, int z) {

}


void main(void) {
	int x = 0, y = 0;
	
	
	
	// initialize I/O-ports
	PDR00  = 0xff;
	DDR00  = 0xff;		// Set Port00 as output (right 7Segment display)
	PDR09  = 0xff;
	DDR09  = 0xff;		// Set Port09 as output (left 7Segment display)
	
	PDR07  = 0x00;
	DDR07  = 0xfc;		// Set P07_0 and P07_1 as input (buttons)
							// 0xfc = 11111100 (bin)
	PIER07 = 0x03;		// enable input
							// 0x03 = 00000011 (bin)
	
	// initialize LCD
	PDR01 = 0x00;
	DDR01 = 0xff;
	PDR02 = 0x00;
	DDR02 = 0xff;
	LCD_PIN_RESET = 1;	// RESET must be OFF (1)
	LCD_PIN_RW    = 0;	// write always
	
	
	
	lcd_clear();
	
	for (x = 0; x < 128; x++) {
		for (y = 0; y < 64; y++) {
			lcd_drawPixel(x, y, ((x/4) + (y/4)) % 2);
		}
	}
	
	lcd_flush();
	
	
	
	for (;;) {
		__wait_nop();
	}
	
}
