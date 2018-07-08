/*
 * motor.c
 *
 *  Created on: Feb 28, 2018
 *      Author: Mohab
 */
#include "../CAR_PERIPHERALS_PARAMETERS.h"
#include "../ECU_CONFIGURATION.h"
#include "../NVM/Eeprom.h"
#include "CarIF.h"

#ifdef ECU1_SENSORYNODE
#include "Encoder/Encoder.h"
#include "Compass/Compass.h"
#endif

#ifdef ECU2_ALGORITHMICNODE
//#include "CarTaskControl/ControlButtons.h"
//#include "CarTaskControl/ControlInput.h"
#endif

#ifdef ECU3_ACTUATORNODE

#include "Motor/Motor_control_new.h"
#include "Steering/steering.h"
//#include "Motor/Motor_PID.h"
#include "Encoder/Encoder.h"


#endif

#ifdef ECU3_ACTUATORNODE

//static void PID_Init(void);
int pwm = 300;
static uint8_t u8SteerAngle_global;
uint8_t Eeprom_Array[1];
uint8_t size;
#endif
//static uint16_t g_Distance_elapsed = 0;
static uint16_t g_current_car_speed=0;
 void Calculate_car_speed(void) //output
{
    uint8_t rpm[2];
    uint16_t motors_speed[2];
//get motors rpm from handler(encoders)

    Encoder_Get_Motors_RPM(rpm);
    /*
     calculate current speed in Km/hr
     */
#ifdef CAR_SPEED_IN_Km_PER_HR
    motors_speed[0]=(rpm[0]*pi*60*diameter)/1000;
    motors_speed[1]=(rpm[1]*pi*60*diameter)/1000;
    *current_car_speed=(motors_speed[0]+motors_speed[1])/2;
#endif
    /*
     calculate current speed in m/hr
     */
#ifdef CAR_SPEED_IN_METER_PER_HR
    motors_speed[0] = (rpm[0] * pi * 60 * diameter);
    motors_speed[1] = (rpm[1] * pi * 60 * diameter);
    g_current_car_speed = (motors_speed[0] + motors_speed[1]) / 2;
//    set_current_car_speed((motors_speed[0] + motors_speed[1]) / 2);
#endif
}

//static void set_current_car_speed(uint16_t car_speed)
//{
//
//    g_current_car_speed = car_speed;
//}
//static void get_current_car_speed(uint16_t* car_speed)
//{
//
//    *car_speed = g_current_car_speed;
//}
static uint16_t s_DistanceElapsed=0;
void CarIF_Get_DistanceElapsed(void) //200ms //clock
{

//    uint16_t my_current_speed;
    //Calculate_car_speed(&my_current_speed);
    //set_current_car_speed(g_current_car_speed);
    s_DistanceElapsed+= (g_current_car_speed*0.2*100)/(60*60);

}

void Car_Modules_Init(void)
{

    //TempreatureSensor_Init();
#ifdef ECU1_SENSORYNODE

//    Compass_Init();
    Encoder_Init();
//    Ultrasonic_Init();
#endif

#ifdef ECU2_ALGORITHMICNODE
    // Buttons_Init();

#endif

#ifdef ECU3_ACTUATORNODE
    ///  Motor_Init();
    Motors_control_init();
//    Eeprom_readArrayID(ID_1, Eeprom_Array, &size);
    steering_init(24);
#endif

}

#ifdef ECU3_ACTUATORNODE
/*
 void Car_Change_Direction(g_Car_Direction Dir)
 {
 if (Dir == Car_FORWARD)
 {
 //  Motor_DIO_Forward();

 }
 else if (Dir == Car_BACKWARD)
 {
 //Motor_DIO_Backward();
 }
 else
 {
 }

 }*/

/*
 *
 speed_in_km/hr= 2*pi*r*RPM*60/1000
 v=r * RPM * 0.10472 //r meter  v m/s
 *
 * this function parameter passed by m/hr
 * this function converts from m/hr to RPM and set it into global variable
 */
