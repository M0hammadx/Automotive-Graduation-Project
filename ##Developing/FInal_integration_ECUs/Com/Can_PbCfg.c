#include "Can_PbCfg.h"
	
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

CanHwFilter filter =
{
     .CanHwFilterCode = 0x08,
     .CanHwFilterMask = 0x7FF
};

CanHwFilter filter2 =
{
     .CanHwFilterCode = 0x03,
     .CanHwFilterMask = 0x7FF
};


CanHwFilter filter3=
{
     .CanHwFilterCode = 0x02,
     .CanHwFilterMask = 0x7FF
};

CanHardwareObject arrHOH[] = {
                              {
                                   .CanControllerRef = &canobj[0],
                                   .CanHandleType= FULL ,
                                   .CanIdType = STANDARD,
                                   .CanObjectId = 1 ,
                                   .CanObjectType = TRANSMIT,
                                   .CanHwFilterptr = &filter ,
                                   .CanTriggerTransmitEnable = TRUE
                              },
                              {
                                   .CanControllerRef = &canobj[0],
                                   .CanHandleType= FULL ,
                                   .CanIdType = STANDARD,
                                   .CanObjectId = 18 ,
                                   .CanObjectType = RECEIVE,
                                   .CanHwFilterptr = &filter2
                              },
                              {
                                 .CanControllerRef = &canobj[0],
                                 .CanHandleType= FULL ,
                                 .CanIdType = STANDARD,
                                 .CanObjectId = 17 ,
                                 .CanObjectType = RECEIVE,
                                 .CanHwFilterptr = &filter3
                              }
};

Can_ConfigType Confiobj =
{
     .canControllers = canobj,
     .HOH = arrHOH
};
