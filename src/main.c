/*! @file main.c
    @brief Starting point of software
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include "UART_driver.h"
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
    DDRB |= (1<<DDB0);
    while(1){ 
        _delay_ms(1000);
        PORTB |= (1<<PB0);
        _delay_ms(1000);
        PORTB &= ~(1<<PB0);

        log_raw_string("XX");
    }
    return 0;
}