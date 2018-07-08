/*
 * Tempreature.h
 *
 *  Created on: Jun 13, 2018
 *      Author: Mohab
 */

#ifndef CARIF_TEMPREATURE_TEMPREATURE_H_
#define CARIF_TEMPREATURE_TEMPREATURE_H_

#include "../../DriverIncludes.h"
#include "../../ECU_CONFIGURATION.h"


void TempreatureSensor_Init(void);
void Temprature_Get_Temp(uint8_t* CarTemp);
#endif /* CARIF_TEMPREATURE_TEMPREATURE_H_ */
