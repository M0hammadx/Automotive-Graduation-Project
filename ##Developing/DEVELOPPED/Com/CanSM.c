#include "CanSM_Cbk.h"

void CanSM_ControllerBusOff( uint8 ControllerId ){
//    UART_OutString("\nCanSM_ControllerBusOff done and controller id is : %d", ControllerId);

}

void CanSM_ConfirmPnAvailability( uint8 TransceiverId )
{
    //UART_OutString("\nCanSM_ConfirmPnAvailability done and TransceiverId is : %d", TransceiverId);
}

void CanSM_ClearTrcvWufFlagIndication( uint8 Transceiver )
{
    //UART_OutString("\nCanSM_ClearTrcvWufFlagIndication done and Transceiver is : %d", Transceiver);

}
void CanSM_CheckTransceiverWakeFlagIndication( uint8 Transceiver )
{
//    UART_OutString("\nCanSM_CheckTransceiverWakeFlagIndication done and Transceiver is : ");
//    UART_OutUDec(Transceiver);
}

void CanSM_ControllerModeIndication( uint8 ControllerId, Can_ControllerStateType ControllerMode )
{
    //UART_OutString("\nCanSM_ControllerModeIndication done ");
}

void CanSM_TransceiverModeIndication( uint8 TransceiverId, CanTrcv_TrcvModeType TransceiverMode )
{
    //UART_OutString("\nCanSM_TransceiverModeIndication done ");
}

void CanSM_CurrentIcomConfiguration( uint8 ControllerId, IcomConfigIdType ConfigurationId, IcomSwitch_ErrorType Error )
{
    //UART_OutString("\nCanSM_CurrentIcomConfiguration done ");
}
