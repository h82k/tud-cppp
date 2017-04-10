/*******************************************************************************
* Copyright (C) 2013-2016, Cypress Semiconductor Corporation or a              *
* subsidiary of Cypress Semiconductor Corporation.  All rights reserved.       *
*                                                                              *
* This software, including source code, documentation and related              *
* materials ("Software"), is owned by Cypress Semiconductor Corporation or     *
* one of its subsidiaries ("Cypress") and is protected by and subject to       *
* worldwide patent protection (United States and foreign), United States       *
* copyright laws and international treaty provisions. Therefore, you may use   *
* this Software only as provided in the license agreement accompanying the     *
* software package from which you obtained this Software ("EULA").             *
*                                                                              *
* If no EULA applies, Cypress hereby grants you a personal, non-exclusive,     *
* non-transferable license to copy, modify, and compile the                    *
* Software source code solely for use in connection with Cypress's             *
* integrated circuit products.  Any reproduction, modification, translation,   *
* compilation, or representation of this Software except as specified          *
* above is prohibited without the express written permission of Cypress.       *
*                                                                              *
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO                         *
* WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING,                         *
* BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED                                 *
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A                              *
* PARTICULAR PURPOSE. Cypress reserves the right to make                       *
* changes to the Software without notice. Cypress does not assume any          *
* liability arising out of the application or use of the Software or any       *
* product or circuit described in the Software. Cypress does not               *
* authorize its products for use in any products where a malfunction or        *
* failure of the Cypress product may reasonably be expected to result in       *
* significant property damage, injury or death ("High Risk Product"). By       *
* including Cypress's product in a High Risk Product, the manufacturer         *
* of such system or application assumes all risk of such use and in doing      *
* so agrees to indemnify Cypress against all liability.                        *
*******************************************************************************/

/******************************************************************************/
/** \file Light_Sensor.c
 **
 ** In this file the ADC is used to read the Signals of the Touch LCD and the 2 Joysticks.
 **
 ** This example set the ADC0 channel 0 in single conversion mode and fetch
 ** the result by polling mode.
 ** Via software trigger the conversion is started.\
 ** When a completion is done, it read the result data
 **
 ******************************************************************************/

 
/******************************************************************************/
/* Global variables                                                           */
/******************************************************************************/

uint8_t u8Data = 0;        // latest ADC result - global variable for debugging
uint8_t old = 0;           // old value of scan.
uint8_t analog0 = 0u;
uint8_t analog3 = 0u;
uint8_t analog4 = 0u;
uint8_t analog6 = 0u;
uint8_t analog7 = 0u;
uint8_t analog16 = 0u;
uint8_t analog17 = 0u;

/******************************************************************************/
/* Defines                                                                    */
/******************************************************************************/
// constants for LED
#define         LED_OFF       1u
#define         LED_ON        0u


/**
 ******************************************************************************
 ** \brief  InitAdc
 **
 ** \return void
 ******************************************************************************/

