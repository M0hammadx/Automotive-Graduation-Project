/*
 * Distance_elapsed_rte.c
 *
 *  Created on: Jun 28, 2018
 *      Author: Mohab
 */

#include "Distance_elapsed_rte.h"
static uint16_t rte_distance_elapsed = 0;
extern Semaphore_Handle rte_Binary_Semaphore_Distance_elapsed_handle;
#ifdef ECU1_SENSORYNODE
void Rte_Distance_elapsed_iwrite(uint16_t data)
{ //swc call
    rte_distance_elapsed = data;
    Semaphore_post(rte_Binary_Semaphore_Distance_elapsed_handle);

}

uint8_t Rte_Distance_elapsed_iread(uint16_t* data)
{ //com main call
    uint8_t SemaValue = 0;
    SemaValue = Semaphore_pend(rte_Binary_Semaphore_Distance_elapsed_handle,
                               BIOS_NO_WAIT);
    if (SemaValue == 0)
    {
    }
    else
    {
        *data = rte_distance_elapsed;
    }
    return SemaValue;
}
#endif

#ifdef ECU2_ALGORITHMICNODE
void Rte_Distance_elapsed_iwrite(uint16_t data)
{ //com rx indication call
    rte_distance_elapsed = data;
    Semaphore_post(rte_Binary_Semaphore_Distance_elapsed_handle);

}

void Rte_Distance_elapsed_iread(uint16_t* data)
{ //swc call
    Semaphore_pend(rte_Binary_Semaphore_Distance_elapsed_handle,BIOS_WAIT_FOREVER);
    Hwi_disableInterrupt(55);
    *data = rte_distance_elapsed;
    Hwi_enableInterrupt(55);
}

#endif

#ifdef ECU3_ACTUATORNODE

#endif
