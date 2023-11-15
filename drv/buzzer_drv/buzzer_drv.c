/** 
 * @file buzzer_drv.c
 * @brief 
*/
#include "utils.h"
#include "logger_tx.h"
#include "buzzer_drv.h"
#include "pin_config.h"

/*****************************************************
 * Macros
 *****************************************************/
#define TASK_PERIOD_MS 10u

/*****************************************************
 * Private variables
 *****************************************************/
static uint16_t buzzer_timer = 0u;

/*****************************************************
 * Private functions
 *****************************************************/

/**********************************************************************
* Public functions 
***********************************************************************/

/** 
 * @brief Initialize the module
*/
void BuzzDrv_Init(void){
    /* Set pin as output */
    Utils_SetBit((Register_T)&BUZZER_DDRx, BUZZER_PIN, BIT_SET);
    BuzzDrv_BuzzON(BUZZ_LONG_MS);
}

/** 
 * @brief Start buzzing
 * Trims values that are not multiples of TASK_PERIOD_MS
*/
void BuzzDrv_BuzzON(uint16_t buzz_time){
    #ifndef COMPETITION_MODE
        buzzer_timer = buzz_time - (buzz_time % TASK_PERIOD_MS);
        Utils_SetBit((Register_T)&BUZZER_PORTx, BUZZER_PIN, BIT_SET);
    #endif
}

/** 
 * @brief Stop buzzing
*/
void BuzzDrv_BuzzOFF(void){
    #ifndef COMPETITION_MODE
        Utils_SetBit((Register_T)&BUZZER_PORTx, BUZZER_PIN, BIT_CLEARED);
    #endif
}

/** 
 * @brief Run buzzer
*/
void BuzzDrv_Run(void){
    if(buzzer_timer > 0u){
        buzzer_timer -= TASK_PERIOD_MS;
    } else {
        BuzzDrv_BuzzOFF();
    }
}