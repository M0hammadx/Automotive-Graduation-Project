/*
 * motor.h
 *
 *  Created on: Feb 28, 2018
 *      Author: Mohab
 */

#ifndef MOTOR_MOTORIF_H_
#define MOTOR_MOTORIF_H_
#include "../ECU_CONFIGURATION.h"
#include "../global.h"
#include "../user_data_types.h"
#include "Ultrasonic/Ultrasonic.h"



typedef enum
{
    Car_FORWARD = 0, Car_BACKWARD

} g_Car_Direction;

void Car_Modules_Init(void);
void Car_Change_Direction(g_Car_Direction Dir);
void Car_Change_Speed(uint16_t u16Car_Speed);
void Car_Change_Steer_Angle(uint8_t u8SteerAngle);
void Motor_Stop(void);
void Car_Get_Car_Info(g_CarInfo_t* CarInfo);
#endif /* MOTOR_MOTORIF_H_ */
