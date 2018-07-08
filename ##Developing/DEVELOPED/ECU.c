/*
 * ECU.c
 *
 *  Created on: Jun 12, 2018
 *      Author: Mohab
 */
#include <xdc/std.h>

#include <xdc/runtime/System.h>

#include <ti/sysbios/BIOS.h>
#include "NVM/Eeprom.h"
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Semaphore.h>

#include "ECU.h"
#include "CarIF/CarIF.h"
#include "System.h"
#include "user_data_types.h"
#include "Com/Com.h"
#include "rte/Car_temperature_rte.h"

//#include "Communication/Communication.h" //inside Communication.c include can pdur canif and init the whole comm stack
//and esp also
#ifdef ECU1_SENSORYNODE
#include "rte/Ultrasonic_data_rte.h"
#include "rte/Ultrasonic_requests_rte.h"
#include "rte/Motor_speed_data_rte.h"
#include "rte/Car_angle_data_rte.h"
#include "rte/Actual_Car_direction_rte.h"
#include "rte/Actual_Car_speed_rte.h"
#include "rte/Distance_elapsed_rte.h"
#include "rte/Car_temperature_rte.h"

#endif

#ifdef ECU2_ALGORITHMICNODE
#include "rte/Ultrasonic_data_rte.h"
#include "rte/Ultrasonic_requests_rte.h"
#include "rte/Desired_Car_speed_direction_rte.h"
#include "rte/Desired_Steering_Angle_rte.h"
#include "rte/Motor_speed_data_rte.h"
#include "rte/Actual_Car_direction_rte.h"
#include "rte/Actual_Car_speed_rte.h"

#endif

#ifdef ECU3_ACTUATORNODE
#include "rte/Car_angle_data_rte.h"
#include "rte/Desired_Car_speed_direction_rte.h"
#include "rte/Desired_Steering_Angle_rte.h"

#endif

//typedef enum
//{
//    PARKING = 0, LANEFOLLOW, DIAGNOSTIC
//} g_RequiredTask;
//
//typedef enum
//{
//    PERPENDICULAR = 0, PARALLEL
//} g_ParkingMode;
//
typedef struct CarTask_ops
{
    g_RequiredTask RequestedTask;
//g_ParkingMode ParkingMode;
} g_CarTask;

//============================================================================================================
g_ErrorType ECU_Init(void)
{

    g_ErrorType result = GOOD;

    System_ClockInit(); //this function must be commented when using Sysbios RTOS
    //Eeprom_init();
    Car_Modules_Init();

    //Communication_Init(); //Can stack and esp and for Node2 Algorithmicnode=> Raspberry_PrivateConnection_Init();
//    Com_INF_Init();

    return result;
}

////============================================================================================================
//static void GetRquestedTask(g_CarTask* CarTask)
//{
////Parking ? (Parallel \ perpend...)
////lanefollow ?
////Diagnostic Request
////polling wait the request of the operation typically
//#ifdef ECU1_SENSORYNODE
//    //Received from CAN bus //blocking
//
//#endif
//
//#ifdef ECU2_ALGORITHMICNODE
//    //received from switch ops and then send it on CAN bus to notify other nodes the mode of the operation
//#endif
//
//#ifdef ECU3_ACTUATORNODE
//    //Received from CAN bus //blocking
//#endif
//
//}
//
//static void PERPENDICULAR_Parking_Task(void)
//{
//
////implement the PERPENDICULAR_Parking here
//
//#ifdef ECU1_SENSORYNODE
//    //write your code here for the sensory ECU
//
//#endif
//#ifdef ECU2_ALGORITHMICNODE
//    //write your code here for the Algorithmic ECU
//#endif
//
//#ifdef ECU3_ACTUATORNODE
//    //write your code here for the Actuator ECU
//#endif
//
//}
////================================================================================= ==========================
//
//static void PARALLEL_Parking_Task(void)
//{
//    //implement the PARALLEL_Parking here
//#ifdef ECU1_SENSORYNODE
//    //write your code here for the sensory ECU
//#endif
//#ifdef ECU2_ALGORITHMICNODE
//    //write your code here for the Algorithmic ECU
//#endif
//
//#ifdef ECU3_ACTUATORNODE
//    //write your code here for the Actuator ECU
//#endif
//}
//
////===========================================================================================================
//static void LANEFOLLOW_Task(void)
//{
//    //implement the LANEFOLLOW_Task here
//#ifdef ECU1_SENSORYNODE
//    //write your code here for the sensory ECU
//#endif
//#ifdef ECU2_ALGORITHMICNODE
//    //write your code here for the Algorithmic ECU
//#endif
//
//#ifdef ECU3_ACTUATORNODE
//    //write your code here for the Actuator ECU
//#endif
//
//}

//===========================================================================================================

