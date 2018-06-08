/**
 * \file	PduR_Routing.c
 *
 * \version ..
 *
 * \brief	this file contain functions definitions used in routing .
 *
 * \date 	..
 *
 * \author  ADAS
 *
 */
/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "PduR.h"
/** Modules can be used by your system */
#if PDUR_CANIF_SUPPORT == STD_ON
#include "CanIf.h"
#endif
#if PDUR_CANTP_SUPPORT == STD_ON
#include "CanTp.h"
#endif
#if PDUR_COM_SUPPORT == STD_ON
#include "Com.h"
#endif
#if PDUR_DCM_SUPPORT == STD_ON
#include "Dcm.h"
#endif

/***************** the API functions required by the PDU Router module **********************
//Communication interface modules:
CanIf_Transmit
CanIf_CancelTransmit

//Transport Protocol Modules:
CanTp_Transmit
CanTp_CancelTransmit
CanTp_CancelReceive
CanTp_ChangeParameter

//Upper layer modules which use transport protocol modules:
Dcm_StartOfReception
Dcm_CopyRxData
Dcm_CopyTxData
Dcm_TpRxIndication
Dcm_TpTxConfirmation

//Upper layer modules which process I-PDUs originating from communication interface modules:
Com_RxIndication
Com_TxConfirmation
Com_TriggerTransmit*/


#if PDUR_ZERO_COST_OPERATION == STD_OFF

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
Std_ReturnType PduR_INF_RouteTransmit( PduIdType TxPduId, const PduInfoType* PduInfoPtr ){
	Std_ReturnType result =	E_OK;
	PduIdType PduHandleId;

    /** Create pointer to routing paths */
    PduRRoutingPath_type ** routes = PduRConfig->RoutingPaths;
    if (routes[0] == NULL){
        //detect error
        return E_NOT_OK;
    }
    /** Query routing paths for target path */
    for (uint8_t i=0 ; routes[i] != NULL ; i++){
        if ( routes[i]->PduRSrcPduRef->SourcePduHandleId == TxPduId){
#if PDUR_CANIF_SUPPORT == STD_ON
            if( CanIf_INF_GetPduHandleId(routes[i]->PduRDestPduRef->DestPduRef, &PduHandleId) == E_OK ){
                result |= CanIf_Transmit(PduHandleId, PduInfoPtr);
            }
#endif
#if PDUR_CANTP_SUPPORT == STD_ON
            if( CanTp_INF_GetPduHandleId(routes[i]->PduRDestPduRef->DestPduRef, &PduHandleId) == E_OK ){
                result |= CanTp_Transmit(PduHandleId, PduInfoPtr);
            }
#endif
            return result;
        }
    }
    return result;
}

Std_ReturnType PduR_INF_RouteCancleTransmit( PduIdType TxPduId ){
    Std_ReturnType result =	E_OK;
    PduIdType PduHandleId;
	/** Create pointer to routing paths */
    PduRRoutingPath_type ** routes = PduRConfig->RoutingPaths;
    if (routes[0] == NULL){
        //detect error
        return E_NOT_OK;
    }
    /** Query routing paths for target path */
    for (uint8_t i=0 ; routes[i] != NULL ; i++){
        if ( routes[i]->PduRSrcPduRef->SourcePduHandleId == TxPduId){

#if PDUR_CANIF_SUPPORT == STD_ON
            if( CanIf_INF_GetPduHandleId(routes[i]->PduRDestPduRef->DestPduRef, &PduHandleId) == E_OK ){
                result |= CanIf_CancelTransmit(PduHandleId);
            }
#endif
#if PDUR_CANTP_SUPPORT == STD_ON
            if( CanTp_INF_GetPduHandleId(routes[i]->PduRDestPduRef->DestPduRef, &PduHandleId) == E_OK ){
                result |= CanTp_CancelTransmit(PduHandleId);
            }
#endif
            return result;
        }

    }
    return result;
}

