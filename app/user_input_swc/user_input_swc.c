/** @file user_input_swc.c
*   @brief Module handling the inputs from user
*/
#include "logger_tx.h"
#include "stdlib.h"
#include "user_input_swc.h"
#include "user_input_drv.h"
#include "state_machine.h"
#include "ir_drv.h"
#include "os.h"
#include "buzzer_drv.h"

#ifdef COMPETITION_MODE
    #define COUNTDOWN_INIT_MS 0u
#else 
    #define COUNTDOWN_INIT_MS 5000u
#endif

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
static bool CheckInput(void);
static void ToggleStateLED(void);

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

/**
 * @brief Check condition for robot activation
 * @return true When either manual or remote trigger has been activated (depending on SM_State)
 * @return false Otherwise
 */
static bool CheckInput(void){
    bool result;
    if(Sm_GetState() == SM_IDLE){
        result = ((Uidrv_GetStartBtnState() == BTN_PRESSED) || (IRDrv_GetState() == IR_TRIGGERED));
    } else {
        result = (Uidrv_GetStartBtnState() == BTN_PRESSED);
    }
    return result;
}

/*****************************************************
 * Public functions
 *****************************************************/

/** 
 * @brief Initialize the module
*/
void UI_Init(void){
    INFO_P(PGM_UI_INIT);
}

/**
 * @brief Main UI function
 */
void UI_Run(void){
    bool trigger_flag = CheckInput();

    switch (Sm_GetState()){
    case SM_IDLE:
        /* Arm the robot */
        if(trigger_flag){
            Sm_SetState(SM_ARMED);
        } 

        /* Auto-arming */
        if(Uidrv_GetMode() == MODE_AUTOARM){
            Sm_SetState(SM_ARMED);
        }
        break;
    case SM_ARMED:
        if(trigger_flag){
            /* Abort arming procedure */
            Sm_SetState(SM_IDLE);
            countdown_counter = COUNTDOWN_INIT_MS;
        } else {
            /* Countdown to activation */
            if(countdown_counter%SEC_TO_MS == 0u){
                if(countdown_counter == 0u){
                    Sm_SetState(SM_SEARCH);
                } else {
                    DATA1("%d...\n", countdown_counter/SEC_TO_MS);
                    BuzzDrv_BuzzON(BUZZ_SHORT_MS);
                }
            }
            countdown_counter -= TASK_PERIOD_MS;
        }
        break;
    case SM_SEARCH:
    case SM_ATTACK:
    case SM_LINE_DETECTED:
    default:
        if(trigger_flag){
            Sm_SetState(SM_IDLE);
            countdown_counter = COUNTDOWN_INIT_MS;
        }
        break;
    }
    ToggleStateLED();
}
