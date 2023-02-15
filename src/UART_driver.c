/** @file UART_driver.c
*   @brief Implementation of UART low level functionalities 
*/
#include <avr/io.h>
#include "MCAL.h"

/* Public functions */
/**
 * @brief UART initialization
 * Function writes to appropriate registers to enable communication over UART. Frame format is 8data, 2stop bit.
 * @param f_cpu     MCU clock
 * @param baudrate  Target baudrate
 */
void UART_init(uint32_t f_cpu, uint32_t baudrate){
    /* Set baud rate */
    uint32_t ubrr = f_cpu/(16*baudrate)-1;
    MCAL_WriteRegister(UBRR0H, (ubrr>>8));
    MCAL_WriteRegister(UBRR0L, ubrr);
    
    MCAL_SetBit(UCSR0A, U2X0, BIT_CLEARED);

    /* Enable receiver and transmitter */
    MCAL_SetBit(UCSR0B, RXEN0, BIT_SET);
    MCAL_SetBit(UCSR0B, TXEN0, BIT_SET);

    /* UMSEL0n
        0: Asynchronous 
        1: Synchrnous
        2: Reserved
        3: Master SPI
    */
    MCAL_SetBit(UCSR0C, UMSEL00, BIT_CLEARED);
    MCAL_SetBit(UCSR0C, UMSEL01, BIT_CLEARED);

    /* UPM0n - Parity Mode
        0: Disabled 
        1: Reserved
        2: Even Parity
        3: Odd Parity
    */
    MCAL_SetBit(UCSR0C, UPM00, BIT_CLEARED);
    MCAL_SetBit(UCSR0C, UPM01, BIT_CLEARED);

    /* UCSZn - Character Size
        0: 5bit 
        1: 6bit
        2: 7bit
        3: 8bit
        4-6: Reserved
        7: 9bit
    */
    MCAL_SetBit(UCSR0C, UCSZ00, BIT_SET);
    MCAL_SetBit(UCSR0C, UCSZ01, BIT_SET);
    
    /* UCPOLn - Clock polarity
        0: For asynchrnous mode
    */
    MCAL_SetBit(UCSR0C, UCPOL0, BIT_CLEARED);

    /* Enable Rx interrupt */
    // UCSR0B |= (1<<RXCIE0);
    
    /* Clear INT0 flag */
    // EIFR |= 1<<INTF0;
}

void UART_WriteBuffer(char c){
    while ( !(UCSR0A & (1<<UDRE0)) )
    ;
    MCAL_WriteRegister(UDR0, (uint8_t)c);
}

char UART_ReadBuffer(){
    return MCAL_ReadRegister(UDR0);
}
