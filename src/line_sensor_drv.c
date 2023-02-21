/** @file linse_sensor_drv.c
*   @brief Implementation of line sensor
*/
#include "UART_TX.h"
#include "line_sensor_drv.h"
#include "I2C.h"

/** @brief Initialize the module
*/
void LSD_Init(void){
    log_info_P(PROGMEM_LSD_INIT);
}

/** @brief Get status of all line sensors
    @param none
    @return status byte - each bit indicates a single sensor:
            0: sensor idle
            1: sensor triggered
*/
uint8_t LSD_GetLineStatus(void){
    uint8_t data = 0;
    I2C_Receive(&data);
    return data;
}