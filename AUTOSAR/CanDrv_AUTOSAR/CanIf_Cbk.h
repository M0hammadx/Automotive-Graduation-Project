
#ifndef CANIF_CBK_H_
#define CANIF_CBK_H_

#include "Can_GeneralTypes.h"
#include "Com_StackTypes.h"

void CanIf_TxConfirmation( PduIdType canTxPduId );
void CanIf_RxIndication(const Can_HwType* Mailbox,const PduInfoType* PduInfoPtr) ;
void CanIf_ControllerModeIndication(uint8 ControllerId,Can_ControllerStateType ControllerMode);
void CanIf_ControllerBusOff(uint8 ControllerId);

#endif
