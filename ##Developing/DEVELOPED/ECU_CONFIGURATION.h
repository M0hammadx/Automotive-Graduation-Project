/*
 * ECU_CONFIGURATION.h
 *
 *  Created on: Jun 12, 2018
 *      Author: Mohab
 */

#ifndef ECU_CONFIGURATION_H_
#define ECU_CONFIGURATION_H_
#define SYSTEM_CLOCK_80_MHZ
//uncomment the target ECU in order to perform the right initialization
//#define ECU1_SENSORYNODE
//#define ECU2_ALGORITHMICNODE
#define ECU3_ACTUATORNODE

//#define CAR_SPEED_IN_Km_PER_HR
#define CAR_SPEED_IN_METER_PER_HR

//Ultrasonic
//#define ULTRASONIC_4TIMER
#define ULTRASONIC_8TIMER

#define Motor_without_PID
//#define Motor_with_PID
#endif /* ECU_CONFIGURATION_H_ */
