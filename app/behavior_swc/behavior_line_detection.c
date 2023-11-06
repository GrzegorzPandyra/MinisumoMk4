/** @file behavior_line_detection.c
*   @brief Line detection is tasked with keeping the robot away from the line.
*/
#include "logger_tx.h"
#include "behavior_line_detection.h"
#include "line_sensor_drv.h"
#include "state_machine.h"
#include "behavior_actions.h"
#include "stdbool.h"
#include "os.h"

/*****************************************************
 * Macros
 *****************************************************/
/*  LINE DETECTION MODE 
    Strict mode means, that in order for line to be detected, both sensors in cluster need to be triggered. 
    Careful mode requires only one sensor triggered to consider line detection. */
#define STRICT  1u
#define CAREFUL 2u

#if LINE_DETECTION_MODE==STRICT
    #define MODE_OPERATOR &&
#elif LINE_DETECTION_MODE==CAREFUL
    #define MODE_OPERATOR ||
#else
    #error "Unsupported line detection MODE - check your config!"
#endif

/* LINE SENSOR STATUS */
#define LS_TRIGGERED 0u
#define LS_NOT_TRIGGERED 1u

#define GET_ARR_LEN(arr) (sizeof(arr)/sizeof(arr[0u]))

#define CLEAR_TIME_MS 200u

/*****************************************************
 * Typedefs
 *****************************************************/
typedef struct {
    bool top_left;
    bool top_right;
    bool bottom_left;
    bool bottom_right;
} Sensor_Status_T;

typedef struct {
    Sensor_Status_T status;
    Action_Cbk_T action_cbk;
} Status_To_Action_Map_T;

/*****************************************************
 * Private variables
 *****************************************************/
/* Line Detection Manager */
static struct {
    Sensor_Status_T LS_status;
    uint32_t clear_timer;
    Action_Recommendation_T recommendation;
}ld_mgr;

/*****************************************************
 * Private functions
 *****************************************************/
static Action_Cbk_T PickAction(void);
static bool CheckLine(void);

/**
 * @brief Map line sensor input to actions
 * @return Action_Cbk_T Selected action
 */
static Action_Cbk_T PickAction(void){
    Action_Cbk_T new_action_cbk = NULL;
    static const Status_To_Action_Map_T map[] = {
        /*                    TOP LEFT           TOP RIGHT       BOTTOM LEFT      BOTTOM RIGHT             CALLBACK          */
        {(Sensor_Status_T){LS_NOT_TRIGGERED, LS_NOT_TRIGGERED, LS_NOT_TRIGGERED, LS_TRIGGERED    }, BEH_Actions_MoveForward  },
        {(Sensor_Status_T){LS_NOT_TRIGGERED, LS_NOT_TRIGGERED, LS_TRIGGERED    , LS_NOT_TRIGGERED}, BEH_Actions_MoveForward  },
        {(Sensor_Status_T){LS_NOT_TRIGGERED, LS_NOT_TRIGGERED, LS_TRIGGERED    , LS_TRIGGERED    }, BEH_Actions_MoveForward  },
        {(Sensor_Status_T){LS_TRIGGERED    , LS_NOT_TRIGGERED, LS_NOT_TRIGGERED, LS_NOT_TRIGGERED}, BEH_Actions_MoveBackward },
        {(Sensor_Status_T){LS_NOT_TRIGGERED, LS_TRIGGERED    , LS_NOT_TRIGGERED, LS_NOT_TRIGGERED}, BEH_Actions_MoveBackward },
        {(Sensor_Status_T){LS_TRIGGERED    , LS_TRIGGERED    , LS_NOT_TRIGGERED, LS_NOT_TRIGGERED}, BEH_Actions_MoveBackward },
        {(Sensor_Status_T){LS_NOT_TRIGGERED, LS_TRIGGERED    , LS_NOT_TRIGGERED, LS_TRIGGERED    }, BEH_Actions_TurnLeft     },
        {(Sensor_Status_T){LS_TRIGGERED    , LS_NOT_TRIGGERED, LS_TRIGGERED    , LS_NOT_TRIGGERED}, BEH_Actions_TurnRight    },
        {(Sensor_Status_T){LS_NOT_TRIGGERED, LS_NOT_TRIGGERED, LS_NOT_TRIGGERED, LS_NOT_TRIGGERED}, BEH_Actions_Turn         },
        /* Illegal combinations */
        {(Sensor_Status_T){LS_TRIGGERED    , LS_TRIGGERED    , LS_TRIGGERED    , LS_TRIGGERED    }, BEH_Actions_Turn         },
        {(Sensor_Status_T){LS_TRIGGERED    , LS_TRIGGERED    , LS_TRIGGERED    , LS_NOT_TRIGGERED}, BEH_Actions_Turn         },
        {(Sensor_Status_T){LS_TRIGGERED    , LS_TRIGGERED    , LS_NOT_TRIGGERED, LS_TRIGGERED    }, BEH_Actions_Turn         },
        {(Sensor_Status_T){LS_TRIGGERED    , LS_NOT_TRIGGERED, LS_TRIGGERED    , LS_TRIGGERED    }, BEH_Actions_Turn         },
        {(Sensor_Status_T){LS_NOT_TRIGGERED, LS_TRIGGERED    , LS_TRIGGERED    , LS_TRIGGERED    }, BEH_Actions_Turn         }
    };

    for (uint8_t i=0u; i<GET_ARR_LEN(map); i++)
    {
        if ((ld_mgr.LS_status.top_left     == map[i].status.top_left    ) &&
            (ld_mgr.LS_status.top_right    == map[i].status.top_right   ) &&
            (ld_mgr.LS_status.bottom_left  == map[i].status.bottom_left ) &&
            (ld_mgr.LS_status.bottom_right == map[i].status.bottom_right))
        {
            new_action_cbk = map[i].action_cbk;
            break;
        }
    }
    return new_action_cbk;
}

