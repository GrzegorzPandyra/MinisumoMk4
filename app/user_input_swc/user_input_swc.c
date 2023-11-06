/** @file user_input_swc.c
*   @brief 
*/
#include "logger_tx.h"
#include "stdlib.h"
#include "user_input_swc.h"
#include "user_input_drv.h"
#include "state_machine.h"

#define COUNTDOWN_INIT_MS 5000u
#define SEC_TO_MS 1000u
#define TASK_PERIOD_MS 100u

#define SM_IDLE_BLINK_PERIOD_MS (600u*TASK_PERIOD_MS)
#define SM_ARMED_BLINK_PERIOD_MS (5u*TASK_PERIOD_MS)
#define SM_SEARCH_BLINK_PERIOD_MS (10u*TASK_PERIOD_MS)
#define SM_ATTACK_BLINK_PERIOD_MS (1u*TASK_PERIOD_MS)
#define SM_LINE_DETECTED_BLINK_PERIOD_MS (50u*TASK_PERIOD_MS)

#define MODE_AUTOARM 1u

/*****************************************************
 * Private variables
 *****************************************************/
static uint16_t countdown_counter = COUNTDOWN_INIT_MS;
/*****************************************************
 * Private functions
 *****************************************************/
/**
 * @brief Toggle state of SM LED depending on current SM State
 */
static void ToggleStateLED(void){
    static Led_Status_T led_status = LED_OFF;
    static uint16_t led_toggle_counter = 0u;
    const uint8_t toggle_delays_idx = (uint8_t)Sm_GetState();
    const uint16_t toggle_delays[] = {   SM_IDLE_BLINK_PERIOD_MS,
                                         SM_ARMED_BLINK_PERIOD_MS,
                                         SM_SEARCH_BLINK_PERIOD_MS,
                                         SM_ATTACK_BLINK_PERIOD_MS,
                                         SM_LINE_DETECTED_BLINK_PERIOD_MS
                                     };

    if(led_toggle_counter >= toggle_delays[toggle_delays_idx]){
        if(led_status == LED_OFF){
            Uidrv_SetStatusLed1(LED_ON);
            led_status = LED_ON;
        } else {
            Uidrv_SetStatusLed1(LED_OFF);
            led_status = LED_OFF;
        }
        led_toggle_counter = 0u;
    } else {
        led_toggle_counter += TASK_PERIOD_MS;
    }
}

/*****************************************************
 * Public functions
 *****************************************************/

/** @brief Initialize the module
*/
void UI_Init(void){
    INFO_P(PGM_UI_INIT);
}

void UI_Run(void){
    switch (Sm_GetState()){
    case SM_IDLE:
        /* Arm the robot */
        if(Uidrv_GetStartBtnState() == BTN_PRESSED){
            Sm_SetState(SM_ARMED);
        } 

        /* Auto-arming */
        if(Uidrv_GetMode() == MODE_AUTOARM){
            Sm_SetState(SM_ARMED);
        }
        break;
    case SM_ARMED:
        if(Uidrv_GetStartBtnState() == BTN_PRESSED){
            /* Abort arming process and reset to IDLE */
            Sm_SetState(SM_IDLE);
            countdown_counter = COUNTDOWN_INIT_MS;
        } else {
            /* Countdown to activation */
            if(countdown_counter%SEC_TO_MS == 0u){
                if(countdown_counter == 0u){
                    Sm_SetState(SM_SEARCH);
                } else {
                    DATA1("%d...\n", countdown_counter/SEC_TO_MS);
                }
            }
            countdown_counter -= TASK_PERIOD_MS;
        }
        break;
    case SM_SEARCH:
    case SM_ATTACK:
    case SM_LINE_DETECTED:
    default:
        if(Uidrv_GetStartBtnState() == BTN_PRESSED){
            /* Go back to IDLE */
            Sm_SetState(SM_IDLE);
            countdown_counter = COUNTDOWN_INIT_MS;
            INFO("GOING IDLE!!!!");
        }
        break;
    }
    ToggleStateLED();
}