void InitAdc(uint8_t analogPort)
{
  // Peripheral Manual - Analog Subsystem CHAPTER 1-2: 12-bit A/D Converter
  // Use the Peripheral Manual for detailed technical understanding of the peripheral
  // for example, how is a sampling time calculated
  // See  -> 5.15 Frequency Division Ratio Setup Register (ADCT)
  // Minimum sampling time (hardware) = (Rin + Rext) * Cin
  // Minimum sampling time (hardware) = (1800 + 0) * 12pF = 21.6ns
  //

  // For PDL, default documentation installation is
  // file:///C:/Program%20Files%20(x86)/Cypress/FM%20PDL/2.0/doc/doxy/html/index.html
  
  // See PDL Documentation, 12-bit Analog Module
  // file:///C:/Program%20Files%20(x86)/Cypress/FM%20PDL/2.0/doc/doxy/html/group___adc_group.html  

  // declare configuration structures
  stc_adc_config_t stcConfig;   // ADC configuration
  stc_adc_scan_t   stcScanCfg;  // Scan configuration
  
  // Clear the structures
  PDL_ZERO_STRUCT(stcConfig);
  PDL_ZERO_STRUCT(stcScanCfg);
 
  // PDL scan configuration structure
  // file:///C:/Program%20Files%20(x86)/Cypress/FM%20PDL/2.0/doc/doxy/html/structstc__adc__scan.html

  // ADC Scan Configuration
  // pick the analog channel
  // single conversion, no timer (software trigger)
  // don't start a timer, and FIFO depth is zero
  
  /*
  switch(analogPort) {
    case 17: stcScanCfg.u32ScanCannelSelect.AD_CH_17 = 1u;       // Analog Input -> Light Sensor
             stcConfig.u32SamplingTimeSelect.AD_CH_17 = 1u; // Channel 17 uses sample time 1
          break;
    case 0:  stcScanCfg.u32ScanCannelSelect.AD_CH_0 = 1u;       // Analog Input -> Joystick2 Y
             stcConfig.u32SamplingTimeSelect.AD_CH_0 = 1u; // JS2 Y uses sample time 1
          break;
    case 3:  stcScanCfg.u32ScanCannelSelect.AD_CH_3 = 1u;       // Analog Input -> Joystick2 X
             stcConfig.u32SamplingTimeSelect.AD_CH_3 = 1u; // JS2X uses sample time 1
          break;
    case 4:  stcScanCfg.u32ScanCannelSelect.AD_CH_4 = 1u;       // Analog Input -> Joystick1 Y
             stcConfig.u32SamplingTimeSelect.AD_CH_4 = 1u; // JS1 Y uses sample time 1
          break;
    case 16: stcScanCfg.u32ScanCannelSelect.AD_CH_16 = 1u;       // Analog Input -> Joystick1 X
             stcConfig.u32SamplingTimeSelect.AD_CH_16 = 1u; // JS1 X uses sample time 1
          break;  
    case 6: stcScanCfg.u32ScanCannelSelect.AD_CH_6 = 1u;       // Analog Input -> LCD_TOUCH Xm
            stcConfig.u32SamplingTimeSelect.AD_CH_6 = 1u; // LCD_T Xm uses sample time 1
          break; 
    case 7: stcScanCfg.u32ScanCannelSelect.AD_CH_7 = 1u;       // Analog Input -> LCD_TOUCH Yo
            stcConfig.u32SamplingTimeSelect.AD_CH_7 = 1u; // LCD_T Yp uses sample time 1
          break;
  }
  */
  
    
    stcScanCfg.u32ScanCannelSelect.AD_CH_17 = 1u;       // Analog Input -> Light Sensor
    stcConfig.u32SamplingTimeSelect.AD_CH_17 = 1u; // Channel 17 uses sample time 1
    
    stcScanCfg.u32ScanCannelSelect.AD_CH_0 = 1u;       // Analog Input -> Joystick2 Y
    stcConfig.u32SamplingTimeSelect.AD_CH_0 = 1u; // JS2 Y uses sample time 1
     
    stcScanCfg.u32ScanCannelSelect.AD_CH_3 = 1u;       // Analog Input -> Joystick2 X
    stcConfig.u32SamplingTimeSelect.AD_CH_3 = 1u; // JS2X uses sample time 1
    
    stcScanCfg.u32ScanCannelSelect.AD_CH_4 = 1u;       // Analog Input -> Joystick1 Y
    stcConfig.u32SamplingTimeSelect.AD_CH_4 = 1u; // JS1 Y uses sample time 1
    
    stcScanCfg.u32ScanCannelSelect.AD_CH_16 = 1u;       // Analog Input -> Joystick1 X
    stcConfig.u32SamplingTimeSelect.AD_CH_16 = 1u; // JS1 X uses sample time 1
    
    stcScanCfg.u32ScanCannelSelect.AD_CH_6 = 1u;       // Analog Input -> LCD_TOUCH Xm
    stcConfig.u32SamplingTimeSelect.AD_CH_6 = 1u; // LCD_T Xm uses sample time 1

    stcScanCfg.u32ScanCannelSelect.AD_CH_7 = 1u;       // Analog Input -> LCD_TOUCH Yo
    stcConfig.u32SamplingTimeSelect.AD_CH_7 = 1u; // LCD_T Yp uses sample time 1
    
  
  stcScanCfg.enScanMode = ScanSingleConversion;
  stcScanCfg.enScanTimerTrigger = AdcNoTimer;
  stcScanCfg.bScanTimerStartEnable = FALSE;
  stcScanCfg.u8ScanFifoDepth = 6u;  // CHANGED 
      
  // ADC configuration structure
  // file:///C:/Program%20Files%20(x86)/Cypress/FM%20PDL/2.0/doc/doxy/html/structstc__adc__config.html

  // ADC Configuration
  stcConfig.bLsbAlignment = TRUE;                // least significant bit alignment

  stcConfig.enSamplingTimeN0 = Value4;           // sample time 0 multiplier
  stcConfig.u8SamplingTime0 = 3u;                // sample time 0 base
  stcConfig.enSamplingTimeN1 = Value8;           // sample time 1 multiplier
  stcConfig.u8SamplingTime1 = 10u;               // sample time 1 base
  stcConfig.u8ComparingClockDiv = 10u;           // clock divisor is 12
  stcConfig.pstcScanInit = &stcScanCfg;          // address of scan config structure
  stcConfig.pstcPrioInit = NULL;                 // no priority scans
  stcConfig.pstcComparisonInit = NULL;           // no comparison
  stcConfig.pstcRangeComparisonInit = NULL;      // no range
  stcConfig.pstcIrqEn = NULL;                    // no interrupts
  stcConfig.pstcIrqCb = NULL;                    // no interrupts
  stcConfig.bTouchNvic = FALSE;                  // not using NVIC

  // Initialize and Start ADC
  if(Ok != Adc_Init(&ADC0, &stcConfig))
  {
    while(1)                    // catch an error
    {}
  }  
  
  Adc_EnableWaitReady(&ADC0);  // Enable ADC0 and wait until ready
  
  return;
}

 /**
******************************************************************************
** \brief   Initialize MFS in UART-Mode
******************************************************************************/

