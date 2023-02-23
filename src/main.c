/*! @file main.c
    @brief Starting point of software
*/

// #include <avr/io.h> //to be removed
#include <avr/interrupt.h>
#include <stdint.h>
#include "UART_driver.h"
#include "motor_drv.h"
#include "ISR.h"
#include "config.h"
#include <util/delay.h>
#include "I2C.h"
#include "line_sensor_drv.h"
#include "distance_sensor_drv.h"
#include "ADC.h"
#include "timer.h"

/**
 * @brief Main function
 */ 
int main(){
    /* Initialization */
    sei();
    UART_Init(F_CPU, BAUD);
    log_info_P(PROGMEM_ECU_INIT);
    MDRV_Init();
    I2C_Init();
    LSD_Init();
    ADC_Init();
    Timer_Init();
    DSD_Init();
    // uint8_t data[] = {0x00};
    while(1){ 
        // MDRV_Forward();
        // _delay_ms(1000);
        // data[0] = 0x00;
        // I2C_Send(data, sizeof(data));
        // MDRV_Backward();
        // _delay_ms(1000);
        // data[0] = 0xff;
        // I2C_Send(data, sizeof(data));

        _delay_ms(500);
        uint16_t distance = 0;
        distance = DSD_GetDistance();
        log_data_1("Distance = %d", distance);
    }
    return 0;
}