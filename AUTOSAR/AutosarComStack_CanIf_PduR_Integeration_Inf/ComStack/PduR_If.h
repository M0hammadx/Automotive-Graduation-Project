/**
 * \file	PduR_If.h
 *
 * \version ..
 *
 * \brief	this file is used to declare functions that can be used in router module interface
 *				such as PduR_CanIf.c, PduR_CanLinIf.c, and PduR_ComIf.c
 *
 * \date 	..
 *
 * \author  ADAS
 *
 */

#ifndef PDUR_IF_H_
#define PDUR_IF_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "PduR.h"

#if PDUR_ZERO_COST_OPERATION == STD_OFF

/* ========================================================================== */
/*                          Function declarations                             */
/* ========================================================================== */

/** Interfaces implemented in PduR_Logic.c and used in PDU interface */
void PduR_INF_RxIndication(PduIdType, const PduInfoType*);
void PduR_INF_TxConfirmation(PduIdType, Std_ReturnType);
void PduR_INF_TpRxIndication(PduIdType, Std_ReturnType);
void PduR_INF_TpTxConfirmation(PduIdType, Std_ReturnType);

Std_ReturnType PduR_INF_TriggerTransmit(PduIdType, PduInfoType*);

BufReq_ReturnType PduR_INF_StartOfReception(PduIdType, const PduInfoType*,
    PduLengthType, PduLengthType*);
BufReq_ReturnType PduR_INF_CopyRxData(PduIdType, const PduInfoType*,
    PduLengthType*);
BufReq_ReturnType PduR_INF_CopyTxData(PduIdType, const PduInfoType*,
    RetryInfoType*, PduLengthType*);

/** Prototypes implemented in PDUR routing and used in PDUR logic */
Std_ReturnType PduR_INF_RouteTransmit( PduIdType TxPduId, const PduInfoType* PduInfoPtr );
Std_ReturnType PduR_INF_RouteCancleTransmit( PduIdType TxPduId );
Std_ReturnType PduR_INF_RouteChangeParameter( PduIdType id, TPParameterType parameter, uint16_t value );
Std_ReturnType PduR_INF_RouteCancelReceive( PduIdType RxPduId );

void PduR_INF_RouteRxIndication(const PduRDestPdu_type *, const PduInfoType *);
void PduR_INF_RouteTxConfirmation(const PduRRoutingPath_type *, Std_ReturnType);
void PduR_INF_RouteTpRxIndication(const PduRDestPdu_type *, Std_ReturnType);
void PduR_INF_RouteTpTxConfirmation(const PduRRoutingPath_type *, Std_ReturnType);

Std_ReturnType PduR_INF_RouteTriggerTransmit(const PduRRoutingPath_type *, PduInfoType *);

BufReq_ReturnType PduR_INF_RouteStartOfReception(const PduRDestPdu_type *, const PduInfoType*,
    PduLengthType, PduLengthType*);
BufReq_ReturnType PduR_INF_RouteCopyRxData(const PduRDestPdu_type *, const PduInfoType* ,
    PduLengthType*);
BufReq_ReturnType PduR_INF_RouteCopyTxData(const PduRSrcPdu_type *, const PduInfoType*,
    RetryInfoType*, PduLengthType*);

#endif //PDUR_ZERO_COST_OPERATION

#endif //PDUR_IF_H_
