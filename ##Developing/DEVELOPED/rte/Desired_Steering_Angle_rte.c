/*
 * Desired_Steering_Angle_rte.c
 *
 *  Created on: Jun 29, 2018
 *      Author: MHmed Hatem
 */

#include "Desired_Steering_Angle_rte.h"

#ifdef ECU2_ALGORITHMICNODE
extern Semaphore_Handle rte_Binary_Semaphore_Desired_Steering_Angle_handle;

static uint8_t Desired_Steering_Angle =0;

void Rte_Desired_Steering_Angle_iwrite(uint8_t angle) //swc call
{
    Desired_Steering_Angle = angle;
    Semaphore_post(rte_Binary_Semaphore_Desired_Steering_Angle_handle);
}
uint8_t Rte_Desired_Steering_Angle_iread(uint8_t* angle) //com main
{
    uint8_t SemaValue= Semaphore_pend(rte_Binary_Semaphore_Desired_Steering_Angle_handle,BIOS_NO_WAIT);
    if(SemaValue==0)
    {

    }
    else
    {
        *angle= Desired_Steering_Angle;
    }
    return SemaValue;

}

#endif


#ifdef ECU3_ACTUATORNODE
extern Semaphore_Handle rte_Binary_Semaphore_Desired_Steering_Angle_handle;
static uint8_t Desired_Car_Direction = 0;

void Rte_Desired_Steering_Angle_iwrite(uint8_t angle)//com rx indication call
{
    Desired_Car_Direction = angle;
    Semaphore_post(rte_Binary_Semaphore_Desired_Steering_Angle_handle);
}
void Rte_Desired_Steering_Angle_iread(uint8_t* angle)//swc call
{
    Semaphore_pend(rte_Binary_Semaphore_Desired_Steering_Angle_handle,
                                           BIOS_WAIT_FOREVER);
    Hwi_disableInterrupt(55);
    *angle = Desired_Car_Direction;
    Hwi_enableInterrupt(55);
}

#endif
