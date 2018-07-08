/*
 * Distance_elapsed_rte.h
 *
 *  Created on: Jun 28, 2018
 *      Author: Mohab
 */

#ifndef RTE_DISTANCE_ELAPSED_RTE_H_
#define RTE_DISTANCE_ELAPSED_RTE_H_

#include "../ECU_CONFIGURATION.h"
#include "rtetypes.h"

#ifdef ECU1_SENSORYNODE
void Rte_Distance_elapsed_iwrite(uint16_t data); //swc call
uint8_t Rte_Distance_elapsed_iread(uint16_t* data);//com main call
#endif

#ifdef ECU2_ALGORITHMICNODE
void Rte_Distance_elapsed_iwrite(uint16_t data); //com rx indication call
void Rte_Distance_elapsed_iread(uint16_t* data); //swc call

#endif

#ifdef ECU3_ACTUATORNODE

#endif


#endif /* RTE_DISTANCE_ELAPSED_RTE_H_ */
