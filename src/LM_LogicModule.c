/** @file LM_LogicModule.c
*   @brief Top-level control, implementation of behaviour algorithm.
*/
#include "UART_TX.h"
#include "LM_LogicModule.h"
#include "DSD_DistanceSensorDrv.h"
#include "LSD_LineSensorDrv.h"
#include "CSD_CollisionSensorDrv.h"
#include "MD_MotorDrv.h"

typedef enum {
    LM_INIT,
    LM_IDLE,
    LM_ARMED,
    LM_SEARCHING,
    LM_LINE_DETECTED,
    LM_ATTACKING
} LM_State_T;

typedef struct Minisumo_Tag{
    LM_State_T LM_state;
    uint8_t armed_cnt;
} Minisumo_T;

static Minisumo_T minisumo = {LM_INIT, 100};

/** @brief Initialize the module
*/
void LM_Init(void){
    log_info_P(PROGMEM_LM_INIT);
    minisumo.LM_state = LM_IDLE;
}

void LM_Run(void){
    switch (minisumo.LM_state)
    {
    case LM_IDLE:
    //check start btn
        break;
    case LM_ARMED:
    //countdown
        break;
    case LM_SEARCHING:
    //check sensors
    //decide action
        break;
    case LM_LINE_DETECTED:
    //reposition
        break;
    case LM_ATTACKING:
    //all forward/backward
        break;
    default:
        break;
    }
}