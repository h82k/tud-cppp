void lcd_clear();     // clear the frame buffer, setting all pixels to 0
void lcd_drawPixel(int x, int y, int black);    // set (black == 1) or clear (black == 0) a pixel in the frame buffer, do nothing, if any input parameter is invalid
void lcd_flush();    // display the frame buffer on the LCD
