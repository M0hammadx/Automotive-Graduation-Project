/**
 * \file	CanIf_Cbk.h
 *
 * \version ..
 *
 * \brief	Contain functions prototypes provided for other modules.
 *
 * \date 	..
 *
 * \author  MHmed Hatem
 *
 */

#ifndef CANIF_CBK_H_INCLUDED
#define CANIF_CBK_H_INCLUDED

/* -------------------------------------------------------------------------- */
/*                             Include Files                                  */
/* -------------------------------------------------------------------------- */
//#include "Can.h"        ///INF
#include "EcuC.h"       ///INF
/* -------------------------------------------------------------------------- */
/*                          Function declarations                             */
/* -------------------------------------------------------------------------- */
Std_ReturnType CanIf_TriggerTransmit( PduIdType TxPduId, PduInfoType * PduInfoPtr );    ///tested
void CanIf_TxConfirmation( PduIdType CanTxPduId );  ///tested
void CanIf_RxIndication( const Can_HwType *Mailbox, const PduInfoType *PduInfoPtr );    ///tested
void CanIf_ControllerBusOff( uint8 ControllerId );  ///tested
void CanIf_ConfirmPnAvailability( uint8 TransceiverId );  ///tested
void CanIf_ClearTrcvWufFlagIndication( uint8 TransceiverId );  ///tested
void CanIf_CheckTrcvWakeFlagIndication( uint8 TransceiverId );  ///tested
void CanIf_ControllerModeIndication( uint8 ControllerId, Can_ControllerStateType ControllerMode );  ///tested
void CanIf_TrcvModeIndication( uint8 TransceiverId, CanTrcv_TrcvModeType TransceiverMode );  ///tested
void CanIf_CurrentIcomConfiguration( uint8 ControllerId, IcomConfigIdType ConfigurationId, IcomSwitch_ErrorType Error );  ///tested
Std_ReturnType CanIf_INF_GetPduHandleId (Pdu_Type *Pdu, PduIdType *PduHandleIdPtr);

#endif // CANIF_CBK_H_INCLUDED
