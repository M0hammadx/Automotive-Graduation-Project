/*
 * Ultrasonic_requests_rte.h
 *
 *  Created on: Jun 23, 2018
 *      Author: Mohab
 */

#ifndef RTE_ULTRASONIC_REQUESTS_RTE_H_
#define RTE_ULTRASONIC_REQUESTS_RTE_H_
#include "rtetypes.h"

#define Front_Left_Ultrasonic  0x01
#define Front_Right_Ultrasonic  0x02
#define Right_Front_Ultrasonic  0x04
#define Right_Back_Ultrasonic  0x08
#define Back_Right_Ultrasonic  0x10
#define Back_Left_Ultrasonic  0x20
#define Left_Back_Ultrasonic  0x40
#define Left_Front_Ultrasonic  0x80
#ifdef ECU1_SENSORYNODE
void Rte_Ultrasonic_requests_iwrite(uint8_t u);
void Rte_Ultrasonic_requests_iread(uint8_t *);
#endif
#ifdef ECU2_ALGORITHMICNODE
void Rte_Ultrasonic_requests_iwrite(uint8_t u);
uint8_t Rte_Ultrasonic_requests_iread(uint8_t *);
#endif
//#ifdef ECU3_ACTUATORNODE
//void Rte_Ultrasonic_requests_iwrite(uint8_t u);
//uint8_t Rte_Ultrasonic_requests_iread(uint8_t *);
//#endif
#endif /* RTE_ULTRASONIC_REQUESTS_RTE_H_ */
