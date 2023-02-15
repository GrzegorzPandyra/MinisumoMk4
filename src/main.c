/*! @file main.c
    @brief Starting point of software
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include "ISR.h"
#include "config.h"
#include <util/delay.h>

/**
 * @brief Main function
 */ 
int main(){
    /* Initialization */
    // sei();
    serial_init(F_CPU, BAUD);
    DDRB |= (1<<DDB0);
    int i;
    while(1){ 
        _delay_ms(1000);
        PORTB |= (1<<PB0);
        _delay_ms(1000);
        PORTB &= ~(1<<PB0);

        // serial_log_raw_string("X");
        while ( !( UCSR0A & (1<<UDRE0)) )
        ;
        UDR0 = '1';
    }
    return 0;
}