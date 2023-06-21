#ifndef UART_DRIVER_GUARD
#define UART_DRIVER_GUARD

/*! @file uart_drv.h
    @brief API for UART driver
*/

void Uart_Init(uint32_t f_cpu, uint32_t baudrate);
void Uart_WriteBuffer(char c);
char Uart_ReadBuffer();
#endif /* #define UART_DRIVER_GUARD
 */
