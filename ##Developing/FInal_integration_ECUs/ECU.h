/*
 * ECU.h
 *
 *  Created on: Jun 12, 2018
 *      Author: Mohab
 */

#ifndef ECU_H_
#define ECU_H_

#include "ECU_CONFIGURATION.h"

typedef enum
{
    GOOD, INITALIZATION_TOTAL_FAIL

} g_ErrorType;

g_ErrorType ECU_Init(void);
void ECU2_Begin_SWC1(void);
void ECU_Begin(void);
#endif /* ECU_H_ */