void InitMfs(void){
    // Peripheral Manual (Communication Subsystem) 
    // -> CHAPTER1-2: UART (Asynchronous Serial Interface)

    // PDL Documentation for MFS
    // file:///C:/Program%20Files%20(x86)/Cypress/FM%20PDL/2.0/doc/doxy/html/group___mfs_group.html
 
    // PDL MSF UART configuration structure
    // file:///C:/Program%20Files%20(x86)/Cypress/FM%20PDL/2.0/doc/doxy/html/structstc__mfs__uart__config.html

  // declare configuration structure
    stc_mfs_uart_config_t stcUartConfig;  
  
    // Clear structure
    PDL_ZERO_STRUCT(stcUartConfig);
    
    // Initialize GPIO for UART output
    SetPinFunc_SIN0_0(); 
    SetPinFunc_SOT0_0();

    // Configure UART channel, 115200 bps, 8N1, no interrupts
    stcUartConfig.enMode = UartNormal;                  // UART normal mode
    stcUartConfig.u32BaudRate = 115200;                 // 155200 bps
    stcUartConfig.enDataLength = UartEightBits;         // 8(N1)
    stcUartConfig.enParity = UartParityNone;            // (8)N(1)
    stcUartConfig.enStopBit = UartOneStopBit;           // (8N)1
    stcUartConfig.enBitDirection = UartDataLsbFirst;    // LSB first direction
    stcUartConfig.bInvertData = FALSE;                  // Mark level: high
    stcUartConfig.bHwFlow = FALSE;                      // No handshaking
    stcUartConfig.pstcFifoConfig = NULL;                // Disable FIFO

    // call UART initialization 
    if(Ok != Mfs_Uart_Init(&UART0, &stcUartConfig))
    {
      while(1)                                          // catch an error
      {}
    }
    
    // Enable UART for TX 
    Mfs_Uart_EnableFunc(&UART0, UartTx);
    
}

/**
 ******************************************************************************
 ** \brief   Send a character via MFS
 **
 ** \param   [in] u8Char   Character to be sent
 ******************************************************************************/
