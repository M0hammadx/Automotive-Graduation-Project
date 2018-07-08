/*
 * Actual_Car_direction.h
 *
 *  Created on: Jun 29, 2018
 *      Author: Mohab
 */

#ifndef RTE_ACTUAL_CAR_DIRECTION_RTE_H_
#define RTE_ACTUAL_CAR_DIRECTION_RTE_H_
#include "rtetypes.h"
#include "../ECU_CONFIGURATION.h"

#ifdef ECU1_SENSORYNODE
void Rte_Actual_Car_direction_iwrite(uint8_t data);
uint8_t Rte_Actual_Car_direction_iread(uint8_t* data);
#endif

#ifdef ECU2_ALGORITHMICNODE
void Rte_Actual_Car_direction_iwrite(uint8_t data);
void Rte_Actual_Car_direction_iread(uint8_t* data);
#endif

#ifdef ECU3_ACTUATORNODE
void Rte_Actual_Car_direction_iwrite(uint8_t data);
void Rte_Actual_Car_direction_iread(uint8_t* data);
#endif


#endif /* RTE_ACTUAL_CAR_DIRECTION_RTE_H_ */
