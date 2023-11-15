
#ifndef BUZZER_GUARD
#define BUZZER_GUARD
#include <stdint.h>

/*****************************************************
 * Exported Macros
 *****************************************************/
#define BUZZ_SHORT_MS 200U
#define BUZZ_LONG_MS 500U

/*****************************************************
 * IR drv interface
 *****************************************************/
void BuzzDrv_Init(void);
void BuzzDrv_BuzzON(uint16_t buzz_time);
void BuzzDrv_BuzzOFF(void);
void BuzzDrv_Run(void);

#endif /* BUZZER_GUARD */