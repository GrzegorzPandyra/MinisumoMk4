
#ifndef BEHAVIOR_LINE_DETECTION_GUARD
#define BEHAVIOR_LINE_DETECTION_GUARD
#include <stdint.h>
#include "behavior_main.h"

void BEH_LineDetection_Init(void);
void BEH_LineDetection_Run(void);
Action_Recommendation_T BEH_LineDetection_GetRecommendation();
#endif /* BEHAVIOR_LINE_DETECTION_GUARD */