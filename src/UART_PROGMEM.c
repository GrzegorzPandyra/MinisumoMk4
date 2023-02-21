/** @file UART_PROGMEM.c
*   @brief Definitions of objects used by PROGMEM 
    PROGMEM macro marks objects that are stored in MCU's flash memory (instead of RAM, which is very limited).
*/
#include <avr/pgmspace.h>

#define DATA_CONVERSION_BUFFER_SIZE 30

/* Literals kept in codeflash for logging      0|                             |29*/
static const char PROGMEM_ECU_INIT[]  PROGMEM = "ECU init";
static const char PROGMEM_MDRV_INIT[] PROGMEM = "Motor drv init";
static const char PROGMEM_I2C_INIT[]  PROGMEM = "I2C init";
static const char PROGMEM_LSD_INIT[]  PROGMEM = "Line sensor drv init";


/* Buffer used for data exchange between RAM and FLASH */
char data_conversion_buffer[DATA_CONVERSION_BUFFER_SIZE] = {};

/* Table for accessing PROGMEM strings*/
const char* const progmem_string_table[] PROGMEM = {
    PROGMEM_ECU_INIT,
    PROGMEM_MDRV_INIT,
    PROGMEM_I2C_INIT,
    PROGMEM_LSD_INIT
};