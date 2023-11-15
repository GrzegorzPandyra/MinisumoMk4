/** @file behavior_search.c
*   @brief Implements default movement in the ring via defined strategies. 
*/
#include "logger_tx.h"
#include "behavior_search.h"
#include "behavior_actions.h"
#include "state_machine.h"
#include "os.h"

/*****************************************************
 * Macros
 *****************************************************/
#define SPIN_AND_GO_MIN_ACTION_TIME_MS 500u
#define SPIN_AND_GO_MAX_ACTION_TIME_MS 1000

/*****************************************************
 * Typedefs
 *****************************************************/

typedef enum{
    STRAT_SPIN_AND_GO
} Search_Strategy_T;


/*****************************************************
 * Private variables
 *****************************************************/
/* Search Manager */
static struct {
    Action_Recommendation_T recommendation;
    Search_Strategy_T strategy;
}s_mgr;

/*****************************************************
 * Private functions
 *****************************************************/
static void Strat_SpinAndGo(void);

/**
 * @brief This strategy consists of alternating between turning around and going forward for random times
 */
static void Strat_SpinAndGo(void){
    static enum {
        SPIN,
        GO
    } action = SPIN;
    static uint32_t timer = 0u;

    /* Check if action timer has expired */
    if(OS_GetTime() >= timer){
        /* Set new action timer */
        timer = 10*OS_GetRandom();
        timer = (timer > SPIN_AND_GO_MAX_ACTION_TIME_MS) ? SPIN_AND_GO_MAX_ACTION_TIME_MS : timer; 
        timer = (timer < SPIN_AND_GO_MIN_ACTION_TIME_MS) ? SPIN_AND_GO_MIN_ACTION_TIME_MS : timer; 
        timer += OS_GetTime();

        /* Pick new action */
        if(action == GO){
            action = SPIN;
            s_mgr.recommendation.action = BEH_Actions_Turn;
            s_mgr.recommendation.speed = SL_MEDIUM;
        } else {
            action = GO;
            s_mgr.recommendation.action = BEH_Actions_MoveForward;
            s_mgr.recommendation.speed = SL_FAST;
            /* Adjustment to give preference to moving forward */
            timer += SPIN_AND_GO_MIN_ACTION_TIME_MS;
        }
    }
}
/*****************************************************
 * Public functions
 *****************************************************/
/** 
 * @brief Initialize the module
*/
void BEH_Search_Init(void){
    s_mgr.recommendation.action = BEH_Actions_MoveForward;
    s_mgr.recommendation.speed = SL_MEDIUM;
    s_mgr.recommendation.id = ID_SEARCH;
    s_mgr.recommendation.state = SM_SEARCH;
    s_mgr.strategy = STRAT_SPIN_AND_GO;
}

/**
 * @brief Execute current strategy
 */
void BEH_Search_Run(void){
    switch (s_mgr.strategy)
    {
    case STRAT_SPIN_AND_GO:
        Strat_SpinAndGo();
        break;
    
    default:
        break;
    }
}

/**
 * @brief Return current recommendation
 * @return Action_Recommendation_T Recoommended action
 */
Action_Recommendation_T BEH_Search_GetRecommendation(void){
    return s_mgr.recommendation;
}
