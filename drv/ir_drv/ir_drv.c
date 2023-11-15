/** 
 * @file ir_drv.c
 * @brief Rudimentary driver for IR receiver. 
 * The driver outputs a digital signal indicating what button on a pilot has been pressed. 
 * This feature is unnecesary, as we only need to get the trigger for the robot, so any 
 * input will do. Therefore the driver only polls digital IO pin to see if any signal is present,
 * even though the signal coming through is actually digital. 
*/
#include "utils.h"
#include "logger_tx.h"
#include "ir_drv.h"
#include "pin_config.h"

/*****************************************************
 * Macros
 *****************************************************/
#define TASK_PERIOD_MS 10u
#define DEBOUNCE_PERIOD_MS 2000u

/*****************************************************
 * Private variables
 *****************************************************/
static IR_State_T drv_status_raw = IR_IDLE;
static IR_State_T drv_status_debounced = IR_IDLE;

/*****************************************************
 * Private functions
 *****************************************************/
static void DebounceInput(void);

/**
 * @brief Debounce signal to avoid multiple toggling
 */
static void DebounceInput(void){
    static uint16_t debounce_counter = DEBOUNCE_PERIOD_MS;
    if(((debounce_counter * TASK_PERIOD_MS) >= DEBOUNCE_PERIOD_MS) && (drv_status_raw == IR_TRIGGERED)){
        drv_status_debounced = IR_TRIGGERED;
        debounce_counter = 0u;
    } else {
        debounce_counter++;
    }
}

/**********************************************************************
* Public functions 
***********************************************************************/

/** 
 * @brief Initialize the module
*/
void IRDrv_Init(void){
    INFO_P(PGM_IRDRV_INIT);
}

/**
 * @brief Return driver status
 */
IR_State_T IRDrv_GetState(void){
    IR_State_T result = drv_status_debounced;
    drv_status_debounced = IR_IDLE;
    return result;
}

/**
 * @brief Polling function that checks state of IR module pin
*/
void IRDrv_ReadPin(void){
    bool pin_status = Utils_GetBit((Register_T)&IR_PORT ,IR_TRIGGER_PIN);
    if(!pin_status){
        drv_status_raw = IR_TRIGGERED;
    } else {
        drv_status_raw = IR_IDLE;
    }
    DebounceInput();
}
