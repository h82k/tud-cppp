                                       #include "kxcjk1013.h"
#include <math.h>

/******************************************************************************/
/* Local pre-processor symbols/macros ('#define')                             */
/******************************************************************************/
#define NORMAL_OPERATION_MODE                   0x00
#define CALIBRATION_READ_POSITIVE_X_MODE        0x01
#define CALIBRATION_READ_NEGATIVE_X_MODE        0x02
#define CALIBRATION_READ_POSITIVE_Y_MODE        0x03
#define CALIBRATION_READ_NEGATIVE_Y_MODE        0x04
#define CALIBRATION_READ_POSITIVE_Z_MODE        0x05
#define CALIBRATION_READ_NEGATIVE_Z_MODE        0x06

#define NUM_OF_AXIS                             3
#define ACCELERATION_AXIS_X                     0x00
#define ACCELERATION_AXIS_Y                     0x01
#define ACCELERATION_AXIS_Z                     0x02

#define GET_RAW_DATA                            0x00
#define GET_MOVING_AVERAGE_256                  0x01

/******************************************************************************/
/* Local variable definitions ('static')                                      */
/******************************************************************************/
static int16_t AccelerationData[NUM_OF_AXIS];
static int16_t Sensitivity[NUM_OF_AXIS];
static uint8_t ResolutionShifter;

static uint8_t data_available = 0;
static uint8_t operation_mode = NORMAL_OPERATION_MODE;
static uint8_t display_accelerations = 0;

/******************************************************************************/
/* Function implementation - global ('extern') and local ('static')           */
/******************************************************************************/
void interrupt_callback(en_kxcjk1013_interrupt_source_t src);

/**
 ******************************************************************************
 ** InitAccelerometer function
 ******************************************************************************/
int InitAccelerometer(void)
{
    stc_kxcjk1013_interrupt_config_t            int_config;
    stc_kxcjk1013_output_performance_config_t   config;

    /* Init the Accelerometer KXCJK-1013 */
    int_config.src      = Kxcjk1013IntSource_DataReady;
    int_config.callback = interrupt_callback;
    
    config.res		= Kxcjk1013Resolution12Bit;
    config.range	= Kxcjk1013Acceleration2g;
    config.odr		= Kxcjk1013Osa_200Hz;
    config.int_config   = &int_config;
    
    // Set Default Sensitivity (counts per g)
    if(config.res == Kxcjk1013Resolution12Bit){
        ResolutionShifter = 4;
        switch(config.range){
            case Kxcjk1013Acceleration2g:
                Sensitivity[ACCELERATION_AXIS_X] = 0x7FF>>1;
                Sensitivity[ACCELERATION_AXIS_Y] = 0x7FF>>1;
                Sensitivity[ACCELERATION_AXIS_Z] = 0x7FF>>1;
                break;
            case Kxcjk1013Acceleration4g:
                Sensitivity[ACCELERATION_AXIS_X] = 0x7FF>>2;
                Sensitivity[ACCELERATION_AXIS_Y] = 0x7FF>>2;
                Sensitivity[ACCELERATION_AXIS_Z] = 0x7FF>>2;
                break;
            case Kxcjk1013Acceleration8g:
                Sensitivity[ACCELERATION_AXIS_X] = 0x7FF>>3;
                Sensitivity[ACCELERATION_AXIS_Y] = 0x7FF>>3;
                Sensitivity[ACCELERATION_AXIS_Z] = 0x7FF>>3;
                break;
        }
    }else{
        ResolutionShifter = 8;
        switch(config.range){
            case Kxcjk1013Acceleration2g:
                Sensitivity[ACCELERATION_AXIS_X] = 0x7F>>1;
                Sensitivity[ACCELERATION_AXIS_Y] = 0x7F>>1;
                Sensitivity[ACCELERATION_AXIS_Z] = 0x7F>>1;
                break;
            case Kxcjk1013Acceleration4g:
                Sensitivity[ACCELERATION_AXIS_X] = 0x7F>>2;
                Sensitivity[ACCELERATION_AXIS_Y] = 0x7F>>2;
                Sensitivity[ACCELERATION_AXIS_Z] = 0x7F>>2;
                break;
            case Kxcjk1013Acceleration8g:
                Sensitivity[ACCELERATION_AXIS_X] = 0x7F>>3;
                Sensitivity[ACCELERATION_AXIS_Y] = 0x7F>>3;
                Sensitivity[ACCELERATION_AXIS_Z] = 0x7F>>3;
                break;
        }
    }
    
    if( KXCJK1013_RET_OK != Kxcjk1013_Init(&config) ){
        // Initialization Error
        while(1);
    }
    
    // Set the device to the operating mode
    if( KXCJK1013_RET_OK != Kxcjk1013_SetOperationMode( Kxcjk1013NormalMode ) ){
        return KXCJK1013_RET_ERROR;
    }
    
    return 0;

}

