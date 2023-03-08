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
#include "config.h"
#include "common_const.h"
#include "MCAL.h"
#include "UART_TX.h"
#include "MD_MotorDrv.h"

#define PWM_INIT 30
#define PWM_MAX 100
#define PWM_PIN PC3

#define PWM_PRECISION_COEFFCIENT 5

typedef struct PWM_Manager_Tag{
    uint8_t set_value;
    uint8_t current_value;
    const uint8_t max_value;
}PWM_Manager_T;

PWM_Manager_T PWM_manager = {PWM_INIT, 0, PWM_MAX};

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

void MDRV_SetPWM(uint8_t pwm){
    PWM_manager.set_value = (pwm > PWM_MAX) ? PWM_MAX : pwm-pwm%PWM_PRECISION_COEFFCIENT;
}

/**
 * @brief Called in a fast cyclic task to simulate PWM signal for hardware motor driver
 *  Characteristic of PWM/speed seems to be nonlinear (high speed change for low PWM)
 */
void MDRV_PWMHandler(void){
    if(PWM_manager.current_value < PWM_manager.set_value){
        MCAL_SetBit((Register_T)&PORTC, PWM_PIN, BIT_SET);
    } else {
        MCAL_SetBit((Register_T)&PORTC, PWM_PIN, BIT_CLEARED);
    }

    if(PWM_manager.current_value == PWM_MAX){
        PWM_manager.current_value = 0;
    } else {
        PWM_manager.current_value += PWM_PRECISION_COEFFCIENT;
    }
}

/**
 * @brief Initialize the module
 */
void MDRV_Init(void){
    MCAL_SetBit((Register_T)&DDRC, PWM_PIN, BIT_SET);
    log_info_P(PROGMEM_MDRV_INIT);
}

