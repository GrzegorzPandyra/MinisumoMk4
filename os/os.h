#ifndef OS_GUARD
#define OS_GUARD

#include "stdint.h"

void Os_Init(void);
void Os_Run(void);
uint32_t OS_GetTime(void);
uint8_t OS_GetRandom(void);

#endif /* OS_GUARD */