/**
 * @brief Check line status and update line detection manager
 * @return TRUE if line has been detected, FALSE otherwise
 */
static bool CheckLine(void){
    Ls_Status_T ls_status = Ls_GetLineStatus();
    bool line_detected = false;

    /* Top left sensor */
    if((ls_status.ls0 == LS_TRIGGERED) MODE_OPERATOR (ls_status.ls1 == LS_TRIGGERED)){
        ld_mgr.LS_status.top_left = LS_TRIGGERED;
        line_detected = true;
        #ifdef ENABLE_BEH_DIAGNOSTICS
            WARNING("Top left LS triggered");
        #endif
    } else {
        ld_mgr.LS_status.top_left = LS_NOT_TRIGGERED;
    }
    
    /* Top right sensor */
    if((ls_status.ls2 == LS_TRIGGERED) MODE_OPERATOR (ls_status.ls3 == LS_TRIGGERED)){
        ld_mgr.LS_status.top_right = LS_TRIGGERED;
        line_detected = true;
        #ifdef ENABLE_BEH_DIAGNOSTICS
            WARNING("Top right LS triggered");
        #endif
    } else {
        ld_mgr.LS_status.top_right = LS_NOT_TRIGGERED;
    }

    /* Bottom right sensor */
    if((ls_status.ls4 == LS_TRIGGERED) MODE_OPERATOR (ls_status.ls5 == LS_TRIGGERED)){
        ld_mgr.LS_status.bottom_right = LS_TRIGGERED;
        line_detected = true;
        #ifdef ENABLE_BEH_DIAGNOSTICS
            WARNING("Bottom right LS triggered");
        #endif
    } else {
        ld_mgr.LS_status.bottom_right = LS_NOT_TRIGGERED;
    }

    /* Bottom left sensor */
    if((ls_status.ls6 == LS_TRIGGERED) MODE_OPERATOR (ls_status.ls7 == LS_TRIGGERED)){
        ld_mgr.LS_status.bottom_left = LS_TRIGGERED;
        line_detected = true;
        #ifdef ENABLE_BEH_DIAGNOSTICS
            WARNING("Bottom left LS triggered");
        #endif
    } else {
        ld_mgr.LS_status.bottom_left = LS_NOT_TRIGGERED;
    }

    return line_detected;
}


/*****************************************************
 * Public functions
 *****************************************************/
/** 
 * @brief Initialize the module
*/
void BEH_LineDetection_Init(void){
    #if DLINE_DETECTION_MODE==STRICT
        INFO_P(PGM_BEH_LD_MODE_STRICT);
    #else
        INFO_P(PGM_BEH_LD_MODE_CAREFUL);
    #endif
    ld_mgr.LS_status.top_left = LS_NOT_TRIGGERED;
    ld_mgr.LS_status.top_right = LS_NOT_TRIGGERED;
    ld_mgr.LS_status.bottom_left = LS_NOT_TRIGGERED;
    ld_mgr.LS_status.bottom_right = LS_NOT_TRIGGERED;
    ld_mgr.recommendation.action = BEH_Actions_MoveForward;
    ld_mgr.recommendation.speed = SL_MEDIUM;
    ld_mgr.recommendation.id = ID_LINE_DETECTION;
    ld_mgr.recommendation.state = SM_SEARCH;
    ld_mgr.clear_timer = 0u;
}

/**
 * @brief This function maps sensor input to predefined actions
 */
void BEH_LineDetection_Run(void){
    SM_State_T previous_state = ld_mgr.recommendation.state;
    bool line_detected = CheckLine();
    ld_mgr.recommendation.action = PickAction();

    if(line_detected){
        /* Take immediate action to gat away from the line */
        ld_mgr.recommendation.state = SM_LINE_DETECTED;
        ld_mgr.recommendation.speed = SL_MAX;
        ld_mgr.clear_timer = 0u;
    } else if((previous_state == SM_LINE_DETECTED)) {
        /* Line has been just cleared, now we must go away from it */
        ld_mgr.recommendation.state = SM_LINE_CLEARED;
        ld_mgr.recommendation.speed = SL_SLOW;
        ld_mgr.clear_timer = OS_GetTime();
    } else if(Sm_GetState() == SM_LINE_CLEARED){
        /* clear timer handling */
        if((ld_mgr.clear_timer + CLEAR_TIME_MS) < OS_GetTime()) {
            /* Transition to searching */
            ld_mgr.recommendation.state = SM_SEARCH;
            ld_mgr.recommendation.speed = SL_MEDIUM;
        } else {
            ld_mgr.recommendation.speed = SL_SLOW;
        }
    } else {
        /* No detection at all */
        ld_mgr.recommendation.state = SM_SEARCH;
        ld_mgr.recommendation.speed = SL_MEDIUM;
    }
}


/**
 * @brief Return current recommendation
 * @return Action_Recommendation_T Recoommended action
 */
Action_Recommendation_T BEH_LineDetection_GetRecommendation(){
    return ld_mgr.recommendation;
}