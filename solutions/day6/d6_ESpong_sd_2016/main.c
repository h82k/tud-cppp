#include "mb96348hs.h"
// Example include from the 16FXlib:
//#include "util.h"
#include "image.h"

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

void wait(long w){
	while(w--){
		__wait_nop();
	}
}

void lcd_sendEnable(void){
	LCD_PIN_E = 1;
	wait(LCD_T);
	LCD_PIN_E = 0;
	wait(LCD_T);
}

void lcd_clear(void) {
	int x,y;
	for(x=0;x<128;x++){
		for(y=0;y<8;y++){
			lcd_buffer[x][y]=0;
		}
	}
}

void lcd_setX(int x){
	LCD_PIN_DI = 0;
	LCD_PORT_DB = x | 0x40;
	lcd_sendEnable();
}

void lcd_setY(int y){
	LCD_PIN_DI = 0;
	LCD_PORT_DB = y | 0xB8;
	lcd_sendEnable();
}

void lcd_writeData(int data){
	LCD_PIN_DI = 1;
	LCD_PORT_DB = data;
	lcd_sendEnable();
}

void lcd_selectChip(int chip){
	if(chip){
		LCD_PIN_CS1 = 0;
		LCD_PIN_CS2 = 1;
	}else{
		LCD_PIN_CS1 = 1;
		LCD_PIN_CS2 = 0;
	}
	lcd_sendEnable();
}

void lcd_on(void){
	lcd_selectChip(0);
	LCD_PIN_DI = 0;
	LCD_PORT_DB = 0x3F;
	lcd_sendEnable();
	
	lcd_selectChip(1);
	LCD_PIN_DI = 0;
	LCD_PORT_DB = 0x3F;
	lcd_sendEnable();
}

void lcd_off(void){
	lcd_selectChip(0);
	LCD_PIN_DI = 0;
	LCD_PORT_DB = 0x3E;
	lcd_sendEnable();
	
	lcd_selectChip(1);
	LCD_PIN_DI = 0;
	LCD_PORT_DB = 0x3E;
	lcd_sendEnable();
}
void lcd_flush(void) {
	int c,x,y;
	for(c=0;c<2;c++){
		lcd_selectChip(c);
		lcd_setX(0);
		for(y=0;y<8;++y){
			lcd_setY(y);
			for(x=0+c*64;x<64+c*64;x++){
				lcd_writeData(lcd_buffer[x][y]);
			}
		}
	}
}

void lcd_drawPixel(int x, int y, int z) {
	if(x < 0 || x > 127)
		return ;
	if(y < 0 || y > 63)
		return;
	if(z){
		lcd_buffer[x][y/8]|=1 << (y%8);
	}else{
		lcd_buffer[x][y/8]&=~(1<< (y%8));
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

void splashScreen(void){
	int i;
	int x, y;
	for(i=0;i<64;i++){
		lcd_clear();
		lcd_flush();
		for (x = 0; x < 128; x++) {
			for (y = 0; y < 64; y++) {
				lcd_drawPixel(x, y-i, header_data[x+y*128]);
			}
		}
		lcd_flush();
		wait(300000l);
	}
	
	
	//wait(5000000l);
}

typedef struct {
	int x;
	int y;
}Point;


void drawBall(Point *point){
	int i,j;
	for(i=-1;i<2;i++){
		for(j=-1;j<2;j++){
			lcd_drawPixel(point->x+i, point->y+j,1);
		}
	}
}

void drawPaddle(Point *point){
	int i;
	for(i=-5;i<5;i++){
		//for(j=-1;j<2;j++){
			lcd_drawPixel(point->x, point->y+i,1);
		//}
	}
}

int getADCValue(int channel) {
	int result;
	ADSR = 0x6C00 + (channel << 5) + channel;	// start and end channel is channelNumber
	ADCS_STRT = 1;								// start A/D conversion
	while(ADCS_INT == 0) {} 					// wait for conversion to finish
	result = ADCRL;								// store result (1 byte)
	ADCRL = 0;									// set bit to 0 for next conversion
	return result;
}

void drawNumber(Point *point, int score){//one decimal
	int i,j,k=0;
	for(i=16*score;i<(16*score+16);i++){
		for(j=0;j<20;j++){
			lcd_drawPixel(point->x+k,point->y+j,number_data[i+j*160]);
		}
		k++;
	}
}

// init A/D converter
void initADC(void) {
	ADCS_MD = 3; 		// ADC Stop Mode
	ADCS_S10 = 1;		// 8 Bit Precision
	ADER0_ADE1 = 1;		// Activate analog input AN1 + AN2
	ADER0_ADE2 = 1;		// (ADER0: Inputs AN0 - AN7)
}

int isOnPaddle(int ball, int paddle){
	if(ball > paddle+5 || ball < paddle-5)
		return 0;
	return 1;
}


int gameMain(void){
	Point ball={64,32};
	Point left={0,32};
	Point right={127,32};
	Point direction={1,1};
	
	Point scoreLeft={10,40};
	Point scoreRight={100,40};
	int leftScore=0;
	int rightScore=0;
	
	for(;;){
		//lcd_off();
		lcd_clear();
		
		right.y = 63-getADCValue(1)/4;
		left.y = 63-getADCValue(2)/4;
		
		
		
		if(ball.x < 0 || ball.x > 127){
			direction.x=-direction.x;
			if(ball.x < 0){
				if(!isOnPaddle(ball.y,left.y)){
					rightScore++;
					ball.x=64;
					ball.y=32;
				}
			}
			
			if(ball.x > 127){
				if(!isOnPaddle(ball.y,right.y)){
					leftScore++;
					ball.x=64;
					ball.y=32;
				}
			}
		}
		
		if(leftScore == 10)
			return 1;
		if(rightScore ==10)
			return 2;
		
		if(ball.y < 0 || ball.y > 63){
			direction.y=-direction.y;
		}
			
		ball.x+=direction.x;
		ball.y+=direction.y;
		
		
		drawNumber(&scoreLeft,leftScore);
		drawNumber(&scoreRight,rightScore);
		
		drawBall(&ball);
		drawPaddle(&left);
		drawPaddle(&right);
		
		
		
		//lcd_on();
		lcd_flush();
		//lcd_off();
		wait(10000l);
	}
}

void drawWinnImage(int winner){
	int x, y;
	lcd_clear();
	for (x = 0; x < 128; x++) {
		for (y = 0; y < 64; y++) {
			if(winner == 1){
				//lcd_drawPixel(x, y, left_won[x+y*128]);
			}else{
				//lcd_drawPixel(x, y, left_won[x+y*128]);
				//lcd_drawPixel(x, y, right_won[x+y*128]);
			}
			
		}
	}
	lcd_flush();

	
	wait(5000000l);
}

void main(void) {
	int winner=0;
	
	//int direction = 0;
	// init buttons and seven-segment displays
	initIO();
	// init LCD
	initLCD();
	
	initADC();
	
	lcd_on();
	// reset buffer at startup
	lcd_clear();
	lcd_flush();
	
	for(;;){
		splashScreen();
		winner = gameMain();
		drawWinnImage(winner);
	}	
}
