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
static void NewActionNotification(Last_Action_T current_action);

/**
 * @brief Print new action that is being executed
 */
static void NewActionNotification(Last_Action_T current_action){
    if(current_action != last_action){
        switch (current_action){
        case MOVE_FORWARD:
            INFO("ACTION: FORWARD");
            break;
        case MOVE_BACKWARD:
            INFO("ACTION: BACKWARWD");
            break;
        case TURN_RIGHT:
            INFO("ACTION: TURN RIGHT");
            break;
        case TURN_LEFT:
            INFO("ACTION: TURN LEFT");
            break;
        case TURN:
            INFO("ACTION: TURN");
            break;
        case STOP:
            INFO("ACTION: STOP");
            break;
        default:
            break;
        }
    }
}
/*****************************************************
 * Public functions
 *****************************************************/
void BEH_Actions_MoveForward(void){
    Mdrv_Forward();
    NewActionNotification(MOVE_FORWARD);
    last_action = MOVE_FORWARD;
}
void BEH_Actions_MoveBackward(void){
    Mdrv_Backward();
    NewActionNotification(MOVE_BACKWARD);
    last_action = MOVE_BACKWARD;
}
void BEH_Actions_TurnRight(void){
    Mdrv_TurnRight();
    NewActionNotification(TURN_RIGHT);
    last_action = TURN_RIGHT;
}
void BEH_Actions_TurnLeft(void){
    Mdrv_TurnLeft();
    NewActionNotification(TURN_LEFT);
    last_action = TURN_LEFT;
}
void BEH_Actions_Turn(void){
    static bool direction_flag = false;
    if(direction_flag){
        Mdrv_TurnLeft();
    } else {
        Mdrv_TurnRight();
    }
    NewActionNotification(TURN);

    /* Switch direction only if Turn is a new action picked. Otherwise robot won't move because of alternating turns. */
    if(last_action != TURN){
        direction_flag = !direction_flag;
    }
    last_action = TURN;
}
void BEH_Actions_Stop(void){
    Mdrv_Stop();
    NewActionNotification(STOP);
    last_action = STOP;
}
void BEH_Actions_SetSpeed(Speed_Level_T speed){
    Mdrv_SetPWM((uint8_t)speed);
}