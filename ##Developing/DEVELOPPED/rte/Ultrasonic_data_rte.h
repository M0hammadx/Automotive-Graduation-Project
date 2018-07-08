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
#ifdef ECU1_SENSORYNODE
void Rte_Ultrasonic_data_iwrite(uint8_t* data);
uint8_t Rte_Ultrasonic_data_iread(uint8_t* data);  //this return for error checking only no wait sema
#endif
#ifdef ECU2_ALGORITHMICNODE
void Rte_Ultrasonic_data_iwrite(uint8_t* data);
uint8_t Rte_Ultrasonic_data_iread(uint8_t* data);  //this return for error checking only no wait sema
#endif
//#ifdef ECU3_ACTUATORNODE
//void Rte_Ultrasonic_data_iwrite(uint8_t* data);
//uint8_t Rte_Ultrasonic_data_iread(uint8_t* data);  //this return for error checking only no wait sema
//#endif

#endif /* RTE_ULTRASONIC_DATA_RTE_H_ */
