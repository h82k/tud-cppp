#include "src/joystick.h"

#include <stdint.h>
#include "s6e2ccxj.h"
#include "analog.h"
#include "src/display.h"

void controlLedsInit_s(){
  // turn off analog Pins
  bFM4_GPIO_ADE_AN08 = 0u; // Analog 8 off
  bFM4_GPIO_ADE_AN18 = 0u; // Analog 18 off
  bFM4_GPIO_ADE_AN10 = 0u; // Analog 10 off

  // Define Pins as outputs
  FM4_GPIO->DDRB_f.P2 = 1u; // Pin 104(B2)
  FM4_GPIO->DDR1_f.P8 = 1u; // Pin 106(18)
  FM4_GPIO->DDR1_f.PA = 1u; // Pin 108(1A)
  
  // turn all LEDs down
  FM4_GPIO->PDORB_f.P2 = 1u; // green off
  FM4_GPIO->PDOR1_f.P8 = 1u; // blue off
  FM4_GPIO->PDOR1_f.PA = 1u; // red off
}

void controlLeds_s(){
  uint8_t analog11;
  uint8_t analog12;
  uint8_t analog13;
  uint8_t analog16;
  uint8_t analog19;
  uint8_t analog23;
  uint8_t analog17;
  getAnalogValues(&analog11, &analog12, &analog13, &analog16, &analog17, &analog19, &analog23);
  const uint32_t sleepTime = 10000; // 0,01s
  // green => Pin104 PB2/A18    blue => Pin106 P18/A08     red => Pin108 P1A/A10
  // JS1X is analog19
  
  // left: JS1 X < 255 und >= 200   => green
  // middle: JS1 X < 200 && >= 180  => blue
  // right: JS1 X <180 && >= 0      => red
  
  // joystick left
  if(analog19 >= 220){
      FM4_GPIO->PDORB_f.P2 = 0u; // green on
      FM4_GPIO->PDOR1_f.P8 = 1u; // blue off
      FM4_GPIO->PDOR1_f.PA = 1u; // red off
  }
  // joystick middle
  else if(analog19 < 220 && analog19 >= 180){
      FM4_GPIO->PDORB_f.P2 = 1u; // green off
      FM4_GPIO->PDOR1_f.P8 = 0u; // blue on
      FM4_GPIO->PDOR1_f.PA = 1u; // red off
  }
  // joystick right
  else if(analog19 < 180){
      FM4_GPIO->PDORB_f.P2 = 1u; // green off
      FM4_GPIO->PDOR1_f.P8 = 1u; // blue off
      FM4_GPIO->PDOR1_f.PA = 0u; // red on
  }
  microDelay(sleepTime); 
}

void printValues_s(){
  uint8_t analog11;
  uint8_t analog12;
  uint8_t analog13;
  uint8_t analog16;
  uint8_t analog19;
  uint8_t analog23;
  uint8_t analog17;
  getAnalogValues(&analog11, &analog12, &analog13, &analog16, &analog17, &analog19, &analog23);

  
  setCursor_s(480,320);       // set cursor of the display
  char freeSpace[] = " ";
  char headlineText[] = "  DEBUG";
  writeTextln_s(freeSpace);
  writeTextln_s(headlineText);
  writeTextln_s(freeSpace);
  
  //fillScreen(BLACK);
  const uint16_t touchZ = readTouchZ();
  const uint16_t touchX = touchZ != 0 ? readTouchX() : 0;
  const uint16_t touchY = touchZ != 0 ? readTouchY() : 0;
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
  write3Digits8Bit(&touchZ);
  writeTextln_s("");
  
  char JS1XText[] = "  Joystick 1 X-Achse: ";
  char JS1YText[] = "  Joystick 1 Y-Achse: ";
  writeText_s(JS1XText);
  write3Digits8Bit(&analog19);
  writeTextln_s("");
  writeText_s(JS1YText);
  write3Digits8Bit(&analog16);
  writeTextln_s("");
  
  char JS2XText[] = "  Joystick 2 X-Achse: ";
  char JS2YText[] = "  Joystick 2 Y-Achse: ";
  writeText_s(JS2XText);
  write3Digits8Bit(&analog23);
  writeTextln_s("");
  writeText_s(JS2YText);
  write3Digits8Bit(&analog13);
  writeTextln_s("");
}
