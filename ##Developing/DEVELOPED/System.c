/*
 * System.c
 *
 *  Created on: Jun 13, 2018
 *      Author: Mohab
 */

#include "System.h"

void System_ClockInit(void)
{

    ROM_SysCtlClockSet(
            SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ
                    | SYSCTL_OSC_MAIN); //80 MHZ

}

void EnableGlobalInterrupts(void)
{
    ROM_IntMasterEnable();

}

void DisableGlobalInterrupts(void)
{

    ROM_IntMasterDisable();
}
