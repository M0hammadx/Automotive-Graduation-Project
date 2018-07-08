/*
 * Compass_data_rte.c
 *
 n *  Created on: ??þ/??þ/????
 *      Author: Sahar Elnagar
 */
#include"Car_angle_data_rte.h"

uint16_t rte_Car_angle = 0;
extern Semaphore_Handle rte_Binary_Semaphore_Car_angle_Data_handle;
#ifdef ECU1_SENSORYNODE
void Rte_Car_angle_data_iwrite(uint16_t data) //swc call
{

    rte_Car_angle = data;
    Semaphore_post(rte_Binary_Semaphore_Car_angle_Data_handle);
//post
}

uint8_t Rte_Car_angle_data_iread(uint16_t* myCarAngle) //com main call
{
//pend
    uint8_t SemaValue = 0;
    SemaValue = Semaphore_pend(rte_Binary_Semaphore_Car_angle_Data_handle,
    BIOS_NO_WAIT);
    if (SemaValue == 0)
    {
    }
    else
    {
        *myCarAngle = rte_Car_angle;
    }
    return SemaValue;

}

#endif

#ifdef ECU2_ALGORITHMICNODE
void Rte_Car_angle_data_iwrite(uint16_t data) //com rx indication //no block
{

    rte_Car_angle = data;
    Semaphore_post(rte_Binary_Semaphore_Car_angle_Data_handle);
//post
}

void Rte_Car_angle_data_iread(uint16_t* myCarAngle) //swc call  block
{
//pend
    Semaphore_pend(rte_Binary_Semaphore_Car_angle_Data_handle,
            BIOS_WAIT_FOREVER);
    Hwi_disableInterrupt(55);
    *myCarAngle = rte_Car_angle;
    Hwi_enableInterrupt(55);

}
#endif

#ifdef ECU3_ACTUATORNODE
void Rte_Car_angle_data_iwrite(uint16_t data) //com rx indication //no block
{

    rte_Car_angle = data;
    Semaphore_post(rte_Binary_Semaphore_Car_angle_Data_handle);
//post
}

void Rte_Car_angle_data_iread(uint16_t* myCarAngle) //swc call  block
{
//pend
    Semaphore_pend(rte_Binary_Semaphore_Car_angle_Data_handle,
            BIOS_WAIT_FOREVER);
    Hwi_disableInterrupt(55);
    *myCarAngle= rte_Car_angle;
    Hwi_enableInterrupt(55);

}

#endif

