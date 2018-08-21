#include "init.h"
#include "blink.h"
#include "blinkrainbow.h"

#include "lib/debug.h"
#include "lib/uart_usb.h"
#include "lib/uart_multicon.h"


int main(){
  initBoard();
  //UART_USB_Init();
  //UART_USB();   
  //initUART3();
  //BlinkMain();
  //debugCPPPBoard();
  //testMulticonConnection();
  //uartMulticonListen();
  //uartListenRainbowLED();
  //uartMulticonWriteTest();
  /*
  while(1u){
    uartSendJoystick1XValue();
  }
  */
  //testAcceleration();
  while(1u){
    rauminformationen_s();
  }
  return 0;
}
