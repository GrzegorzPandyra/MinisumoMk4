#ifndef UART_DRIVER_GUARD
#define UART_DRIVER_GUARD

/*! @file UART_init.h
    @brief API for UART driver
*/

void UART_init(uint32_t f_cpu, uint32_t baudrate);
void UART_WriteBuffer(char c);
char UART_ReadBuffer();
#endif /* #define UART_DRIVER_GUARD
 */
