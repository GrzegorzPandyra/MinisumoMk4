
#ifndef DSD_GUARD
#define DSD_GUARD
#include <stdint.h>

typedef struct Ds_Output_Tag {
    uint16_t l_ds_output;
    uint16_t r_ds_output;
} Ds_Output_T;

void Dsdrv_Init(void);
void Dsdrv_ConversionCallback();
Ds_Output_T Dsdrv_GetDistance(void);

#if ENABLE_DS_DIAGNOSTICS
    void Dsdrv_RunDiagnostics(void);
#endif

#endif /* DSD_GUARD */