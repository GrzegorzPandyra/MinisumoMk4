/*! @file main.c
    @brief Starting point of software
*/

#include <avr/interrupt.h>
#include <stdint.h>
#include "UART_DRV.h"
#include "MD_MotorDrv.h"
#include "ISR.h"
#include "config.h"
#include <util/delay.h>
#include "I2C.h"
#include "LSD_LineSensorDrv.h"
#include "DSD_DistanceSensorDrv.h"
#include "ADC.h"
#include "TMR.h"
#include "CSD_CollisionSensorDrv.h"
#include "LM_LogicModule.h"
#include "UIM_UserInputModule.h"

/**
 * @brief Main function
 */ 
int main(){
    /* Initialization */
    sei();
    UART_Init(F_CPU, BAUD);
    MDRV_Init();
    I2C_Init();
    LSD_Init();
    ADC_Init();
    Timer_Init();
    DSD_Init();
    CSD_Init();
    UIM_Init();
    LM_Init();
    log_info_P(PROGMEM_ECU_INIT);
    while(1){ 
        // LM_Run();
        MDRV_Forward();
        // _delay_ms(1000);
        // data[0] = 0x00;
        // I2C_Send(data, sizeof(data));
        // MDRV_Backward();

        MDRV_SetPWM(100);
        _delay_ms(1000);
        MDRV_SetPWM(90);
        _delay_ms(1000);
        MDRV_SetPWM(80);
        _delay_ms(1000);
        MDRV_SetPWM(70);
        _delay_ms(1000);
        MDRV_SetPWM(60);
        _delay_ms(1000);
        MDRV_SetPWM(50);
        _delay_ms(1000);
        MDRV_SetPWM(40);
        _delay_ms(1000);
        MDRV_SetPWM(30);
        _delay_ms(1000);
        MDRV_SetPWM(20);
        _delay_ms(1000);
        MDRV_SetPWM(10);
        _delay_ms(1000);
        MDRV_SetPWM(0);
        _delay_ms(1000);

        _delay_ms(500);
        // uint16_t distance = 0;
        // distance = DSD_GetDistance();
        // log_data_1("Distance = %d", distance);
        // log_data_1("Mode = %d", UIM_GetMode());
    }
    return 0;
}

void Task_10ms(void){
}

void Task_1ms(void){
    MDRV_PWMHandler();
}