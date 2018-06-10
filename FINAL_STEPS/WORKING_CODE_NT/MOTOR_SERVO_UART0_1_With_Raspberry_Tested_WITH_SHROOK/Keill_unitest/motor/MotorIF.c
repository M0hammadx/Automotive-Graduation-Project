/*
 * motor.c
 *
 *  Created on: Feb 28, 2018
 *      Author: Mohab
 */

#include "Motor_DIO.h"
#include "Motor_PWM.h"
#include "MotorIF.h"


#ifdef AUTO_SPEED_IF_DIRECTION_CHANGED
static uint16_t u16Motor1;
static uint16_t u16Motor2;
#endif
void Motor_Init(void){
	
	Motor_DIO_Init();
	Motor_PWM_Init();
	
}


void Motor_Set_Direction(g_Motor_Direction Dir){
	if(Dir == MOTOR_FORWARD){
		//Motor_PWM_break();
		SysCtlDelay(1000);
		Motor_DIO_Forward();
		
#ifdef AUTO_SPEED_IF_DIRECTION_CHANGED
		Motor_Change_Speed(u16Motor1,u16Motor2);
#endif
		
	}
	else if(Dir == MOTOR_BACKWARD){
	//	Motor_PWM_break();
		SysCtlDelay(1000);
		Motor_DIO_Backward();
		
#ifdef AUTO_SPEED_IF_DIRECTION_CHANGED
		Motor_Change_Speed(u16Motor1,u16Motor2);
#endif
	}
	else{}
	
}

void Motor_Change_Speed(uint16_t u16Motor1_Speed,uint16_t u16Motor2_Speed){
	
#ifdef AUTO_SPEED_IF_DIRECTION_CHANGED
	u16Motor1= u16Motor1_Speed;
	u16Motor2= u16Motor2_Speed;
#endif
	//map
	Motor_PWM_Speed_Control(u16Motor1_Speed,u16Motor2_Speed);
	
}

void Motor_Stop(void){
//	Motor_PWM_break();
}
