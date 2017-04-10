#ifndef __DISPLAY_H__
#define __DISPLAY_H__

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
#define LCD_T			20l
#define LCD_WIDTH		128
#define LCD_HEIGHT		64

void display_init(void);
void display_clear(void);
void display_drawPixel(int x, int y, char on);
void display_flush(void);

void display_drawCircle(int x, int y, int radius);

#endif // __DISPLAY_H__