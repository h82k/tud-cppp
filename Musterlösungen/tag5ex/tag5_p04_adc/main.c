#include "mb96348hs.h"

const char DEC7SEG[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
#define DELAY 300000l

void wait(long time) {
	long i;

	for(i = 0; i < time; i++) {
		__wait_nop();
	}
}

void SetLeft7Seg(int i) {
	if(i >= 0 && i <= 9){
		PDR09 = DEC7SEG[i];
	}
}

void SetRight7Seg(int i) {
	if(i >= 0 && i <= 9){
		PDR00 = DEC7SEG[i];
	}

}

//displays a two digit value
void Set7Seg(int i) {
	int left, right;

	right = i % 10;
	left = (i - right)/10;

	SetLeft7Seg(left);
	SetRight7Seg(right);

}

//Scale from 0-255 to 0-9
int ScaleInt(int num) {
	return (num*9)/255;
}

//returns the value for specified channel
int getADValue(int channel) {
	int result;

	ADSR = 0x6C00 + (channel << 5) + channel; 			  //Start and end channel is channelNumber
	ADCS_STRT = 1;										  //Start A/D conversion
	while(ADCS_INT == 0) {} 							  //Wait for conversion to finish
	result = ADCRL;										  //Store result (1 Byte)
	ADCRL = 0;										      //Set bit to 0 for next conversion
	return result;
}

void main(void) {
	/* definitions go here */
	int value;

	// initialize I/O-ports
	PDR00  = 0xff;
	DDR00  = 0xff;		// Set Port00 as output (right 7Segment display)
	PDR09  = 0xff;
	DDR09  = 0xff;		// Set Port09 as output (left 7Segment display)

	PDR07  = 0x00;
	DDR07  = 0xfc;		// Set P07_0 and P07_1 as input (buttons)
							// 0xfc = 11111100 (bin)
	PIER07 = 0x03;		// enable input
							// 0x03 = 00000011 (bin)

	//Initialisation of AD converter
	ADCS_MD = 3; 		//ADC Stop Mode
	ADCS_S10 = 1;		//8 Bit Precision
	ADER0_ADE1 = 1;		//Activate analog input AN1 + AN2
	ADER0_ADE2 = 1;		//(ADER0: Inputs AN0 - AN7)

	for (;;) {
		value = getADValue(1);
		SetLeft7Seg(ScaleInt(value));

		wait(5);

		value = getADValue(2);
		SetRight7Seg(ScaleInt(value));

		wait(5);

	}

}
