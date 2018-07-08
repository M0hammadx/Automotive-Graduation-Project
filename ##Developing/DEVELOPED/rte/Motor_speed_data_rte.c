/*
 * Motor_speed_data.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Sahar Elnagar
 */

#include "Motor_speed_data_rte.h"

static uint8_t motor_speed[2];

extern Semaphore_Handle rte_Binary_Semaphore_Motor_speed_Data_handle;
extern Semaphore_Handle rte_Mutex_Motor_speed_Data_handle;
#ifdef ECU1_SENSORYNODE
void Rte_Motor_speed_data_iwrite(uint8_t* data) //swc call
{

    Semaphore_pend(rte_Mutex_Motor_speed_Data_handle, BIOS_WAIT_FOREVER);
    for (uint8_t i = 0; i < 2; i++)
    {
        motor_speed[i] = data[i];
    }
    Semaphore_post(rte_Mutex_Motor_speed_Data_handle);
    Semaphore_post(rte_Binary_Semaphore_Motor_speed_Data_handle);

    //post
}

uint8_t Rte_Motor_speed_data_iread(uint8_t* data) //Com Call
{
//pend
    uint8_t SemaValue = Semaphore_pend(
            rte_Binary_Semaphore_Motor_speed_Data_handle, BIOS_NO_WAIT);
    if (SemaValue == 0)
    {

    }
    else
    {
        Semaphore_pend(rte_Mutex_Motor_speed_Data_handle, BIOS_WAIT_FOREVER);
        for (uint8_t i = 0; i < 2; i++)
        {
            data[i] = motor_speed[i];
        }
        Semaphore_post(rte_Mutex_Motor_speed_Data_handle);
    }

    return SemaValue;
}

#endif
#ifdef ECU2_ALGORITHMICNODE

void Rte_Motor_speed_data_iwrite(uint8_t* data) //com Rx_indication call
{

    for (uint8_t i = 0; i < 2; i++)
    {
        motor_speed[i] = data[i];
    }
    Semaphore_post(rte_Binary_Semaphore_Motor_speed_Data_handle);
    //post
}

void Rte_Motor_speed_data_iread(uint8_t* data) //swc call
{

//pend
    Semaphore_pend(rte_Binary_Semaphore_Motor_speed_Data_handle,
            BIOS_WAIT_FOREVER);
    Hwi_disableInterrupt(55);
    for (uint8_t i = 0; i < 2; i++)
    {
        data[i] = motor_speed[i];
    }
    Hwi_enableInterrupt(55);

}

#endif

#ifdef ECU3_ACTUATORNODE
void Rte_Motor_speed_data_iwrite(uint8_t* data)
{
    for (uint8_t i = 0; i < 2; i++)
    {
        motor_speed[i] = data[i];
    }
    Semaphore_post(rte_Binary_Semaphore_Motor_speed_Data_handle);
    //post
}

void Rte_Motor_speed_data_iread(uint8_t* data)
{
    Semaphore_pend(rte_Binary_Semaphore_Motor_speed_Data_handle,
            BIOS_WAIT_FOREVER);
    Hwi_disableInterrupt(55);
    for (uint8_t i = 0; i < 2; i++)
    {
        data[i] = motor_speed[i];
    }
    Hwi_enableInterrupt(55);

}

#endif
