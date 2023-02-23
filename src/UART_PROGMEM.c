/** @file UART_PROGMEM.c
*   @brief Definitions of objects used by PROGMEM 
    PROGMEM macro marks objects that are stored in MCU's flash memory (instead of RAM, which is very limited).
*/
#include <avr/pgmspace.h>

#define DATA_CONVERSION_BUFFER_SIZE 30

/* Literals kept in codeflash for logging       0|                             |29*/
static const char PROGMEM_ECU_INIT[]   PROGMEM = "ECU init";
static const char PROGMEM_MDRV_INIT[]  PROGMEM = "Motor drv init";
static const char PROGMEM_I2C_INIT[]   PROGMEM = "I2C init";
static const char PROGMEM_LSD_INIT[]   PROGMEM = "Line sensor drv init";
static const char PROGMEM_DSD_INIT[]   PROGMEM = "Distance sensor drv init";
static const char PROGMEM_ADC_INIT[]   PROGMEM = "ADC init";
static const char PROGMEM_TIMER_INIT[] PROGMEM = "Timer init";
static const char PROGMEM_CSD_INIT[]   PROGMEM = "CSD init";
static const char PROGMEM_LM_INIT[]    PROGMEM = "LM init";


/* Buffer used for data exchange between RAM and FLASH */
char data_conversion_buffer[DATA_CONVERSION_BUFFER_SIZE] = {};

/* Table for accessing PROGMEM strings*/
const char* const progmem_string_table[] PROGMEM = {
    PROGMEM_ECU_INIT,
    PROGMEM_MDRV_INIT,
    PROGMEM_I2C_INIT,
    PROGMEM_LSD_INIT,
    PROGMEM_DSD_INIT,
    PROGMEM_ADC_INIT,
    PROGMEM_TIMER_INIT,
    PROGMEM_CSD_INIT,
    PROGMEM_LM_INIT
};