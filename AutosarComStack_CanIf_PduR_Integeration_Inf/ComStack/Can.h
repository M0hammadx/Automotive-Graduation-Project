#ifndef CAN_H_INCLUDED
#define CAN_H_INCLUDED

#include "Can_GeneralTypes.h"
#include "ComStack_Types.h"

#define     CAN_INF_HARDWARE_OBJECT_REF_0 &CanHardwareObjectConfig_Controller_A[0]
#define     CAN_INF_HARDWARE_OBJECT_REF_1 &CanHardwareObjectConfig_Controller_A[1]

extern const CanHardwareObjectType CanHardwareObjectConfig_Controller_A[];

Std_ReturnType Can_SetControllerMode( uint8 Controller, Can_ControllerStateType Transition);
Std_ReturnType Can_GetControllerErrorState( uint8 ControllerId, Can_ErrorStateType* ErrorStatePtr );
Std_ReturnType Can_GetControllerMode( uint8 Controller, Can_ControllerStateType* ControllerModePtr );
Std_ReturnType Can_SetBaudrate( uint8 Controller, uint16 BaudRateConfigID );
Std_ReturnType Can_Write( Can_HwHandleType Hth, const Can_PduType* PduInfo );
Std_ReturnType Can_SetIcomConfiguration( uint8 Controller, IcomConfigIdType ConfigurationId );

#endif // CAN_H_INCLUDED
