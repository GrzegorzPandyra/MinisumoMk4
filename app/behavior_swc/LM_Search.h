
#ifndef LM_SEARCH_GUARD
#define LM_SEARCH_GUARD
#include <stdint.h>

typedef enum{
    FORWARD = 0,
    BACKWARD,
    TURN_RIGHT,
    TURN_LEFT
} Direction_T;

void LM_Search_Init(void);
Direction_T LM_Search(void);
#endif /* LM_SEARCH_GUARD */