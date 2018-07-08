/*
 *  ======== main.c ========
 */
#include "ECU_CONFIGURATION.h"
#include <xdc/std.h>
#include "UART.h"
#include <xdc/runtime/System.h>

#include <ti/sysbios/BIOS.h>

#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/knl/Clock.h>
#include "Com/Com.h"
#include "ECU.h"
#include "CarIF/CarIF.h"
#include "CarIF/Ultrasonic/Ultrasonic.h"

void clockHandler0()
{
    UART_OutString("ClK Handler Enter\n");
//    System_flush();
    Task_yield();
//    System_printf("ClK Handler Exit\n");
//    System_flush();
}

/*
 *  ======== taskFxn ========
 */
#ifdef ECU1_SENSORYNODE
uint32_t Read;
void taskFxn1() // com
{
    Com_Main();
}

void taskFxn2()
{

    ECU1_Begin_Ultrasonic_SWC1();
}

void taskFxn3()
{
    ECU1_Begin_ActualSpeedDirection_SWC3();
//    while(1){
//
//    }
}

void taskFxn4()
{
    ECU1_Begin_Compass_SWC2();
}

g_CarInfo_t car_info;
void taskFxn5()
{
    while (1)
    {
        Car_Get_Car_Info(&car_info);
        Task_sleep(100);
    }
}
void fxn_idle1() //dummy SWC
{
//    UART_OutString("enter Idle fxn\n");
//    System_flush();

}

void Clock_Calculate_DistanceElapsed(void) //Periodic SWI -> 200 ms
{
    CarIF_Get_DistanceElapsed();
}

#endif

#ifdef ECU2_ALGORITHMICNODE
void taskFxn1() // com
{
    Com_Main();
}

void taskFxn2() // ultra
{
    ECU2_Begin_Ultrasonic_SWC1();
}

void taskFxn3() //empty
{
    while(1)
    {
        Task_sleep(1000);
    }
}

void taskFxn4() //empty
{
    while(1)
    {
        Task_sleep(1000);
    }
}

void taskFxn5() //empty
{
    while(1)
    {
        Task_sleep(1000);
    }
}
void fxn_idle1() // SWC
{

}

void Clock_Calculate_DistanceElapsed() //Periodic SWI -> 10 ms
{

}

#endif

#ifdef ECU3_ACTUATORNODE

Void taskFxn1() //Com_Main
{

    while (1)
    {

        Task_sleep(1000);
    }
}

Void taskFxn2()
{
    //ECU3_Begin_SteeringAngle_SWC3();
    ECU3_Begin_Motor_SWC1();
}

void taskFxn3()
{
    ECU3_Begin_ActualData_SWC4();
}
void taskFxn4()
{
    ECU3_Begin_SteeringAngle_SWC3();
}

void taskFxn5()
{

    ECU3_Begin_Compass_SWC2();
}

void fxn_idle1()
{

}

void Clock_Calculate_DistanceElapsed() //Periodic SWI -> 10 ms
{
    Car_Change_Steer_Angle(0);
                   Car_Change_Steer_Angle(24);
                   Car_Change_Steer_Angle(48);
   //
           Car_Change_Speed_Direction(1200, Car_FORWARD);
           for (uint32_t i = 0; i < 8000000; i++)
               ;
           Car_Change_Speed_Direction(2500, Car_FORWARD);
           for (uint32_t i = 0; i < 8000000; i++)
               ;
           Car_Change_Speed_Direction(4000, Car_FORWARD);
           for (uint32_t i = 0; i < 8000000; i++)
               ;
           Car_Change_Speed_Direction(5600, Car_FORWARD);
           for (uint32_t i = 0; i < 8000000; i++)
               ;
           Car_Change_Speed_Direction(0, Car_FORWARD);


           Car_Change_Speed_Direction(1200, Car_BACKWARD);
           for (uint32_t i = 0; i < 8000000; i++)
               ;
           Car_Change_Speed_Direction(2500, Car_BACKWARD);
           for (uint32_t i = 0; i < 8000000; i++)
               ;
           Car_Change_Speed_Direction(4000, Car_BACKWARD);
           for (uint32_t i = 0; i < 8000000; i++)
               ;
           Car_Change_Speed_Direction(5600, Car_BACKWARD);
           for (uint32_t i = 0; i < 8000000; i++)
               ;
           Car_Change_Speed_Direction(0, Car_FORWARD);

   //        Car_Change_Steer_Angle(48);
           Car_Change_Speed_Direction(0, Car_FORWARD);
           for (uint32_t i = 0; i < 8000000; i++);
}

#endif
/*
 *  ======== main ========
 */

Int main()
{
    /*
     * use ROV->SysMin to view the characters in the circular buffer
     */
    ECU_Init();
    UART_Init();
//    Com_Main();
//    while (1)
//    {

//        Car_Change_Steer_Angle(24);

//                Car_Change_Steer_Angle(0);
//                Car_Change_Steer_Angle(24);
//                Car_Change_Steer_Angle(48);
////
//        Car_Change_Speed_Direction(1200, Car_FORWARD);
//        for (uint32_t i = 0; i < 8000000; i++)
//            ;
//        Car_Change_Speed_Direction(2500, Car_FORWARD);
//        for (uint32_t i = 0; i < 8000000; i++)
//            ;
//        Car_Change_Speed_Direction(4000, Car_FORWARD);
//        for (uint32_t i = 0; i < 8000000; i++)
//            ;
//        Car_Change_Speed_Direction(5600, Car_FORWARD);
//        for (uint32_t i = 0; i < 8000000; i++)
//            ;
//        Car_Change_Speed_Direction(0, Car_FORWARD);
//
//
//        Car_Change_Speed_Direction(1200, Car_BACKWARD);
//        for (uint32_t i = 0; i < 8000000; i++)
//            ;
//        Car_Change_Speed_Direction(2500, Car_BACKWARD);
//        for (uint32_t i = 0; i < 8000000; i++)
//            ;
//        Car_Change_Speed_Direction(4000, Car_BACKWARD);
//        for (uint32_t i = 0; i < 8000000; i++)
//            ;
//        Car_Change_Speed_Direction(5600, Car_BACKWARD);
//        for (uint32_t i = 0; i < 8000000; i++)
//            ;
//        Car_Change_Speed_Direction(0, Car_FORWARD);
//
////        Car_Change_Steer_Angle(48);
//        Car_Change_Speed_Direction(0, Car_FORWARD);
//        Car_Change_Steer_Angle(24);


//
//        Car_Change_Steer_Angle(25);
//
//        Car_Change_Steer_Angle(18);
//
//        Car_Change_Steer_Angle(30);
//

//        Car_Change_Steer_Angle(5);


  //  }
////
////
//    Car_Get_Car_Info(&car_info);
//}
//    ECU1_Begin_SWC1();
    BIOS_start(); /* does not return */
    return (0);
}
