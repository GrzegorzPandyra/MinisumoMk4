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

/**
 * @brief Main function
 */ 
int main(){
    /* Initialization */
    // sei();
    UART_init(F_CPU, BAUD);
    log_info_P(PROGMEM_ECU_INIT);
    MDRV_init();
    // DDRB |= (1<<DDB0);
    while(1){ 
        MDRV_forward();
        _delay_ms(1000);
        MDRV_backward();
        _delay_ms(1000);
        // PORTB ^= (1<<PB0);

        log_raw_string("XX");
    }
    return 0;
}