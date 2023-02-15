/** @file UART.c
*   @brief Implementation of MCAL
*/
#include <avr/io.h>
#include "MCAL.h"

/** @brief Write 8bit register
    @param reg Register ID
    @param val Value to be written
*/
void MCAL_WriteRegister(MCAL_Register_T reg, uint8_t val){
    reg = val;
    // switch (reg)
    // {
    // case MCAL_UDR:
    //     while ( !(UCSR0A & (1<<UDRE0)) )
    //     ;
    //     UDR0 = val;
    //     break;
    // case MCAL_UBRRH:
    //     UBRR0H = val;
    //     break;
    // case MCAL_UBRRL:
    //     UBRR0L = val;
    //     break;
    // default:
    //     break;
    // }
}

/** @brief Read 8bit register
    @param reg Register ID
    @return Register value
*/
uint8_t MCAL_ReadRegister(uint8_t reg){
    // uint8_t result;
    // switch (reg)
    // {
    // case MCAL_UDR:
    //     result = UDR0;
    //     break;
    // case MCAL_UBRRH:
    //     result = UBRR0H;
    //     break;
    // case MCAL_UBRRL:
    //     result = UBRR0L;
    //     break;
    // default:
    //     result = 0;
    //     break;
    // }
    // return result;
    return reg;
} 

/** @brief Write single bit into a register
    @param reg Register ID
    @param bit_id Bit ID
    @param val Value to be written
*/
void MCAL_SetBit(MCAL_Register_T reg, uint8_t bit_id, uint8_t val){
    if(val == 0){
        reg &= ~(1<<bit_id);
    } else {
        reg |= (1<<bit_id);
    }
}