void SendByteMfs(uint8_t byteMfs)
{
    // Peripheral Manual (Communication Subsystem) 
    // -> CHAPTER1-2: UART (Asynchronous Serial Interface)
    // Section 7.3: Wait for transmit buffer empty 
    // Section 7.5: Put u8Char into Transmit Data Register

    // PDL Documentation for MFS
    // file:///C:/Program%20Files%20(x86)/Cypress/FM%20PDL/2.0/doc/doxy/html/group___mfs_group.html
  
   
    // wait for the transmit buffer to be empty
    while (TRUE != Mfs_Uart_GetStatus(&UART0, UartTxEmpty))
    {}
  
    // transmit the data
    Mfs_Uart_SendData(&UART0, byteMfs);
}

/**
 ******************************************************************************
 **  \brief   Sends a complete string (0-terminated) 
 **
 **  \param  pu8Buffer  Pointer to (constant) file of bytes in mem
 ******************************************************************************/
void SendStringMfs(uint8_t *pu8Buffer)              
{
  while (*pu8Buffer != '\0')
  { 
    SendByteMfs(*pu8Buffer++);        // send every char of string
  }
}

/**
 ******************************************************************************
 ** \brief   Send ADC result via MFS
 **
 ** \param   [in] uint8   8-bit ADC Value
 ******************************************************************************/
void SendAdcMfs(uint8_t u8AdcValue)
{
  float     f16AdcValue;
  uint8_t   au8String[20];  

  // Calculate and Convert ADC value into string
  f16AdcValue = (float)5 * ((float)u8AdcValue / (float)256);
  sprintf((char*)au8String, "%f V", f16AdcValue);
  
  SendStringMfs("\b\b\b\b\b\b\b\b\b\b");
  SendStringMfs(au8String);
}



/**
 ******************************************************************************
 ** \brief   Initialize GPIO for RGB LED
 ******************************************************************************/

void InitLED (void)
{
    // See schematic: Search for LED (RGB-LED)
    Gpio1pin_InitOut( GPIO1PIN_P1A, Gpio1pin_InitVal( LED_OFF ) );     // set GPIO P1A as output (R), initial output value 1 (off) -> (R)
    Gpio1pin_InitOut( GPIO1PIN_PB2, Gpio1pin_InitVal( LED_OFF ) );     // set GPIO PB2 as output (G), initial output value 1 (off) -> (G)
    Gpio1pin_InitOut( GPIO1PIN_P18, Gpio1pin_InitVal( LED_OFF ) );     // set GPIO P18 as output (B), initial output value 1 (off) -> (B)
}

/**
 ******************************************************************************
 ** \brief   Change LED based on ADC value
 ******************************************************************************/

void ChangeLED (void)  // change color based on the value from the ADC
{
    // Split data range [0..FF] into three segments for R,G,B
    if ( (0xFF/3*2) < u8Data )
    {
      Gpio1pin_Put( GPIO1PIN_P1A, LED_ON); // set GPIO P1A to 0 (on)  -> (R)
      Gpio1pin_Put( GPIO1PIN_PB2, LED_OFF); // set GPIO PB2 to 1 (off) -> (G)
      Gpio1pin_Put( GPIO1PIN_P18, LED_OFF); // set GPIO P18 to 1 (off) -> (B)
    }
    else
    if ( (0xFF/3*1) > u8Data )
    {
      Gpio1pin_Put( GPIO1PIN_P1A, LED_OFF); // set GPIO P1A to 0 (off) -> (R)
      Gpio1pin_Put( GPIO1PIN_PB2, LED_OFF); // set GPIO PB2 to 1 (off) -> (G)
      Gpio1pin_Put( GPIO1PIN_P18, LED_ON); // set GPIO P18 to 1 (on)  -> (B)
    }
    else
    {
      Gpio1pin_Put( GPIO1PIN_P1A, LED_OFF); // set GPIO P1A to 1 (off) -> (R)
      Gpio1pin_Put( GPIO1PIN_PB2, LED_ON); // set GPIO PB2 to 0 (on)  -> (G)
      Gpio1pin_Put( GPIO1PIN_P18, LED_OFF); // set GPIO P18 to 1 (off) -> (B)
    }
    
}



