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
#include "utils.h"
#include "motor_drv.h"
#include "logger_tx.h"

#define PWM_INIT 30
#define PWM_MAX 100
#define PWM_PIN PD6
#define PWM_PORT PORTD
#define PWM_DDR DDRD

#define MCTRL_1A_PIN PB0
#define MCTRL_1B_PIN PD7
#define MCTRL_2A_PIN PB2
#define MCTRL_2B_PIN PB1
#define MCTRL_1A_PORT PORTB
#define MCTRL_1B_PORT PORTD
#define MCTRL_2A_PORT PORTB
#define MCTRL_2B_PORT PORTB
#define MCTRL_1A_DDR DDRB
#define MCTRL_1B_DDR DDRD
#define MCTRL_2A_DDR DDRB
#define MCTRL_2B_DDR DDRB

#define PWM_PRECISION_COEFFCIENT 5

typedef struct PWM_Manager_Tag{
    uint8_t set_value;
    uint8_t current_value;
    const uint8_t max_value;
}PWM_Manager_T;

PWM_Manager_T pwm_mgr = {PWM_INIT, 0, PWM_MAX};

/* Set of functions to combine wheel movements into robot movement*/
void Mdrv_Stop(void){
    Utils_SetBit((Register_T)&MCTRL_1A_PORT, MCTRL_1A_PIN, BIT_CLEARED);
    Utils_SetBit((Register_T)&MCTRL_1B_PORT, MCTRL_1B_PIN, BIT_CLEARED);
    Utils_SetBit((Register_T)&MCTRL_2A_PORT, MCTRL_2A_PIN, BIT_CLEARED);
    Utils_SetBit((Register_T)&MCTRL_2B_PORT, MCTRL_2B_PIN, BIT_CLEARED);
}

void Mdrv_Forward(void){
    Utils_SetBit((Register_T)&MCTRL_1A_PORT, MCTRL_1A_PIN, BIT_SET);
    Utils_SetBit((Register_T)&MCTRL_1B_PORT, MCTRL_1B_PIN, BIT_CLEARED);
    Utils_SetBit((Register_T)&MCTRL_2A_PORT, MCTRL_2A_PIN, BIT_SET);
    Utils_SetBit((Register_T)&MCTRL_2B_PORT, MCTRL_2B_PIN, BIT_CLEARED);
}

void Mdrv_Backward(void){
    Utils_SetBit((Register_T)&MCTRL_1A_PORT, MCTRL_1A_PIN, BIT_CLEARED);
    Utils_SetBit((Register_T)&MCTRL_1B_PORT, MCTRL_1B_PIN, BIT_SET);
    Utils_SetBit((Register_T)&MCTRL_2A_PORT, MCTRL_2A_PIN, BIT_CLEARED);
    Utils_SetBit((Register_T)&MCTRL_2B_PORT, MCTRL_2B_PIN, BIT_SET);
}

void Mdrv_TurnRight(void){
    Utils_SetBit((Register_T)&MCTRL_1A_PORT, MCTRL_1A_PIN, BIT_CLEARED);
    Utils_SetBit((Register_T)&MCTRL_1B_PORT, MCTRL_1B_PIN, BIT_SET);
    Utils_SetBit((Register_T)&MCTRL_2A_PORT, MCTRL_2A_PIN, BIT_SET);
    Utils_SetBit((Register_T)&MCTRL_2B_PORT, MCTRL_2B_PIN, BIT_CLEARED);
}

void Mdrv_TurnLeft(void){
    Utils_SetBit((Register_T)&MCTRL_1A_PORT, MCTRL_1A_PIN, BIT_SET);
    Utils_SetBit((Register_T)&MCTRL_1B_PORT, MCTRL_1B_PIN, BIT_CLEARED);
    Utils_SetBit((Register_T)&MCTRL_2A_PORT, MCTRL_2A_PIN, BIT_CLEARED);
    Utils_SetBit((Register_T)&MCTRL_2B_PORT, MCTRL_2B_PIN, BIT_SET);
}

