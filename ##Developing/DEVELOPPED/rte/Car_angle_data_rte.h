/*
 * Motor_speed_data_rte.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: Sahar Elnagar
 */

#ifndef RTE_CAR_ANGLE_DATA_RTE_H_
#define RTE_CAR_ANGLE_DATA_RTE_H_
#include <stdint.h>
#include "rtetypes.h"
#ifdef ECU1_SENSORYNODE
void Rte_Car_angle_data_iwrite(uint16_t data);

uint8_t Rte_Car_angle_data_iread(uint16_t* myCarAngle);

#endif

#ifdef ECU2_ALGORITHMICNODE
void Rte_Car_angle_data_iwrite(uint16_t data);//com rx indication //no block
void Rte_Car_angle_data_iread(uint16_t* myCarAngle);//swc call  block

#endif

#ifdef ECU3_ACTUATORNODE

void Rte_Car_angle_data_iwrite(uint16_t data);


void Rte_Car_angle_data_iread(uint16_t* myCarAngle);
#endif


#endif /* RTE_COMPASS_DATA_RTE_H_ */
