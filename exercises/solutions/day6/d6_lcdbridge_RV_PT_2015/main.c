/**
 * Authors: Rick Vogel, Philipp Thomasberger
 * Created: 24.09.2015
 */

#include "utils.h"

void main(void) {
	unsigned char ch, x, y, z;
	int i = 0;
	int j = 0;
	unsigned char mode = 0x00;
	unsigned char oldMode = 0x00;

	// init buttons and seven-segment displays
	initIO();
	// init LCD
	initLCD();

	// initialize I/O-ports
	PDR08 = 0x00;
	DDR08 = 0x00;
	PIER08 = 0x24;    // SIN0, SIN1 input enable

	InitUart1();      // initialize UART

	Puts1("\nUART LCD Bridge\n");   // Output welcome string

	// reset buffer at startup
	//lcd_clear();
	lcd_splash();	// loading splashscreen
	lcd_flush();

	while (1) {
		if (SSR1_RDRF != 0) {			// Wait for data received
			ch = RDR1;					// Save receive register
			if ((SSR1 & 0xE0) != 0) {	// Check for errors PE, ORE, FRE
				SCR1_CRE = 1;			// Clear error flags
			}
			else {
				switch(mode) {
				case 0x00: // idle
					if(ch == 0xAA) {		// cmd for setPixel mode
						if(oldMode == 0xBB || oldMode == 0x00) {
							lcd_clear();
							lcd_flush();
						}
						mode = 0xAA;
						i=0;
					}
					if(ch == 0xBB) {		// cmd for framebuffer mode
						mode = 0xBB;
						i=0;
						j=0;
					}
					break;

				case 0xAA: // setPixel mode
					if (i == 0) {			// x coordinate
						x = ch;
						i++;
					} else if (i == 1) {	// y coordinate
						y = ch;
						i++;
					} else if (i == 2) {	// value (1=black,0="white")
						z = ch;
						i = 0;
						lcd_drawPixelDirect(x, y, z);
						oldMode = mode;
						mode = 0x00;
					}
					break;

				case 0xBB: // framebuffer mode
					lcd_buffer[i][j] = ch;	// write current uart buffer content to framebuffer
					if(j==7) {
						i++;
						j=0;
					}
					else
						j++;

					// print received framebuffer
					if(i>=128) {
						lcd_flush();
						oldMode = mode;
						mode = 0x00;
					}
					break;
				}
				Putch1(ch);	// debug output
			}
		}
	}
}
