/*! @file main.c
    @brief Starting point of software
*/

#include <avr/interrupt.h>
#include <stdint.h>
#include <util/delay.h>
#include "isr.h"
#ifdef LOGGING_ENABLED
    #include "logging.h"
#endif
#include "uart_drv.h"
#include "logger_tx.h"
// #include "MD_MotorDrv.h"
// #include "os.h"
#include "i2c_drv.h"
// #include "LSD_LineSensorDrv.h"
// #include "DSD_DistanceSensorDrv.h"
// #include "ADC.h"
// #include "TMR.h"
// #include "CSD_CollisionSensorDrv.h"
// #include "LM_LogicModule.h"
// #include "UIM_UserInputModule.h"

/**
 * @brief Main function
 */ 
int main(){
    /* Initialization */
    sei();
    Uart_Init();
//     MDRV_Init();
    // os_init();
    I2c_Init();
//     LSD_Init();
//     ADC_Init();
//     Timer_Init();
//     DSD_Init();
//     CSD_Init();
//     UIM_Init();
//     LM_Init();
    log_info_P(PGM_ECU_INIT);
    while(1){ 
//         // LM_Run();
//         MDRV_Forward();
//         // _delay_ms(1000);
//         // data[0] = 0x00;
//         // I2C_Send(data, sizeof(data));
//         // MDRV_Backward();

//         MDRV_SetPWM(100);
//         _delay_ms(1000);
//         MDRV_SetPWM(90);
//         _delay_ms(1000);
//         MDRV_SetPWM(80);
//         _delay_ms(1000);
//         MDRV_SetPWM(70);
//         _delay_ms(1000);
//         MDRV_SetPWM(60);
//         _delay_ms(1000);
//         MDRV_SetPWM(50);
//         _delay_ms(1000);
//         MDRV_SetPWM(40);
//         _delay_ms(1000);
//         MDRV_SetPWM(30);
//         _delay_ms(1000);
//         MDRV_SetPWM(20);
//         _delay_ms(1000);
//         MDRV_SetPWM(10);
//         _delay_ms(1000);
//         MDRV_SetPWM(0);
//         _delay_ms(1000);

        _delay_ms(2000);
        logger_transmit();
//         // uint16_t distance = 0;
//         // distance = DSD_GetDistance();
//         // log_data_1("Distance = %d", distance);
//         // log_data_1("Mode = %d", UIM_GetMode());
    }
    return 0;
}