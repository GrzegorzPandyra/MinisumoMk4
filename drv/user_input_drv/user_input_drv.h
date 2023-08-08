
#ifndef UIM_GUARD
#define UIM_GUARD
#include <stdint.h>

typedef enum {
    BTN_PRESSED = 0,
    BTN_RELEASED = 1
} Btn_State_T;

typedef enum {
    LED_OFF = 0,
    LED_ON = 1
} Led_Status_T;

void UIM_Init(void);
uint8_t UIM_GetMode(void);
Btn_State_T UIM_GetStartBtnState(void);
void UIM_SetStatusLed1(Led_Status_T bit_status);
void UIM_SetStatusLed2(Led_Status_T bit_status);

#endif /* UIM_GUARD */