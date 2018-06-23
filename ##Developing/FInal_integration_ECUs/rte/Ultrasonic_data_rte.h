/*
 * Ultrasonic_data_rte.h
 *
 *  Created on: Jun 23, 2018
 *      Author: Mohab
 */

#ifndef RTE_ULTRASONIC_DATA_RTE_H_
#define RTE_ULTRASONIC_DATA_RTE_H_
#include "rtetypes.h"

#define Front_Left  0
#define Front_Right  1
#define Right_Front  2
#define Right_Back  3
#define Back_Right  4
#define Back_Left  5
#define Left_Back  6
#define Left_Front  7

void Rte_Ultrasonic_data_iwrite(uint32_t data, uint8_t ultrasonic_index);

uint32_t Rte_Ultrasonic_data_iread(uint8_t ultrasonic_Index);
#endif /* RTE_ULTRASONIC_DATA_RTE_H_ */
