/** @file SM_StateMachine.c
*   @brief 
*/
#include "state_machine.h"
#include "logger_tx.h"
#include "stdlib.h"

static struct {
    SM_State_T state;
} sm;


static void Sm_LogStateTransition(void);
/*****************************************************
 * Private variables
 *****************************************************/
/*****************************************************
 * Private functions
 *****************************************************/

static void Sm_LogStateTransition(void){
    switch (sm.state){
        case SM_IDLE:
            INFO_P(PGM_SM_STATE_IDLE);
            break;
        case SM_ARMED:
            INFO_P(PGM_SM_STATE_ARMED);
            break;
        case SM_ATTACK:
            INFO_P(PGM_SM_STATE_ATTACK);
            break;
        case SM_LINE_DETECTED:
            INFO_P(PGM_SM_STATE_LINE_DETECTED);
            break;
        case SM_LINE_CLEARED:
            INFO_P(PGM_SM_STATE_LINE_CLEARED);
            break;
        case SM_SEARCH:
            INFO_P(PGM_SM_STATE_SEARCH);
            break;
        default:
            INFO_P(PGM_SM_STATE_INVALID);
            break;
    }
}
/*****************************************************
 * Public functions
 *****************************************************/

/** @brief Initialize the module
*/
void Sm_Init(void){
    INFO_P(PGM_SM_INIT);
    Sm_SetState(SM_IDLE);
}

/**
 * @brief Sets state of state machine
 * @param state state to be set
 */
void Sm_SetState(SM_State_T new_state){
    SM_State_T old_state = sm.state;
    sm.state = new_state;
    if(old_state != new_state){
        Sm_LogStateTransition();
    }
}

/**
 * @brief Returns current state machine state
 * @return SM_State_T current state
 */
SM_State_T Sm_GetState(void){
    return sm.state;
}
