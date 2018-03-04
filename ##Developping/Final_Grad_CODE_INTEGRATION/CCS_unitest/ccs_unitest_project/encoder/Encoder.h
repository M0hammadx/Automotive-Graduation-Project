/*
 * Encoder.h
 *
 *  Created on: Mar 3, 2018
 *      Author: Mohab
 */

#ifndef ENCODER_ENCODER_H_
#define ENCODER_ENCODER_H_
#define QEI1_CPR        16
#define QEI0_CPR        16
#include "../DriverIncludes.h"

void Encoders_Init(void);
void Encoders_Enable(void);
void Encoders_Disable(void);
//Get functions here must be implemented
#endif /* ENCODER_ENCODER_H_ */
