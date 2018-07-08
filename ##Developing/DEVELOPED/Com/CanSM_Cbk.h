#ifndef CANSM_CBK_H_INCLUDED
#define CANSM_CBK_H_INCLUDED

#include "ComStack_Types.h"     ///INF
#include "Can_GeneralTypes.h"   ///INF

void CanSM_ControllerBusOff( uint8 ControllerId );
void CanSM_ConfirmPnAvailability( uint8 TransceiverId );
void CanSM_ClearTrcvWufFlagIndication( uint8 Transceiver );
void CanSM_CheckTransceiverWakeFlagIndication( uint8 Transceiver );
void CanSM_ControllerModeIndication( uint8 ControllerId, Can_ControllerStateType ControllerMode );
void CanSM_TransceiverModeIndication( uint8 TransceiverId, CanTrcv_TrcvModeType TransceiverMode );
void CanSM_CurrentIcomConfiguration( uint8 ControllerId, IcomConfigIdType ConfigurationId, IcomSwitch_ErrorType Error );

#endif // CANSM_CBK_H_INCLUDED
