/*
 * Motor_control_new.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: Sahar Elnagar
 */

#ifndef CARIF_MOTOR_MOTOR_CONTROL_NEW_H_
#define CARIF_MOTOR_MOTOR_CONTROL_NEW_H_


#include "../../DriverIncludes.h"
#include "../../ECU_CONFIGURATION.h"
#include "../CarIF_Datatypes.h"

void Motors_Control(uint16_t duty, g_Car_Direction CarDir);
void Motors_control_init(void);

#endif /* CARIF_MOTOR_MOTOR_CONTROL_NEW_H_ */
