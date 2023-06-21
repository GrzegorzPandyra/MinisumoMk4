#ifndef I2C_GUARD
#define I2C_GUARD

/*! @file UART_init.h
    @brief API for UART driver
*/

void I2c_Init();
uint8_t I2c_Send(uint8_t *data, uint8_t len);
uint8_t I2c_Receive(uint8_t* response);
#endif /* #define I2C_GUARD */
