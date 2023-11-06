
#ifndef LSD_GUARD
#define LSD_GUARD
#include <stdint.h>

/*
x--^^^^^^^--x
| 0 1   2 3 |
| 7 6   5 4 |
x-----------x
*/

typedef struct Ls_Status_Tag {
    uint8_t ls0:1;
    uint8_t ls1:1;
    uint8_t ls2:1;
    uint8_t ls3:1;
    uint8_t ls4:1;
    uint8_t ls5:1;
    uint8_t ls6:1;
    uint8_t ls7:1;
} Ls_Status_T;

void Ls_Init(void);
Ls_Status_T Ls_GetLineStatus(void);

#if ENABLE_LS_DIAGNOSTICS
    void Ls_RunDiagnostics(void);
#endif

#endif /* LSD_GUARD */