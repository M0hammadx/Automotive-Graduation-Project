/*
 * ECU.h
 *
 *  Created on: Jun 12, 2018
 *      Author: Mohab
 */

#ifndef ECU_H_
#define ECU_H_
#include "ECU_CONFIGURATION.h"

typedef enum
{
    GOOD, INITALIZATION_TOTAL_FAIL

} g_ErrorType;



g_ErrorType ECU_Init(void);



#ifdef ECU1_SENSORYNODE
void ECU1_Begin_Ultrasonic_SWC1(void);
void ECU1_Begin_Compass_SWC2(void);
void ECU1_Begin_ActualSpeedDirection_SWC3(void);
//void ECU1_DistanceElapsed_SWI1(void);

#endif
#ifdef ECU2_ALGORITHMICNODE
void ECU2_Begin_Ultrasonic_SWC1(void);
#endif
#ifdef ECU3_ACTUATORNODE
void ECU3_Begin_Motor_SWC1(void);
void ECU3_Begin_Compass_SWC2(void);
void ECU3_Begin_SteeringAngle_SWC3(void);
void ECU3_Begin_ActualData_SWC4(void);
#endif


#endif /* ECU_H_ */
