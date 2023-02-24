
#ifndef LSD_GUARD
#define LSD_GUARD
#include <stdint.h>

/*
x x x               x x x
x   1               2   x
x 0                   3 x


x 7                   4 x
x   6               5   x
x x x               x x x
*/

#define LS0 0
#define LS1 1
#define LS2 2
#define LS3 3
#define LS4 4
#define LS5 5
#define LS6 6
#define LS7 7

void LSD_Init(void);
uint8_t LSD_GetLineStatus(void);
#endif /* LSD_GUARD */