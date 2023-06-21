/** @file linse_sensor_drv.c
*   @brief Implementation of line sensor
*/
#include "line_sensor_drv.h"
#include "i2c_drv.h"
#ifdef LOGGING_ENABLED
    #include "logging.h"
#endif

/** @brief Initialize the module
*/
void Lsd_Init(void){
    #ifdef LOGGING_ENABLED
        log_info_P(PROGMEM_LSD_INIT);
    #endif
}

/** @brief Get status of all line sensors
    @param none
    @return status byte - each bit indicates a single sensor:
            1: sensor idle
            0: sensor triggered
*/
uint8_t Lsd_GetLineStatus(void){
    uint8_t data = 0;
    I2c_Receive(&data);
    // log_data_2("LS state F=0x%x R=0x%x", data&0x0F, data&0xF0);
    // log_data_1("data %d", data);
    return data;
}