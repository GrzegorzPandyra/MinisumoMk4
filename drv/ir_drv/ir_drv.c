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

/*****************************************************
 * Private variables
 *****************************************************/
static IR_State_T drv_status = IR_IDLE;

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
    return drv_status;
}

/**
 * @brief Polling function that checks state of IR module pin
*/
void IRDrv_ReadPin(void){
    bool pin_status = Utils_GetBit((Register_T)&IR_PORT ,IR_TRIGGER_PIN);
    if(!pin_status){
        drv_status = IR_TRIGGERED;
    }
}

/**
 * @brief Clear driver state
*/
void IRDrv_ClearState(void){
    drv_status = IR_IDLE;
}
