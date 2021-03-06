/*
 * ECU.c
 *
 *  Created on: Jun 12, 2018
 *      Author: Mohab
 */

#include "ECU.h"
#include "CarIF/CarIF.h"
#include "System.h"
//#include "Communication/Communication.h" //inside Communication.c include can pdur canif and init the whole comm stack
//and esp also
#ifdef ECU2_ALGORITHMICNODE
#include "rte/Ultrasonic_data_rte.h"
#include "rte/Ultrasonic_requests_rte.h"
#endif

#ifdef ECU1_SENSORYNODE
#include "rte/Ultrasonic_data_rte.h"
#include "rte/Ultrasonic_requests_rte.h"
#endif

typedef enum
{
    PARKING = 0, LANEFOLLOW, DIAGNOSTIC
} g_RequiredTask;

typedef enum
{
    PERPENDICULAR = 0, PARALLEL
} g_ParkingMode;
typedef struct CarTask_ops
{
    g_RequiredTask RequestedTask;
    g_ParkingMode ParkingMode;
} g_CarTask;

//============================================================================================================
g_ErrorType ECU_Init(void)
{

    g_ErrorType result = GOOD;

    System_ClockInit(); //this function must be commented when using Sysbios RTOS
    Car_Modules_Init();
    //Communication_Init(); //Can stack and esp and for Node2 Algorithmicnode=> Raspberry_PrivateConnection_Init();
    // NonVolatileMemory_Init(); //eeprom
    return result;
}

//============================================================================================================
static void GetRquestedTask(g_CarTask* CarTask)
{
//Parking ? (Parallel \ perpend...)
//lanefollow ?
//Diagnostic Request
//polling wait the request of the operation typically
#ifdef ECU1_SENSORYNODE
    //Received from CAN bus //blocking

#endif

#ifdef ECU2_ALGORITHMICNODE
    //received from switch ops and then send it on CAN bus to notify other nodes the mode of the operation
#endif

#ifdef ECU3_ACTUATORNODE
    //Received from CAN bus //blocking
#endif

}

static void PERPENDICULAR_Parking_Task(void)
{

//implement the PERPENDICULAR_Parking here

#ifdef ECU1_SENSORYNODE
    //write your code here for the sensory ECU

#endif
#ifdef ECU2_ALGORITHMICNODE
    //write your code here for the Algorithmic ECU
#endif

#ifdef ECU3_ACTUATORNODE
    //write your code here for the Actuator ECU
#endif

}
//================================================================================= ==========================

static void PARALLEL_Parking_Task(void)
{
    //implement the PARALLEL_Parking here
#ifdef ECU1_SENSORYNODE
    //write your code here for the sensory ECU
#endif
#ifdef ECU2_ALGORITHMICNODE
    //write your code here for the Algorithmic ECU
#endif

#ifdef ECU3_ACTUATORNODE
    //write your code here for the Actuator ECU
#endif
}

//===========================================================================================================
static void LANEFOLLOW_Task(void)
{
    //implement the LANEFOLLOW_Task here
#ifdef ECU1_SENSORYNODE
    //write your code here for the sensory ECU
#endif
#ifdef ECU2_ALGORITHMICNODE
    //write your code here for the Algorithmic ECU
#endif

#ifdef ECU3_ACTUATORNODE
    //write your code here for the Actuator ECU
#endif

}

//===========================================================================================================
g_CarInfo_t myCarInfo;

#ifdef ECU1_SENSORYNODE
uint32_t dist1, dist2, dist3, dist4, dist5, dist6, dist7, dist8;

void ECU_Begin(void)
{

    EnableGlobalInterrupts();
    while (1)
    {
        delay_microSec(30000); //this function is must be init with the ultrasonic :D
//        for(int k=0 ; k<=8000000;k++);
        Ultrasonic_Trig(Front_Left_Ultrasonic);
        Ultrasonic_Trig(Front_Right_Ultrasonic);
        Ultrasonic_Trig(Right_Front_Ultrasonic);
//        Ultrasonic_Trig(Right_Back_Ultrasonic);
//        Ultrasonic_Trig(Back_Right_Ultrasonic);
//        Ultrasonic_Trig(Back_Left_Ultrasonic);
//        Ultrasonic_Trig(Left_Back_Ultrasonic);
//        Ultrasonic_Trig(Left_Front_Ultrasonic);

        dist1 = Get_Distant(Front_Left);
        dist2 = Get_Distant(Front_Right);
        dist3 = Get_Distant(Right_Front);
//        dist4 = Get_Distant(Right_Back);
//        dist5 = Get_Distant(Back_Right);
//        dist6 = Get_Distant(Back_Left);
//        dist7 = Get_Distant(Left_Back);
//        dist8 = Get_Distant(Left_Front);

        Car_Get_Car_Info(&myCarInfo);

    }

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
     }
     }
     */
}
#endif

#ifdef ECU2_ALGORITHMICNODE
void ECU2_Begin_SWC1(void)
{
    while(1)
    {
        Rte_Ultrasonic_requests_iwrite(Front_Left_Ultrasonic|Back_Left_Ultrasonic);
        Rte_Ultrasonic_data_iread(Front_Left);
        Rte_Ultrasonic_data_iread(Back_Left);

    }

}

#endif

#ifdef ECU3_ACTUATORNODE
void ECU_Begin(void)
{
    while (1)
    {
        Car_Change_Direction(Car_FORWARD);
        //Motor_PWM_Speed_Control(620, 620);
        Car_Change_Speed(5700);
        for (int k = 0; k <= 8000000; k++)
            ;

        Car_Change_Direction(Car_FORWARD);
        //  Motor_PWM_Speed_Control(300, 300);
        Car_Change_Speed(4500);
        for (int k = 0; k <= 8000000; k++)
            ;

        Car_Change_Direction(Car_BACKWARD);
        // Motor_PWM_Speed_Control(620, 620);
        Car_Change_Speed(2000);
        for (int k = 0; k <= 8000000; k++)
            ;

        Car_Change_Direction(Car_BACKWARD);
        //Motor_PWM_Speed_Control(300, 300);
        Car_Change_Speed(1000);
        for (int k = 0; k <= 8000000; k++)
            ;

    }
}

#endif
