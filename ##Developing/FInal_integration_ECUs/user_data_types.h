








#ifndef USERDATATYPES_H_
#define USERDATATYPES_H_

#include "ECU_CONFIGURATION.h"
typedef struct CarInfo{
#ifdef  ECU3_ACTUATORNODE
	uint8_t Steering_Angle;
#endif
#ifdef ECU1_SENSORYNODE
	uint16_t Car_Speed;
	uint16_t Motor_R_RPM;
	uint16_t Motor_L_RPM;
	double Distance_Elapsed;
	int32_t x_angle;
	int32_t y_angle;	
#endif

	uint32_t Device_Temprature;
}g_CarInfo_t;



#endif
