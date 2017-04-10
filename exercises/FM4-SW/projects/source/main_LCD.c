                                /*******************************************************************************
 * Copyright (C) 2013 Spansion LLC. All Rights Reserved.
 *
 * This software is owned and published by:
 * Spansion LLC, 915 DeGuigne Dr. Sunnyvale, CA  94088-3453 ("Spansion").
 *
 * BY DOWNLOADING, INSTALLING OR USING THIS SOFTWARE, YOU AGREE TO BE BOUND
 * BY ALL THE TERMS AND CONDITIONS OF THIS AGREEMENT.
 *
 * This software contains source code for use with Spansion
 * components. This software is licensed by Spansion to be adapted only
 * for use in systems utilizing Spansion components. Spansion shall not be
 * responsible for misuse or illegal use of this software for devices not
 * supported herein.  Spansion is providing this software "AS IS" and will
 * not be responsible for issues arising from incorrect user implementation
 * of the software.
 *
 * SPANSION MAKES NO WARRANTY, EXPRESS OR IMPLIED, ARISING BY LAW OR OTHERWISE,
 * REGARDING THE SOFTWARE (INCLUDING ANY ACOOMPANYING WRITTEN MATERIALS),
 * ITS PERFORMANCE OR SUITABILITY FOR YOUR INTENDED USE, INCLUDING,
 * WITHOUT LIMITATION, THE IMPLIED WARRANTY OF MERCHANTABILITY, THE IMPLIED
 * WARRANTY OF FITNESS FOR A PARTICULAR PURPOSE OR USE, AND THE IMPLIED
 * WARRANTY OF NONINFRINGEMENT.
 * SPANSION SHALL HAVE NO LIABILITY (WHETHER IN CONTRACT, WARRANTY, TORT,
 * NEGLIGENCE OR OTHERWISE) FOR ANY DAMAGES WHATSOEVER (INCLUDING, WITHOUT
 * LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS, BUSINESS INTERRUPTION,
 * LOSS OF BUSINESS INFORMATION, OR OTHER PECUNIARY LOSS) ARISING FROM USE OR
 * INABILITY TO USE THE SOFTWARE, INCLUDING, WITHOUT LIMITATION, ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL OR CONSEQUENTIAL DAMAGES OR LOSS OF DATA,
 * SAVINGS OR PROFITS,
 * EVEN IF SPANSION HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 * YOU ASSUME ALL RESPONSIBILITIES FOR SELECTION OF THE SOFTWARE TO ACHIEVE YOUR
 * INTENDED RESULTS, AND FOR THE INSTALLATION OF, USE OF, AND RESULTS OBTAINED
 * FROM, THE SOFTWARE.
 *
 * This software may be replicated in part or whole for the licensed use,
 * with the restriction that this Disclaimer and Copyright notice must be
 * included with each copy of this software, whether used in part or whole,
 * at all times.
 */

/******************************************************************************/
/** \file main.c
 **
 ** Main Module
 **
 ** History:
 **   - 2013-03-21  0.0.1  MWi        First version.
 **
 ******************************************************************************/

/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/
#include "uart.h"
#include "lcd.h"
#include "analog_read.h"


/**
 ******************************************************************************
 ** \brief  Main function of project for S6E2CC series.
 **
 ** \return uint32_t return value, if needed
 ******************************************************************************/
       
int32_t main(void)
{
    volatile unsigned long u32Delay;
    
    bFM4_FLASH_IF_FBFCR_BE = 1; // Enable Flash Accelerator
    
    // Initialize pin that drives LCD background illumination LED as GPIO output (P24)
    bFM4_GPIO_ADE_AN08 = 0; // deactivate shared ADC AN29
    FM4_GPIO->PDOR1_f.P8  = 1u; // GPIO, not special function
    FM4_GPIO->DDR1_f.P8  = 1u; // Direction: Output
    
    //Uart0_Init();
    //printf("Hello World! \t Hello iSYSTEM!\n");
    
    //Uart_Io_Init();
    //printf("Started..\n");
    
    /**
     *   AREA FOR LCD
     **/
    
    //testbench(); 
    
    
    init();
    reset();
    setupLCD();
    
    fillScreen(0xF800);
    fillScreen(RED);
    
    /*
    fillScreen(WHITE);
    fillScreen(BLUE);
    fillScreen(CYAN);
    fillScreen(MAGENTA);
    fillScreen(YELLOW);
    */
    /*
    drawFastHLine(1,50,300,WHITE);
    drawFastVLine(40,40,50,BLACK);
    drawLine(20,20,40,40,RED);
    fillRect(60,60,70,70,CYAN);
    fillRect(70,70,70,70,GREEN);
    fillRect(0,0,479,319,YELLOW);
    fillRect(0,0,480,320,BLACK);
    fillRect(0,0,480,320,BLUE);
    fillRect(0,0,480,320,GREEN);
    fillRect(0,0,480,320,BLACK);
    drawCircle(40,160, 10, RED); 
    drawCircle(460,160, 10, RED);
    drawCircle(240,160, 10, RED);
    fillRect(0,0,480,320,BLACK);
    */
    char myText[] = "LOVE YOU KRISTIN! <3";
    printLove(myText);
    
    
    /*
    int i = 0;
    for(i = 0; i<491; i=i+10) {
      fillRect(20+i,160, 40+i, 180, RED);
      fillRect(20+i,160, 40+i, 180, BLACK);
    }
    
    int cursor_x = 50;
    int cursor_y = 310;
    char myChar = 'c';
    char myChar2 = 'a';      
    */
    
    
    /**
     *  AREA FOR TOUCH FUNCTION OF LCD
     **/
    
    /**
     *  AREA FOR THE JOYSTICKS
     **/
    

    
    /**
     *   BLINKING BLUE LED
     **/
    while(1)
    {
        for(u32Delay = 12000000; u32Delay > 0; u32Delay--);
        FM4_GPIO->PDOR1_f.P8 = 0u;
        printf("Light on\n");
        for(u32Delay = 12000000; u32Delay > 0; u32Delay--);
        FM4_GPIO->PDOR1_f.P8 = 1u;
        printf("Light off\n");
    }
}
