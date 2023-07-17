/** @file linse_sensor_drv.c
*   @brief Implementation of line sensor
*/
#include "line_sensor_drv.h"
#include "i2c_drv.h"
#include "logger_tx.h"

/** @brief Initialize the module
*/
void Ls_Init(void){
    INFO_P(PGM_LSD_INIT);
}

/** @brief Get status of all line sensors
    @param none
    @return status byte - each bit indicates a single sensor:
            1: sensor idle
            0: sensor triggered
*/
uint8_t Ls_GetLineStatus(void){
    uint8_t data = 0;
    I2c_Receive(&data);
    // log_data_2("LS state F=0x%x R=0x%x", data&0x0F, data&0xF0);
    // log_data_1("data %d", data);
    return data;
}