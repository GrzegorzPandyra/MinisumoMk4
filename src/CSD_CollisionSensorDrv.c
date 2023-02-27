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
    /* Set pins as input */
    MCAL_SetBit((Register_T)&DDRB, CS1, BIT_CLEARED);
    MCAL_SetBit((Register_T)&DDRB, CS2, BIT_CLEARED);
    /* Pull-ups */
    MCAL_SetBit((Register_T)&PORTB, CS1, BIT_SET);
    MCAL_SetBit((Register_T)&PORTB, CS2, BIT_SET);
}

/** @brief Get status of collision sensors
    @param none
    @return status byte - each bit indicates a single sensor:
            0: sensor idle
            1: sensor triggered
*/
CollisionStatus_T CSD_GetCollisionStatus(void){
    CollisionStatus_T status = NO_COLLISION;
    uint8_t cs1_status = MCAL_GetBit((Register_T)&PINB, CS1);
    uint8_t cs2_status = MCAL_GetBit((Register_T)&PINB, CS2);
    if(cs1_status){
        status = FRONT_COLLISION;
    } else if (cs2_status)
    {
        status = REAR_COLLISION;
    }
    
    return status;
}