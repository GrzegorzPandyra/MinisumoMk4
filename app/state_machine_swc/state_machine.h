
#ifndef STATE_MACHINE_GUARD
#define STATE_MACHINE_GUARD
#include <stdint.h>

typedef enum {
    SM_IDLE = 0u,
    SM_ARMED, 
    SM_ATTACK,
    SM_LINE_DETECTED
} SM_State_T;


void Sm_Init(void);
SM_State_T Sm_GetState(void);
void Sm_SetState(SM_State_T state);
#endif /* STATE_MACHINE_GUARD */