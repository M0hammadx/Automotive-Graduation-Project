/*
 * motor.h
 *
 *  Created on: Feb 28, 2018
 *      Author: Mohab
 */

#ifndef MOTOR_MOTORIF_H_
#define MOTOR_MOTORIF_H_

//define AUTO_SPEED_IF_DIRECTION_CHANGED
typedef enum {
	MOTOR_FORWARD=0,
	MOTOR_BACKWARD
	
}g_Motor_Direction;

void Motor_Init(void);
void Motor_Set_Direction(g_Motor_Direction Dir);
void Motor_Change_Speed(uint16_t Motor1_Speed,uint16_t Motor2_Speed);
void Motor_Stop(void);
#endif /* MOTOR_MOTORIF_H_ */
