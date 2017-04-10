#include "display.h"

#include "util.h"

#include "mb96348hs.h"

#include "segment.h"

unsigned char lcd_buffer[128][64];

void lcd_sendEnable(void)
{
	LCD_PIN_E = 1;
	delay(LCD_T);
	LCD_PIN_E = 0;
}

/* Implementations */

void display_clear(void) 
{	
	memset(lcd_buffer, 0, sizeof(lcd_buffer));
}

void display_flush(void) 
{
	char x, y;
	
	// Draw left side
	// set display to ON
	LCD_PIN_DI  = 0;
	LCD_PORT_DB = 0x3F;
	lcd_sendEnable();
	
	LCD_PIN_CS1 = 1;
	LCD_PIN_CS2 = 0;
	lcd_sendEnable();
	
	for (y = 0; y < 8; ++y) {
		// Set Y
		LCD_PIN_DI = 0;
		LCD_PIN_RW = 0;
		LCD_PORT_DB = (23 << 3) | y;
		lcd_sendEnable();
		
		// Set X to zero
		LCD_PIN_DI = 0;
		LCD_PIN_RW = 0;
		LCD_PORT_DB = 0x40;
		lcd_sendEnable();
		
		// LCD: set y address to 'y', set x address to 0
		for (x = 0; x < 64; ++x) {
			// LCD: draw pixel -> column/x address is incremented automatically
			LCD_PIN_DI = 1;
			LCD_PIN_RW = 0;
			LCD_PORT_DB = (lcd_buffer[x][8 * y + 7] << 7) | (lcd_buffer[x][8 * y + 6] << 6) | (lcd_buffer[x][8 * y + 5] << 5)
				| (lcd_buffer[x][8 * y + 4] << 4) | (lcd_buffer[x][8 * y + 3] << 3) | (lcd_buffer[x][8 * y + 2] << 2)
				| (lcd_buffer[x][8 * y + 1] << 1) | lcd_buffer[x][8 * y];
			lcd_sendEnable();
		}
	}
	
	// Draw right side
	// set display to ON
	LCD_PIN_DI  = 0;
	LCD_PORT_DB = 0x3F;
	lcd_sendEnable();
	
	LCD_PIN_CS1 = 0;
	LCD_PIN_CS2 = 1;
	lcd_sendEnable();
	
	for (y = 0; y < 8; ++y) {
		// Set Y
		LCD_PIN_DI = 0;
		LCD_PIN_RW = 0;
		LCD_PORT_DB = (23 << 3) | y;
		lcd_sendEnable();
		
		// Set X to zero
		LCD_PIN_DI = 0;
		LCD_PIN_RW = 0;
		LCD_PORT_DB = 0x40;
		lcd_sendEnable();
		
		// LCD: set y address to 'y', set x address to 0
		for (x = 0; x < 64; ++x) {
			// LCD: draw pixel -> column/x address is incremented automatically
			LCD_PIN_DI = 1;
			LCD_PIN_RW = 0;
			LCD_PORT_DB = 
				  (lcd_buffer[x + 64][8 * y + 7] << 7) | (lcd_buffer[x + 64][8 * y + 6] << 6) | (lcd_buffer[x + 64][8 * y + 5] << 5)
				| (lcd_buffer[x + 64][8 * y + 4] << 4) | (lcd_buffer[x + 64][8 * y + 3] << 3) | (lcd_buffer[x + 64][8 * y + 2] << 2)
				| (lcd_buffer[x + 64][8 * y + 1] << 1) | lcd_buffer[x + 64][8 * y];
			lcd_sendEnable();
		}
	}
}

void display_drawPixel(int x, int y, char on) 
{
	if(x >= 0 && x < LCD_WIDTH && y >= 0 && y < LCD_HEIGHT)
	{
		lcd_buffer[x][y] = on;
	}
}

void display_drawCircle(int x, int y, int radius)
{
	display_drawPixel(x, y, 1);
	display_drawPixel(x+1, y, 1);
	display_drawPixel(x, y+1, 1);
	display_drawPixel(x-1, y, 1);
	display_drawPixel(x, y-1, 1);
	
	if(radius > 2)
	{
		display_drawPixel(x+1, y+1, 1);
		display_drawPixel(x+1, y-1, 1);
		display_drawPixel(x-1, y+1, 1);
		display_drawPixel(x-1, y-1, 1);
	}
}

// init LCD
void display_init(void) 
{
	PDR01 = 0x00;
	DDR01 = 0xff;
	PDR02 = 0x00;
	DDR02 = 0xff;
	LCD_PIN_RESET = 1;	// RESET must be OFF (1)
	LCD_PIN_RW = 0;		// write always
}
