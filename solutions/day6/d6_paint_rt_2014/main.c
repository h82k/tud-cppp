/**
 * Author: Ralf Turzer
 * Created: 11.09.2014
 */

#include "mb96348hs.h"
#include "lcd.h"
#include "adc.h"
#include "seg.h"

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

void wait(long w) // wait for w cycles
{
	long i;
	for(i=0; i<w; i++)
	{
		__wait_nop();
	}
}

char readChannel(int i)
{
	char result;
	ADSR = 0x6C00 + (i << 5) + i; // Start- und End-Kanal i
	ADCS_STRT = 1; // A/D-Wandler starten
	while (ADCS_INT == 0) { } // Warten bis A/D-Wandlung beendet
	result = ADCRL; // Ergebnis speichern
	ADCS_INT = 0; // Bit auf 0 fr nchste Wandlung
	
	return result;
}

void main(void)
{
	int schreiben = 1;  //(wahr/falsch)
	char storeRight = 0;  //speicher fr rechten knopf
	char storeLeft = 0;  //speicher fr linken knopf
	//cursor-position
	char xPos;
	char yPos;
	int type = 0;  //pinseltyp
	
	// initialize I/O-ports
	PDR00  = 0xff;
	DDR00  = 0xff;		// set port00 as output (right seven-segment display)
	PDR09  = 0xff;
	DDR09  = 0xff;		// set port09 as output (left seven-segment display)
	PDR07  = 0x00;
	DDR07  = 0xfc;		// set P07_0 and P07_1 as input (buttons) - 0xfc = 11111100 (bin)
	PIER07 = 0x03;		// enable input - 0x03 = 00000011 (bin)
	
	// initialize A/D converter
	adc_init();
	// initialize lcd
	lcd_init();
	// initialize 7seg
	seg_init();
	
	for (;;)
	{
		xPos = 127 - (adc_getValue(2)*127)/255;
		yPos = 63 - (adc_getValue(1)*63)/255;
		
		if(schreiben)
		{
			switch(type)
			{
			case 0: lcd_drawPixel(xPos, yPos, 1); break;
			case 1: lcd_drawCircle(xPos, yPos, 2, 1, 1); break;
			case 2: lcd_drawRect(xPos, yPos, 3, 3, 1, 1); break;
			default: break;
			}
		}
		
		if((storeRight != 0) && (PDR07_P1 == 0))
		{
			if(type<2)
			{
				type++;
			}
			else type = 0;
		}
		if((storeLeft != 0) && (PDR07_P0 == 0) && (schreiben == 1))
		{
			schreiben = 0;
		
		}
		else if((storeLeft != 0) && (PDR07_P0 == 0) && (schreiben == 0))
		{
			schreiben = 1;
		}
		storeRight = PDR07_P1;
		storeLeft = PDR07_P0;
		lcd_flush();
		seg_numRight(type);
		
		wait(255);
	}
}