void Mdrv_SetPWM(uint8_t pwm){
    pwm_mgr.set_value = (pwm > PWM_MAX) ? PWM_MAX : pwm-pwm%PWM_PRECISION_COEFFCIENT;
}

/**
 * @brief Called in a fast cyclic task to simulate PWM signal for hardware motor driver
 *  Characteristic of PWM/speed seems to be nonlinear (high speed change for low PWM)
 */
void Mdrv_PWMHandler(void){
    if(pwm_mgr.current_value < pwm_mgr.set_value){
        Utils_SetBit((Register_T)&PWM_PORT, PWM_PIN, BIT_SET);
    } else {
        Utils_SetBit((Register_T)&PWM_PORT, PWM_PIN, BIT_CLEARED);
    }

    if(pwm_mgr.current_value == PWM_MAX){
        pwm_mgr.current_value = 0;
    } else {
        pwm_mgr.current_value += PWM_PRECISION_COEFFCIENT;
    }
}

/**
 * @brief Initialize the module
 */
void Mdrv_Init(void){
    /* Set pins as outputs */
    Utils_SetBit((Register_T)&PWM_DDR, PWM_PIN, BIT_SET);
    Utils_SetBit((Register_T)&MCTRL_1A_DDR, MCTRL_1A_PIN, BIT_SET);
    Utils_SetBit((Register_T)&MCTRL_1B_DDR, MCTRL_1B_PIN, BIT_SET);
    Utils_SetBit((Register_T)&MCTRL_2A_DDR, MCTRL_2A_PIN, BIT_SET);
    Utils_SetBit((Register_T)&MCTRL_2B_DDR, MCTRL_2B_PIN, BIT_SET);
    INFO_P(PGM_MDRV_INIT);
}

/**
 * @brief Automatic check on driver init to let user know if driver is working correctly. Should be called from a slow cyclic task (2-5seconds).
 */
void Mdrv_Selfcheck(void){
    static enum {
        FORWARD = 0u,
        BACKWARD,
        TURN_RIGHT,
        TURN_LEFT,
        PWM_20 = 20,
        PWM_40 = 40,
        PWM_60 = 60,
        PWM_80 = 80,
        PWM_100 = 100,
        STOP
    } test_stage;

    switch (test_stage){
    case FORWARD:
        INFO_P(PGM_MDRV_DIAG_FORWARD);
        Mdrv_Forward();
        test_stage=BACKWARD;
        break;
    case BACKWARD:
        INFO_P(PGM_MDRV_DIAG_BACKWARD);
        Mdrv_Backward();
        test_stage=TURN_RIGHT;
        break;
    case TURN_RIGHT:
        INFO_P(PGM_MDRV_DIAG_TURN_RIGHT);
        Mdrv_TurnRight();
        test_stage=TURN_LEFT;
        break;
    case TURN_LEFT:
        INFO_P(PGM_MDRV_DIAG_TURN_LEFT);
        Mdrv_TurnLeft();
        test_stage=PWM_20;
        break;
    case PWM_20:
        INFO_P(PGM_MDRV_DIAG_PWM20);
        Mdrv_Forward();
        Mdrv_SetPWM(PWM_20);
        test_stage=PWM_40;
        break;
    case PWM_40:
        INFO_P(PGM_MDRV_DIAG_PWM40);
        Mdrv_SetPWM(PWM_40);
        test_stage=PWM_60;
        break;
    case PWM_60:
        INFO_P(PGM_MDRV_DIAG_PWM60);
        Mdrv_SetPWM(PWM_60);
        test_stage=PWM_80;
        break;
    case PWM_80:
        INFO_P(PGM_MDRV_DIAG_PWM80);
        Mdrv_SetPWM(PWM_80);
        test_stage=PWM_100;
        break;
    case PWM_100:
        INFO_P(PGM_MDRV_DIAG_PWM100);
        Mdrv_SetPWM(PWM_100);
        test_stage=STOP;
        break;
    case STOP:
        INFO_P(PGM_MDRV_DIAG_STOP);
        Mdrv_Stop();
        test_stage++;
        break;
    default:
        break;
    }
}