#include "debug.h"

void initDebug(){
  // Initialize left button as input and activate pullup resistor
  BUTTON_LEFT_DDR &= ~(1 << BUTTON_LEFT_PIN);
  BUTTON_LEFT_PCR |= (1 << BUTTON_LEFT_PIN);
  
  // Initialize right button as input and activate pullup resistor
  BUTTON_RIGHT_DDR &= ~(1 << BUTTON_RIGHT_PIN);
  BUTTON_RIGHT_PCR |= (1 << BUTTON_RIGHT_PIN);
}

int isLeftJoystickButtonPressed(){
  return !(BUTTON_LEFT_DIR & (1 << BUTTON_LEFT_PIN)); 
}

int isRightJoystickButtonPressed(){
  return !(BUTTON_RIGHT_DIR & (1 << BUTTON_RIGHT_PIN)); 
}

void debugCPPPBoard(){
  uint8_t analog11;
  uint8_t analog12;
  uint8_t analog13;
  uint8_t analog16;
  uint8_t analog19;
  uint8_t analog23;
  uint8_t analog17;
  
  while(1u){
    getAnalogValues(&analog11, &analog12, &analog13, &analog16, &analog17, &analog19, &analog23);
  
    setCursor_s(480,320); 
    char freeSpace[] = " ";
    char headlineText[] = "  DEBUG";
    writeTextln_s(freeSpace);
    writeTextln_s(freeSpace);
    writeTextln_s(headlineText);
    writeTextln_s(freeSpace);
    
    // Get analog values of the touchscreen
    const uint16_t touchZ = readTouchZ();
    const uint16_t touchX = touchZ != 0 ? readTouchX() : 0;
    const uint16_t touchY = touchZ != 0 ? readTouchY() : 0;
    
    // Write x,y, and z-values on the screen
    char touchXText[] = "  Touch X: ";
    char touchYText[] = "  Touch Y: ";
    char touchZText[] = "  Touch Z: ";
    writeText_s(touchXText);
    write3Digits16Bit(&touchX);
    writeTextln_s("");
    writeText_s(touchYText);
    write3Digits16Bit(&touchY);
    writeTextln_s("");
    writeText_s(touchZText);
    write3Digits16Bit(&touchZ);
    writeTextln_s("");
    
    writeTextln_s(freeSpace);
    
    // Display joystick values
    writeText_s("  Joystick 1 X-Achse: ");
    writeNumberOnDisplayRight_s(&analog16);
    writeTextln_s("");
    writeText_s("  Joystick 1 Y-Achse: ");
    writeNumberOnDisplayRight_s(&analog19);
    writeTextln_s("");
    if(isLeftJoystickButtonPressed())
      writeText_s("  Joystick 1 Button: X"); 
    else
      writeText_s("  Joystick 1 Button:  ");
    writeTextln_s("");
    
    writeTextln_s("");
    
    writeText_s("  Joystick 2 X-Achse: ");
    writeNumberOnDisplayRight_s(&analog13);
    writeTextln_s("");
    writeText_s("  Joystick 2 Y-Achse: ");
    writeNumberOnDisplayRight_s(&analog23);
    writeTextln_s("");
    if(isRightJoystickButtonPressed())
      writeText_s("  Joystick 2 Button: X"); 
    else
      writeText_s("  Joystick 2 Button:  ");
    writeTextln_s("");
  }
}