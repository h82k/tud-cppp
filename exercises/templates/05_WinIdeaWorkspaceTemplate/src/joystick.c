#include "joystick.h"

#include <stdint.h>
#include "s6e2ccxj.h"
#include "analog.h"


void controlLedsInit(){
  // turn off analog Pins
  
  
  // Define Pins as outputs
  
  
  // turn all LEDs down

}

void controlLeds(){
  // get analog values 
  
  // green => Pin104 PB2/A18    blue => Pin106 P18/A08     red => Pin108 P1A/A10
  // JS1X is analog19
  
  // left: JS1 X < 255 und >= 200   => green
  // middle: JS1 X < 200 && >= 180  => blue
  // right: JS1 X <180 && >= 0      => red
  
  // joystick left
   // green on
   // blue off
   // red off
  
  // joystick middle
    // green off
    // blue on
    // red off
  
  // joystick right
    // green off
    // blue off
    // red on
  
  // delay 0,01s
}

void printValues(){
  // get analog valuess
  // Read and print all analog values of the system
  
  // set cursor of the display to (480,320)
  
  
  // write one linebreak then the headline, afterwards 4 linebreaks
  
  
  
  // write analog values of joystick 1
  
  // write analog values of joystick 2
}
