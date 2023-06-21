/** @file UIM_UserInputModule.c
*   @brief Reads input from user - mode, start, reset
*/
#include "Utils.h"
#include "user_input_drv.h"
#ifdef LOGGING_ENABLED
    #include "logging.h"
#endif

#define MODE_SELECT_H PD7
#define MODE_SELECT_L PD6
#define START_BTN PD5

/**********************************************************************
* Public functions 
***********************************************************************/

/** @brief Initialize the module
*/
void UIM_Init(void){
    /* Set pins as inputs */
    Utils_SetBit((Register_T)&DDRD, MODE_SELECT_H, BIT_CLEARED);
    Utils_SetBit((Register_T)&DDRD, MODE_SELECT_L, BIT_CLEARED);
    Utils_SetBit((Register_T)&DDRD, START_BTN, BIT_CLEARED);
    /* Pull-ups */
    Utils_SetBit((Register_T)&PORTD, MODE_SELECT_H, BIT_SET);
    Utils_SetBit((Register_T)&PORTD, MODE_SELECT_L, BIT_SET);
    Utils_SetBit((Register_T)&PORTD, START_BTN, BIT_SET);
    #ifdef LOGGING_ENABLED
        log_info_P(PROGMEM_UIM_INIT);
    #endif
}

/**
 * @brief Return one of four predefined modes
 * @return uint8_t mode ID
 */
uint8_t UIM_GetMode(void)
{
    uint8_t mode_h = Utils_GetBit((Register_T)&PIND, MODE_SELECT_H);
    uint8_t mode_l = Utils_GetBit((Register_T)&PIND, MODE_SELECT_L);
    return ((mode_h<<1) | mode_l);
}

/**
 * @brief Return state of start btn
 * @return uint8_t start btn status
 */
Btn_State_T UIM_GetStartBtnState(void)
{
    // log_data_1("startbtn %d", Utils_GetBit((Register_T)&PIND, START_BTN));
    return Utils_GetBit((Register_T)&PIND, START_BTN);
}
