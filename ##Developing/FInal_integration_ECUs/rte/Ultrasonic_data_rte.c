
#include "Ultrasonic_data_rte.h"
static uint32_t Ultrasonic_Reading[8];

void Rte_Ultrasonic_data_iwrite(uint32_t data, uint8_t ultrasonic_index)
{

    Ultrasonic_Reading[ultrasonic_index] = data;
    //post
}

uint32_t Rte_Ultrasonic_data_iread(uint8_t ultrasonic_index)
{
//pend
    return Ultrasonic_Reading[ultrasonic_index];
}

