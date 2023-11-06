/** @file behavior_main.c
*   @brief Top-level control, implementation of behaviour algorithm.
*/
#include "logger_tx.h"
#include "behavior_main.h"
#include "behavior_line_detection.h"
#include "behavior_enemy_detection.h"
#include "behavior_search.h"
#include "state_machine.h"
/*****************************************************
 * Private variables
 *****************************************************/
/* Behavior Manager */
static struct {
    Action_Recommendation_T ld_rec;
    Action_Recommendation_T ed_rec;
    Action_Recommendation_T s_rec;
}beh_mgr;

/*****************************************************
 * Private functions
 *****************************************************/

/**
 * @brief Analyze recommendations from submodules and pick action to take
 */
static void PickRecommendation(void){
    Action_Recommendation_T* picked_recommendation = NULL;
    if((beh_mgr.ld_rec.state == SM_LINE_DETECTED) || (beh_mgr.ld_rec.state == SM_LINE_CLEARED)){
        picked_recommendation = &beh_mgr.ld_rec;
    } else if(beh_mgr.ed_rec.state == SM_ATTACK) {
        picked_recommendation = &beh_mgr.ed_rec;
    } else /* beh_mgr.s_rec.state == SM_SEARCH */ {
        picked_recommendation = &beh_mgr.s_rec;
    }
    
    Sm_SetState(picked_recommendation->state);
    BEH_Actions_SetSpeed(picked_recommendation->speed);
    picked_recommendation->action();
}

/*****************************************************
 * Public functions
 *****************************************************/

/** @brief Initialize the module
*/
void BEH_Init(void){
    BEH_LineDetection_Init();
    BEH_EnemyDetection_Init();
    BEH_Search_Init();
    INFO_P(PGM_BEH_INIT);
}

/**
 * @brief Top level function of behavior module
 * Fall-through switch is intended. 
 */
void BEH_Run(void){
    switch (Sm_GetState()){
    case SM_IDLE:
    case SM_ARMED:
        BEH_Actions_Stop();
        break;
    case SM_SEARCH:
    case SM_ATTACK:
    case SM_LINE_DETECTED:
    case SM_LINE_CLEARED:
        BEH_Search_Run();
        BEH_EnemyDetection_Run();
        BEH_LineDetection_Run();
        beh_mgr.ld_rec = BEH_LineDetection_GetRecommendation();
        beh_mgr.ed_rec = BEH_EnemyDetection_GetRecommendation();
        beh_mgr.s_rec  = BEH_Search_GetRecommendation();
        PickRecommendation();
        break;
    default:
        break;
    }
}