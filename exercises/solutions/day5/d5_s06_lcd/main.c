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
#define LCD_WIDTH		128
#define LCD_HEIGHT		64

unsigned char lcd_buffer[128][8];
unsigned char (*lcd_activeBuffer)[LCD_HEIGHT / 8] = lcd_buffer;

enum {LEFT, RIGHT} side;

// wait a specified amount of cycles
void wait(long cycle) {
	long i;
	for (i = 0; i < cycle; ++i) {
		__wait_nop();
	}
}

// trigger lcd read
void lcd_sendEnable(void) {
	wait(LCD_T);
	LCD_PIN_E = 1;
	wait(LCD_T);
	LCD_PIN_E = 0;
	wait(LCD_T);
}

// clear lcd buffer (disable all pixels in the buffer)
void lcd_clear(void) {
	int x, y;
	for (x = 0; x < LCD_WIDTH; ++x) {
		for (y = 0; y < 8; ++y) {
			lcd_buffer[x][y] = 0;
		}
	}
}

// flush the content of the buffer to the lcd
void lcd_flush(void) {
	int x, y, offsetx;
	side = LEFT;
	for (side = LEFT; side <= RIGHT; ++side) {
		// side
		LCD_PIN_CS1 = (side == LEFT) ? 1 : 0;
		LCD_PIN_CS2 = (side == RIGHT) ? 1 : 0;
		offsetx = (side == LEFT) ? 0 : 64;
		// note that x and y are the LCD ones here!
		for (y = 0; y < 8; ++y) {
			// send y address
			LCD_PIN_DI  = 0;
			LCD_PORT_DB = 0xB8 + y;
			lcd_sendEnable();
			// send x address
			LCD_PIN_DI  = 0;
			LCD_PORT_DB = 0x40;
			lcd_sendEnable();
			for (x = offsetx; x < offsetx + 64; ++x) {
				// send data
				LCD_PIN_DI  = 1;
				LCD_PORT_DB = lcd_activeBuffer[x][y];
				lcd_sendEnable();
			}
		}
		// set display to ON
		LCD_PIN_DI  = 0;
		LCD_PORT_DB = 0x3F;
		lcd_sendEnable();
	}
	// reset buffer pointer
	lcd_activeBuffer = lcd_buffer;
}

// set or delete one specific pixel in the lcd buffer array
void lcd_drawPixel(int x,int y, int z) {
	unsigned char old = lcd_buffer[x][y / 8];
	if (x >= 0 && x < LCD_WIDTH && y >= 0 && y < LCD_HEIGHT) {
		// cursor at valid position, write pixel
		if (z) {
			// set
			lcd_buffer[x][y / 8] = old | (1 << (y % 8));
		} else {
			// delete
			lcd_buffer[x][y / 8] = old & (~(1 << (y % 8)));
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
	int x, y;
	
	// init buttons and seven-segment displays
	initIO();
	// init LCD
	initLCD();
	// reset buffer at startup
	lcd_clear();
	
	// draw chess pattern
	for (x = 0; x < 128; x++) {
		for (y = 0; y < 64; y++) {
			lcd_drawPixel(x, y, ((x/4) + (y/4)) % 2);
		}
	}
	// push the newly generated data to the lcd
	lcd_flush();
	
	for (;;) {
		__wait_nop();
	}
}
