/*! @file timer.c
    @brief timer implementation
*/
#include "MCAL.h"
#include "TMR.h"
#include "UART_TX.h"

void Timer_Init(void){
    /* Set timer clk source and prescaler(256) */
    MCAL_SetBit((Register_T)&TCCR0B, CS00, BIT_SET);
    MCAL_SetBit((Register_T)&TCCR0B, CS01, BIT_CLEARED);
    MCAL_SetBit((Register_T)&TCCR0B, CS02, BIT_SET);

    /* Enable timer0 overflow interrupt */
    MCAL_SetBit((Register_T)&TIMSK0, TOIE0, BIT_SET);
    
    log_info_P(PROGMEM_TIMER_INIT);
}