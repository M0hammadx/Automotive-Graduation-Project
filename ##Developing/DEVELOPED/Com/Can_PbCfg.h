#ifndef CAN_PBCFG_H_INCLUDED
#define CAN_PBCFG_H_INCLUDED

#include "Can.h"

//integeration_00

#ifdef ECU1_SENSORYNODE

extern CanHardwareObject arrHOH[];
#define     CAN_INF_HARDWARE_OBJECT_REF_0 &arrHOH[0]    //Encoder_Data
#define     CAN_INF_HARDWARE_OBJECT_REF_1 &arrHOH[1]    //Ultra_Data1
#define     CAN_INF_HARDWARE_OBJECT_REF_2 &arrHOH[3]    //Car_Task
#define     CAN_INF_HARDWARE_OBJECT_REF_3 &arrHOH[4]    //Ultra_REQ

#define     CAN_INF_HARDWARE_OBJECT_REF_4 &arrHOH[2]    //Comp_Data


#endif

#ifdef ECU2_ALGORITHMICNODE

extern CanHardwareObject arrHOH[];
#define     CAN_INF_HARDWARE_OBJECT_REF_0 &arrHOH[0]    //Car_Task
#define     CAN_INF_HARDWARE_OBJECT_REF_1 &arrHOH[1]    //Ultra_REQ
#define     CAN_INF_HARDWARE_OBJECT_REF_2 &arrHOH[2]    //Ultra_Data1
#define     CAN_INF_HARDWARE_OBJECT_REF_3 &arrHOH[3]    //Encoder_Data
#define     CAN_INF_HARDWARE_OBJECT_REF_4 &arrHOH[4]    //Comp_Data

#endif

#ifdef ECU3_ACTUATORNODE

extern CanHardwareObject arrHOH[];
#define     CAN_INF_HARDWARE_OBJECT_REF_0 &arrHOH[0]    //Steer_Encoder
#define     CAN_INF_HARDWARE_OBJECT_REF_1 &arrHOH[1]    //Car_Task
#define     CAN_INF_HARDWARE_OBJECT_REF_2 &arrHOH[2]    //Encoder_Data
#define     CAN_INF_HARDWARE_OBJECT_REF_3 &arrHOH[3]    //Comp_Data

#endif


extern Can_ConfigType Confiobj;
//end_00

#endif // CAN_PBCFG_H_INCLUDED
