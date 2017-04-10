/**
 * Author: Laurenz Kamp
 * Created: 10.09.2015
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

void initLCD(void);

void lcd_clear(void);
void lcd_setall(void);
void lcd_flush(void);
void lcd_drawPixel(int x, int y, char black);

#endif /* DISPLAY_H_ */
