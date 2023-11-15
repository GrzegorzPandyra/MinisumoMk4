/** @file os.c
*   @brief
*/
#include <stdint.h>
#include <avr/interrupt.h>
#include "isr.h"
#include "os.h"
/* MCAL */
#include "timer0.h"
#include "adc.h"
#include "utils.h"
/* drivers */
#include "uart_drv.h"
#include "motor_drv.h"
#include "i2c_drv.h"
#include "line_sensor_drv.h"
#include "distance_sensor_drv.h"
#include "user_input_drv.h"
#include "ir_drv.h"
#include "buzzer_drv.h"
/* SWCs */
#include "logger_tx.h"
#include "state_machine.h"
#include "behavior_main.h"
#include "behavior_line_detection.h"
#include "user_input_swc.h"

#define OS_TASKS_TOTAL 8U
#define ALIVE_TIMER_DEFUALT_VALUE 0U
#define RANDOM_MOD_FACTOR 100u

/* Custom types */
enum TaskType {INIT, PERIODIC, TRIGGERED};
enum OsStatus {OS_UNINITIALIZED, OS_INITIALIZED};
/**
 * @brief Task structure
 * @var type - can be INIT or PERIODIC
 * @var period_ms - only for periodic tasks
 * @var *task_handler - pointer to execution callback
 */
typedef struct{
    enum TaskType type;
    uint16_t period_ms;
    void (*task_handler)(void);
} Task_T;

/**
 * @brief OS structure
 * @var tasks - array containing all tasks
 * @var alive_timer - timer counting how long OS is alive
 */
typedef struct{
    Task_T tasks[OS_TASKS_TOTAL];
    uint32_t alive_timer;
    enum OsStatus status;
} Os_T;

/* Static functions declarations */
static void Os_Task_1ms(void);
static void Os_Task_2ms(void);
static void Os_Task_10ms(void);
static void Os_Task_100ms(void);
static void Os_Task_500ms(void);
static void Os_Task_1000ms(void);
static void Os_Task_2000ms(void);

/* Local variables */
static Os_T os = {
    {
        {INIT,     0U,    &Os_Init       },
        {PERIODIC, 1U,    &Os_Task_1ms   },
        {PERIODIC, 2U,    &Os_Task_2ms   },
        {PERIODIC, 10U,   &Os_Task_10ms  },
        {PERIODIC, 100U,  &Os_Task_100ms },
        {PERIODIC, 500U,  &Os_Task_500ms },
        {PERIODIC, 1000U, &Os_Task_1000ms},
        {PERIODIC, 2000U, &Os_Task_2000ms}
    },
    ALIVE_TIMER_DEFUALT_VALUE,
    OS_UNINITIALIZED
};

/*****************************************************
 * Private functions
 *****************************************************/
static void Os_Task_1ms(void){
    Mdrv_PWMHandler();
}

static void Os_Task_2ms(void){
    #ifndef ENABLE_MDRV_DIAGNOSTICS
        BEH_Run();
    #endif
}

static void Os_Task_10ms(void){
    logger_transmit();
    IRDrv_ReadPin();
    BuzzDrv_Run();
}

static void Os_Task_100ms(void){
    UI_Run();
}

static void Os_Task_500ms(void){
    #if ENABLE_UIM_FULL_DIAGNOSTICS
        Uidrv_Diagnostics_Full3();
    #endif

    #if ENABLE_UIM_HEARTBEAT_ONLY
        Uidrv_Diagnostics_Heartbeat1();
    #endif
}

static void Os_Task_1000ms(void){
    #if ENABLE_RAM_TRACKING
        int free_ram = Utils_FreeRam();
        DATA1("RAM = %i\n", free_ram);
    #endif
    #if ENABLE_LS_DIAGNOSTICS
        Ls_RunDiagnostics();
    #endif

    #if ENABLE_DS_DIAGNOSTICS
        Dsdrv_RunDiagnostics();
    #endif

    #if ENABLE_UIM_FULL_DIAGNOSTICS
        Uidrv_Diagnostics_Full1();
    #endif

    #ifdef ENABLE_UIM_HEARTBEAT_ONLY
        Uidrv_Diagnostics_Heartbeat2();
    #endif 
}

static void Os_Task_2000ms(void){
    #ifdef ENABLE_MDRV_DIAGNOSTICS
        Mdrv_Selfcheck();
    #endif

    #ifdef ENABLE_UIM_FULL_DIAGNOSTICS
        Uidrv_Diagnostics_Full2();
    #endif 
}

/*****************************************************
 * Public functions
 *****************************************************/

/**
 * @brief Initiate the module
 */
void Os_Init(void){
    Uart_Init();
    INFO_P(PGM_OS_INIT);
    Timer0_Init();
    Mdrv_Init();
    I2c_Init();
    Ls_Init();
    Adc_Init();
    Dsdrv_Init();
    IRDrv_Init();
    Sm_Init();
    BEH_Init();
    UI_Init();
    BuzzDrv_Init();

    os.status = OS_INITIALIZED;
    sei();
}

/**
 * @brief Increment OS main timer and execute apropriate tasks
 */
void Os_Run(void){
    if(os.status == OS_INITIALIZED){
        Task_T *current_task;
        os.alive_timer++;
        for(uint8_t i=0u; i<OS_TASKS_TOTAL; i++){
            current_task = &os.tasks[i];
            if((current_task->type == PERIODIC) && (os.alive_timer%current_task->period_ms == 0)){
                current_task->task_handler();
            }
        }
    }
}

/**
 * @brief Return current OS time
 * @return uint32_t time
 */
uint32_t OS_GetTime(void){
    return os.alive_timer;
}

/**
 * @brief Return pseudo-random number
 * @return uint8_t random value from 1-100
 */
uint8_t OS_GetRandom(void){
    static uint8_t iteration_factor;
    iteration_factor++;
    return (((os.alive_timer+iteration_factor+ADC_GetValue())%RANDOM_MOD_FACTOR)+1);
}