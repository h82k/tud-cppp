//
//  pins.h
//  
//
//  Created by Puria on 12.12.16.
//
//

#ifndef pins_h
#define pins_h
// LCD Data Bit :   7    6    5    4    3    2    1    0
// Cyp port/pin :   PF3  P45  P44  PF5  P43  PF7  P1C  P1B

#define LCD_D0 FM4_GPIO->PDOR1_f.PB   // 1B
#define LCD_D1 FM4_GPIO->PDOR1_f.PC   // 1C
#define LCD_D2 FM4_GPIO->PDORF_f.P7   // F7
#define LCD_D3 FM4_GPIO->PDOR4_f.P3   // 43
#define LCD_D4 FM4_GPIO->PDORF_f.P5   // F5
#define LCD_D5 FM4_GPIO->PDOR4_f.P4   // 44
#define LCD_D6 FM4_GPIO->PDOR4_f.P5   // 45
#define LCD_D7 FM4_GPIO->PDORF_f.P3   // F3

#define LCD_D0_IO FM4_GPIO->DDR1_f.PB  // 1B
#define LCD_D1_IO FM4_GPIO->DDR1_f.PC  // 1C
#define LCD_D2_IO FM4_GPIO->DDRF_f.P7  // F7
#define LCD_D3_IO FM4_GPIO->DDR4_f.P3  // 43
#define LCD_D4_IO FM4_GPIO->DDRF_f.P5  // F5
#define LCD_D5_IO FM4_GPIO->DDR4_f.P4  // 44
#define LCD_D6_IO FM4_GPIO->DDR4_f.P5  // 45
#define LCD_D7_IO FM4_GPIO->DDRF_f.P3  // F3

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
#define TOUCH_XM    FM4_GPIO->PDOR1_f.P6 // TOUCH_XM => P16 / A6
#define TOUCH_XP    FM4_GPIO->PDOR7_f.PB // TOUCH_XP => P7B
#define TOUCH_YM    FM4_GPIO->PDORF_f.P6 // TOUCH_YM => PF6
#define TOUCH_YP    FM4_GPIO->PDOR1_f.P7 // TOUCH_YP => P17 / A7

#define TOUCH_XM_IO FM4_GPIO->DDR1_f.P6  // TOUCH_XM => P16 / A6
#define TOUCH_XP_IO FM4_GPIO->DDR7_f.PB  // TOUCH_XP => P7B 
#define TOUCH_YM_IO FM4_GPIO->DDRF_f.P6  // TOUCH_YM => PF6
#define TOUCH_YP_IO FM4_GPIO->DDR1_f.P7  // TOUCH_YP => P17 / A7

// JOYSTICK PINS
#define JS1_X_IO    FM4_GPIO->DDRB_f.P0
#define JS1_Y_IO    FM4_GPIO->DDR1_f.P4
#define JS2_X_IO    FM4_GPIO->DDR1_f.P3
#define JS2_Y_IO    FM4_GPIO->DDR1_f.P0

#endif /* pins_h */