Std_ReturnType PduR_INF_RouteChangeParameter( PduIdType id, TPParameterType parameter, uint16_t value ){

    Std_ReturnType RetVal = E_OK;
    PduIdType PduHandleId;
	/** Create pointer to routing paths */
    PduRRoutingPath_type ** routes = PduRConfig->RoutingPaths;
    if (routes[0] == NULL){
        //detect error
        return E_NOT_OK;
    }
    /** Query routing paths for target path */
    for (uint8_t i=0 ; routes[i] != NULL ; i++){
        if ( routes[i]->PduRSrcPduRef->SourcePduHandleId == id){

#if PDUR_CANTP_SUPPORT == STD_ON
            if( CanTp_INF_GetPduHandleId(routes[i]->PduRDestPduRef->DestPduRef, &PduHandleId) == E_OK ){
                RetVal |= CanTp_ChangeParameter( id, parameter, value );
            }
#endif
            return RetVal;
        }
    }
    return RetVal;
}

Std_ReturnType PduR_INF_RouteCancelReceive( PduIdType RxPduId ){

    Std_ReturnType RetVal = E_OK;
    PduIdType PduHandleId;
	/** Create pointer to routing paths */
    PduRRoutingPath_type ** routes = PduRConfig->RoutingPaths;
    if (routes[0] == NULL){
        //detect error
        return E_NOT_OK;
    }
    /** Query routing paths for target path */
    for (uint8_t i=0 ; routes[i] != NULL ; i++){
        if ( routes[i]->PduRSrcPduRef->SourcePduHandleId == RxPduId){

#if PDUR_CANTP_SUPPORT == STD_ON
            if( CanTp_INF_GetPduHandleId(routes[i]->PduRDestPduRef->DestPduRef, &PduHandleId) == E_OK ){
                RetVal |= CanTp_CancelReceive( RxPduId );
            }
#endif
            return RetVal;
        }
    }
    return RetVal;
}


void PduR_INF_RouteRxIndication(const PduRDestPdu_type *destination, const PduInfoType *PduInfo){
    PduIdType PduHandleId;

#if PDUR_COM_SUPPORT == STD_ON
    if (Com_INF_GetPduHandleId (destination->DestPduRef, &PduHandleId) == E_OK){
        Com_RxIndication(PduHandleId ,PduInfo);
    }
#endif
#if PDUR_CANIF_SUPPORT == STD_ON
//    if (CanIf_INF_GetPduHandleId (destination->DestPduRef ,&PduHandleId) == E_OK){
//        Std_ReturnType retVal = CanIf_Transmit(PduHandleId, PduInfo);
//        if (retVal != E_OK) {
//            //raise an error
//        }
//    }
#endif
}

void PduR_INF_RouteTxConfirmation(const PduRRoutingPath_type *route, Std_ReturnType result) {
    PduIdType PduHandleId;

#if PDUR_COM_SUPPORT == STD_ON
    if (Com_INF_GetPduHandleId (route->PduRSrcPduRef->SrcPduRef ,&PduHandleId) == E_OK){
		Com_TxConfirmation(PduHandleId, result);
    }
#endif
}

void PduR_INF_RouteTpRxIndication(const PduRDestPdu_type *destination, Std_ReturnType result){
    PduIdType PduHandleId;

#if PDUR_COM_SUPPORT == STD_ON
    if (Com_INF_GetPduHandleId (destination->DestPduRef, &PduHandleId) == E_OK){
        Com_TpRxIndication(PduHandleId, result);
    }
#endif
#if PDUR_DCM_SUPPORT == STD_ON
    if (Dcm_INF_GetPduHandleId (destination->DestPduRef ,&PduHandleId) == E_OK){
        Dcm_TpRxIndication(PduHandleId, result);
    }
#endif
#if PDUR_CANTP_SUPPORT == STD_ON

#endif

}

void PduR_INF_RouteTpTxConfirmation(const PduRRoutingPath_type *route, Std_ReturnType result) {
    PduIdType PduHandleId;

#if PDUR_COM_SUPPORT == STD_ON
    if (Com_INF_GetPduHandleId (route->PduRSrcPduRef->SrcPduRef ,&PduHandleId) == E_OK){
		Com_TpTxConfirmation(PduHandleId, result);
    }
#endif
#if PDUR_DCM_SUPPORT == STD_ON
    if (Dcm_INF_GetPduHandleId (route->PduRSrcPduRef->SrcPduRef ,&PduHandleId) == E_OK){
		Dcm_TpTxConfirmation(PduHandleId, result);
    }
#endif
}


