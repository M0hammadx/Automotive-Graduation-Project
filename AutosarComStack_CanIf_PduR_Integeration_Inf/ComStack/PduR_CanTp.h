/**
 * \file	PduR_CanTp.h
 *
 * \version ..
 *
 * \brief   Configurable interfaces declarations for CanTp module .
 *
 * \date 	..
 *
 * \author  ADAS
 *
 */

#ifndef PDUR_CANTP_H_INCLUDED
#define PDUR_CANTP_H_INCLUDED

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "PduR.h"

/* ========================================================================== */
/*                          Function declarations                             */
/* ========================================================================== */
void PduR_CanTpRxIndication(PduIdType, Std_ReturnType);
void PduR_CanTpTxConfirmation(PduIdType, Std_ReturnType);

BufReq_ReturnType PduR_CanTpStartOfReception(PduIdType, const PduInfoType*,
    PduLengthType, PduLengthType*);
BufReq_ReturnType PduR_CanTpCopyRxData(PduIdType, const PduInfoType*,
    PduLengthType*);
BufReq_ReturnType PduR_CanTpCopyTxData(PduIdType, const PduInfoType*,
    RetryInfoType*, PduLengthType*);

#endif // PDUR_CANTP_H_INCLUDED
