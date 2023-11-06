
#ifndef REGISTER_GUARD
#define REGISTER_GUARD
#include <stdint.h>
#include <avr/io.h>

#define BIT_SET 1
#define BIT_CLEARED 0

typedef volatile uint8_t* Register_T;
typedef volatile uint16_t* Register16_T;

void Utils_WriteRegister(Register_T reg, uint8_t val);
uint8_t Utils_ReadRegister(Register_T reg);
uint16_t Utils_ReadRegister16(Register16_T reg);
void Utils_SetBit(Register_T reg, uint8_t bit, uint8_t val);
uint8_t Utils_GetBit(Register_T reg, uint8_t bit);
int Utils_FreeRam(void);
#endif /* REGISTER_GUARD */