
#ifndef USERDATATYPES_H_
#define USERDATATYPES_H_

#include "ECU_CONFIGURATION.h"
#include "stdint.h"


typedef enum task_t{
    PERPENDICULAR_PARKING = 0, PARALLEL_PARKING, LANEFOLLOW, DIAGNOSTIC
} g_RequiredTask;

//#include
typedef struct CarInfo
{

#ifdef  ECU3_ACTUATORNODE
    uint8_t Steering_Angle;
#endif
#ifdef ECU1_SENSORYNODE
    uint16_t myCar_Speed;
    uint8_t Motor_R_RPM;
    uint8_t Motor_L_RPM;
    uint16_t Distance_Elapsed;
    uint16_t myCar_Angle;
#endif

#ifdef ECU2_ALGORITHMICNODE

#endif
    uint8_t Device_Temprature;
} g_CarInfo_t;




#endif
