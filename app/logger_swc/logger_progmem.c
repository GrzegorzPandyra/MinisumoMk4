/** @file logger_progmem.c
*   @brief Definitions of objects used by PROGMEM 
    PROGMEM macro marks objects that are stored in MCU's flash memory (instead of RAM, which is very limited).
*/
#include "logger_progmem.h"

/* Literals kept in codeflash for logging                    0|                             |29*/
static const char PGM_DATA_ECU_INIT[]               PROGMEM = "ECU init";
static const char PGM_DATA_MDRV_INIT[]              PROGMEM = "MDRV init";
static const char PGM_DATA_I2C_INIT[]               PROGMEM = "I2C init";
static const char PGM_DATA_LSD_INIT[]               PROGMEM = "LS drv init";
static const char PGM_DATA_DSD_INIT[]               PROGMEM = "DS drv init";
static const char PGM_DATA_ADC_INIT[]               PROGMEM = "ADC init";
static const char PGM_DATA_TIMER_INIT[]             PROGMEM = "Timer init";
static const char PGM_DATA_CSD_INIT[]               PROGMEM = "CSD init";
static const char PGM_DATA_LM_INIT[]                PROGMEM = "LM init";
static const char PGM_DATA_UIM_INIT[]               PROGMEM = "UIM init";
static const char PGM_DATA_OS_INIT[]                PROGMEM = "OS init";
static const char PGM_DATA_LOGTYPE_INFO[]           PROGMEM = "INFO";
static const char PGM_DATA_LOGTYPE_WARNING[]        PROGMEM = "WARNING";
static const char PGM_DATA_LOGTYPE_ERROR[]          PROGMEM = "ERROR";
static const char PGM_DATA_LOGTYPE_DATA[]           PROGMEM = "DATA";
static const char PGM_DATA_OVFL_ERROR[]             PROGMEM = "TX OVERFLOW";
static const char PGM_DATA_MDRV_DIAG_FORWARD[]      PROGMEM = "Driving forward...";
static const char PGM_DATA_MDRV_DIAG_BACKWARD[]     PROGMEM = "Driving backward...";
static const char PGM_DATA_MDRV_DIAG_TURN_RIGHT[]   PROGMEM = "Turning right...";
static const char PGM_DATA_MDRV_DIAG_TURN_LEFT[]    PROGMEM = "Turning left...";
static const char PGM_DATA_MDRV_DIAG_PWM20[]        PROGMEM = "PWM 20%";
static const char PGM_DATA_MDRV_DIAG_PWM40[]        PROGMEM = "PWM 40%";
static const char PGM_DATA_MDRV_DIAG_PWM60[]        PROGMEM = "PWM 60%";
static const char PGM_DATA_MDRV_DIAG_PWM80[]        PROGMEM = "PWM 80%";
static const char PGM_DATA_MDRV_DIAG_PWM100[]       PROGMEM = "PWM 100%";
static const char PGM_DATA_MDRV_DIAG_STOP[]         PROGMEM = "Stopping...";
static const char PGM_DATA_SM_INIT[]                PROGMEM = "SM init";


Small_Buffer_T BUFFER(flash_to_ram_buffer); 

/* Table for accessing PROGMEM strings*/
const char* const PGM_DATA_LIST[] PROGMEM = {
    PGM_DATA_ECU_INIT,
    PGM_DATA_MDRV_INIT,
    PGM_DATA_I2C_INIT,
    PGM_DATA_LSD_INIT,
    PGM_DATA_DSD_INIT,
    PGM_DATA_ADC_INIT,
    PGM_DATA_TIMER_INIT,
    PGM_DATA_CSD_INIT,
    PGM_DATA_LM_INIT,
    PGM_DATA_UIM_INIT,
    PGM_DATA_OS_INIT,
    PGM_DATA_LOGTYPE_INFO,
    PGM_DATA_LOGTYPE_WARNING,
    PGM_DATA_LOGTYPE_ERROR,
    PGM_DATA_LOGTYPE_DATA,
    PGM_DATA_OVFL_ERROR,
    PGM_DATA_MDRV_DIAG_FORWARD,
    PGM_DATA_MDRV_DIAG_BACKWARD,
    PGM_DATA_MDRV_DIAG_TURN_RIGHT,
    PGM_DATA_MDRV_DIAG_TURN_LEFT,
    PGM_DATA_MDRV_DIAG_PWM20,
    PGM_DATA_MDRV_DIAG_PWM40,
    PGM_DATA_MDRV_DIAG_PWM60,
    PGM_DATA_MDRV_DIAG_PWM80,
    PGM_DATA_MDRV_DIAG_PWM100,
    PGM_DATA_MDRV_DIAG_STOP,
    PGM_DATA_SM_INIT,
};