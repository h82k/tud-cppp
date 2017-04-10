/**
 * Debug.c is used for the verification of a new development plattform
 */

#include "debug.h"

void debugPeripherie(){
      setCursor(480,320);
      char freeSpace[] = " ";
      char headlineText[] = "      DEBUG";
      writeTextln(freeSpace);
      writeTextln(freeSpace);
      writeTextln(freeSpace);
      writeTextln(headlineText);
      writeTextln(freeSpace);
      uint16_t touchX, touchY, touchZ;

      //fillScreen(BLACK);
      touchX = readTouchX();
      touchY = readTouchY();
      touchZ = readTouchZ();
      char touchXText[] = "      Touch X: ";
      char touchYText[] = "      Touch Y: ";
      char touchZText[] = "      Touch Z: ";
      writeText(touchXText);
      write3Digits16Bit(&touchX);
      writeText(touchYText);
      write3Digits16Bit(&touchY);
      writeText(touchZText);
      write3Digits16Bit(&touchZ);
      
      char JS1XText[] = "      Joystick 1 X-Achse: ";
      char JS1YText[] = "      Joystick 1 Y-Achse: ";
      writeText(JS1XText);
      write3Digits8Bit( &analog19);
      writeText(JS1YText);
      write3Digits8Bit( &analog16);
  
      char JS2XText[] = "      Joystick 2 X-Achse: ";
      char JS2YText[] = "      Joystick 2 Y-Achse: ";
      writeText(JS2XText);
      write3Digits8Bit( &analog23);
      writeText(JS2YText);
      write3Digits8Bit( &analog13);
}