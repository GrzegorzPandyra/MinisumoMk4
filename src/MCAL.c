/** @file MCAL.c
*   @brief Implementation of MCAL
*/
#include <avr/io.h>
#include "MCAL.h"

/** @brief Write 8bit register
    @param reg Register address
    @param val Value to be written
*/
void MCAL_WriteRegister(Register_T reg, uint8_t val){
    *reg = val;
}

/** @brief Read 8bit register
    @param reg Register address
    @return Register value
*/
uint8_t MCAL_ReadRegister(Register_T reg){
    return *reg;
} 

/** @brief Read 16bit register
    @param reg Register address
    @return Register value
*/
uint16_t MCAL_ReadRegister16(Register16_T reg){
    return *reg;
} 

/** @brief Write single bit into a register
    @param reg Register address
    @param bit Bit ID
    @param val Value to be written
*/
void MCAL_SetBit(Register_T reg, uint8_t bit, uint8_t val){
    if(val == 0){
        *reg &= ~(1<<bit);
    } else {
        *reg |= (1<<bit);
    }
}

uint8_t MCAL_GetBit(Register_T reg, uint8_t bit){
    return 0;
}