
#ifndef BEHAVIOR_MAIN_GUARD
#define BEHAVIOR_MAIN_GUARD
#include <stdint.h>
#include "behavior_actions.h"
#include "state_machine.h"

typedef enum{
    ID_LINE_DETECTION,
    ID_ENEMY_DETECTION,
    ID_SEARCH
}Sub_Module_ID_T;

typedef struct {
    Action_Cbk_T action;
    Speed_Level_T speed;
    Sub_Module_ID_T id;
    SM_State_T state;
} Action_Recommendation_T;

void BEH_Init(void);
void BEH_Run(void);
#endif /* BEHAVIOR_MAIN_GUARD */