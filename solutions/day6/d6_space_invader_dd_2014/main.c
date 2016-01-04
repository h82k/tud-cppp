/**
 * Author: David Dahlem
 * Created: 11.09.2014
 */

#include "mb96348hs.h"
#include "util.h"
#include "font.h"

const char DEC7SEG[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};

#define LCD_PORT_DB     PDR01
#define LCD_PIN_DI      PDR02_P0
#define LCD_PIN_RW      PDR02_P1
#define LCD_PIN_E       PDR02_P2
#define LCD_PIN_CS1     PDR02_P3
#define LCD_PIN_CS2     PDR02_P4
#define LCD_PIN_RESET   PDR02_P5

#define LCD_T 50l
#define LCD_WIDTH 128
#define LCD_HEIGHT 64

unsigned char lcd_buffer[128][8];
unsigned char meteorit_layer[128][8];	//Enthaelt nur den Meteoritenschauer.
unsigned char player_layer[128][8];		//Enthaelt nur den Spieler
char playerPos;
char potPos;
char meteoritSpeed = 2;
char lives = 3;
int meteoritCounter = 0;
int score;

void lcd_sendEnable(void) {
	int i;
	LCD_PIN_E = 1;
	for(i=0; i<LCD_T;i++){
		__wait_nop();
	}
	LCD_PIN_E = 0;
}

void on(void) {
	LCD_PIN_DI = 0;
	LCD_PORT_DB = 0x3f;
	lcd_sendEnable(); //Daten senden
}

void lcd_drawPixel(int x,int y, int black) { //y ist hier keine Zeilenadresse sondern absolut!
	int line = y/8;
	int pos = y%8;
	char cell = lcd_buffer[x][line]; //alte Zelle laden
	
	if(black) {
		cell |= (1 << pos);		//neue Zelldaten, wenn schwarz
	}
	else {
		cell &=~ (1 << pos);	//neue Zelldaten, wenn weiss
	}
	lcd_buffer[x][line] = cell;
}

void player_drawPixel(int x,int y, int black) { //y ist hier keine Zeilenadresse sondern absolut!
	int line = y/8;
	int pos = y%8;
	char cell = player_layer[x][line]; //alte Zelle laden
	
	if(black) {
		cell |= (1 << pos);		//neue Zelldaten, wenn schwarz
	}
	else {
		cell &=~ (1 << pos);	//neue Zelldaten, wenn weiss
	}
	
	player_layer[x][line] = cell;
}

void lcd_flush(void) {
	int line;
	int x;
	//Erst linke Haelfte zeilenweise flushen
	
	LCD_PIN_CS1 = 1; //Linke Displayhaelfte ansteuern
	LCD_PIN_CS2 = 0;
	on();
	for(line=0; line<8; line++) {
		//x auf 0 setzen, wird dann automatisch hoch gezaehlt
		LCD_PIN_DI = 0;
		LCD_PORT_DB = 0x40;
		lcd_sendEnable();
		
		//Zeilenadresse senden
		LCD_PIN_DI = 0;
		LCD_PORT_DB = 0xb8;  //DB=10111...
		LCD_PORT_DB |= line; //Zeilenadresse in DB 2 bis DB0 schreiben;
		lcd_sendEnable(); //Daten senden
		
		//Zeichen einer Zeile schreiben
		for(x=0; x<64; x++) {
			LCD_PIN_DI = 1;
			LCD_PORT_DB = lcd_buffer[x][line];
			lcd_sendEnable();
		}
	}
	
	//Dann rechte Haelfte zeilenweise flushen
	LCD_PIN_CS1 = 0;
	LCD_PIN_CS2 = 1; //Rechte Displayhaelfte ansteuern
	on();
	for(line=0; line<8; line++) {
		//x auf 0 setzen, wird dann automatisch hoch gezaehlt
		LCD_PIN_DI = 0;
		LCD_PORT_DB = 0x40;
		lcd_sendEnable();
		
		//Zeilenadresse senden
		LCD_PIN_DI = 0;
		LCD_PORT_DB = 0xb8;  //DB=10111...
		LCD_PORT_DB |= line; //Zeilenadresse in DB 2 bis DB0 schreiben;
		lcd_sendEnable(); //Daten senden
		
		//Zeichen einer Zeile schreiben
		for(x=64; x<128; x++) {
			LCD_PIN_DI = 1;
			LCD_PORT_DB = lcd_buffer[x][line];
			lcd_sendEnable();
		}
	}
}

