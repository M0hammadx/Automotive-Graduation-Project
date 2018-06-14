/**
 * main.c
 */
//#define PART_TM4C123GH6PM
#define TARGET_IS_BLIZZARD_RB0
#include <stdint.h>
#include "ultrasonic.h"
extern int flag_1;
uint32_t Dis[4];

int main(void)
{

    Ultrasonic_init();

    while (1)
    {

        distance_in_cm(Dis);
        while(flag_1 &0x0F != 0x0F);
        //delay_mSec(1000);
    }

}