Std_ReturnType PduR_INF_RouteTriggerTransmit(const PduRRoutingPath_type *route, PduInfoType * pduInfoPtr) {
	Std_ReturnType retVal = E_NOT_OK;
    PduIdType PduHandleId;
#if PDUR_COM_SUPPORT == STD_ON
    if (Com_INF_GetPduHandleId (route->PduRSrcPduRef->SrcPduRef ,&PduHandleId) == E_OK){
        retVal = Com_TriggerTransmit(PduHandleId, pduInfoPtr);
    }
#endif

    // raise an error if retVal E_NOT_OK
	return retVal;
}


BufReq_ReturnType PduR_INF_RouteStartOfReception(const PduRDestPdu_type *destination, const PduInfoType* info,
    PduLengthType TpSduLength, PduLengthType* bufferSizePtr){

    BufReq_ReturnType retVal = BUFREQ_OK;
    PduIdType PduHandleId;
#if PDUR_DCM_SUPPORT == STD_ON
    if (Dcm_INF_GetPduHandleId (destination->DestPduRef ,&PduHandleId) == E_OK){
        retVal |= Dcm_StartOfReception(PduHandleId, info, TpSduLength, bufferSizePtr);
    }
#endif
#if PDUR_COM_SUPPORT == STD_ON
    if (Com_INF_GetPduHandleId (destination->DestPduRef, &PduHandleId) == E_OK){
        retVal |= Com_StartOfReception(PduHandleId, info, TpSduLength, bufferSizePtr);
    }
#endif
#if PDUR_CANIF_SUPPORT == STD_ON

#endif
#if PDUR_CANTP_SUPPORT == STD_ON

#endif
    return retVal;
}

BufReq_ReturnType PduR_INF_RouteCopyRxData(const PduRDestPdu_type *destination, const PduInfoType* info,
    PduLengthType* bufferSizePtr){

    BufReq_ReturnType retVal = BUFREQ_OK;
    PduIdType PduHandleId;
#if PDUR_DCM_SUPPORT == STD_ON
    if (Dcm_INF_GetPduHandleId (destination->DestPduRef ,&PduHandleId) == E_OK){
        retVal |= Dcm_CopyRxData(PduHandleId, info, bufferSizePtr);
    }
#endif
#if PDUR_COM_SUPPORT == STD_ON
    if (Com_INF_GetPduHandleId (destination->DestPduRef, &PduHandleId) == E_OK){
        retVal |= Com_CopyRxData(PduHandleId, info, bufferSizePtr);
    }
#endif
#if PDUR_CANIF_SUPPORT == STD_ON

#endif
#if PDUR_CANTP_SUPPORT == STD_ON

#endif
    return retVal;
}

BufReq_ReturnType PduR_INF_RouteCopyTxData(const PduRSrcPdu_type *sourceRef, const PduInfoType* info,
    RetryInfoType* retry, PduLengthType* availableDataPtr){

    BufReq_ReturnType retVal = BUFREQ_OK;
    PduIdType PduHandleId;
#if PDUR_DCM_SUPPORT == STD_ON
    if (Dcm_INF_GetPduHandleId (sourceRef->SrcPduRef ,&PduHandleId) == E_OK){
        retVal |= Dcm_CopyTxData(PduHandleId, info, retry, availableDataPtr);
    }
#endif
#if PDUR_COM_SUPPORT == STD_ON
    if (Com_INF_GetPduHandleId (sourceRef->SrcPduRef, &PduHandleId) == E_OK){
        retVal |= Com_CopyTxData(PduHandleId, info, retry, availableDataPtr);
    }
#endif
#if PDUR_CANIF_SUPPORT == STD_ON

#endif
#if PDUR_CANTP_SUPPORT == STD_ON

#endif
    return retVal;
}

#endif //PDUR_ZERO_COST_OPERATION
