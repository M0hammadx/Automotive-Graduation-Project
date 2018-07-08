/*
 * Desired_Steering_Angle_rte.h
 *
 *  Created on: Jun 29, 2018
 *      Author: MHmed Hatem
 */

#ifndef RTE_DESIRED_STEERING_ANGLE_RTE_H_
#define RTE_DESIRED_STEERING_ANGLE_RTE_H_

#include "rtetypes.h"

#ifdef ECU2_ALGORITHMICNODE

void Rte_Desired_Steering_Angle_iwrite(uint8_t angle); //swc call
uint8_t Rte_Desired_Steering_Angle_iread(uint8_t* angle); //com main

#endif

#ifdef ECU3_ACTUATORNODE

void Rte_Desired_Steering_Angle_iwrite(uint8_t angle);//com rx indication call
void Rte_Desired_Steering_Angle_iread(uint8_t* angle);//swc call

#endif

#endif /* RTE_DESIRED_STEERING_ANGLE_RTE_H_ */
