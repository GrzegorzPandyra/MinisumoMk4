
#ifndef MCAL_GUARD
#define MCAL_GUARD
#include <stdint.h>

#define BIT_SET 1
#define BIT_CLEARED 0

typedef volatile uint8_t* Register_T;

void MCAL_WriteRegister(Register_T reg, uint8_t val);
uint8_t MCAL_ReadRegister(Register_T reg);
void MCAL_SetBit(Register_T reg, uint8_t bit, uint8_t val);
uint8_t MCAL_GetBit(Register_T reg, uint8_t bit);

#endif /* MCAL_GUARD */