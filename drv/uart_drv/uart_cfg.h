#ifndef UART_CFG_GUARD
#define UART_CFG_GUARD

/*! @file uart_cfg.h
    @brief Config for UART driver for Atmega328P
*/

#ifndef F_CPU
    #define F_CPU 16000000L
    #warning "F_CPU is not defined! Assigning default value."
#endif

#ifndef UART_BAUDRATE
    #define UART_BAUDRATE 9600U
    #warning "UART_BAUDRATE is not defined! Assigning default value."
#endif

#endif /* #define UART_CFG_GUARD
 */
