/** @file collision_sensor_drv.c
*   @brief Implementation of collision sensor (tact-switch)
*/
#include "MCAL.h"
#include "UART_TX.h"
#include "CSD_CollisionSensorDrv.h"

#define CS1 PB0 /* front */
#define CS2 PB1 /* back */

/** @brief Initialize the module
*/
void CSD_Init(void){
    log_info_P(PROGMEM_CSD_INIT);
}

/** @brief Get status of collision sensors
    @param none
    @return status byte - each bit indicates a single sensor:
            0: sensor idle
            1: sensor triggered
*/
uint8_t CSD_GetCollisionStatus(void){
    uint8_t cs1_status = MCAL_GetBit((Register_T)&PORTB, CS1);
    uint8_t cs2_status = MCAL_GetBit((Register_T)&PORTB, CS2);
    return ((cs2_status<<1) | cs1_status);
}