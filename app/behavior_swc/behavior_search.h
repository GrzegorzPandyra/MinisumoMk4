
#ifndef BEHAVIOR_SEARCH_GUARD
#define BEHAVIOR_SEARCH_GUARD
#include <stdint.h>
#include "behavior_main.h"

void BEH_Search_Init(void);
void BEH_Search_Run(void);
Action_Recommendation_T BEH_Search_GetRecommendation(void);
#endif /* BEHAVIOR_SEARCH_GUARD */