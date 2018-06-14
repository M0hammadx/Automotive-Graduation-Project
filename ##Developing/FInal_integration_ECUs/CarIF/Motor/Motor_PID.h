
#ifndef _PID_H_
#define _PID_H_

#include "Motor_PWM.h"


#define   k   0.32
#define   b    46
#define   Kd   0.47
#define   Ki   0.04
#define   Kp   4






void set_desired_speed(uint16_t speed_in_m_hr);
void set_Actual_Speed(uint16_t* act_speed);
void PID_Speed_Init(void);
void PID_Speed_System(void);
void PID_Get_Current_Car_Speed(uint16_t* PtrCarSpeed);
uint16_t get_Actual_Speed(void);

#endif  //_PID_H_
