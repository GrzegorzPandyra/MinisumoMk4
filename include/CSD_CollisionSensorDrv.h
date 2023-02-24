
#ifndef CSD_GUARD
#define CSD_GUARD
#include <stdint.h>

typedef enum {
    NO_COLLISION = 0,
    FRONT_COLLISION,
    REAR_COLLISION
} CollisionStatus_T;

void CSD_Init(void);
CollisionStatus_T CSD_GetCollisionStatus(void);
#endif /* CSD_GUARD */