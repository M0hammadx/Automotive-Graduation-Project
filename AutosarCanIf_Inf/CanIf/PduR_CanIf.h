/**
 * \file	PduR_CanIf.h
 *
 * \version ..
 *
 * \brief   Configurable interfaces declarations for CanIf module .
 *
 * \date 	..
 *
 * \author  ADAS
 *
 */
#ifndef PDUR_CANIF_H_
#define PDUR_CANIF_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "PduR.h"

#if PDUR_ZERO_COST_OPERATION == STD_OFF

/* ========================================================================== */
/*                          Function declarations                             */
/* ========================================================================== */
void PduR_CanIfRxIndication(PduIdType CanRxPduId, const PduInfoType* PduInfoPtr);
void PduR_CanIfTxConfirmation(PduIdType CanTxPduId, Std_ReturnType result);
Std_ReturnType PduR_CanIfTriggerTransmit(PduIdType TxPduId, PduInfoType* PduInfoPtr);


#endif //PDUR_ZERO_COST_OPERATION

#endif //PDUR_CANIF_H_