void analogPolling(){
      uint32_t u32Data = 0u;
  
        // See PDL Documentation, 12-bit Analog Module
       // file:///C:/Program%20Files%20(x86)/Cypress/FM%20PDL/2.0/doc/doxy/html/group___adc_group.html

      // Start single ADC Scan 
      Adc_SwTriggerScan(&ADC0);
    
    // Signals for reading X-ordinate of touchpoint
    /*
    TOUCH_YP_IO = 0u;   //    pinMode(_yp, INPUT);
    TOUCH_YM_IO = 0u;   //    pinMode(_ym, INPUT);
    TOUCH_YP = 0u;      //    digitalWrite(_yp, LOW);
    TOUCH_YM = 0u;      //    digitalWrite(_ym, LOW);

    TOUCH_XP_IO = 1u;   //    pinMode(_xp, OUTPUT);
    TOUCH_XP = 1u;      //    digitalWrite(_xp, HIGH);
    TOUCH_XM_IO = 1u;   //    pinMode(_xm, OUTPUT);
    TOUCH_XM = 0u;      //    digitalWrite(_xm, LOW);
    */
    /*
    // signals for reading Y-ordinate of touchpoint
    TOUCH_XP_IO = 0u;   // pinMode(_xp, INPUT);
    TOUCH_XM_IO = 0u;   // pinMode(_xm, INPUT);
    TOUCH_XP = 0u;      // digitalWrite(_xp, LOW);
    TOUCH_XM = 0u;      // digitalWrite(_xm, LOW);
    
    TOUCH_YP_IO = 1u;   // pinMode(_yp, OUTPUT);
    TOUCH_YP = 1u;      // digitalWrite(_yp, HIGH);
    TOUCH_YM_IO = 1u;   // pinMode(_ym, OUTPUT);
    TOUCH_YM = 0u;      // digitalWrite(_ym, LOW);
    */
      // Wait for valid data for Analog 16
      do
      {
        // read ADC Value
        u32Data = Adc_ReadScanFifo(&ADC0);
 
        // check if data is valid
      } while(AdcFifoDataValid != Adc_GetScanDataValid(&ADC0, u32Data));
      
      // extract the ADC value from the data
      u8Data = (uint8_t)(Adc_GetScanData(&ADC0, u32Data) >> 4);
      
      // transmit the data byte
      SendAdcMfs(u8Data);
      //if(u8Data != old){
       char buffer1[20];
       itoa(u8Data, buffer1, 10);
       char text1[] = "Die X-Ordinate des JS1: ";
      
      // ANALOG 4 messen
      do
      {
        // read ADC Value
        u32Data = Adc_ReadScanFifo(&ADC0);
 
        // check if data is valid
      } while(AdcFifoDataValid != Adc_GetScanDataValid(&ADC0, u32Data));
       // extract the ADC value from the data
       u8Data = (uint8_t)(Adc_GetScanData(&ADC0, u32Data) >> 4);
       // transmit the data byte
       SendAdcMfs(u8Data);
       char buffer2[20];
       itoa(u8Data, buffer2, 10);
       char text2[] = "Die Y-Ordinate des JS1: ";
      
      // ANALOG 17 messen
      do
      {
        // read ADC Value
        u32Data = Adc_ReadScanFifo(&ADC0);
 
        // check if data is valid
      } while(AdcFifoDataValid != Adc_GetScanDataValid(&ADC0, u32Data));
       // extract the ADC value from the data
       u8Data = (uint8_t)(Adc_GetScanData(&ADC0, u32Data) >> 4);
       // transmit the data byte
       SendAdcMfs(u8Data);
       char buffer3[20];
       itoa(u8Data, buffer3, 10);
       char text3[] = "Die Helligkeit betraegt: ";
         
       fillScreen(BLACK);
       setCursor(480,320);
       writeText(text1);
       writeTextln(buffer1);
       writeText(text2);
       writeTextln(buffer2);
       writeText(text3);
       writeText(buffer3);
      //}
      
}


