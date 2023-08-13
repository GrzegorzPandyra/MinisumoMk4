
#ifndef UIDRV_GUARD
#define UIDRV_GUARD
#include <stdint.h>

typedef enum {
    BTN_PRESSED = 0,
    BTN_RELEASED = 1
} Btn_State_T;

typedef enum {
    LED_OFF = 0,
    LED_ON = 1
} Led_Status_T;

void Uidrv_Init(void);
uint8_t Uidrv_GetMode(void);
Btn_State_T Uidrv_GetStartBtnState(void);
void Uidrv_SetStatusLed1(Led_Status_T bit_status);
void Uidrv_SetStatusLed2(Led_Status_T bit_status);
void Uidrv_Diagnostics_Full1(void);
void Uidrv_Diagnostics_Full2(void);
void Uidrv_Diagnostics_Full3(void);
void Uidrv_Diagnostics_Heartbeat1(void);
void Uidrv_Diagnostics_Heartbeat2(void);

#endif /* UIDRV_GUARD */