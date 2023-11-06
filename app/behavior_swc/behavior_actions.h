
#ifndef BEHAVIOR_ACTIONS_GUARD
#define BEHAVIOR_ACTIONS_GUARD
#include <stdint.h>

typedef enum{
    SL_VERY_SLOW   = 10u,
    SL_SLOW        = 20u,
    SL_MEDIUM      = 30u,
    SL_FAST        = 60u,
    SL_MAX         = 100u
} Speed_Level_T;

typedef void (*Action_Cbk_T)(void);

void BEH_Actions_MoveForward(void);
void BEH_Actions_MoveBackward(void);
void BEH_Actions_TurnRight(void);
void BEH_Actions_TurnLeft(void);
void BEH_Actions_Turn(void);
void BEH_Actions_Stop(void);
void BEH_Actions_SetSpeed(Speed_Level_T speed);
#endif /* BEHAVIOR_ACTIONS_GUARD */