void pollData(uint32_t *u32Data){
      // Wait for ADC data to receive.
      do
      {
        // read ADC Value
        *u32Data = Adc_ReadScanFifo(&ADC0);
 
        // check if data is valid
      } while(AdcFifoDataValid != Adc_GetScanDataValid(&ADC0, *u32Data)); 
}

void getAnalogValues(uint8_t *analog0, uint8_t *analog3, uint8_t *analog4, uint8_t *analog6, uint8_t *analog7,  uint8_t *analog16, uint8_t *analog17){
      uint32_t u32Data = 0u;     // 32 Bit Data buffer for measurements
      uint8_t i = 0;
      // Start single ADC Scan 
      Adc_SwTriggerScan(&ADC0);
  
      for(i = 0; i<7; i++){
          pollData(&u32Data);
          // extract the ADC value from the data
          switch(i){
              case 0: *analog0 = (uint8_t)(Adc_GetScanData(&ADC0, u32Data) >> 4);
                      break;
              case 1: *analog3 = (uint8_t)(Adc_GetScanData(&ADC0, u32Data) >> 4);
                      break;
              case 2: *analog4 = (uint8_t)(Adc_GetScanData(&ADC0, u32Data) >> 4);
                      break;
              case 3: *analog6 = (uint8_t)(Adc_GetScanData(&ADC0, u32Data) >> 4);
                      break;
              case 4: *analog7 = (uint8_t)(Adc_GetScanData(&ADC0, u32Data) >> 4);
                      break;
              case 5: *analog16 = (uint8_t)(Adc_GetScanData(&ADC0, u32Data) >> 4);
                      break;
              case 6: *analog17 = (uint8_t)(Adc_GetScanData(&ADC0, u32Data) >> 4);
                      break;
          }
      }
}

void write8BitValueOnLCD(uint8_t *value){
    char buffer[20];
    itoa(*value, buffer, 10);
    writeTextln(buffer);
}

void write16BitValueOnLCD(uint16_t *value){
    char buffer[20];
    itoa(*value, buffer, 10);
    writeTextln(buffer);
}

uint16_t readTouchX(){
    TOUCH_XP_IO = 1u;   // pinMode(_xp, OUTPUT);
    TOUCH_XM_IO = 1u;   // pinMode(_xm, OUTPUT);
    bFM4_GPIO_ADE_AN06 = 0u; // ANALOG 6 OFF
    TOUCH_XP = 0u;      // digitalWrite(_xp, LOW);
    TOUCH_XM = 0u;      // digitalWrite(_xm, LOW);
    TOUCH_XP_IO = 0u;   // pinMode(_xp, INPUT);
    TOUCH_XM_IO = 0u;   // pinMode(_xm, INPUT);
    
    bFM4_GPIO_ADE_AN07 = 0u;   // ANALOG7 OFF
    TOUCH_YP_IO = 1u;   // pinMode(_yp, OUTPUT);
    TOUCH_YP = 1u;      // digitalWrite(_yp, HIGH);
    TOUCH_YM_IO = 1u;   // pinMode(_ym, OUTPUT);
    TOUCH_YM = 0u;      // digitalWrite(_ym, LOW);
    bFM4_GPIO_ADE_AN06 = 1u; // ANALOG 6 ON
    
    
    /**
      * DOUBLE SAMPLING
      */
    uint16_t i = 0;
    uint16_t samples[2];
    for(i=0; i<2; i++){
      getAnalogValues(&analog0, &analog3, &analog4, &analog6, &analog7, &analog16,&analog17);
      samples[i] = analog6;
    }
    if (samples[0] - samples[1] < -4 || samples[0] - samples[1] > 4) {
        return 500;
    } else {
        samples[1] = (samples[0] + samples[1]) >> 1; // average 2 samples
    } 
    uint8_t xCorrected = TOUCHXMAX + TOUCHXMIN - samples[1];
    uint16_t result = map(xCorrected, TOUCHXMIN, TOUCHXMAX, 0, 480);
    return result;
}


