/** @file LM_LogicModule.c
*   @brief Top-level control, implementation of behaviour algorithm.
*/
#include "UART_TX.h"
#include "LM_LogicModule.h"
#include "LM_Search.h"
#include "DSD_DistanceSensorDrv.h"
#include "LSD_LineSensorDrv.h"
#include "CSD_CollisionSensorDrv.h"
#include "MD_MotorDrv.h"
#include "UIM_UserInputModule.h"

#define ARMED_CNT_TOP 100
#define ARMED_CNT_DECREMENT 10
#define DS_TRIGGER_THRESHOLD 50
#define ACTION_TIME_MS 100
#define MOVE_NUMBER 5

typedef enum {
    LM_INIT,
    LM_IDLE,
    LM_ARMED,
    LM_SEARCHING,
    LM_LINE_DETECTED,
    LM_ATTACKING
} LM_State_T;

typedef struct Sensors_Tag{
    uint8_t line_status;
    CollisionStatus_T collision_status;
    uint8_t distance;
} Sensors_T;

typedef struct Minisumo_Tag{
    LM_State_T LM_state;
    uint8_t armed_cnt;
    uint8_t move_cnt;
    Direction_T movement;
    Sensors_T sensors;
} Minisumo_T;

static Minisumo_T minisumo = {LM_INIT, ARMED_CNT_TOP, 0, FORWARD, {0, NO_COLLISION, 0}};

static void SensorCheck(void);
static void ClearSensorState(void);
static void StateTransition(LM_State_T state);
/*****************************************************
 * Private functions
 *****************************************************/
static void SensorCheck(void){
    uint8_t line_sensor_status = LSD_GetLineStatus();
    CollisionStatus_T collision_sensor_status = CSD_GetCollisionStatus();
    uint8_t distance_sensor_status = DSD_GetDistance();
    if(line_sensor_status != LS_NOT_TRIGGERED){
        StateTransition(LM_LINE_DETECTED);
        minisumo.sensors.line_status = line_sensor_status;
    } else if (collision_sensor_status != NO_COLLISION){
        StateTransition(LM_ATTACKING);
        minisumo.sensors.collision_status = collision_sensor_status;
    } else if (distance_sensor_status > DS_TRIGGER_THRESHOLD){
        StateTransition(LM_ATTACKING);
        minisumo.sensors.distance = distance_sensor_status;
    }
}

static void ClearSensorState(void){
    minisumo.sensors.collision_status = NO_COLLISION;
    minisumo.sensors.distance = 0;
    minisumo.sensors.line_status = 0;
}

static void StateTransition(LM_State_T state){
    minisumo.LM_state = state;
    // log_data_1("LM_State: %d", state);
}

/*****************************************************
 * Public functions
 *****************************************************/

/** @brief Initialize the module
*/
void LM_Init(void){
    LM_Search_Init();
    StateTransition(LM_IDLE);
    log_info_P(PROGMEM_LM_INIT);
}

void LM_Run(void){
    ClearSensorState();
    SensorCheck();
    switch (minisumo.LM_state)
    {
    case LM_IDLE:
        if(UIM_GetStartBtnState() == BTN_PRESSED){
            StateTransition(LM_ARMED);
            minisumo.armed_cnt = ARMED_CNT_TOP;
            log_info("ARMED!");
        }
        //diode off
        break;
    case LM_ARMED:
        minisumo.armed_cnt -= ARMED_CNT_DECREMENT;
        if(minisumo.armed_cnt <= 0 ){
            StateTransition(LM_SEARCHING);
            log_info("START!");
        }
        //add diode blinking
        break;
    case LM_SEARCHING:
        if(minisumo.move_cnt == 0){
            LM_Search();
            minisumo.move_cnt = MOVE_NUMBER;
        } else {
            minisumo.move_cnt--;
        }
        break;
    case LM_LINE_DETECTED:
    //reposition
        break;
    case LM_ATTACKING:
        if(minisumo.move_cnt == 0){
            if (minisumo.sensors.collision_status == FRONT_COLLISION){
                MDRV_Forward();
            } else if (minisumo.sensors.collision_status == REAR_COLLISION){
                MDRV_Backward();
            } else if (minisumo.sensors.distance > DS_TRIGGER_THRESHOLD){
                MDRV_Forward();
            }
            minisumo.move_cnt = MOVE_NUMBER;
        } else {
            minisumo.move_cnt--;
        }
        break;
    default:
        break;
    }
    //execute delay
}