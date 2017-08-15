//
//  pins.h
//  Makros for the MCU pins
//
//  @author Puria Izady
//
//

#ifndef pins_h
#define pins_h

#define LCD_DATA FM4_GPIO->PDOR1  // LCD_DATA


#define LCD_DATA_IO FM4_GPIO->DDR1 // LCD_DATA_IO

#define LCD_RD   FM4_GPIO->PDOR4_f.P1  // LCD_RD => P41
#define LCD_WR   FM4_GPIO->PDORF_f.P0  // LCD_WR => PF0
#define LCD_CD   FM4_GPIO->PDORF_f.P1  // LCD_CD => PF1    
#define LCD_CS   FM4_GPIO->PDOR7_f.PD  // LCD_CS => P7D
#define LCD_RS   FM4_GPIO->PDOR4_f.P0  // LCD_RS => P40

#define LCD_RD_IO   FM4_GPIO->DDR4_f.P1  // LCD_RD => P41
#define LCD_WR_IO   FM4_GPIO->DDRF_f.P0  // LCD_WR => PF0    
#define LCD_CD_IO   FM4_GPIO->DDRF_f.P1  // LCD_CD => PF1
#define LCD_CS_IO   FM4_GPIO->DDR7_f.PD  // LCD_CS => P7D
#define LCD_RS_IO   FM4_GPIO->DDR4_f.P0  // LCD_RS => P40

// TOUCH SIGNALE LCD
#define TOUCH_XM    FM4_GPIO->PDOR1_f.PB // TOUCH_XM => P1B / A11
#define TOUCH_XP    FM4_GPIO->PDOR7_f.PB // TOUCH_XP => P7B
#define TOUCH_YM    FM4_GPIO->PDORF_f.P6 // TOUCH_YM => PF6
#define TOUCH_YP    FM4_GPIO->PDOR1_f.PC // TOUCH_YP => P1C / A12

#define TOUCH_XM_IO FM4_GPIO->DDR1_f.PB  // TOUCH_XM => P1B / A11
#define TOUCH_XP_IO FM4_GPIO->DDR7_f.PB  // TOUCH_XP => P7B 
#define TOUCH_YM_IO FM4_GPIO->DDRF_f.P6  // TOUCH_YM => PF6
#define TOUCH_YP_IO FM4_GPIO->DDR1_f.PC  // TOUCH_YP => P1C / A12

// JOYSTICK PINS
#define JS1_X_IO    FM4_GPIO->DDRB_f.P0 // A16
#define JS1_Y_IO    FM4_GPIO->DDRB_f.P3 // A19
#define JS2_X_IO    FM4_GPIO->DDR1_f.PD // A13 
#define JS2_Y_IO    FM4_GPIO->DDRB_f.P7 // A23

#define JS1_X    FM4_GPIO->PDORB_f.P0 // JS1_X => PB0
#define JS1_Y    FM4_GPIO->PDORB_f.P3 // JS1_Y => PB3
#define JS2_X    FM4_GPIO->PDOR1_f.PD // JS2_X => P1D
#define JS2_Y    FM4_GPIO->PDORB_f.P7 // JS2_Y => PB7

// DHT11 Pin
#define DHT11_SIGNAL_OUT     FM4_GPIO->PDORF_f.P7   // PF7 PIN 75
#define DHT11_SIGNAL_IO  FM4_GPIO->DDRF_f.P7        // PF7 PIN 75
#define DHT11_SIGNAL_IN  FM4_GPIO->PDIRF_f.P7       // PF7 PIN 75

#endif /* pins_h */