/**
 ******************************************************************************
 ** GetAcceleration function
 ******************************************************************************/
int GetAcceleration( int16_t *data )
{   
    int16_t xout, yout, zout;
    
    if(data == NULL )return (-1);
    
    if( KXCJK1013_RET_OK != Kxcjk1013_GetAccelerations( &xout, &yout, &zout ) ){
        // Register read error
        while(1);
    }

    // Raw data
    data[ACCELERATION_AXIS_X] = xout>>ResolutionShifter;
    data[ACCELERATION_AXIS_Y] = yout>>ResolutionShifter;
    data[ACCELERATION_AXIS_Z] = zout>>ResolutionShifter;
            
    return 0;
}

/**
 ******************************************************************************
 ** callback function for get KXCJK1013 interrupt
 ******************************************************************************/
void interrupt_callback(en_kxcjk1013_interrupt_source_t src)
{
    data_available = 1;
    if( 0 != GetAcceleration( AccelerationData ) ){
        // Register read error
        while(1);
    }
}

/**
 ******************************************************************************
 ** NMI callback function
 ******************************************************************************/
void Main_NmiCallback(void)
{
    static int16_t temp;
    
    switch(operation_mode){
        case NORMAL_OPERATION_MODE:
            operation_mode = CALIBRATION_READ_POSITIVE_X_MODE;
            break;
        case CALIBRATION_READ_POSITIVE_X_MODE:
            operation_mode = CALIBRATION_READ_NEGATIVE_X_MODE;
            temp = AccelerationData[ACCELERATION_AXIS_X];
            break;
        case CALIBRATION_READ_NEGATIVE_X_MODE:
            operation_mode = CALIBRATION_READ_POSITIVE_Y_MODE;
            Sensitivity[ACCELERATION_AXIS_X] = (temp - AccelerationData[ACCELERATION_AXIS_X])>>1;
            break;
        case CALIBRATION_READ_POSITIVE_Y_MODE:
            operation_mode = CALIBRATION_READ_NEGATIVE_Y_MODE;
            temp = AccelerationData[ACCELERATION_AXIS_Y];
            break;
        case CALIBRATION_READ_NEGATIVE_Y_MODE:
            operation_mode = CALIBRATION_READ_POSITIVE_Z_MODE;
            Sensitivity[ACCELERATION_AXIS_Y] = (temp - AccelerationData[ACCELERATION_AXIS_Y])>>1;
            break;
        case CALIBRATION_READ_POSITIVE_Z_MODE:
            operation_mode = CALIBRATION_READ_NEGATIVE_Z_MODE;
            temp = AccelerationData[ACCELERATION_AXIS_Z];
            break;
        case CALIBRATION_READ_NEGATIVE_Z_MODE:
            operation_mode = NORMAL_OPERATION_MODE;
            Sensitivity[ACCELERATION_AXIS_Z] = (temp - AccelerationData[ACCELERATION_AXIS_Z])>>1;
            break;      
    }
}

/**
 ******************************************************************************
 ** InitNMI function
 ******************************************************************************/
int InitNMI(void)
{
    stc_exint_nmi_config_t                      stcNmiConfig;

    /* Congfigure NMI for "User" Buttone */
    PDL_ZERO_STRUCT(stcNmiConfig);
    stcNmiConfig.pfnNmiCallback = Main_NmiCallback;
    Exint_Nmi_Init(&stcNmiConfig);
    SetPinFunc_NMIX(0u);                      /* Pin Function: NMIX */
    
    return 0;
}

