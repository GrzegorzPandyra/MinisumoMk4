/** @file behavior_enemy_detection.c
*   @brief 
*/
#include "logger_tx.h"
#include "behavior_enemy_detection.h"
#include "state_machine.h"
#include "distance_sensor_drv.h"
#include "behavior_actions.h"
#include "os.h"

/*****************************************************
 * Macros
 *****************************************************/
/* The higher the proximity level, the closer enemy is and more dependable readings are */
#define PROXIMITY_THRESHOLD_1 150u
#define PROXIMITY_THRESHOLD_2 300u
#define PROXIMITY_THRESHOLD_3 450u

/* Maximum difference between sensors to consider their reading as valid */
#define SENSOR_DELTA 100U

/*****************************************************
 * Typedefs
 *****************************************************/

/*****************************************************
 * Private variables
 *****************************************************/
/* Enemy Detection Manager */
static struct {
    Ds_Output_T sensor_data;
    Action_Recommendation_T recommendation;
}ed_mgr;

/*****************************************************
 * Private functions
 *****************************************************/
/*****************************************************
 * Public functions
 *****************************************************/
/** 
 * @brief Initialize the module
*/
void BEH_EnemyDetection_Init(void){
    ed_mgr.recommendation.action = BEH_Actions_MoveForward;
    ed_mgr.recommendation.speed = SL_MEDIUM;
    ed_mgr.recommendation.id = ID_ENEMY_DETECTION;
}

/**
 * @brief Analize sensor data and prepare recommendation for main module
 */
void BEH_EnemyDetection_Run(void){
    ed_mgr.sensor_data = Dsdrv_GetDistance();
    if((ed_mgr.sensor_data.l_ds_output >= PROXIMITY_THRESHOLD_3) && (ed_mgr.sensor_data.r_ds_output >= PROXIMITY_THRESHOLD_3)){
        /* Both sensors triggered - close proximity, maximum speed */
        ed_mgr.recommendation.action = BEH_Actions_MoveForward;
        ed_mgr.recommendation.speed = SL_MAX;
        ed_mgr.recommendation.state = SM_ATTACK;

    } else if((ed_mgr.sensor_data.l_ds_output >= PROXIMITY_THRESHOLD_2) && (ed_mgr.sensor_data.r_ds_output >= PROXIMITY_THRESHOLD_2)){
        /* Both sensors triggered - confident reading, faster movement*/
        ed_mgr.recommendation.action = BEH_Actions_MoveForward;
        ed_mgr.recommendation.speed = SL_FAST;
        ed_mgr.recommendation.state = SM_ATTACK;

    } else if((ed_mgr.sensor_data.l_ds_output >= PROXIMITY_THRESHOLD_1) && (ed_mgr.sensor_data.r_ds_output >= PROXIMITY_THRESHOLD_1)){
        /* Both sensors triggered - barely */
        ed_mgr.recommendation.action = BEH_Actions_MoveForward;
        ed_mgr.recommendation.speed = SL_MEDIUM;
        ed_mgr.recommendation.state = SM_ATTACK;

    } else if((ed_mgr.sensor_data.l_ds_output < PROXIMITY_THRESHOLD_1) && (ed_mgr.sensor_data.r_ds_output >= PROXIMITY_THRESHOLD_1)) {
        /* Only right sensor triggered */
        ed_mgr.recommendation.action = BEH_Actions_TurnRight;
        ed_mgr.recommendation.speed = SL_MEDIUM;
        ed_mgr.recommendation.state = SM_ATTACK;

    } else if((ed_mgr.sensor_data.l_ds_output >= PROXIMITY_THRESHOLD_1) && (ed_mgr.sensor_data.r_ds_output < PROXIMITY_THRESHOLD_1)) {
        /* Only left sensor triggered */
        ed_mgr.recommendation.action = BEH_Actions_TurnLeft;
        ed_mgr.recommendation.speed = SL_MEDIUM;
        ed_mgr.recommendation.state = SM_ATTACK;
        
    } else {
        /* Default action */
        ed_mgr.recommendation.action = BEH_Actions_TurnRight;
        ed_mgr.recommendation.speed = SL_MEDIUM;
        ed_mgr.recommendation.state = SM_SEARCH;
    }
}

/**
 * @brief Return recomendation of what action should be taken now
 * @return Action_Recommendation_T current recommendation
 */
Action_Recommendation_T BEH_EnemyDetection_GetRecommendation(void){
    return ed_mgr.recommendation;
}