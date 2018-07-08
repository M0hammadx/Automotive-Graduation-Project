/*
 * NVICInterruptHandler.h
 *
 *  Created on: Aug 13, 2017
 *      Author: Muhammad Ali
 */


#ifndef DRIVERS_SL_NVICINTERRUPTHANDLER_H_
#define DRIVERS_SL_NVICINTERRUPTHANDLER_H_
#include "Com/HAL/sysctrl.h"
#define CAN0ID          0
#define CAN1ID          1

void installNIVCISRFunction(g_ISRVirIdx_t idx, void (*isr)(uint8));
void deInstallNIVCISRFunction(g_ISRVirIdx_t idx);
void IntVirDefaultFun(uint8);

#endif /* DRIVERS_SL_NVICINTERRUPTHANDLER_H_ */
