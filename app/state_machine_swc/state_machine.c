/** @file SM_StateMachine.c
*   @brief 
*/
#include "state_machine.h"
#include "logger_tx.h"
#include "stdlib.h"

static struct {
    SM_State_T state;
} sm;

/*****************************************************
 * Private variables
 *****************************************************/
/*****************************************************
 * Private functions
 *****************************************************/
/*****************************************************
 * Public functions
 *****************************************************/

/** @brief Initialize the module
*/
void Sm_Init(void){
    sm.state = SM_IDLE;
    INFO_P(PGM_SM_INIT);
}

/**
 * @brief Sets state of state machine
 * @param state state to be set
 */
void Sm_SetState(SM_State_T state){
    sm.state = state;
}

/**
 * @brief Returns current state machine state
 * @return SM_State_T current state
 */
SM_State_T Sm_GetState(void){
    return sm.state;
}
