/** @file user_input_module.c
*   @brief Reads input from user - mode, start, reset. Sets status of LEDs.
*/
#include "utils.h"
#include "user_input_drv.h"
#include "logger_tx.h"

#define MODE_SELECT_H PD2
#define MODE_SELECT_L PD3
#define START_BTN PC2
#define STATUS_LED_1 PC3
#define STATUS_LED_2 PD4

#define MODE_SELECT_H_DDR DDRD
#define MODE_SELECT_L_DDR DDRD
#define START_BTN_DDR DDRC
#define STATUS_LED_1_DDR DDRC
#define STATUS_LED_2_DDR DDRD

#define MODE_SELECT_H_PIN PIND
#define MODE_SELECT_L_PIN PIND
#define START_BTN_PIN PINC
#define STATUS_LED_1_PIN PINC
#define STATUS_LED_2_PIN PIND

#define STATUS_LED_1_PORT PORTC
#define STATUS_LED_2_PORT PORTD
/*****************************************************
 * Private variables
 *****************************************************/
static Btn_State_T previous_state = BTN_RELEASED; 
/**********************************************************************
* Public functions 
***********************************************************************/

/** @brief Initialize the module
*/
void Uidrv_Init(void){
    /* Set pins as inputs */
    Utils_SetBit((Register_T)&MODE_SELECT_H_DDR, MODE_SELECT_H, BIT_CLEARED);
    Utils_SetBit((Register_T)&MODE_SELECT_H_DDR, MODE_SELECT_L, BIT_CLEARED);
    Utils_SetBit((Register_T)&START_BTN_DDR, START_BTN, BIT_CLEARED);
    /* Set status LED pins as outputs */
    Utils_SetBit((Register_T)&START_BTN_DDR, STATUS_LED_1_DDR, BIT_SET);
    Utils_SetBit((Register_T)&START_BTN_DDR, STATUS_LED_2_DDR, BIT_SET);

    #if 0
    /* HW pullups present - no need for SW pullups */
    /* Pull-ups */
    Utils_SetBit((Register_T)&PORTD, MODE_SELECT_H, BIT_SET);
    Utils_SetBit((Register_T)&PORTD, MODE_SELECT_L, BIT_SET);
    Utils_SetBit((Register_T)&PORTD, START_BTN, BIT_SET);
    #endif
    INFO_P(PGM_UIDRV_INIT);
}

/**
 * @brief Return one of four predefined modes
 * @return uint8_t mode ID
 */
uint8_t Uidrv_GetMode(void)
{
    uint8_t mode_h = Utils_GetBit((Register_T)&MODE_SELECT_H_PIN, MODE_SELECT_H);
    uint8_t mode_l = Utils_GetBit((Register_T)&MODE_SELECT_L_PIN, MODE_SELECT_L);
    return ((mode_h<<1) | mode_l);
}

/**
 * @brief Return state of start btn. Reports button press only once per press.
 * @return uint8_t start btn status
 */
Btn_State_T Uidrv_GetStartBtnState(void)
{
    Btn_State_T result;
    Btn_State_T current_state = Utils_GetBit((Register_T)&START_BTN_PIN, START_BTN)?BTN_RELEASED:BTN_PRESSED;
    if(previous_state != current_state){
        previous_state = result = current_state;
    } else {
        result = BTN_RELEASED;
    }
    return result;
}

/**
 * @brief Set status of LED1
 * 
 * @param led_status 1 - set, 0 - unset
 */
void Uidrv_SetStatusLed1(Led_Status_T led_status){
    Utils_SetBit((Register_T)&STATUS_LED_1_PORT, STATUS_LED_1, (uint8_t)led_status);
}

/**
 * @brief Set status of LED2
 * 
 * @param led_status 1 - set, 0 - unset
 */
void Uidrv_SetStatusLed2(Led_Status_T led_status){
    Utils_SetBit((Register_T)&STATUS_LED_2_PORT, STATUS_LED_2, (uint8_t)led_status);
}

#ifdef ENABLE_UIM_FULL_DIAGNOSTICS

    /**
     * @brief Perform Uidrv diagnostics - requires ENABLE_UIM_FULL_DIAGNOSTICS flag
     */
    void Uidrv_Diagnostics_Full1(void){
            Uidrv_SetStatusLed1(LED_ON);
    }

    /**
     * @brief Perform Uidrv diagnostics - requires ENABLE_UIM_FULL_DIAGNOSTICS flag
     */
    void Uidrv_Diagnostics_Full2(void){
        uint8_t mode = 0xFF;
        mode = Uidrv_GetMode();
        DATA1("Mode %d\n", mode);
        Uidrv_SetStatusLed1(LED_OFF);
    }

    /**
     * @brief Perform Uidrv diagnostics - requires ENABLE_UIM_FULL_DIAGNOSTICS flag
     */
    void Uidrv_Diagnostics_Full3(void){
        Btn_State_T btn_state = BTN_RELEASED;
        btn_state = Uidrv_GetStartBtnState();
        if(btn_state == BTN_PRESSED){
            INFO("START button pressed");
        }
    }
#endif

/**
 * @brief Perform Uidrv diagnostics - requires ENABLE_UIM_FULL_DIAGNOSTICS flag
 */
void Uidrv_Diagnostics_Heartbeat1(void){
        Uidrv_SetStatusLed2(LED_ON);
}

/**
 * @brief Perform Uidrv diagnostics - requires ENABLE_UIM_FULL_DIAGNOSTICS flag
 */
void Uidrv_Diagnostics_Heartbeat2(void){
    Uidrv_SetStatusLed2(LED_OFF);
}
