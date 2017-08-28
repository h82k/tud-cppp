#include "joystick.h"

#include <stdint.h>
#include "s6e2ccxj.h"
#include "analog.h"


void controlLedsInit(){
  // Turn off analog Pins
  
  
  // Define Pins as outputs
  
  
  // Turn all LEDs down

}

void controlLeds(){
  // Get analog values
  
  // green => Pin104 PB2/A18    blue => Pin106 P18/A08     red => Pin108 P1A/A10
  // JS1X is analog16
  
  // left: JS1 X < 255 && >= 200   => green
  // middle: JS1 X < 200 && >= 180  => blue
  // right: JS1 X <180 && >= 0      => red
  
  // Joystick left
    // green on
    // blue off
    // red off
  
  // Joystick middle
    // green off
    // blue on
    // red off
  
  // Joystick right
    // green off
    // blue off
    // red on
  
  // delay 0,01s
}

void printValues(){
  // Get analog values
  // Read and print all analog values of the system
  
  // Set cursor of the display to (480,320)
  
  
  // Write one linebreak then the headline, afterwards 4 linebreaks
  
  
  
  // Write analog values of joystick 1
  
  // Write analog values of joystick 2
}
