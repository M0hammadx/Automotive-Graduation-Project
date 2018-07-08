/*
 * Motor_speed_data.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: Sahar Elnagar
 */

#ifndef RTE_MOTOR_SPEED_DATA_H_
#define RTE_MOTOR_SPEED_DATA_H_
#include <stdint.h>
#include "rtetypes.h"
#define Motor_right  0
#define Motor_left  1

#ifdef ECU1_SENSORYNODE
void Rte_Motor_speed_data_iwrite(uint8_t* data);
uint8_t Rte_Motor_speed_data_iread(uint8_t* data);
#endif


#ifdef ECU2_ALGORITHMICNODE
void Rte_Motor_speed_data_iwrite(uint8_t* data);
void Rte_Motor_speed_data_iread(uint8_t* data);
#endif

#ifdef ECU3_ACTUATORNODE
void Rte_Motor_speed_data_iwrite(uint8_t* data);
void Rte_Motor_speed_data_iread(uint8_t* data);
#endif
#endif /* RTE_MOTOR_SPEED_DATA_H_ */
