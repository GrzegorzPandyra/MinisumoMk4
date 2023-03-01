/** @file linse_sensor_drv.c
*   @brief Implementation of line sensor
*/
#include "UART_TX.h"
#include "LSD_LineSensorDrv.h"
#include "I2C.h"

/** @brief Initialize the module
*/
void LSD_Init(void){
    log_info_P(PROGMEM_LSD_INIT);
}

/** @brief Get status of all line sensors
    @param none
    @return status byte - each bit indicates a single sensor:
            1: sensor idle
            0: sensor triggered
*/
uint8_t LSD_GetLineStatus(void){
    uint8_t data = 0;
    I2C_Receive(&data);
    // log_data_2("LS state F=0x%x R=0x%x", data&0x0F, data&0xF0);
    // log_data_1("data %d", data);
    return data;
}