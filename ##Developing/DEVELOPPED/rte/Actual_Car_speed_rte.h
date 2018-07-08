/*
 * Actual_Car_speed_rte.h
 *
 *  Created on: Jun 29, 2018
 *      Author: Mohab
 */

#ifndef RTE_ACTUAL_CAR_SPEED_RTE_H_
#define RTE_ACTUAL_CAR_SPEED_RTE_H_

#include "../ECU_CONFIGURATION.h"
#include "rtetypes.h"

#ifdef ECU1_SENSORYNODE

void Rte_Actual_Car_speed_iwrite(uint16_t data);
uint8_t Rte_Actual_Car_speed_iread(uint16_t* data);

#endif

#ifdef ECU2_ALGORITHMICNODE
void Rte_Actual_Car_speed_iwrite(uint16_t data);
void Rte_Actual_Car_speed_iread(uint16_t* data);
#endif

#ifdef ECU3_ACTUATORNODE
void Rte_Actual_Car_speed_iwrite(uint16_t data);
void Rte_Actual_Car_speed_iread(uint16_t* data);
#endif
#endif /* RTE_ACTUAL_CAR_SPEED_RTE_H_ */