void lcd_clear(void) {
	int x;
	int y;
	
	for(x=0; x<128; x++) {
		for(y=0; y<8; y++) {
			lcd_buffer[x][y] = 0x00;
		}
	}
	//lcd_flush();
}

void meteorit_clear(void) {
	int x;
	int y;
	
	for(x=0; x<128; x++) {
		for(y=0; y<8; y++) {
			meteorit_layer[x][y] = 0x00;
		}
	}
	//lcd_flush();
}

void initAdc(void) {
	ADCS_MD = 3; // ADC Stop Modus
	ADCS_S10 = 1; // 8 Bit Genauigkeit
	ADER0_ADE1 = 1; // Analoge Eingaenge aktivieren: AN1 + AN2
	//ADER0_ADE2 = 1;
}

//Gibt die Position des ersten Schiebereglers zwischen 0 und 255 zurueck
char getPotPos(void) {
	char result;
	ADSR = 0x6C00 + (1 << 5) + 1; // Startkanal=1; Endkanal=1;
	ADCS_STRT = 1; // A/D-Wandler starten
	while (ADCS_INT == 0) { } // Warten bis A/D-Wandlung beendet
	result = ADCRL; // Ergebnis speichern
	ADCS_INT = 0; // Bit auf 0 fuer naechste Wandlung
	return result;
}

void player_clear(void) {
	int x;
	int y;

	for(x=1; x<4; x++) {
		for(y=0; y<8; y++) {
			player_layer[x][y] = 0x00;
		}
	}
	//lcd_flush();
}

void drawPlayer(void) {
	player_clear();
	player_drawPixel(1, playerPos, 1);
	player_drawPixel(1, playerPos+1, 1);
	player_drawPixel(1, playerPos-1, 1);
	player_drawPixel(2, playerPos, 1);
	player_drawPixel(2, playerPos + 1, 1);
	player_drawPixel(2, playerPos - 1, 1);
	player_drawPixel(3, playerPos, 1);
	player_drawPixel(3, playerPos + 1, 0);
	player_drawPixel(3, playerPos - 1, 0);
}

void generateNewMeteorit(void) {
	unsigned long rand;
	static int lastGeneration = 0;
	
	rand =  random() / 536870912;
	
	if(lastGeneration==6) {
		meteorit_layer[127][rand] = 0xff;
		lastGeneration = 0;
		meteoritCounter++;
	}
	else {
		lastGeneration++;
	}
}

void moveMeteorits(void) {
	unsigned char x, l;
	static int lastMove = 0; //Speichern, wann Meteoriten das letzte mal bewegt werden, da dies nicht bei jedem aufruf geschehen soll
	//Wenn mal wieder ne Bewegung faellig ist
	if(lastMove==meteoritSpeed) {
		for(x=0; x<128; x++) {
			for(l=0; l<8;l++) {
				meteorit_layer[x][l] = meteorit_layer[x+1][l];
			}
		}
		lastMove=0;
	}
	else {
		lastMove++;
	}
}

void generateFinalOutputBuffer(void) {
	unsigned char x, l;
	for(x=0; x<128; x++) {
		for(l=0; l<8;l++) {
			lcd_buffer[x][l] = meteorit_layer[x][l] | player_layer[x][l];
		}
	}
}

char collusionDetected(void) {
	unsigned char x, l;
	for(x=0; x<4; x++) {
		for(l=0; l<8;l++) {
			if(meteorit_layer[x][l] & player_layer[x][l]) { //Collusion detected!!
				return 1;
			}
		}
	}
	return 0;
}

/*
void addText(void) {
	int x;
	int l;
	for(x=120; x<128; x++) {
		for(l=0; l<8; l++) {
			lcd_buffer[x][l] = 0x00;
		}
	}
	uint8_t c= font_getChar('A', FONTNANOELEMENTS);
	for(i=0; i<4; i++) {
		lcd_drawPixel()
	}
}
*/

