
#ifndef MCAL_GUARD
#define MCAL_GUARD
#include <stdint.h>

#define BIT_SET 1
#define BIT_CLEARED 0

typedef enum MCAL_Register_Tag {
    MCAL_UDR = 0,
    MCAL_UBRRH,
    MCAL_UBRRL
} MCAL_Register_T;

void MCAL_WriteRegister(MCAL_Register_T reg, uint8_t val);
uint8_t MCAL_ReadRegister(uint8_t reg);
void MCAL_SetBit(MCAL_Register_T reg, uint8_t bit_id, uint8_t val);

#endif /* MCAL_GUARD */