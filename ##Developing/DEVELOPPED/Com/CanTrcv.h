#ifndef CANTRCV_H_INCLUDED
#define CANTRCV_H_INCLUDED

#include "Can_GeneralTypes.h"
#include "ComStack_Types.h"


Std_ReturnType CanTrcv_SetOpMode( uint8 Transceiver, CanTrcv_TrcvModeType OpMode );
Std_ReturnType CanTrcv_GetOpMode( uint8 Transceiver, CanTrcv_TrcvModeType* OpMode );
Std_ReturnType CanTrcv_GetBusWuReason( uint8 Transceiver, CanTrcv_TrcvWakeupReasonType* reason );
Std_ReturnType CanTrcv_SetWakeupMode( uint8 Transceiver, CanTrcv_TrcvWakeupModeType TrcvWakeupMode );
Std_ReturnType CanTrcv_ClearTrcvWufFlag( uint8 Transceiver );
Std_ReturnType CanTrcv_CheckWakeFlag( uint8 Transceiver );

#endif // CANTRCV_H_INCLUDED
