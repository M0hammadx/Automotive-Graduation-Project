/**
 * \file	PduR_Logic.c
 *
 * \version ..
 *
 * \brief	this file is used to check if error exits and
 * 				forward requests to routing functions .
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

#if PDUR_ZERO_COST_OPERATION == STD_OFF

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
/** lower layer functions implementation */
void PduR_INF_RxIndication(PduIdType pduId, const PduInfoType* pduInfoPtr){

	/** Create pointer to routing paths */
    PduRRoutingPath_type ** routes = PduRConfig->RoutingPaths;
    if (routes[0] == NULL){
        //raise an error
        return;
    }
    /** Query routing paths for target path */
    uint8 i;
    for ( i=0 ; routes[i] != NULL ; i++){
        if ( routes[i]->PduRSrcPduRef->SourcePduHandleId == pduId){
            PduR_INF_RouteRxIndication(routes[i]->PduRDestPduRef , pduInfoPtr);
            return;
        }
    }
}

void PduR_INF_TxConfirmation(PduIdType PduId, Std_ReturnType result){

	/** Create pointer to routing paths */
    PduRRoutingPath_type ** routes = PduRConfig->RoutingPaths;
    if (routes[0] == NULL){
        //raise an error
        return;
    }
    /** Query routing paths for target path */
    uint8 i;
    for ( i=0 ; routes[i] != NULL ; i++){
        if ( routes[i]->PduRDestPduRef->DestPduHandleId == PduId){
            PduR_INF_RouteTxConfirmation(routes[i], result);
            return;
        }
    }
}

/** lower layer Tp functions implementation */
void PduR_INF_TpRxIndication(PduIdType pduId, Std_ReturnType result){

	/** Create pointer to routing paths */
    PduRRoutingPath_type ** routes = PduRConfig->RoutingPaths;
    if (routes[0] == NULL){
        //raise an error
        return;
    }
    /** Query routing paths for target path */
    uint8 i;
    for ( i=0 ; routes[i] != NULL ; i++){
        if ( routes[i]->PduRSrcPduRef->SourcePduHandleId == pduId){
            PduR_INF_RouteTpRxIndication(routes[i]->PduRDestPduRef , result);
            return;
        }
    }
}

void PduR_INF_TpTxConfirmation(PduIdType PduId, Std_ReturnType result){

	/** Create pointer to routing paths */
    PduRRoutingPath_type ** routes = PduRConfig->RoutingPaths;
    if (routes[0] == NULL){
        //raise an error
        return;
    }
    /** Query routing paths for target path */
    uint8 i;
    for ( i=0 ; routes[i] != NULL ; i++){
        if ( routes[i]->PduRDestPduRef->DestPduHandleId == PduId){
            PduR_INF_RouteTpTxConfirmation(routes[i], result);
            return;
        }
    }
}


Std_ReturnType PduR_INF_TriggerTransmit(PduIdType pduId, PduInfoType* PduInfoPtr) {
	Std_ReturnType retVal = E_OK;

	/** Create pointer to routing paths */
    PduRRoutingPath_type ** routes = PduRConfig->RoutingPaths;
    if (routes[0] == NULL){
        //raise an error
        return E_NOT_OK;
    }
    /** Query routing paths for target path */
    uint8 i;
    for ( i=0 ; routes[i] != NULL ; i++){
        if ( routes[i]->PduRDestPduRef->DestPduHandleId == pduId){
            retVal |= PduR_INF_RouteTriggerTransmit(routes[i], PduInfoPtr);
            return retVal;
        }
    }
	return retVal;
}


BufReq_ReturnType PduR_INF_StartOfReception(PduIdType id, const PduInfoType* info,
    PduLengthType TpSduLength, PduLengthType* bufferSizePtr){

	/** Create pointer to routing paths */
    PduRRoutingPath_type ** routes = PduRConfig->RoutingPaths;
    if (routes[0] == NULL){
        //raise an error
        return BUFREQ_NOT_OK;
    }
    /** Query routing paths for target path */
    uint8 i;
    for ( i=0 ; routes[i] != NULL ; i++){
        if ( routes[i]->PduRSrcPduRef->SourcePduHandleId == id){
             return PduR_INF_RouteStartOfReception(routes[i]->PduRDestPduRef, info, TpSduLength, bufferSizePtr);
        }
    }
    return BUFREQ_NOT_OK;
}

BufReq_ReturnType PduR_INF_CopyRxData(PduIdType id, const PduInfoType* info,
    PduLengthType* bufferSizePtr){

	/** Create pointer to routing paths */
    PduRRoutingPath_type ** routes = PduRConfig->RoutingPaths;
    if (routes[0] == NULL){
        //raise an error
        return BUFREQ_NOT_OK;
    }
    /** Query routing paths for target path */
    uint8 i;
    for ( i=0 ; routes[i] != NULL ; i++){
        if ( routes[i]->PduRSrcPduRef->SourcePduHandleId == id){
             return PduR_INF_RouteCopyRxData(routes[i]->PduRDestPduRef, info, bufferSizePtr);            ;
        }
    }
    return BUFREQ_NOT_OK;
}

BufReq_ReturnType PduR_INF_CopyTxData(PduIdType id, const PduInfoType* info,
    RetryInfoType* retry, PduLengthType* availableDataPtr){

	/** Create pointer to routing paths */
    PduRRoutingPath_type ** routes = PduRConfig->RoutingPaths;
    if (routes[0] == NULL){
        //raise an error
        return BUFREQ_NOT_OK;
    }
    /** Query routing paths for target path */
    uint8 i;
    for ( i=0 ; routes[i] != NULL ; i++){
        if ( routes[i]->PduRDestPduRef->DestPduHandleId == id){
             return PduR_INF_RouteCopyTxData(routes[i]->PduRSrcPduRef, info, retry, availableDataPtr);
        }
    }
    return BUFREQ_NOT_OK;
}

#endif //PDUR_ZERO_COST_OPERATION
