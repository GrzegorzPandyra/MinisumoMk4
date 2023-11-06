/** @file behavior_actions.c
*   @brief Implementation of possible actions to be taken by behavior SWC.
*/
#include "logger_tx.h"
#include "motor_drv.h"
#include "behavior_actions.h"
#include "stdbool.h"
/*****************************************************
 * Typedefs
 *****************************************************/
typedef enum{
    MOVE_FORWARD,
    MOVE_BACKWARD,
    TURN_RIGHT,
    TURN_LEFT,
    TURN,
    STOP
} Last_Action_T;
/*****************************************************
 * Private variables
 *****************************************************/
static Last_Action_T last_action = MOVE_FORWARD;
/*****************************************************
 * Private functions
 *****************************************************/

/*****************************************************
 * Public functions
 *****************************************************/
void BEH_Actions_MoveForward(void){
    Mdrv_Forward();
    last_action = MOVE_FORWARD;
    #ifdef ENABLE_BEH_DIAGNOSTICS
        INFO("FW");
    #endif
}
void BEH_Actions_MoveBackward(void){
    Mdrv_Backward();
    last_action = MOVE_BACKWARD;
    #ifdef ENABLE_BEH_DIAGNOSTICS
        INFO("BW");
    #endif
}
void BEH_Actions_TurnRight(void){
    Mdrv_TurnRight();
    last_action = TURN_RIGHT;
    #ifdef ENABLE_BEH_DIAGNOSTICS
        INFO("TR");
    #endif
}
void BEH_Actions_TurnLeft(void){
    Mdrv_TurnLeft();
    last_action = TURN_LEFT;
    #ifdef ENABLE_BEH_DIAGNOSTICS
        INFO("TL");
    #endif
}
void BEH_Actions_Turn(void){
    static bool direction_flag = false;
    if(direction_flag){
        Mdrv_TurnLeft();
    } else {
        Mdrv_TurnRight();
    }

    /* Switch direction only if Turn is a new action picked. Otherwise robot won't move because of alternating turns. */
    if(last_action != TURN){
        direction_flag = !direction_flag;
    }
    last_action = TURN;
    #ifdef ENABLE_BEH_DIAGNOSTICS
        INFO("T");
    #endif
}
void BEH_Actions_Stop(void){
    Mdrv_Stop();
    last_action = STOP;
    #ifdef ENABLE_BEH_DIAGNOSTICS
        INFO("STOP");
    #endif
}
void BEH_Actions_SetSpeed(Speed_Level_T speed){
    Mdrv_SetPWM((uint8_t)speed);
}