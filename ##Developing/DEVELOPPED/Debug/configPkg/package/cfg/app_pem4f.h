/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-D13
 */

#include <xdc/std.h>

#include <ti/sysbios/hal/Hwi.h>
extern const ti_sysbios_hal_Hwi_Handle Can0_handle;

#include <ti/sysbios/knl/Semaphore.h>
extern const ti_sysbios_knl_Semaphore_Handle rte_Binary_Semaphore_Ultrasonic_Data_handle;

#include <ti/sysbios/knl/Semaphore.h>
extern const ti_sysbios_knl_Semaphore_Handle rte_Binary_Semaphore_Ultrasonic_Requests_handle;

#include <ti/sysbios/hal/Hwi.h>
extern const ti_sysbios_hal_Hwi_Handle Timer2A_Handle;

#include <ti/sysbios/hal/Hwi.h>
extern const ti_sysbios_hal_Hwi_Handle Timer3A_Handle;

#include <ti/sysbios/hal/Hwi.h>
extern const ti_sysbios_hal_Hwi_Handle Timer3B_Handle;

#include <ti/sysbios/hal/Hwi.h>
extern const ti_sysbios_hal_Hwi_Handle WTimer2B_Handle;

#include <ti/sysbios/hal/Hwi.h>
extern const ti_sysbios_hal_Hwi_Handle WTimer3A_Handle;

#include <ti/sysbios/hal/Hwi.h>
extern const ti_sysbios_hal_Hwi_Handle WTimer3B_Handle;

#include <ti/sysbios/hal/Hwi.h>
extern const ti_sysbios_hal_Hwi_Handle Timer1A_Handle;

#include <ti/sysbios/hal/Hwi.h>
extern const ti_sysbios_hal_Hwi_Handle Timer1B_Handle;

#include <ti/sysbios/knl/Semaphore.h>
extern const ti_sysbios_knl_Semaphore_Handle rte_Mutex_Ultrasonic_Requests_handle;

#include <ti/sysbios/knl/Semaphore.h>
extern const ti_sysbios_knl_Semaphore_Handle rte_Mutex_Ultrasonic_Data_handle;

#include <ti/sysbios/knl/Semaphore.h>
extern const ti_sysbios_knl_Semaphore_Handle rte_Binary_Semaphore_Car_angle_Data_handle;

#include <ti/sysbios/knl/Semaphore.h>
extern const ti_sysbios_knl_Semaphore_Handle rte_Mutex_Motor_speed_Data_handle;

#include <ti/sysbios/knl/Semaphore.h>
extern const ti_sysbios_knl_Semaphore_Handle rte_Binary_Semaphore_Motor_speed_Data_handle;

#include <ti/sysbios/knl/Semaphore.h>
extern const ti_sysbios_knl_Semaphore_Handle rte_Mutex_Desired_Car_speed_Data_handle;

#include <ti/sysbios/knl/Semaphore.h>
extern const ti_sysbios_knl_Semaphore_Handle rte_Binary_Semaphore_Desired_Car_speed_handle;

#include <ti/sysbios/knl/Semaphore.h>
extern const ti_sysbios_knl_Semaphore_Handle rte_Binary_Semaphore_Car_temperature_Data_handle;

#include <ti/sysbios/knl/Task.h>
extern const ti_sysbios_knl_Task_Handle task1;

#include <ti/sysbios/knl/Task.h>
extern const ti_sysbios_knl_Task_Handle task2;

#include <ti/sysbios/knl/Clock.h>
extern const ti_sysbios_knl_Clock_Handle clock0;

#include <ti/sysbios/knl/Task.h>
extern const ti_sysbios_knl_Task_Handle task3;

#include <ti/sysbios/knl/Semaphore.h>
extern const ti_sysbios_knl_Semaphore_Handle rte_Binary_Semaphore_Desired_Car_Direction_handle;

#include <ti/sysbios/knl/Semaphore.h>
extern const ti_sysbios_knl_Semaphore_Handle rte_Binary_Semaphore_Desired_Steering_Angle_handle;

