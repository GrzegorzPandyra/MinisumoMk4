#ifndef MOTOR_DRV_GUARD
#define MOTOR_DRV_GUARD
/** @file drive_ctrl.h
    @brief API to control the movement of the robot
*   Motors are numbered as follows:
*   |1 2| => |1A 2A|
*   |4 3| => |1B 2B|
*/

void Mdrv_Init(void);
void Mdrv_Forward(void);
void Mdrv_Backward(void);
void Mdrv_TurnRight(void);
void Mdrv_TurnLeft(void);
void Mdrv_SetPWM(uint8_t pwm);
void Mdrv_PWMHandler(void);
void Mdrv_Selfcheck(void);
#endif /* MOTOR_DRV_GUARD */