uint16_t readTouchY(){
    TOUCH_YP_IO = 1u;   //    pinMode(_yp, OUTPUT);
    TOUCH_YM_IO = 1u;   //    pinMode(_ym, OUTPUT);
    bFM4_GPIO_ADE_AN07 = 0u;  // ANALOG 7 OFF
    TOUCH_YP = 0u;      //    digitalWrite(_yp, LOW);
    TOUCH_YM = 0u;      //    digitalWrite(_ym, LOW);
    TOUCH_YP_IO = 0u;   //    pinMode(_yp, INPUT);
    TOUCH_YM_IO = 0u;   //    pinMode(_ym, INPUT);

    TOUCH_XP_IO = 1u;   //    pinMode(_xp, OUTPUT);
    TOUCH_XP = 1u;      //    digitalWrite(_xp, HIGH);
    TOUCH_XM_IO = 1u;   //    pinMode(_xm, OUTPUT);
    bFM4_GPIO_ADE_AN06 = 0u; // Xm/P16 ANALOG OFF
    TOUCH_XM = 0u;      //    digitalWrite(_xm, LOW);
    bFM4_GPIO_ADE_AN07 = 1u;   // ANALOG 7 ON 
    
    /**
      * DOUBLE SAMPLING
      */
    uint16_t i = 0;
    uint16_t samples[2];
    for(i=0; i<2; i++){
      getAnalogValues(&analog0, &analog3, &analog4, &analog6, &analog7, &analog16,&analog17);
      samples[i] = analog7;
    }
    if (samples[0] - samples[1] < -4 || samples[0] - samples[1] > 4) {
        return 500;
    } else {
        samples[1] = (samples[0] + samples[1]) >> 1; // average 2 samples
    } 
    uint8_t yCorrected = TOUCHYMAX + TOUCHYMIN - samples[1];
    uint16_t result = map(yCorrected, TOUCHYMIN, TOUCHYMAX, 0, 320);
    return result;
}

uint16_t readTouchZ(){
    uint16_t rXPlate = 248;  // Resistance between X+ and X-
 
    // Set X+ to ground
    TOUCH_XP_IO = 1u;   // pinMode(_xp, OUTPUT);
    TOUCH_XP = 0u;      // digitalWrite(_xp, LOW);
    
    // Set Y- to VCC
    TOUCH_YM_IO = 1u;   // pinMode(_ym, OUTPUT);
    TOUCH_YM = 1u;      // digitalWrite(_ym, HIGH);
    
    // Hi-Z X- and Y+
    bFM4_GPIO_ADE_AN06 = 0u; //Xm/Analog 6 OFF
    bFM4_GPIO_ADE_AN07 = 0u; //Yp/Analog 7 OFF
    TOUCH_XM_IO = 1u; // Xm OUTPUT
    TOUCH_XM = 0u;      // digitalWrite(_xm, LOW);
    TOUCH_YP = 1u;      // Yp OUTPUT
    TOUCH_YP = 0u;      // digitalWrite(_yp, LOW);
    
    TOUCH_XM_IO = 0u;   // pinMode(_xm, INPUT);
    TOUCH_YP_IO = 0u;   // pinMode(_yp, INPUT);
    bFM4_GPIO_ADE_AN06 = 1u; //Xm/Analog 6 ON
    bFM4_GPIO_ADE_AN07 = 1u; //Yp/Analog 7 ON
    
    getAnalogValues(&analog0, &analog3, &analog4, &analog6, &analog7, &analog16,&analog17);
    uint8_t z1 = analog6; // z1 = Xm = analog6
    uint8_t z2 = analog7; // z2 = Ym = analog7 
    
    return (255-(z2-z1));
}

void printTouchValues(){
  uint16_t xValue = readTouchX();
  uint16_t yValue = readTouchY();
  uint16_t zValue = readTouchZ();
  
  setCursor(480,320);
  fillScreen(BLACK);
  char text1[] = "Die X-Koordinate ist: ";
  char text2[] = "Die Y-Koordinate ist: ";
  char text3[] = "Die Z-Koordinate ist: ";
  writeText(text1);
  write16BitValueOnLCD(&xValue);
  writeText(text2);
  write16BitValueOnLCD(&yValue);
  writeText(text3);
  write16BitValueOnLCD(&zValue);
}
