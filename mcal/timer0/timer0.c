/*! @file timer0.c
    @brief timer0 implementation
    16MHz/64/250 -> 10ms 
*/
#include "utils.h"
#include "timer0.h"
#include "logger_tx.h"

/* Value picked via testing to achieve real time measurement */
#define TIMER0_COMPA 150

void Timer0_Init(void){
    /* Set timer clk source and prescaler(64) */
    Utils_SetBit((Register_T)&TCCR0B, CS00, BIT_SET);
    Utils_SetBit((Register_T)&TCCR0B, CS01, BIT_SET);
    Utils_SetBit((Register_T)&TCCR0B, CS02, BIT_CLEARED);

    /* Enable timer0 overflow interrupt */
    Utils_SetBit((Register_T)&TIMSK0, TOIE0, BIT_SET);

    /* Enable timer0 compare interrupt A */
    Utils_SetBit((Register_T)&TIMSK0, OCIE0A, BIT_SET);
    
    /* Set compare value A for timer0 */
    Utils_WriteRegister((Register_T)&OCR0A, TIMER0_COMPA);

    INFO_P(PGM_TIMER_INIT);
}

void Timer0_Clear(void){
    Utils_WriteRegister((Register_T)&TCNT0, 0);
}