#ifndef I2C_GUARD
#define I2C_GUARD

/*! @file UART_init.h
    @brief API for UART driver
*/

void I2C_init();
void I2C_send(uint8_t *data, uint8_t len);
#endif /* #define I2C_GUARD */
