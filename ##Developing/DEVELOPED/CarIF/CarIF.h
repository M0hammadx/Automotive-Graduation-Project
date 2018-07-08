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
#include "Tempreature/Tempreature.h"
#include "CarIF_Datatypes.h"

typedef enum
{
    STEER_OK = 0,
    STEER_OFR
} g_SteeringAngle;


void Calculate_car_speed(void);
void Car_Modules_Init(void);
void Car_Change_Direction(g_Car_Direction Dir);
void Car_Change_Speed_Direction(uint16_t u16Car_Speed, g_Car_Direction Dir); //5700
g_SteeringAngle Car_Change_Steer_Angle(uint8_t u8SteerAngle);
void Motor_Stop(void);
void Car_Get_Car_Info(g_CarInfo_t* CarInfo);
void CarIF_Get_DistanceElapsed(void);
#endif /* MOTOR_MOTORIF_H_ */
