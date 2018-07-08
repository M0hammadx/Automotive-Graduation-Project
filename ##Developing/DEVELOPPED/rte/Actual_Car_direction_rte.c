/*
 * Actual_Car_direction.c
 *
 *  Created on: Jun 29, 2018
 *      Author: Mohab
 */

#include <rte/Actual_Car_direction_rte.h>
static uint8_t rte_Actual_Car_direction = 0;
extern Semaphore_Handle rte_Binary_Semaphore_Actual_Car_direction_handle;
#ifdef ECU1_SENSORYNODE

void Rte_Actual_Car_direction_iwrite(uint8_t data)
{ //swc call
    rte_Actual_Car_direction = data;
    Semaphore_post(rte_Binary_Semaphore_Actual_Car_direction_handle);
}

uint8_t Rte_Actual_Car_direction_iread(uint8_t* data)
{ // com main call
    uint8_t SemaValue = 0;
    SemaValue = Semaphore_pend(rte_Binary_Semaphore_Actual_Car_direction_handle,
                                   BIOS_NO_WAIT);
    if (SemaValue == 0)
    {
    }
    else
    {
        *data = rte_Actual_Car_direction;
    }
    return SemaValue;

}

#endif

#ifdef ECU2_ALGORITHMICNODE
void Rte_Actual_Car_direction_iwrite(uint8_t data) //com rx indication
{
    rte_Actual_Car_direction = data;
    Semaphore_post(rte_Binary_Semaphore_Actual_Car_direction_handle);
}

void Rte_Actual_Car_direction_iread(uint8_t* data) //swc call
{
    Semaphore_pend(rte_Binary_Semaphore_Actual_Car_direction_handle,
            BIOS_WAIT_FOREVER);
    Hwi_disableInterrupt(55);
    *data = rte_Actual_Car_direction;
    Hwi_enableInterrupt(55);
}
#endif

#ifdef ECU3_ACTUATORNODE
void Rte_Actual_Car_direction_iwrite(uint8_t data) //com rx indication
{
    rte_Actual_Car_direction = data;
    Semaphore_post(rte_Binary_Semaphore_Actual_Car_direction_handle);
}

void Rte_Actual_Car_direction_iread(uint8_t* data) //swc call
{
    Semaphore_pend(rte_Binary_Semaphore_Actual_Car_direction_handle,
            BIOS_WAIT_FOREVER);
    Hwi_disableInterrupt(55);
    *data = rte_Actual_Car_direction;
    Hwi_enableInterrupt(55);
}
#endif

