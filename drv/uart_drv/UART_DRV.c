/** @file uart_drv.c
*   @brief Implementation of UART read/write for Atmega328P 
*/
#include "utils.h"
#include "uart_drv.h"
#include "uart_cfg.h"

#ifdef UART_SELFCHECK
    static const char SELFCHECK_STRING[] = "\t  uart_drv.c:100 :INFO !UART DRV SELFCHECK!\n";
#endif

/* Private functions */
#ifdef UART_SELFCHECK
    static void Uart_Selfcheck(void);
#endif

/* Public functions */
/**
 * @brief UART initialization
 * Function writes to appropriate registers to enable communication over UART. Frame format is 8data, 2stop bit.
 */

void Uart_Init(void){
    /* Set baud rate */
    uint32_t ubrr = (uint32_t)F_CPU/(16*(uint32_t)UART_BAUDRATE)-1;
    Utils_WriteRegister((Register_T)&UBRR0H, (unsigned char)(ubrr>>8));
    Utils_WriteRegister((Register_T)&UBRR0L, (unsigned char)ubrr);
    
    Utils_SetBit((Register_T)&UCSR0A, U2X0, BIT_CLEARED);

    /* Enable receiver and transmitter */  
    Utils_WriteRegister((Register_T)&UCSR0B, BIT_CLEARED);
    Utils_SetBit((Register_T)&UCSR0B, RXEN0, BIT_SET);
    Utils_SetBit((Register_T)&UCSR0B, TXEN0, BIT_SET);
    

    /* UMSEL0n
        0: Asynchronous 
        1: Synchrnous
        2: Reserved
        3: Master SPI
    */
    Utils_SetBit((Register_T)&UCSR0C, UMSEL00, BIT_CLEARED);
    Utils_SetBit((Register_T)&UCSR0C, UMSEL01, BIT_CLEARED);

    /* UPM0n - Parity Mode
        0: Disabled 
        1: Reserved
        2: Even Parity
        3: Odd Parity
    */
    Utils_SetBit((Register_T)&UCSR0C, UPM00, BIT_CLEARED);
    Utils_SetBit((Register_T)&UCSR0C, UPM01, BIT_CLEARED);

    /* UCSZn - Character Size
        0: 5bit 
        1: 6bit
        2: 7bit
        3: 8bit
        4-6: Reserved
        7: 9bit
    */
    Utils_SetBit((Register_T)&UCSR0C, UCSZ00, BIT_SET);
    Utils_SetBit((Register_T)&UCSR0C, UCSZ01, BIT_SET);
    
    /* UCPOLn - Clock polarity
        0: For asynchrnous mode
    */
    Utils_SetBit((Register_T)&UCSR0C, UCPOL0, BIT_CLEARED);

    /* Enable Rx interrupt */
    // UCSR0B |= (1<<RXCIE0);
    
    /* Clear INT0 flag */
    // EIFR |= 1<<INTF0;
    #ifdef UART_SELFCHECK
        Uart_Selfcheck();
    #endif
}

/**
 * @brief Write single character into UDR
 * @param c char to be written
 */
void Uart_Write(char c){
    while ( !(UCSR0A & (1<<UDRE0)) )
    ;
    Utils_WriteRegister((Register_T)&UDR0, (uint8_t)c);
}

/**
 * @brief Read data in UDR
 * @return char data received from UDR
 */
char Uart_Read(){
    return Utils_ReadRegister((Register_T)&UDR0);
}

#ifdef UART_SELFCHECK
    /**
     * @brief Automatic check on driver init to let user know if driver is working correctly
     */
    static void Uart_Selfcheck(void){
        for(uint8_t i=0; i<sizeof(SELFCHECK_STRING)/sizeof(SELFCHECK_STRING[0]); i++){
            Uart_Write(SELFCHECK_STRING[i]);
        }
    }
#endif