
#ifndef DSD_GUARD
#define DSD_GUARD
#include <stdint.h>

void Dsdrv_Init(void);
void Dsdrv_ConversionCallback();
uint16_t Dsdrv_GetDistance(void);

#if ENABLE_DS_DIAGNOSTICS
    void Dsdrv_RunDiagnostics(void);
#endif

#endif /* DSD_GUARD */