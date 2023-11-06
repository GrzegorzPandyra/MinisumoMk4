/** @file register.c
*   @brief Implementation of register access
*/
#include <avr/io.h>
#include "utils.h"

/** @brief Write 8bit register
    @param reg Register address
    @param val Value to be written
*/
void Utils_WriteRegister(Register_T reg, uint8_t val){
    *reg = val;
}

/** @brief Read 8bit register
    @param reg Register address
    @return Register value
*/
uint8_t Utils_ReadRegister(Register_T reg){
    return *reg;
} 

/** @brief Read 16bit register
    @param reg Register address
    @return Register value
*/
uint16_t Utils_ReadRegister16(Register16_T reg){
    return *reg;
} 

/** @brief Write single bit into a register
    @param reg Register address
    @param bit Bit ID
    @param val Value to be written
*/
void Utils_SetBit(Register_T reg, uint8_t bit, uint8_t val){
    if(val == 0){
        *reg &= ~(1<<bit);
    } else {
        *reg |= (1<<bit);
    }
}

uint8_t Utils_GetBit(Register_T reg, uint8_t bit){
    return (((*reg) & (1<<bit)) > 0 )? 1 : 0;
}

/**
 * @brief Tool to get current size of free RAM
 * @return int Size of free RAM
 */
int Utils_FreeRam(void){
  extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}