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

/**
 * @brief Main function
 */ 
int main(){
    /* Initialization */
    // sei();
    UART_init(F_CPU, BAUD);
    log_info_P(PROGMEM_ECU_INIT);
    MDRV_init();
    I2C_init();
    uint8_t data[] = {0x00};
    while(1){ 
        MDRV_forward();
        _delay_ms(1000);
        data[0] = 0x00;
        I2C_send(data, sizeof(data));
        MDRV_backward();
        _delay_ms(1000);
        data[0] = 0xff;
        I2C_send(data, sizeof(data));
    }
    return 0;
}