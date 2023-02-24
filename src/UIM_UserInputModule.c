/** @file UIM_UserInputModule.c
*   @brief Reads input from user - mode, start, reset
*/
#include "MCAL.h"
#include "UART_TX.h"
#include "UIM_UserInputModule.h"

#define MODE_SELECT_H PD7
#define MODE_SELECT_L PD6
#define START_BTN PD5

/**********************************************************************
* Public functions 
***********************************************************************/

/** @brief Initialize the module
*/
void UIM_Init(void){
    MCAL_SetBit((Register_T)&DDRD, MODE_SELECT_H, BIT_CLEARED);
    MCAL_SetBit((Register_T)&DDRD, MODE_SELECT_L, BIT_CLEARED);
    MCAL_SetBit((Register_T)&DDRD, START_BTN, BIT_CLEARED);
    log_info_P(PROGMEM_UIM_INIT);
}

/**
 * @brief Return one of four predefined modes
 * @return uint8_t mode ID
 */
uint8_t UIM_GetMode(void)
{
    uint8_t mode_h = MCAL_GetBit((Register_T)&PIND, MODE_SELECT_H);
    uint8_t mode_l = MCAL_GetBit((Register_T)&PIND, MODE_SELECT_L);
    return ((mode_h<<1) | mode_l);
}

/**
 * @brief Return state of start btn
 * @return uint8_t start btn status
 */
Btn_State_T UIM_GetStartBtnState(void)
{
    return MCAL_GetBit((Register_T)&PIND, START_BTN);
}
