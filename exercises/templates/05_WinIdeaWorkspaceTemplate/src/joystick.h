#ifndef JOYSTICK_H
#define JOYSTICK_H

/**
 *  Initializes the wires of the joysticks.
 */
void controlLedsInit();
void controlLedsInit_s();

/**
 *  Controlls the color of the rgb-led with the x-axis of joystick 1.
 */
void controlLeds();
void controlLeds_s();


/**
 *  Prints the analog values of joystick 1 and 2 on the display.
 *
 * Code sample:
   while(1) {
     printValues_s();
     microDelay(100000);
   }
 */
void printValues();
void printValues_s();

#endif
