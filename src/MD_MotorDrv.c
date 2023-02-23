/** @file drive_ctrl.c
*   @brief Interface for controlling the motors (direction and power)
*   Motors are numbered as follows:
*   |1 2|
*   |4 3|
*
*   @note PWM control works in range of 20% - 100% with step every 10%. Values below 20% are insufficient for turning around, therefore should not be used.
*   @note Functions ended with _cbk suffix are for debugging only!
*/
#include <avr/io.h>
// #include <stdlib.h>
// #include <stdio.h>
#include "config.h"
#include "common_const.h"
#include "MCAL.h"
#include "UART_TX.h"
#include "MD_MotorDrv.h"
// #include <util/delay.h>

/* Set of functions to combine wheel movements into robot movement*/
void MDRV_Stop(void){
    MCAL_SetBit((Register_T)&PORTC, MCTRL_1A, BIT_CLEARED);
    MCAL_SetBit((Register_T)&PORTC, MCTRL_1B, BIT_CLEARED);
    MCAL_SetBit((Register_T)&PORTD, MCTRL_2A, BIT_CLEARED);
    MCAL_SetBit((Register_T)&PORTD, MCTRL_2B, BIT_CLEARED);
}

void MDRV_Forward(void){
    MCAL_SetBit((Register_T)&PORTC, MCTRL_1A, BIT_SET);
    MCAL_SetBit((Register_T)&PORTC, MCTRL_1B, BIT_CLEARED);
    MCAL_SetBit((Register_T)&PORTD, MCTRL_2A, BIT_SET);
    MCAL_SetBit((Register_T)&PORTD, MCTRL_2B, BIT_CLEARED);
}

void MDRV_Backward(void){
    MCAL_SetBit((Register_T)&PORTC, MCTRL_1A, BIT_CLEARED);
    MCAL_SetBit((Register_T)&PORTC, MCTRL_1B, BIT_SET);
    MCAL_SetBit((Register_T)&PORTD, MCTRL_2A, BIT_CLEARED);
    MCAL_SetBit((Register_T)&PORTD, MCTRL_2B, BIT_SET);
}

void MDRV_TurnRight(void){
    MCAL_SetBit((Register_T)&PORTC, MCTRL_1A, BIT_SET);
    MCAL_SetBit((Register_T)&PORTC, MCTRL_1B, BIT_CLEARED);
    MCAL_SetBit((Register_T)&PORTD, MCTRL_2A, BIT_CLEARED);
    MCAL_SetBit((Register_T)&PORTD, MCTRL_2B, BIT_SET);
}

void MDRV_TurnLeft(void){
    MCAL_SetBit((Register_T)&PORTC, MCTRL_1A, BIT_CLEARED);
    MCAL_SetBit((Register_T)&PORTC, MCTRL_1B, BIT_SET);
    MCAL_SetBit((Register_T)&PORTD, MCTRL_2A, BIT_SET);
    MCAL_SetBit((Register_T)&PORTD, MCTRL_2B, BIT_CLEARED);
}

void MDRV_Init(void){
    log_info_P(PROGMEM_MDRV_INIT);
}

