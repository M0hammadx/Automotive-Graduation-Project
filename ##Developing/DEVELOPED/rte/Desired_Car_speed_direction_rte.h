/*
 * Desired_Car_speed.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: Sahar Elnagar
 */

#ifndef RTE_DESIRED_CAR_SPEED_DIRECTION_RTE_H_
#define RTE_DESIRED_CAR_SPEED_DIRECTION_RTE_H_

#include "rtetypes.h"


#ifdef ECU2_ALGORITHMICNODE

void Rte_Desired_Car_speed_groupSignal_iwrite(uint16_t data);    //swc
uint8_t Rte_Desired_Car_speed_groupSignal_iread(uint16_t* data);

void Rte_Desired_Car_Direction_signalGroup_iwrite(uint8_t data);
uint8_t Rte_Desired_Car_Direction_signalGroup_iread(uint8_t* data);  //com main

#endif

#ifdef ECU3_ACTUATORNODE

void Rte_Desired_Car_speed_iwrite(uint16_t data);
void Rte_Desired_Car_Direction_iwrite(uint8_t data);

void Rte_Desired_Car_speed_iread(uint16_t* data);
void Rte_Desired_Car_Direction_iread(uint8_t* data);   //swc

#endif

#endif /* RTE_DESIRED_CAR_SPEED_DIRECTION_RTE_H_ */
