/** @file I2C.c
*   @brief Higher level component for TWI lib
*/
#include <avr/io.h>
#include "twi_master.h"
#include "UART_TX.h"

/* See datasheet PCF8574 8.3.3*/
#define PCF8574N_I2C_WRITE_ADDR 0x42
#define PCF8574N_I2C_READ_ADDR 0x43

#define I2C_INIT_VALUE 0xFF
#define SINGLE_BYTE 1
/* Public functions */
/**
 * @brief I2C initialization
 */

void I2C_Init(){
    uint8_t init_value = I2C_INIT_VALUE;
    tw_init(TW_FREQ_100K, true);
    tw_master_transmit(PCF8574N_I2C_WRITE_ADDR, &init_value, sizeof(init_value), false);
    log_info_P(PROGMEM_I2C_INIT);
}

uint8_t I2C_Send(uint8_t *data, uint8_t len){
    uint8_t ret_code;
    ret_code = tw_master_transmit(PCF8574N_I2C_WRITE_ADDR, data, len, false);
    return ret_code;
}

uint8_t I2C_Receive(uint8_t* response){
    uint8_t ret_code;
    ret_code = tw_master_receive(PCF8574N_I2C_READ_ADDR, response, SINGLE_BYTE);
    return ret_code;
}