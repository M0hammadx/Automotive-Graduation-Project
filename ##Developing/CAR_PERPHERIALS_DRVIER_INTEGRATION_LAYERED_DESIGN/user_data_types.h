








#ifndef USERDATATYPES_H_
#define USERDATATYPES_H_


typedef struct CarInfo{

	uint8_t Steering_Angle;
	uint8_t Device_Temprature;
	uint16_t Car_Speed;
	uint16_t Motor_R_RPM;
	uint16_t Motor_L_RPM;
	double Distance_Elapsed;
	int32_t x_angle;
	int32_t y_angle;	
		
}g_CarInfo_t;



#endif
