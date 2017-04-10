/**
 * Author: Jan Hohmann
 * Created: 22.10.2015
 */

#include "mb96348hs.h"
#include "5x8_vertikal_LSB_1.h"
#include "loremipsum.h"

const char DEC7SEG[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
#define DELAY 1000000l
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

char buffer[128][8] = {0};
char textBuffer[128][115] = {0};
const char COLS = 25;
const char ROWS = 115;
int lines = 0;
int curMode = 0;
char curLine = 0;

void wait(unsigned long cycles) {
  unsigned long cur = 0;
  while (++cur < cycles)
    __wait_nop();
}

void set(void) {
  wait(LCD_T);
  LCD_PIN_E = 1;
  wait(LCD_T);
  LCD_PIN_E = 0;
}

// return ADC value of the specified channel (either 1 or 2)
int getADCValue(int channel) {
  int result;
  ADSR = 0x6C00 + (channel << 5) + channel; // start and end channel is channelNumber
  ADCS_STRT = 1;                // start A/D conversion
  while(ADCS_INT == 0) {}           // wait for conversion to finish
  result = ADCRL;               // store result (1 byte)
  ADCRL = 0;                  // set bit to 0 for next conversion
  return result;
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

// init A/D converter
void initADC(void) {
	ADCS_MD = 3; 		// ADC Stop Mode
	ADCS_S10 = 1;		// 8 Bit Precision
	ADER0_ADE1 = 1;		// Activate analog input AN1 + AN2
	ADER0_ADE2 = 1;		// (ADER0: Inputs AN0 - AN7)
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

void printNumber(short num) {
  PDR00 = DEC7SEG[num%10];
  PDR09 = DEC7SEG[(num/10) % 10];
}

void drawBuffer(void) {
  char curX = 0;
  char curY = 0;
  LCD_PIN_CS1 = 1;
  LCD_PIN_CS2 = 0;
  LCD_PORT_DB = 0x01;
  set();
  do {
      LCD_PIN_DI = 0;
      LCD_PIN_RW = 0;
      LCD_PORT_DB = 0xb8 + curY;
      set();
      LCD_PORT_DB = 0x40;
      set();

      curX = 0;
      do {
        LCD_PIN_DI = 1;
        LCD_PIN_RW = 0;
        LCD_PORT_DB = buffer[curX][curY];
        set();
      } while (++curX < 64);
  } while (++curY < 8);
  LCD_PIN_DI = 0;
  LCD_PIN_RW = 0;
  LCD_PORT_DB = 0x3f;
  set();
  LCD_PIN_CS1 = 0;
  LCD_PIN_CS2 = 1;
  LCD_PORT_DB = 0x01;
  set();
  curY = 0;
  do {
      LCD_PIN_DI = 0;
      LCD_PIN_RW = 0;
      LCD_PORT_DB = 0xb8 + curY;
      set();
      LCD_PORT_DB = 0x40;
      set();

      curX = 64;
      do {
        LCD_PIN_DI = 1;
        LCD_PIN_RW = 0;
        LCD_PORT_DB = buffer[curX][curY];
        set();
      } while (++curX < 128);
  } while (++curY < 8);
  LCD_PIN_DI = 0;
  LCD_PIN_RW = 0;
  LCD_PORT_DB = 0x3f;
  set();
}

void setPixel(char x, char y, char value) {
  char tmp = 0;
  if (value)
    value = 1;
  tmp = buffer[x][(y/8)];
  tmp = tmp & ~(1<<(y&8));
  tmp = tmp | value << (y%8);
  buffer[x][y/8] = tmp;
}

void drawChar(char row, char col, char character) {
  int curCol;
  for (curCol = 0; curCol < CHARACTER_WIDTH; curCol++) {
    buffer[col+curCol][row] = font[character][curCol];
  }
}

void drawCharBuf(char row, char col, char character) {
  int curCol;
  for (curCol = 0; curCol < CHARACTER_WIDTH; curCol++) {
    textBuffer[col+curCol][row] = font[character][curCol];
  }
}

void writeString(char row, char col, char* str) {
  char offset = 0;
  for (;*str != 0; str++) {
    drawChar(row, col+offset, *str);
    offset+= CHARACTER_WIDTH;
  }
}

void itoa(int number, char* str, int precision) {
  int cnt = 0;
  for(cnt = 1; cnt <= precision; cnt++) {
    str[(precision - cnt)] = number%10 + 48;
    number = number/10;
  }
}

void writeInt(char row, char col, int number) {
  char offset = 0;
  char str[8] = {0};
  char* ptr = str;
  for (itoa(number, str, 4);*ptr != 0; ptr++) {
    drawChar(row, col+offset, *ptr);
    offset+= CHARACTER_WIDTH;
  }
}

int getWordLen(const char* text) {
  int cnt = 0;
  for (;*text != 0 && *text != 32; text++) {
    cnt++;
  }
  return cnt;
}

void writeText(const char* text) {
  char row;
  char col;
  for(row = 0; row < ROWS; row++) {
    for(col = 0; col < COLS; col++) {
      if (*text == 0) {
        lines++;
        return;
      }
      if (*text == 10) {
        text++;
        goto newline;
      }
      if (col == 0 && *text == 32) {
        text++;
        drawCharBuf(row, col*CHARACTER_WIDTH, *text);
        text++;
      } else if ((getWordLen(text) + col) < COLS) {
        drawCharBuf(row, col*CHARACTER_WIDTH, *text);
        text++;
      } else {
        break;
      }
    }
    newline:
    lines++;
  }
}

void copyBuffer(char start, char num) {
  char row = 0;
  char col;
  if (start < lines) {
    for(row = 0; row < num; row++) {
      for(col = 0; col < 128; col++) {
        buffer[col][row] = textBuffer[col][start+row];
        if ((row+start) >= lines) {
        buffer[col][row] = 0;
        }
      }
    }
  }
}
int scaleDown(int value, int target) {
  return (value * target) / 256;
}
int inverseScaleDown(int value, int target) {
  return (target - 1) - (value * target) / 256;
}

void eventloop(int count) {
  char leftButton = 1;
  char leftButtonLast = 1;
  char rightButton = 1;
  char rightButtonLast = 1;
  leftButton = PDR07_P0;
  rightButton = PDR07_P2;
  if(leftButton == 1 && leftButtonLast == 0) {
    if (curMode == 0) {
      //curLine = 0;
      curMode = 1;
      printNumber(curMode);
    }
    else {
      curMode = 0;

    }
  }
  leftButtonLast = leftButton;
  
}

void main(void) {
	/* your definitions here */
  int leftADValue = 0;
  int rightADValue = 0;
  char leftButton = 1;
  char leftButtonLast = 1;
  char rightButton = 1;
  char rightButtonLast = 1;
	
	// init buttons and seven-segment displays
	initIO();
	// init LCD
	initLCD();
	// init A/D converter
	initADC();

	
	/* your code here */
  drawBuffer();
  wait(100001);
  //setPixel(10, 10, 1);

  //writeString(5, 0, "Hallo Welt");
  writeText(LOREM);

  for(;;) {
    switch (curMode) {
      case 0:
        leftADValue = getADCValue(1);
        curLine = inverseScaleDown(leftADValue, lines);
        writeInt(7, 0, curLine+1);
        writeInt(7, 104, lines);
        copyBuffer(curLine, 7);
        drawBuffer();
    //eventloop(4);
      break;
      case 1:
        copyBuffer(curLine, 7);
        writeInt(7, 0, curLine+1);
        writeInt(7, (128 - 4*CHARACTER_WIDTH), lines);
        drawBuffer();
        curLine++;
        if(curLine > lines)
          curMode = 6;
        else
          curMode = 2;
      break;
      case 2:
        wait(DELAY/2);
        curMode = 3;
      break;
      case 3:
        wait(DELAY/2);
        curMode = 4;
      break;
      case 4:
        wait(DELAY/2);
        curMode = 5;
      break;
      case 5:
        wait(DELAY/2);
        curMode = 1;
      break;
      case 6:
        __wait_nop();
      break;
    }
  printNumber(curMode);
  leftButton = PDR07_P0;
  rightButton = PDR07_P2;
  if(leftButton == 1 && leftButtonLast == 0) {
    if (curMode == 0) {
      curLine = 0;
      curMode = 1;
    }
    else {
      curMode = 0;

    }
  }
  leftButtonLast = leftButton;
  rightButtonLast = rightButton;
		__wait_nop();
  }
}
