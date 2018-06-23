








#ifndef USERDATATYPES_H_
#define USERDATATYPES_H_

#include "ECU_CONFIGURATION.h"
//#include
typedef struct CarInfo{
#ifdef  ECU3_ACTUATORNODE
	uint8_t Steering_Angle;
#endif
#ifdef ECU1_SENSORYNODE
	uint16_t myCar_Speed;
	uint16_t Motor_R_RPM;
	uint16_t Motor_L_RPM;
	double Distance_Elapsed;
	double myCar_Angle;
#endif

#ifdef ECU2_ALGORITHMICNODE

#endif
	uint32_t Device_Temprature;
}g_CarInfo_t;



#endif
