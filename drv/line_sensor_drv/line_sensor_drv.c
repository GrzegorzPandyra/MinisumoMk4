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
Ls_Status_T Ls_GetLineStatus(void){
    uint8_t data = 0;
    Ls_Status_T ls_status;
    I2c_Receive(&data);
    /*  Mapping from I2C data to vehicle view.
        Shift values were adjusted during live-test */
    ls_status.ls0 = data>>6u;
    ls_status.ls1 = data>>7u;
    ls_status.ls2 = data>>4u;
    ls_status.ls3 = data>>5u;
    ls_status.ls4 = data>>1u;
    ls_status.ls5 = data>>0u;
    ls_status.ls6 = data>>3u;
    ls_status.ls7 = data>>2u;
    return ls_status;
}

#if ENABLE_LS_DIAGNOSTICS
    void Ls_RunDiagnostics(void){
        Ls_Status_T ls_status = (Ls_Status_T)Ls_GetLineStatus();
        INFO("x--^^^^^^^--x");
        DATA4("| %d %d   %d %d |\n", ls_status.ls0, ls_status.ls1, ls_status.ls2, ls_status.ls3);
        DATA4("| %d %d   %d %d |\n", ls_status.ls7, ls_status.ls6, ls_status.ls5, ls_status.ls4);
        INFO("x-----------x");
    }
#endif