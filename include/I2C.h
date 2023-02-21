#ifndef I2C_GUARD
#define I2C_GUARD

/*! @file UART_init.h
    @brief API for UART driver
*/

void I2C_init();
uint8_t I2C_send(uint8_t *data, uint8_t len);
uint8_t I2C_receive(uint8_t* response);
#endif /* #define I2C_GUARD */
