/** @file I2C.c
*   @brief 
*/
#include <avr/io.h>
#include "MCAL.h"
#include "twi_master.h"
#include "UART_TX.h"

/* Public functions */
/**
 * @brief I2C initialization
 */

void I2C_init(){
    tw_init(TW_FREQ_100K, true);
    log_info_P(PROGMEM_I2C_INIT);
}

void I2C_send(uint8_t *data, uint8_t len){
    uint8_t ret_code = 0xff;
    ret_code = tw_master_transmit(0x21, data, len, false);
    log_data_3("retcode: 0x%x data: 0x%x len: %d\n", ret_code, *data, len);   
    // uint8_t response = 22;
    // ret_code = tw_master_receive(0x43, (uint8_t*)&response, 1);
    // log_data_1("PinStatus: %d", response);   
    // log_data_1("retcode: %d\n", ret_code);   
}