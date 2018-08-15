#include "uart_multicon.h"


void testMulticonConnection(){
  // ONLY FOR DEBUG 
  /*
  TEST_PIN_2_MULTICON_DDR &= ~(1 << TEST_PIN_2_MULTICON_PIN);
  TEST_PIN_2_MULTICON_PCR |= (1 << TEST_PIN_2_MULTICON_PIN); 
  
  TEST_PIN_3_MULTICON_DDR &= ~(1 << TEST_PIN_3_MULTICON_PIN);
  TEST_PIN_3_MULTICON_PCR |= (1 << TEST_PIN_3_MULTICON_PIN); 
  */
  
  // Initialize test pin as input and activate pullup resistor
  TEST_PIN_MULTICON_DDR &= ~(1 << TEST_PIN_MULTICON_PIN);
  TEST_PIN_MULTICON_PCR |= (1 << TEST_PIN_MULTICON_PIN); 

  LED_BLUE_DDR |= (1 << LED_BLUE_PIN); // Configure blue LED pin as output.
  LED_BLUE_DOR |= (1 << LED_BLUE_PIN); // Turn LED off.
  
  while(1u){
    uint8_t pinStatus = !(TEST_PIN_MULTICON_DIR & (1 << TEST_PIN_MULTICON_PIN));
    //setCursor_s(480,320); 
    //char freeSpace[] = " ";
    //char headlineText[] = "  BLE Multicon Test";
    //writeTextln_s(headlineText);
    //writeTextln_s(freeSpace);
    if(pinStatus == 1){
       LED_BLUE_DOR &= ~(1 << LED_BLUE_PIN);
      //writeText_s("  test pin is high ");
      //writeTextln_s(freeSpace);
    }
    else {
       LED_BLUE_DOR |= (1 << LED_BLUE_PIN);
      //writeText_s("  test pin is low ");
      //writeTextln_s(freeSpace);
    }
  }
}
int uartMulticon(void){
  volatile stc_mfsn_uart_t* pstcUart3 = &UART3; 
  stc_mfs_uart_config_t stcUartConfig; 
  uint8_t u8Count; 
  PDL_ZERO_STRUCT(stcUartConfig); 
  SetPinFunc_SIN3_1();
  SetPinFunc_SOT3_1();
  stcUartConfig.enMode = UartNormal;
  stcUartConfig.u32BaudRate = 115200u;
  stcUartConfig.enParity = UartParityNone; // No parity 
  stcUartConfig.enStopBit = UartOneStopBit; // 1 Stop bit 
  stcUartConfig.enDataLength = UartEightBits; // 8 Bit Character Length 
  stcUartConfig.enBitDirection = UartDataLsbFirst; // LSB first
  stcUartConfig.bInvertData = FALSE; 
  stcUartConfig.bHwFlow = FALSE; 
  stcUartConfig.bUseExtClk = FALSE; 
  stcUartConfig.pstcFifoConfig = NULL;

  Mfs_Uart_Init(pstcUart3, &stcUartConfig); // Initialize UART 
  Mfs_Uart_EnableFunc(pstcUart3, UartTx); 
  Mfs_Uart_EnableFunc(pstcUart3, UartRx);
  for (u8Count = 0u; u8Count < strlen((char*)&txBuf); u8Count++) {
    // wait until TX buffer empty
    while (TRUE != Mfs_Uart_GetStatus(pstcUart3, UartTxEmpty)) {}
    Mfs_Uart_SendData(pstcUart3, txBuf[u8Count]);
  } 
  while(1u) {
    // wait until RX buffer full
    while(TRUE != Mfs_Uart_GetStatus(pstcUart3, UartRxFull)) {}
    // Echo data
    Mfs_Uart_SendData(pstcUart3, Mfs_Uart_ReceiveData(pstcUart3));
  }
}

void uartMulticonListen(){
  
  LED_BLUE_DDR |= (1 << LED_BLUE_PIN); // Configure blue LED pin as output.
  LED_BLUE_DOR |= (1 << LED_BLUE_PIN); // Turn LED off.
    
  volatile stc_mfsn_uart_t* pstcUart3 = &UART3; 
  stc_mfs_uart_config_t stcUartConfig; 
  uint8_t u8Count; 
  PDL_ZERO_STRUCT(stcUartConfig); 
  SetPinFunc_SIN3_1();
  SetPinFunc_SOT3_1();
  stcUartConfig.enMode = UartNormal;
  stcUartConfig.u32BaudRate = 9600u;
  stcUartConfig.enParity = UartParityNone; // No parity 
  stcUartConfig.enStopBit = UartOneStopBit; // 1 Stop bit 
  stcUartConfig.enDataLength = UartEightBits; // 8 Bit Character Length 
  stcUartConfig.enBitDirection = UartDataLsbFirst; // LSB first
  stcUartConfig.bInvertData = FALSE; 
  stcUartConfig.bHwFlow = FALSE; 
  stcUartConfig.bUseExtClk = FALSE; 
  stcUartConfig.pstcFifoConfig = NULL;
  if(Ok != Mfs_Uart_Init(pstcUart3, &stcUartConfig)){
    while(1){}
  }
  Mfs_Uart_EnableFunc(pstcUart3, UartTx); 
  Mfs_Uart_EnableFunc(pstcUart3, UartRx);
  setCursor_s(480,320); 
  char headlineText[] = "  BLE Multicon UART Test";
  writeTextln_s(headlineText);
  writeTextln_s("");
  writeText_s("  UART received: ");
  while(1u) {
    // wait until RX buffer full

    if (TRUE == Mfs_Uart_GetStatus(pstcUart3, UartRxFull)) {
      // received data from the BLE module
      uint8_t tmp = Mfs_Uart_ReceiveData(pstcUart3);
      char tmpChar = (char) tmp;
      /*
      if(tmpChar == 'a')
        LED_BLUE_DOR &= ~(1 << LED_BLUE_PIN);
      else
        LED_BLUE_DOR |= (1 << LED_BLUE_PIN);
        */
      writeAuto_s(tmpChar);
    }
  }
  

}
