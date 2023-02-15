#ifndef MOTOR_DRV_GUARD
#define MOTOR_DRV_GUARD
/** @file drive_ctrl.h
    @brief API to control the movement of the robot
*   Motors are numbered as follows:
*   |1 2| => |1A 2A|
*   |4 3| => |1B 2B|
*/

#define MCTRL_1A PC1
#define MCTRL_1B PD2
#define MCTRL_2A PD2
#define MCTRL_2B PD3

void MDRV_init(void);
void MDRV_forward(void);
void MDRV_backward(void);
void MDRV_turn_right(void);
void MDRV_turn_left(void);
#endif /* MOTOR_DRV_GUARD */




