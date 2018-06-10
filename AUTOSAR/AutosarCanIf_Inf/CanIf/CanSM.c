#include "CanSM_Cbk.h"

void CanSM_ControllerBusOff( uint8 ControllerId ){
    printf("\nCanSM_ControllerBusOff done and controller id is : %d", ControllerId);
}

void CanSM_ConfirmPnAvailability( uint8 TransceiverId )
{
    printf("\nCanSM_ConfirmPnAvailability done and TransceiverId is : %d", TransceiverId);
}

void CanSM_ClearTrcvWufFlagIndication( uint8 Transceiver )
{
    printf("\nCanSM_ClearTrcvWufFlagIndication done and Transceiver is : %d", Transceiver);

}
void CanSM_CheckTransceiverWakeFlagIndication( uint8 Transceiver )
{
    printf("\nCanSM_CheckTransceiverWakeFlagIndication done and Transceiver is : %d", Transceiver);
}

void CanSM_ControllerModeIndication( uint8 ControllerId, Can_ControllerStateType ControllerMode )
{
    printf("\nCanSM_ControllerModeIndication done ");
}

void CanSM_TransceiverModeIndication( uint8 TransceiverId, CanTrcv_TrcvModeType TransceiverMode )
{
    printf("\nCanSM_TransceiverModeIndication done ");
}

void CanSM_CurrentIcomConfiguration( uint8 ControllerId, IcomConfigIdType ConfigurationId, IcomSwitch_ErrorType Error )
{
    printf("\nCanSM_CurrentIcomConfiguration done ");
}