#include <ti/sysbios/knl/Clock.h>
extern const ti_sysbios_knl_Clock_Handle clock1;

#include <ti/sysbios/knl/Semaphore.h>
extern const ti_sysbios_knl_Semaphore_Handle Com_Binary_Semaphore_Timeout_Frame0_SpeedDirection_Handle;

#include <ti/sysbios/knl/Semaphore.h>
extern const ti_sysbios_knl_Semaphore_Handle Com_Binary_Semaphore_Timeout_Frame0_SteeringAngle_Handle;

#include <ti/sysbios/knl/Semaphore.h>
extern const ti_sysbios_knl_Semaphore_Handle Com_Binary_Semaphore_Timeout_Frame1_UltrasonicReq_Handle;

#include <ti/sysbios/knl/Semaphore.h>
extern const ti_sysbios_knl_Semaphore_Handle Com_Binary_Semaphore_Timeout_Frame0_UltrasonicData_Handle;

#include <ti/sysbios/knl/Semaphore.h>
extern const ti_sysbios_knl_Semaphore_Handle Com_ECU1_Binary_Semaphore_Timeout_Frame2_CarAngle_Handle;

#include <ti/sysbios/knl/Semaphore.h>
extern const ti_sysbios_knl_Semaphore_Handle Com_ECU1_Binary_Semaphore_Timeout_Frame2_Temp_Handle;

#include <ti/sysbios/knl/Semaphore.h>
extern const ti_sysbios_knl_Semaphore_Handle Com_ECU1_Binary_Semaphore_Timeout_Frame1_MotorSpeed_Handle;

#include <ti/sysbios/knl/Semaphore.h>
extern const ti_sysbios_knl_Semaphore_Handle Com_ECU1_Binary_Semaphore_Timeout_Frame1_Actual_CarSpeed_Handle;

#include <ti/sysbios/knl/Semaphore.h>
extern const ti_sysbios_knl_Semaphore_Handle Com_ECU1_Binary_Semaphore_Timeout_Frame1_Actual_CarDirection_Handle;

#include <ti/sysbios/knl/Semaphore.h>
extern const ti_sysbios_knl_Semaphore_Handle Com_ECU1_Binary_Semaphore_Timeout_Frame1_DistanceElapsed_Handle;

#include <ti/sysbios/knl/Semaphore.h>
extern const ti_sysbios_knl_Semaphore_Handle rte_Binary_Semaphore_Distance_elapsed_handle;

#include <ti/sysbios/knl/Semaphore.h>
extern const ti_sysbios_knl_Semaphore_Handle rte_Binary_Semaphore_Actual_Car_direction_handle;

#include <ti/sysbios/knl/Semaphore.h>
extern const ti_sysbios_knl_Semaphore_Handle rte_Binary_Semaphore_Actual_Car_speed_handle;

#include <ti/sysbios/knl/Clock.h>
extern const ti_sysbios_knl_Clock_Handle clock2;

#include <ti/sysbios/knl/Task.h>
extern const ti_sysbios_knl_Task_Handle task4;

#include <ti/sysbios/knl/Task.h>
extern const ti_sysbios_knl_Task_Handle task5;

#include <ti/sysbios/knl/Clock.h>
extern const ti_sysbios_knl_Clock_Handle clock3;

#include <ti/sysbios/knl/Semaphore.h>
extern const ti_sysbios_knl_Semaphore_Handle Com_Binary_Semaphore_Timeout_Frame1_Temp_Handle;

#include <ti/sysbios/hal/Hwi.h>
extern const ti_sysbios_hal_Hwi_Handle QEI0_Handler;

#include <ti/sysbios/hal/Hwi.h>
extern const ti_sysbios_hal_Hwi_Handle QEI1_Handler;

extern int xdc_runtime_Startup__EXECFXN__C;

extern int xdc_runtime_Startup__RESETFXN__C;

