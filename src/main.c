/*! @file main.c
    @brief Starting point of software
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include "ISR.h"
#include "config.h"

/**
 * @brief Main function
 */ 
int main(){
    /* Initialization */
    sei();
    while(1){ 
        // UART_log("HEARTBEAT");
    }
    return 0;
}