uint8_t Ultrasonic_readings_Batch[8], Ultra_Trig_Requests;
#ifdef ECU1_SENSORYNODE
void ECU1_Begin_Ultrasonic_SWC1(void)
{
    static uint8_t x = 0;
    while (1)
    {
        x++;
//        delay_microSec(30000); //this function is must be init with the ultrasonic :D
        Rte_Ultrasonic_requests_iread(&Ultra_Trig_Requests);
        //debug
        // Task_sleep(10);
//        Ultrasonic_Trig(Ultra_Trig_Requests);
//        for (int i = 0; i < 8; i++)
//        {
//            if (Ultra_Trig_Requests & 1 << i)
//            {
//                Ultrasonic_readings_Batch[i] = Ultrasonic_Get_Distant(i);
//            }
//            else
//            {
//                Ultrasonic_readings_Batch[i] = 0;   //not requested
//            }
//        }
        for (int i = 0; i < 8; i++)
        {
            if (x == 0xaa)
            x = 0;
            Ultrasonic_readings_Batch[i] = x;
        }
        //debug
        Rte_Ultrasonic_data_iwrite(Ultrasonic_readings_Batch);
        Task_sleep(100);
        /*
         * g_CarTask myCarTask;
         * while (1)
         {
         //wait for parking | Lane follow request interrupt from UART0 | Hardware switch

         GetRquestedTask(&myCarTask); //blocking function waiting for the request
         #ifdef ECU3_ACTUATORNODE
         //send identifier of the task on can to other ecus
         #endif
         if (myCarTask.RequestedTask == PARKING)
         {
         //check for parking mode(perpendicular | parallel)
         if (myCarTask.ParkingMode == PERPENDICULAR)
         PERPENDICULAR_Parking_Task();
         else if (myCarTask.ParkingMode == PARALLEL)
         PARALLEL_Parking_Task();
         }
         else if (myCarTask.RequestedTask == LANEFOLLOW)
         {
         LANEFOLLOW_Task();
         }
         else
         {
         }*/
    }
}
g_CarInfo_t ECU1_myCarInfo;
//uint16_t comp = 0;
void ECU1_Begin_Compass_SWC2(void)   //R&L RPM
{
    while (1)
    {
        //Get Compass
          Car_Get_Car_Info(&ECU1_myCarInfo);
//        comp++;
        Rte_Car_angle_data_iwrite(ECU1_myCarInfo.myCar_Angle);
        Rte_Car_temperature_iwrite(ECU1_myCarInfo.Device_Temprature);
        Task_sleep(100);
    }
}

uint8_t ECU1_SWC3_motorSpeed[2];
uint16_t ECU1_SWC3_actualCarSpeed;
uint16_t ECU1_SWC3_distanceElapsed;
uint8_t ECU1_SWC3_actualCarDirection;
void ECU1_Begin_ActualSpeedDirection_SWC3(void)   //R&L RPM
{
    while (1)
    {
        //...processing
//        static uint16 randomValue = 0;
//        randomValue++;
//        if (randomValue == 0xaa)
//        randomValue = 0;
        //...end_processing

//Get RPM Left,Right
        Car_Get_Car_Info(&ECU1_myCarInfo);
        ECU1_SWC3_motorSpeed[0] = ECU1_myCarInfo.Motor_R_RPM;
        ECU1_SWC3_motorSpeed[1] = ECU1_myCarInfo.Motor_L_RPM;
//        ECU1_SWC3_motorSpeed[0] = randomValue & 0xFF;
//        ECU1_SWC3_motorSpeed[1] = (randomValue >> 8) & 0xFF;
        Rte_Motor_speed_data_iwrite(ECU1_SWC3_motorSpeed);
//Get actual car speed
        ECU1_SWC3_actualCarSpeed = ECU1_myCarInfo.myCar_Speed;
//        ECU1_SWC3_actualCarSpeed = randomValue;
        Rte_Actual_Car_speed_iwrite(ECU1_SWC3_actualCarSpeed);
//Get actual direction
//        ECU1_SWC3_actualCarDirection = randomValue & 0xFF;
//        Rte_Actual_Car_direction_iwrite(ECU1_SWC3_actualCarDirection);
        //Get distance elapsed
        ECU1_SWC3_distanceElapsed = ECU1_myCarInfo.Distance_Elapsed;
        Rte_Distance_elapsed_iwrite(ECU1_myCarInfo.Distance_Elapsed);
        Task_sleep(100);

    }
}



#endif

#ifdef ECU2_ALGORITHMICNODE
uint8_t ECU2_SWC1_UltrasonicReads[8];
uint16_t ECU2_SWC1_ActualCarSpeed = 0;
uint8_t ECU2_SWC1_ActualDirection = 0;
uint16_t ECU2_SWC1_DistanceElapsed = 0;

uint8_t ECU2_SWC1_motorSpeed[2] =
{   0, 0};