/*******************************************************************************
* Function Name: SampleRtcHalfSecondCb
*******************************************************************************/
static void SampleRtcHalfSecondCb(void)
{
    display_accelerations = 1;
}

/**
 ******************************************************************************
 ** InitRTC function
 ******************************************************************************/
int InitRTC(void)
{
    static stc_rtc_time_t   stcTimeDate;

    en_result_t enResult;
    stc_rtc_config_t stcRtcConfig;
    stc_rtc_irq_en_t stcIrqEn;
    stc_rtc_irq_cb_t stcIrqCb;
    stc_rtc_timer_t  stcTimer;

    /* Clear structures */
    PDL_ZERO_STRUCT(stcRtcConfig);
    PDL_ZERO_STRUCT(stcTimeDate);
    PDL_ZERO_STRUCT(stcIrqEn);
    PDL_ZERO_STRUCT(stcIrqCb);

    /* Time setting (23:59:00 1st of January 2014) */
    stcTimeDate.u8Second = 0;                    /* Second      : 00 */
    stcTimeDate.u8Minute = 59;                   /* Minutes     : 59 */
    stcTimeDate.u8Hour   = 23;                   /* Hour        : 23 */
    stcTimeDate.u8Day    = 30;                   /* Date        : 30th */
    stcTimeDate.u8Month  = RtcNovember;          /* Month       : November */
    stcTimeDate.u16Year   = 2014;                /* Year        : 2014 */
    (void)Rtc_SetDayOfWeek(&stcTimeDate);        /* Set Day of the Week in stcRtcTime */
        
    /* Initialize interrupts */
    stcIrqEn.bHalfSecondIrq  = 1u;
    stcIrqCb.pfnHalfSecondIrqCb  = SampleRtcHalfSecondCb;
    
    /* Set time, alarm and interrupt structure pointer */
#if (PDL_RTC_TYPE == PDL_RTC_WITHOUT_VBAT_TYPEA) || (PDL_RTC_TYPE == PDL_RTC_WITHOUT_VBAT_TYPEB)      
    stcRtcConfig.enClkSel = RtcUseSubClk;
    stcRtcConfig.u32ClkPrescaler = 32768;
#endif    
    stcRtcConfig.pstcTimeDate = &stcTimeDate;
    stcRtcConfig.pstcTimer = &stcTimer;
    stcRtcConfig.pstcIrqEn = &stcIrqEn;
    stcRtcConfig.pstcIrqCb = &stcIrqCb;
    
    stcRtcConfig.bRunNotInit = FALSE;
    stcRtcConfig.bTouchNvic = TRUE;
    
    /* Initialize the RTC */
    enResult = Rtc_Init(&RTC0, &stcRtcConfig);

    if (Ok != enResult)
    {
		// Error
        while(1)
        {
            
        }
    } 
	
    /* Start RTC counting */
    Rtc_EnableFunc(&RTC0, RtcCount);
    
    /* Start RTC timer */
    Rtc_EnableFunc(&RTC0, RtcTimer);
    
    return 0;
}

/**
 ******************************************************************************
 ** DisplayAccelerations function
 ******************************************************************************/