uint16_t PWM = 0;
void Car_Change_Speed_Direction(uint16_t u16Car_Speed, g_Car_Direction Dir)
{

#ifdef CAR_SPEED_IN_Km_PER_HR //MAX 5.7
    uint16_t desired_rpm = (uint16_t) ((double) u16Car_Speed * 1000)
    / (60 * pi * diameter);
#ifdef Motor_without_PID

#endif
#ifdef Motor_with_PID
    set_Desired_RPM(desired_rpm);
#endif
#endif

#ifdef CAR_SPEED_IN_METER_PER_HR  //MAX 2225
    if(u16Car_Speed==0){
        PWM=0;
    }
    else{
    uint16_t desired_rpm = (uint16_t) ((double) u16Car_Speed)
    / (60 * pi * diameter);
#ifdef Motor_without_PID
    PWM = (desired_rpm + b) / k;
    // Motor_PWM_Speed_Control(PWM,Dir);
    }
    Motors_Control(PWM+2, Dir);

#endif
#ifdef Motor_with_PID
    set_Desired_RPM(desired_rpm);
#endif
#endif

}

/*
 This function is the real interface to the Application
 this function maps its input to match the hardware interface -Servo OR DC- for steering actuator
 parameter : u8SteerAngle value from 0 (left most) => 10 (Forward) => 20 (Right most)


 */
g_SteeringAngle Car_Change_Steer_Angle(uint8_t u8SteerAngle)
{
    g_SteeringAngle res = STEER_OK;
    u8SteerAngle_global = u8SteerAngle;
    if (u8SteerAngle_global >= (uint8_t)0 && u8SteerAngle_global <= 48)
    {
        if (u8SteerAngle_global == 0)
        u8SteerAngle_global = 5;
        if (u8SteerAngle_global == 48)
        u8SteerAngle_global = 43;
        steering_AngleSet(u8SteerAngle_global);
    }
    else
    {
        res= STEER_OFR;
    }
    return res;

}
//
//static void SysTick_Init(void)
//{
//    NVIC_ST_CTRL_R = 0;            // disable systick
//    NVIC_ST_RELOAD_R = 80000000 - 1;            // 1s  //240000 3ms
//    NVIC_ST_CURRENT_R = 0;
//    NVIC_SYS_PRI3_R &= ~0XFF000000;            // priority 0
//    NVIC_ST_CTRL_R = 0X04;            // setup the clk src
//}
//
//static void PID_Init(void)
//{
//  PID_Speed_Init();     //from Motor_PID_Module
//  PID_Angle_Init();		//From Servo_PID_Module
//  SysTick_Init();//this function must set the Systick timeout to 30 ms
//}
//
//void SysTick_Handler(void) //periodic task from RTOS
//{
//  PID_Speed_System();
//  PID_Angle_System();
//  Motor_PWM_Speed_Control(pwm,pwm);
//	if(pwm<620) pwm+=31;
//}
#endif

void Car_Get_Car_Info(g_CarInfo_t* CarInfo)
{

    // Temprature_Get_Temp(&(CarInfo->Device_Temprature));

#ifdef ECU1_SENSORYNODE
    uint8_t Motors_RPM[2];
//    uint16_t current_car_speed;
    Encoder_Get_Motors_RPM(Motors_RPM);
    CarInfo->Motor_R_RPM = Motors_RPM[0];
    CarInfo->Motor_L_RPM = Motors_RPM[1];
//    get_current_car_speed(&current_car_speed);
    CarInfo->myCar_Speed = g_current_car_speed;
    CarInfo->Distance_Elapsed=s_DistanceElapsed;
//    PID_Get_Current_Car_Speed(&(CarInfo->myCar_Speed));

    // Compass_Get_Angles(&(CarInfo->myCar_Angle));

#endif

#ifdef ECU2_ALGORITHMICNODE
    // CarTaskControl_Get_Current_Car_Task(); //Buttons and Input like UART0
#endif

#ifdef ECU3_ACTUATORNODE
    CarInfo->Steering_Angle = u8SteerAngle_global;

#endif

}
