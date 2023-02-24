
#ifndef UIM_GUARD
#define UIM_GUARD
#include <stdint.h>

typedef enum {
    BTN_RELEASED = 0,
    BTN_PRESSED
} Btn_State_T;

void UIM_Init(void);
uint8_t UIM_GetMode(void);
Btn_State_T UIM_GetStartBtnState(void);

#endif /* UIM_GUARD */