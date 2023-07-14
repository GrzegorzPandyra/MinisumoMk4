/** @file os.c
*   @brief
*/
#include <stdint.h>
#include "os.h"
#include "logger_tx.h"

#define TASKS_TOTAL 8U
#define ALIVE_TIMER_DEFUALT_VALUE 0U

/* Custom types */
enum TaskType {INIT, PERIODIC};
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
    Task_T tasks[TASKS_TOTAL];
    uint32_t alive_timer;
} Os_T;

/* Static functions declarations */
static void os_task_1ms(void);
static void os_task_10ms(void);
static void os_task_100ms(void);
static void os_task_500ms(void);
static void os_task_1000ms(void);
static void os_task_2000ms(void);
static void os_task_5000ms(void);

/* Local variables */
static Os_T os = {
    {
        {INIT,     0U,    &os_init          },
        {PERIODIC, 1U,    &os_task_1ms      },
        {PERIODIC, 10U,   &os_task_10ms     },
        {PERIODIC, 100U,  &os_task_100ms    },
        {PERIODIC, 500U,  &os_task_500ms    },
        {PERIODIC, 1000U, &os_task_1000ms   },
        {PERIODIC, 2000U, &os_task_2000ms   },
        {PERIODIC, 5000U, &os_task_5000ms   }
    },
    ALIVE_TIMER_DEFUALT_VALUE
};

/*****************************************************
 * Private functions
 *****************************************************/

/*****************************************************
 * Public functions
 *****************************************************/
void os_init(void){
}

void os_run(void){
    Task_T *current_task;
    os.alive_timer++;
    for(uint8_t i=0; i<TASKS_TOTAL; i++){
        current_task = &os.tasks[i];
        if((current_task->type == PERIODIC) && (os.alive_timer%current_task->period_ms == 0)){
            current_task->task_handler();
        }
    }
}

static void os_task_1ms(void){

}

static void os_task_10ms(void){
    
}

static void os_task_100ms(void){
    
}

static void os_task_500ms(void){
    
}

static void os_task_1000ms(void){
    
}

static void os_task_2000ms(void){
    
}

static void os_task_5000ms(void){
    
}