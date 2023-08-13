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
/* drivers */
#include "uart_drv.h"
#include "motor_drv.h"
#include "i2c_drv.h"
#include "line_sensor_drv.h"
#include "distance_sensor_drv.h"
#include "user_input_drv.h"
/* SWCs */
#include "logger_tx.h"
#include "state_machine.h"

#define OS_TASKS_TOTAL 8U
#define ALIVE_TIMER_DEFUALT_VALUE 0U

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
static void Os_Task_10ms(void);
static void Os_Task_100ms(void);
static void Os_Task_500ms(void);
static void Os_Task_1000ms(void);
static void Os_Task_2000ms(void);
static void Os_Task_5000ms(void);

/* Local variables */
static Os_T os = {
    {
        {INIT,     0U,    &Os_Init       },
        {PERIODIC, 1U,    &Os_Task_1ms   },
        {PERIODIC, 10U,   &Os_Task_10ms  },
        {PERIODIC, 100U,  &Os_Task_100ms },
        {PERIODIC, 500U,  &Os_Task_500ms },
        {PERIODIC, 1000U, &Os_Task_1000ms},
        {PERIODIC, 2000U, &Os_Task_2000ms},
        {PERIODIC, 5000U, &Os_Task_5000ms}
    },
    ALIVE_TIMER_DEFUALT_VALUE,
    OS_UNINITIALIZED
};

/*****************************************************
 * Private functions
 *****************************************************/

/*****************************************************
 * Public functions
 *****************************************************/
void Os_Init(void){
    Uart_Init();
    INFO_P(PGM_OS_INIT);
    Timer0_Init();
    Mdrv_Init();
    I2c_Init();
    Ls_Init();
    Adc_Init();
    Dsdrv_Init();
    Sm_Init();

    os.status = OS_INITIALIZED;
    sei();
}

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

static void Os_Task_1ms(void){
    Mdrv_PWMHandler();
}

static void Os_Task_10ms(void){
    logger_transmit();
}

static void Os_Task_100ms(void){
}

static void Os_Task_500ms(void){
    #if ENABLE_UIM_DIAGNOSTICS
        Uidrv_RunDiagnostics3();
    #endif

    Dsdrv_GetDistance();
}

static void Os_Task_1000ms(void){
    // INFO("1000ms task");
    #if ENABLE_LS_DIAGNOSTICS
        Ls_RunDiagnostics();
    #endif

    #if ENABLE_DS_DIAGNOSTICS
        Dsdrv_RunDiagnostics();
    #endif

    #if ENABLE_UIM_DIAGNOSTICS
        Uidrv_RunDiagnostics1();
    #endif
}

static void Os_Task_2000ms(void){
    #ifdef ENABLE_MDRV_DIAGNOSTICS
        Mdrv_Selfcheck();
    #endif

    #ifdef ENABLE_UIM_DIAGNOSTICS
        Uidrv_RunDiagnostics2();
    #endif 
    // INFO("2000ms task");
}

static void Os_Task_5000ms(void){
    // INFO("5000ms task");
}