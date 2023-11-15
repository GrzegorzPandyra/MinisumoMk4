
#ifndef IRDRV_GUARD
#define IRDRV_GUARD
#include <stdint.h>

typedef enum {
    IR_TRIGGERED = 0,
    IR_IDLE = 1
} IR_State_T;

/* IR drv interface */
void IRDrv_Init(void);
IR_State_T IRDrv_GetState(void);
void IRDrv_ReadPin(void);

#endif /* IRDRV_GUARD */