#ifndef UART_DRV_GUARD
#define UART_DRV_GUARD

/*! @file uart_drv.h
    @brief API for UART driver for Atmega328P, only basic read/write single character
*/


void Uart_Init();
void Uart_Write(char c);
char Uart_Read();
#endif /* #define UART_DRV_GUARD
 */
