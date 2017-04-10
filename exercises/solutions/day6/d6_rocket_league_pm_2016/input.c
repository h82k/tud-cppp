#include "input.h"

int buttonDown[2];
int buttonPressed[2];

void input_init(void)
{
	// Initialize buttons
	PDR07  = 0x00;
	DDR07  = 0xfc;		// set P07_0 and P07_1 as input (buttons) - 0xfc = 11111100 (bin)
	PIER07 = 0x03;		// enable input - 0x03 = 00000011 (bin)
	
	memset(buttonDown, 0, sizeof(buttonDown));
	memset(buttonPressed, 0, sizeof(buttonPressed));
	
	// Initialize analog input
	ADCS_MD = 3; 		// ADC Stop Mode
	ADCS_S10 = 1;		// 8 Bit Precision
	ADER0_ADE1 = 1;		// Activate analog input AN1 + AN2
	ADER0_ADE2 = 1;		// (ADER0: Inputs AN0 - AN7)
}

void input_update(void)
{
	int leftButtonDown, rightButtonDown;

	leftButtonDown = !PDR07_P0;
	rightButtonDown = !PDR07_P1;
	
	buttonPressed[0] = leftButtonDown && !buttonDown[0];
	buttonPressed[1] = rightButtonDown && !buttonDown[1];
	
	buttonDown[0] = leftButtonDown;
	buttonDown[1] = rightButtonDown;
}

int input_button_pressed(int index)
{
	return buttonPressed[index];
}

int input_button_down(int index)
{
	return buttonDown[index];
}

float input_get_analog(int index)
{
	int result;
	int analogIndex = index == 0 ? 2 : 1;
	
	ADSR = 0x6C00 + (analogIndex << 5) + analogIndex;		// start and end channel is channelNumber
	ADCS_STRT = 1;								// start A/D conversion
	while(ADCS_INT == 0) {} 					// wait for conversion to finish
	result = ADCRL;								// store result (1 byte)
	ADCRL = 0;									// set bit to 0 for next conversion
	
	if(index == 0)
	{
		result = -result;
	}
	
	return 2.0f * (result / 255.0f - 0.5f);
}