void ECU2_Begin_Ultrasonic_SWC1(void)
{
    uint16_t ECU2_SWC1_DesiredCarSpeed = 0;
    uint8_t ECU2_SWC1_DesiredDirection = 0;
    uint8_t ECU2_SWC1_DesiredSteeringAngle = 0;
    static uint8_t DataRx_Timeout=0;
    while(1)
    {
//        Rte_Ultrasonic_requests_iwrite(0xFF);
//        DataRx_Timeout=Rte_Ultrasonic_data_iread(ECU2_SWC1_UltrasonicReads);
//        Rte_Actual_Car_direction_iread(&ECU2_SWC1_ActualDirection);
//        Rte_Actual_Car_speed_iread(&ECU2_SWC1_ActualCarSpeed);
//        Rte_Motor_speed_data_iread(ECU2_SWC1_motorSpeed);
//        Rte_Distance_elapsed_iread(&ECU2_SWC1_DistanceElapsed);
//        //debug data
        //processing..........
//        if(DataRx_Timeout ==0)
//        {
//
//        }
//        else
//        {
//            ECU2_SWC1_DesiredCarSpeed += 1000;
//            if(ECU2_SWC1_DesiredCarSpeed > 5000)
//            {
//                ECU2_SWC1_DesiredCarSpeed = 1000;
//                ECU2_SWC1_DesiredDirection = (ECU2_SWC1_DesiredDirection)? 0 : 1;
//            }
//            ECU2_SWC1_DesiredSteeringAngle++;
//            if(ECU2_SWC1_DesiredSteeringAngle >= 48)
//            {
//                ECU2_SWC1_DesiredSteeringAngle = 0;
//            }
//        }
        ECU2_SWC1_DesiredCarSpeed =
        //rte_write car_speed, direction.
        Rte_Desired_Car_speed_groupSignal_iwrite(ECU2_SWC1_DesiredCarSpeed);
        Rte_Desired_Car_Direction_signalGroup_iwrite(ECU2_SWC1_DesiredDirection);
        //rte_write desired_steering.
        Rte_Desired_Steering_Angle_iwrite(ECU2_SWC1_DesiredSteeringAngle);
        Task_sleep(20);
    }
}

#endif

#ifdef ECU3_ACTUATORNODE
uint16_t ECU3_SWC1_DesiredCarSpeed = 0;
uint8_t ECU3_SWC1_DesiredCarDirection = 0;
void ECU3_Begin_Motor_SWC1(void)
{
    while (1)
    {
        Rte_Desired_Car_speed_iread(&ECU3_SWC1_DesiredCarSpeed);
        Rte_Desired_Car_Direction_iread(&ECU3_SWC1_DesiredCarDirection);

        //Debug
        Car_Change_Speed_Direction(
                ECU3_SWC1_DesiredCarSpeed,
                (g_Car_Direction) ECU3_SWC1_DesiredCarDirection);
        Task_sleep(20);

    }
}
uint16_t ECU3_SWC2_CompassAngle = 0;
void ECU3_Begin_Compass_SWC2(void)
{
    while (1)
    {
//        Task_sleep(10);
        Rte_Car_angle_data_iread(&ECU3_SWC2_CompassAngle);
        //Debug
        Task_sleep(20);
    }
}

uint8_t ECU3_SWC3_DesiredSteeringAngle = 0;
void ECU3_Begin_SteeringAngle_SWC3(void)
{
    g_SteeringAngle Steer_Res;
    while (1)
    {
        Rte_Desired_Steering_Angle_iread(&ECU3_SWC3_DesiredSteeringAngle);
        //Debug
        //0 => most left
        //48 => most right
        Steer_Res = Car_Change_Steer_Angle(ECU3_SWC3_DesiredSteeringAngle);
        if (Steer_Res == STEER_OK)
        {
//ok
        }
        else
        {
//report error
        }
        //Car_Change_Steering_Angle(ECU3_SWC3_DesiredSteeringAngle);

        Task_sleep(20);
    }
}

#include "rte/Actual_Car_direction_rte.h"
#include "rte/Actual_Car_speed_rte.h"
#include "rte/Motor_speed_data_rte.h"

uint16_t ECU3_SWC4_ActualCarSpeed = 0;
uint8_t ECU3_SWC4_ActualDirection = 0;
uint8_t ECU3_SWC4_motorSpeed[2] = { 0, 0 };
void ECU3_Begin_ActualData_SWC4(void)
{
    while (1)
    {
        Rte_Actual_Car_direction_iread(&ECU3_SWC4_ActualDirection);
        Rte_Actual_Car_speed_iread(&ECU3_SWC4_ActualCarSpeed);
        Rte_Motor_speed_data_iread(ECU3_SWC4_motorSpeed);
        //debug data
    }
}
#endif
