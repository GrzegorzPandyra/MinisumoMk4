
#ifndef BEHAVIOR_ENEMY_DETECTION_GUARD
#define BEHAVIOR_ENEMY_DETECTION_GUARD
#include <stdint.h>
#include "behavior_main.h"

void BEH_EnemyDetection_Init(void);
void BEH_EnemyDetection_Run(void);
Action_Recommendation_T BEH_EnemyDetection_GetRecommendation(void);
#endif /* BEHAVIOR_ENEMY_DETECTION_GUARD */