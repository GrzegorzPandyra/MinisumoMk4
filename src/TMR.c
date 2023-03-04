/*! @file timer.c
    @brief timer0 implementation
    16MHz/64/250 -> 10ms 
*/
#include "MCAL.h"
#include "TMR.h"
#include "UART_TX.h"

#define TIMER0_COMPA 250

void Timer_Init(void){
    /* Set timer clk source and prescaler(64) */
    MCAL_SetBit((Register_T)&TCCR0B, CS00, BIT_SET);
    MCAL_SetBit((Register_T)&TCCR0B, CS01, BIT_SET);
    MCAL_SetBit((Register_T)&TCCR0B, CS02, BIT_CLEARED);

    /* Enable timer0 overflow interrupt */
    MCAL_SetBit((Register_T)&TIMSK0, TOIE0, BIT_SET);

    /* Enable timer0 compare interrupt A */
    MCAL_SetBit((Register_T)&TIMSK0, OCIE0A, BIT_SET);
    
    /* Set compare value A for timer0 */
    MCAL_WriteRegister((Register_T)&OCR0A, TIMER0_COMPA);

    
    log_info_P(PROGMEM_TIMER_INIT);
}

void Timer_Clear(void){
    MCAL_WriteRegister((Register_T)&TCNT0, 0);
}