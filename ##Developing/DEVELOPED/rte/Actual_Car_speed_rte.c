/*
 * Actual_Car_speed_rte.c
 *
 *  Created on: Jun 29, 2018
 *      Author: Mohab
 */

#include "Actual_Car_speed_rte.h"

static uint16_t rte_Actual_speed = 0;
extern Semaphore_Handle rte_Binary_Semaphore_Actual_Car_speed_handle;

#ifdef ECU1_SENSORYNODE

void Rte_Actual_Car_speed_iwrite(uint16_t data)  //swc call
{
    rte_Actual_speed = data;
    Semaphore_post(rte_Binary_Semaphore_Actual_Car_speed_handle);

}

uint8_t Rte_Actual_Car_speed_iread(uint16_t* data) // com main call
{
    uint8_t SemaValue = 0;
    SemaValue = Semaphore_pend(rte_Binary_Semaphore_Actual_Car_speed_handle,
                               BIOS_NO_WAIT);
    if (SemaValue == 0)
    {
    }
    else
    {
        *data = rte_Actual_speed;
    }
    return SemaValue;
}

#endif

#ifdef ECU2_ALGORITHMICNODE

void Rte_Actual_Car_speed_iwrite(uint16_t data) //com rx indication
{
    rte_Actual_speed = data;
    Semaphore_post(rte_Binary_Semaphore_Actual_Car_speed_handle);
}

void Rte_Actual_Car_speed_iread(uint16_t* data) //swc call
{
    Semaphore_pend(rte_Binary_Semaphore_Actual_Car_speed_handle,
            BIOS_WAIT_FOREVER);
    Hwi_disableInterrupt(55);
    *data = rte_Actual_speed;
    Hwi_enableInterrupt(55);
}
#endif

#ifdef ECU3_ACTUATORNODE

void Rte_Actual_Car_speed_iwrite(uint16_t data) //com rx indication
{
    rte_Actual_speed = data;
    Semaphore_post(rte_Binary_Semaphore_Actual_Car_speed_handle);
}

void Rte_Actual_Car_speed_iread(uint16_t* data) //swc call
{
    Semaphore_pend(rte_Binary_Semaphore_Actual_Car_speed_handle,
            BIOS_WAIT_FOREVER);
    Hwi_disableInterrupt(55);
    *data = rte_Actual_speed;
    Hwi_enableInterrupt(55);
}

#endif

