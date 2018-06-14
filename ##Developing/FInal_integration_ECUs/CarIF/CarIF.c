/*
 * motor.c
 *
 *  Created on: Feb 28, 2018
 *      Author: Mohab
 */
#include "../ECU_CONFIGURATION.h"
#include "CarIF.h"

//#include "Tempreature/Tempreature.h"

#ifdef ECU1_SENSORYNODE
#include "Encoder/Encoder.h"

//#include "Compass/Compass.h"
#include "Tempreature/Tempreature.h"
#endif

#ifdef ECU2_ALGORITHMICNODE
#include "CarTaskControl/ControlButtons.h"
#include "CarTaskControl/ControlInput.h"
#endif

#ifdef ECU3_ACTUATORNODE

#include "Motor/Motor_DIO.h"
#include "Motor/Motor_PWM.h"
#include "Motor/Motor_PID.h"
#include "Servo/Servo.h"

#endif

#ifdef ECU3_ACTUATORNODE
static void PID_Init(void);

//#define CAR_SPEED_IN_Km_PER_HR
#define CAR_SPEED_IN_METER_PER_HR

int pwm = 300;

static uint8_t u8SteerAngle_global;
#endif
void Car_Modules_Init(void)
{

     TempreatureSensor_Init();
#ifdef ECU1_SENSORYNODE

    // Compass_Init();
   // Encoder_Init();
    Ultrasonic_Init();
#endif

#ifdef ECU2_ALGORITHMICNODE
    Buttons_Init();

#endif

#ifdef ECU3_ACTUATORNODE
    //  Motor_Init();

    Motor_DIO_Init();
    Motor_PWM_Init();
    Motor_PID_Init();
    // Steering_Init();
    // PID_Angle_Init();
#endif

}

#ifdef ECU3_ACTUATORNODE
void Car_Change_Direction(g_Car_Direction Dir)
{
    if (Dir == Car_FORWARD)
    {
        Motor_DIO_Forward();

    }
    else if (Dir == Car_BACKWARD)
    {
        Motor_DIO_Backward();
    }
    else
    {
    }

}

/*
 *
 speed_in_km/hr= 2*pi*r*RPM*60/1000
 v=r * RPM * 0.10472 //r meter  v m/s
 *
 * this function parameter passed by m/hr
 * this function converts from m/hr to RPM and set it into global variable
 */

void Car_Change_Speed(uint16_t u16Car_Speed)
{

#ifdef CAR_SPEED_IN_Km_PER_HR
    uint16_t desired_rpm = (uint16_t)((double)u16Car_Speed*1000)/(60*pi*diameter);
    set_Desired_RPM(desired_rpm);
#endif

#ifdef CAR_SPEED_IN_METER_PER_HR
    uint16_t desired_rpm = (uint16_t) ((double) u16Car_Speed)
    / (60 * pi * diameter);
    set_Desired_RPM(desired_rpm);
#endif

}

/*
 This function is the real interface to the Application
 this function maps its input to match the hardware interface -Servo OR DC- for steering actuator
 parameter : u8SteerAngle value from 0 (left most) => 10 (Forward) => 20 (Right most)


 */
void Car_Change_Steer_Angle(uint8_t u8SteerAngle)
{

    u8SteerAngle_global = u8SteerAngle;
//Servo angle 65 <-> 75 <-> 85
    Servo_Go(u8SteerAngle + 65);
}

static void SysTick_Init(void)
{
    NVIC_ST_CTRL_R = 0;            // disable systick
    NVIC_ST_RELOAD_R = 80000000 - 1;// 1s  //240000 3ms
    NVIC_ST_CURRENT_R = 0;
    NVIC_SYS_PRI3_R &= ~0XFF000000;// priority 0
    NVIC_ST_CTRL_R = 0X04;// setup the clk src
}

static void PID_Init(void)
{
    // PID_Speed_Init();     //from Motor_PID_Module
//PID_Angle_Init();		//From Servo_PID_Module
    //SysTick_Init();//this function must set the Systick timeout to 30 ms
}

void SysTick_Handler(void) //periodic task from RTOS
{
 //   PID_Speed_System();
//PID_Angle_System();
//Motor_PWM_Speed_Control(pwm,pwm);
//	if(pwm<620) pwm+=31;
}
#endif

void Car_Get_Car_Info(g_CarInfo_t* CarInfo)
{

#ifdef ECU1_SENSORYNODE
    uint16_t Motors_RPM[2];
    Encoder_Get_Motors_RPM(Motors_RPM);
    CarInfo->Motor_R_RPM = Motors_RPM[0];
    CarInfo->Motor_L_RPM = Motors_RPM[1];
    Encoder_Get_Distance_Elapsed(&(CarInfo->Distance_Elapsed));
    //  PID_Get_Current_Car_Speed(&(CarInfo->Car_Speed));
    //int32_t x,y;
//Compass_Get_Angles(&x,&y);
//CarInfo->x_angle = x;
//CarInfo->y_angle = y;

#endif

#ifdef ECU2_ALGORITHMICNODE
    // CarTaskControl_Get_Current_Car_Task(); //Buttons and Input like UART0
#endif

#ifdef ECU3_ACTUATORNODE
    CarInfo->Steering_Angle = u8SteerAngle_global;

#endif

Temprature_Get_Temp(&(CarInfo->Device_Temprature ));

}
