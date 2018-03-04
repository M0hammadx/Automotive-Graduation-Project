/*
 * motor_pwm.h
 *
 *  Created on: Feb 28, 2018
 *      Author: Mohab
 */

#ifndef MOTOR_MOTOR_PWM_H_
#define MOTOR_MOTOR_PWM_H_

#include "../DriverIncludes.h"


void Motor_PWM_Init(void);
void Motor_PWM_Start(void);
void Motor_PWM_Stop(void);
void Motor_PWM_Speed_Control(uint16_t ui16AdjustMotor1 ,uint16_t ui16AdjustMotor2);
void Motor_PWM_break(void);
#endif /* MOTOR_MOTOR_PWM_H_ */
