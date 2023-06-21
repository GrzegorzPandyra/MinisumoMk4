
#ifndef DSD_GUARD
#define DSD_GUARD
#include <stdint.h>

void Dsd_Init(void);
void Dsd_ConversionCallback();
uint16_t Dsd_GetDistance(void);

#endif /* DSD_GUARD */