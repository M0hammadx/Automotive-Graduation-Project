#include "Can_PbCfg.h"
#include "ECU_CONFIGURATION.h"

CanControllerBaudRateConfig baudobj =
{
     .CanControllerBaudRate = 100,
     .CanControllerBaudRateConfigID =0,
     .CanControllerPropSeg = 1,
     .CanControllerSeg1 =4,
     .CanControllerSeg2 = 3,
     .CanControllerSyncJumpWidth = 1
} ;

CanController canobj[] =
{
 {
     .CanControllerBaseAddress = 0x40040000,
     .CanControllerId = 0,
     .CanControllerBaudRateConfigobj = &baudobj
 }
};

#ifdef ECU1_SENSORYNODE
//Encoder_Data
CanHwFilter T_filter1 =
{
     .CanHwFilterCode = 0x0B,
     .CanHwFilterMask = 0x7FF
};
//Ultra_Data1
CanHwFilter T_filter2 =
{
     .CanHwFilterCode = 0x0D,
     .CanHwFilterMask = 0x7FF
};
//Comp_Data
CanHwFilter T_filter5 =
{
     .CanHwFilterCode = 0x0F,
     .CanHwFilterMask = 0x7FF
};
//Car_Task
CanHwFilter R_filter3=
{
     .CanHwFilterCode = 0x0A,
     .CanHwFilterMask = 0x7FF
};
//Ultra_REQ
CanHwFilter R_filter4=
{
     .CanHwFilterCode = 0x0C,
     .CanHwFilterMask = 0x7FF
};

CanHardwareObject arrHOH[] = {
                              {//0
                                   .CanControllerRef = &canobj[0],
                                   .CanHandleType= FULL ,
                                   .CanIdType = STANDARD,
                                   .CanObjectId = 1 ,
                                   .CanObjectType = TRANSMIT,
                                   .CanHwFilterptr = &T_filter1 ,
                                   .CanTriggerTransmitEnable = TRUE
                              },
                              {//1
                                   .CanControllerRef = &canobj[0],
                                   .CanHandleType= FULL ,
                                   .CanIdType = STANDARD,
                                   .CanObjectId = 2 ,
                                   .CanObjectType = TRANSMIT,
                                   .CanHwFilterptr = &T_filter2 ,
                                   .CanTriggerTransmitEnable = TRUE
                              },
                              {//2
                                   .CanControllerRef = &canobj[0],
                                   .CanHandleType= FULL ,
                                   .CanIdType = STANDARD,
                                   .CanObjectId = 3 ,
                                   .CanObjectType = TRANSMIT,
                                   .CanHwFilterptr = &T_filter5 ,
                                   .CanTriggerTransmitEnable = TRUE
                              },
                              {//3
                                   .CanControllerRef = &canobj[0],
                                   .CanHandleType= FULL ,
                                   .CanIdType = STANDARD,
                                   .CanObjectId = 17 ,
                                   .CanObjectType = RECEIVE,
                                   .CanHwFilterptr = &R_filter3
                              },
                              {//4
                                 .CanControllerRef = &canobj[0],
                                 .CanHandleType= FULL ,
                                 .CanIdType = STANDARD,
                                 .CanObjectId = 18 ,
                                 .CanObjectType = RECEIVE,
                                 .CanHwFilterptr = &R_filter4
                              }
};
#endif

#ifdef ECU2_ALGORITHMICNODE
//Car_Task
CanHwFilter T_filter1 =
{
     .CanHwFilterCode = 0x0A,
     .CanHwFilterMask = 0x7FF
};
//Ultra_REQ
CanHwFilter T_filter2 =
{
     .CanHwFilterCode = 0x0C,
     .CanHwFilterMask = 0x7FF
};
//Ultra_Data1
CanHwFilter R_filter3=
{
     .CanHwFilterCode = 0x0D,
     .CanHwFilterMask = 0x7FF
};
//Encoder_Data
CanHwFilter R_filter4=
{
     .CanHwFilterCode = 0x0B,
     .CanHwFilterMask = 0x7FF
};
//Comp_Data
CanHwFilter R_filter5=
{
     .CanHwFilterCode = 15,
     .CanHwFilterMask = 0x7FF
};