int DisplayAccelerations(float x_out, float y_out, float z_out)
{
    printf("\x1b[1;1H");
    switch(operation_mode){
        case NORMAL_OPERATION_MODE:
            printf("\x1b[2K");
            printf("Push User Button to calibrate accleration output.\n");
            break;
        case CALIBRATION_READ_POSITIVE_X_MODE:
            printf("\x1b[2K");
            printf("Orient the board and keep X axis output to around +1.0g. Then, push User Button to capture the accleration output.\n");
            break;
        case CALIBRATION_READ_NEGATIVE_X_MODE:
            printf("\x1b[2K");
            printf("Orient the board and keep X axis output to around -1.0g. Then, push User Button to capture the accleration output.\n");
            break;
        case CALIBRATION_READ_POSITIVE_Y_MODE:
            printf("\x1b[2K");
            printf("Orient the board and keep Y axis output to around +1.0g. Then, push User Button to capture the accleration output.\n");
            break;
        case CALIBRATION_READ_NEGATIVE_Y_MODE:
            printf("\x1b[2K");
            printf("Orient the board and keep Y axis output to around -1.0g. Then, push User Button to capture the accleration output.\n");
            break;
        case CALIBRATION_READ_POSITIVE_Z_MODE:
            printf("\x1b[2K");
            printf("Orient the board and keep Z axis output to around +1.0g. Then, push User Button to capture the accleration output.\n");
            break;
        case CALIBRATION_READ_NEGATIVE_Z_MODE:
            printf("\x1b[2K");
            printf("Orient the board and keep Z axis output to around -1.0g. Then, push User Button to capture the accleration output.\n");
            break;      
    }
    printf("\x1b[2K"); printf( "XOUT = % 2.3f [g]\n", x_out );
    printf("\x1b[2K"); printf( "YOUT = % 2.3f [g]\n", y_out );
    printf("\x1b[2K"); printf( "ZOUT = % 2.3f [g]\n", z_out );
    
    return 0;
    
}

/**
 ******************************************************************************
 ** DisplayAccelerations function
 ******************************************************************************/
int DisplayPositionMap(float x_deg, float y_deg, float z_deg)
{
    static int prev_x, prev_y;
    
    printf("\x1b[%d;%dH ", prev_y, prev_x);
    printf("\x1b[30;64H+");
    printf("\x1b[%d;%dH*", 30 + (int)(y_deg * 16.0f), 64 + (int)(x_deg * 32.0f));
    prev_x = 64 + (int)(x_deg * 32.0f);
    prev_y = 30 + (int)(y_deg * 16.0f);
    
    return 0;
}
 
/*******************************************************************************
* Function Name: main
********************************************************************************
* Main function of project for FM family.
*
* \return int return value, if needed
*******************************************************************************/
int testAcceleration(void)
{   
    float x_out, y_out, z_out;
    float x_deg, y_deg, z_deg;
    
    /* Enable the SUB, it is necessary for the RTC in this example */
    Clk_EnableSubClock(TRUE);
    
    /* Initializatio of the UART unit and GPIO used in the communication */
    Uart_Io_Init();
    
    
    // Init Accelerometer
    InitAccelerometer();

    // Init NMI for Push Button
    InitNMI();
    
    // Init RTC for periodical reports via UART
    InitRTC();
    
    /* Start to read Acceleration data */
//    printf("\x1b[2 q\n");
    //printf("\x1b[?25l\n");
    
    /*
    while(1)
    {
        if( data_available == 1 ){
		    x_out = ((float)((AccelerationData[ACCELERATION_AXIS_X]))) / (float)Sensitivity[ACCELERATION_AXIS_X];
		    y_out = ((float)((AccelerationData[ACCELERATION_AXIS_Y]))) / (float)Sensitivity[ACCELERATION_AXIS_Y];
		    z_out = ((float)((AccelerationData[ACCELERATION_AXIS_Z]))) / (float)Sensitivity[ACCELERATION_AXIS_Z];
		    
		    x_deg = (x_out>1.0f?1.0f:(x_out<-1.0f?-1.0f:x_out));
		    y_deg = (y_out>1.0f?1.0f:(y_out<-1.0f?-1.0f:y_out));
		    z_deg = (z_out>1.0f?1.0f:(z_out<-1.0f?-1.0f:z_out));
		    //x_deg = asin(x_deg)/(3.141592f/2.0f);
		    //y_deg = asin(y_deg)/(3.141592f/2.0f);
		    //z_deg = asin(z_deg)/(3.141592f/2.0f);
        
		        //DisplayPositionMap(x_deg, y_deg, z_deg);
            //data_available = 0;
        }
        
        if( display_accelerations == 1 ){
			DisplayAccelerations(x_out, y_out, z_out);
            display_accelerations = 0;
        }
        
    } 
    */
    
}