void printLives() {
	int i;
	int xPos=120;
	int yPos = 2;
	int x;
	int l;
	for(x=118; x<128; x++) {
		for(l=0; l<8; l++) {
			lcd_buffer[x][l] = 0x00;
		}
	}
	
	for(i=0; i<lives; i++) {
		yPos+=6;
		lcd_drawPixel(xPos+0, yPos+4, 0);
		lcd_drawPixel(xPos+1, yPos+4, 0);
		lcd_drawPixel(xPos+2, yPos+4, 1);
		lcd_drawPixel(xPos+3, yPos+4, 0);
		
		lcd_drawPixel(xPos+0, yPos+3, 0);
		lcd_drawPixel(xPos+1, yPos+3, 1);
		lcd_drawPixel(xPos+2, yPos+3, 1);
		lcd_drawPixel(xPos+3, yPos+3, 1);
		
		lcd_drawPixel(xPos+0, yPos+2, 1);
		lcd_drawPixel(xPos+1, yPos+2, 1);
		lcd_drawPixel(xPos+2, yPos+2, 1);
		lcd_drawPixel(xPos+3, yPos+2, 0);
		
		lcd_drawPixel(xPos+0, yPos+1, 0);
		lcd_drawPixel(xPos+1, yPos+1, 1);
		lcd_drawPixel(xPos+2, yPos+1, 1);
		lcd_drawPixel(xPos+3, yPos+1, 1);
		
		lcd_drawPixel(xPos+0, yPos+0, 0);
		lcd_drawPixel(xPos+1, yPos+0, 0);
		lcd_drawPixel(xPos+2, yPos+0, 1);
		lcd_drawPixel(xPos+3, yPos+0, 0);
	}
}

void reset(void) {
	meteorit_clear();
}

char run() {
	lcd_clear();
	
	//Zustand abfragen
	potPos = getPotPos();
	playerPos=62-potPos*62/256;

	//Display berechnen
	generateNewMeteorit();
	moveMeteorits();
	drawPlayer();

	if(collusionDetected()) {
		if(lives>0) {
			lives--;
			reset();
		}
		else {
			return 0;
		}
	}
	generateFinalOutputBuffer();
	//Leben anzeigen
	printLives();
	//Score anzeigen
	score = meteoritCounter/100;
	if(score>99) score = 99;
	PDR00 = DEC7SEG[score%10]; //Einer
	PDR09 = DEC7SEG[score/10]; //Zehner
	//Ausgabe
	lcd_flush();

	return 1;
}
void main(void) {
	int x = 0, y = 0;
	// initialize I/O-ports
	PDR00  = 0xff;
	DDR00  = 0xff;		// set port00 as output (right seven-segment display)
	PDR09  = 0xff;
	DDR09  = 0xff;		// set port09 as output (left seven-segment display)
	PDR07  = 0x00;
	DDR07  = 0xfc;		// set P07_0 and P07_1 as input (buttons) - 0xfc = 11111100 (bin)
	PIER07 = 0x03;		// enable input - 0x03 = 00000011 (bin)
	
	// initialize LCD
	PDR01 = 0x00;
	DDR01 = 0xff;
	PDR02 = 0x00;
	DDR02 = 0xff;
	LCD_PIN_RESET = 1;	// RESET must be OFF (1)
	LCD_PIN_RW = 0;		// write always
	
	random_init(); //Initialize Random Num Generator
	lcd_clear();
	
	for (x = 0; x < 128; x++) {
		for (y = 0; y < 64; y++) {
			lcd_drawPixel(x, y, ((x/4) + (y/4)) % 2);
		}
	}
	
	initAdc();
	lcd_flush();
	while(run()) {}
	
	for(;;) {
		score = meteoritCounter/100;
		if(score>99) score = 99;
		PDR00 = DEC7SEG[score%10]; //Einer
		PDR09 = DEC7SEG[score/10]; //Zehner
		delay_s(1);
		PDR00 = 0xff; //Einer
		PDR09 = 0xff; //Zehner
		delay_s(1);
		__wait_nop();
	}
}
