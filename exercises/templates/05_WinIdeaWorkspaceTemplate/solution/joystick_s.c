#include "joystick_s.h"

#include <stdint.h>
#include "s6e2ccxj.h"
#include "analog.h"

void newLEDinit(){
  volatile uint32_t *redLEDDirectionPort = &(FM4_GPIO->DDR1);
  volatile uint32_t *redLEDValuePort = &(FM4_GPIO->PDOR1);
  volatile uint32_t *greenLEDDirectionPort = &(FM4_GPIO->DDRB);
  volatile uint32_t *greenLEDValuePort = &(FM4_GPIO->PDORB);
  volatile uint32_t *blueLEDDirectionPort = &(FM4_GPIO->DDR1);
  volatile uint32_t *blueLEDValuePort = &(FM4_GPIO->PDOR1);
  
	
  bFM4_GPIO_ADE_AN10 = 0; // Disable analog-digital channel 10
  *redLEDDirectionPort |= 0x0400; // Configure Port 1 Pin 10 as output pin
  *redLEDValuePort |= 0x0400; // Switch LED off
  
  bFM4_GPIO_ADE_AN18 = 0; // Disable analog-digital channel 18
  *greenLEDDirectionPort |= 0x0004; // Configure Port B Pin 2 as output pin
  *greenLEDValuePort |= 0x0004; // Switch LED off
  
  bFM4_GPIO_ADE_AN08 = 0; // Disable analog-digital channel 08
  *blueLEDDirectionPort |= 0x0100; // Configure Port 1 Pin 8 as output pin
  *blueLEDValuePort |= 0x0100; // Switch LED off
  
	const uint32_t sleepTime = 1000000;
	// Main loop. Color order: red, green, blue
	//while (1) {
    
		// Set Port 1 Pin 8 -> Switch blue LED off
    *blueLEDValuePort |= 0x0100;
    // Clear Port 1 Pin 10 -> Switch red LED on
    *redLEDValuePort &= 0xFBFF;
    
    microDelay(sleepTime);
    
    // Set Port 1 Pin 10 -> Switch red LED off
    *redLEDValuePort |= 0x0400; // Switch LED off
    // Clear Port B Pin 2 -> Switch green LED off
    *greenLEDValuePort &= 0xFFFB;
    
    microDelay(sleepTime);
    
    // Set Port B Pin 2 -> Switch green LED off
    *greenLEDValuePort |= 0x0004;
		// Clear Port 1 Pin 8 -> Switch blue LED on
    *blueLEDValuePort &= 0xFEFF; 
    
    microDelay(sleepTime); 
    
  //}
}

void controllLEDsInit(){
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

void controllLEDs(){
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

void printValues(){
    
    getAnalogValues(&analog11, &analog12, &analog13, &analog16, &analog17, &analog19, &analog23);
    // Read and print all analog values of the system
    
    setCursor(480,320);       // set cursor of the display
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
