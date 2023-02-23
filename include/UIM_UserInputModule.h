
#ifndef UIM_GUARD
#define UIM_GUARD
#include <stdint.h>

void UIM_Init(void);
uint8_t UIM_GetMode(void);
uint8_t UIM_GetStartBtnState(void);

#endif /* UIM_GUARD */