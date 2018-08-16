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
  //BlinkMain();
  //debugCPPPBoard();
  //testMulticonConnection();
  //uartMulticonListen();
  //uartListenRainbowLED();
  uartMulticonWrite();
  return 0;
}