CanHardwareObject arrHOH[] = {
                              {//0
                                   .CanControllerRef = &canobj[0],
                                   .CanHandleType= FULL ,
                                   .CanIdType = STANDARD,
                                   .CanObjectId = 1 ,
                                   .CanObjectType = TRANSMIT,
                                   .CanHwFilterptr = &T_filter1 ,
                                   .CanTriggerTransmitEnable = TRUE
                              },
                              {//1
                                   .CanControllerRef = &canobj[0],
                                   .CanHandleType= FULL ,
                                   .CanIdType = STANDARD,
                                   .CanObjectId = 2 ,
                                   .CanObjectType = TRANSMIT,
                                   .CanHwFilterptr = &T_filter2 ,
                                   .CanTriggerTransmitEnable = TRUE
                              },
                              {//2
                                   .CanControllerRef = &canobj[0],
                                   .CanHandleType= FULL ,
                                   .CanIdType = STANDARD,
                                   .CanObjectId = 17 ,
                                   .CanObjectType = RECEIVE,
                                   .CanHwFilterptr = &R_filter3
                              },
                              {//3
                                 .CanControllerRef = &canobj[0],
                                 .CanHandleType= FULL ,
                                 .CanIdType = STANDARD,
                                 .CanObjectId = 18 ,
                                 .CanObjectType = RECEIVE,
                                 .CanHwFilterptr = &R_filter4
                              },
                              {//4
                                 .CanControllerRef = &canobj[0],
                                 .CanHandleType= FULL ,
                                 .CanIdType = STANDARD,
                                 .CanObjectId = 19 ,
                                 .CanObjectType = RECEIVE,
                                 .CanHwFilterptr = &R_filter5
                              }
};
#endif

#ifdef ECU3_ACTUATORNODE
//Steer_Encoder
CanHwFilter T_filter1 =
{
     .CanHwFilterCode = 0x0E,
     .CanHwFilterMask = 0x7FF
};
//Car_Task
CanHwFilter R_filter2 =
{
     .CanHwFilterCode = 0x0A,
     .CanHwFilterMask = 0x7FF
};
//Encoder_Data
CanHwFilter R_filter3=
{
     .CanHwFilterCode = 0x0B,
     .CanHwFilterMask = 0x7FF
};
//Comp_Data
CanHwFilter R_filter4=
{
     .CanHwFilterCode = 15,
     .CanHwFilterMask = 0x7FF
};

CanHardwareObject arrHOH[] = {
                              {//0
                                   .CanControllerRef = &canobj[0],
                                   .CanHandleType= FULL ,
                                   .CanIdType = STANDARD,
                                   .CanObjectId = 1 ,
                                   .CanObjectType = TRANSMIT,
                                   .CanHwFilterptr = &T_filter1 ,
                                   .CanTriggerTransmitEnable = TRUE
                              },
                              {//1
                                   .CanControllerRef = &canobj[0],
                                   .CanHandleType= FULL ,
                                   .CanIdType = STANDARD,
                                   .CanObjectId = 17 ,
                                   .CanObjectType = RECEIVE,
                                   .CanHwFilterptr = &R_filter2
                              },
                              {//2
                                 .CanControllerRef = &canobj[0],
                                 .CanHandleType= FULL ,
                                 .CanIdType = STANDARD,
                                 .CanObjectId = 18 ,
                                 .CanObjectType = RECEIVE,
                                 .CanHwFilterptr = &R_filter3
                              },
                              {//3
                                 .CanControllerRef = &canobj[0],
                                 .CanHandleType= FULL ,
                                 .CanIdType = STANDARD,
                                 .CanObjectId = 19 ,
                                 .CanObjectType = RECEIVE,
                                 .CanHwFilterptr = &R_filter4
                              }
};

#endif  //ECU3_ACTUATORNODE

Can_ConfigType Confiobj =
{
     .canControllers = canobj,
     .HOH = arrHOH
};
