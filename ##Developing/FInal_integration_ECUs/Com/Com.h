/** incomplete COM header file used as a test to PDUR module */

#ifndef COM_H_INCLUDED
#define COM_H_INCLUDED

/*  Tiva */


#include "Com_Types.h"
#include "Com_PbCfg.h"

#include "Can.h"
#include "Can_PbCfg.h"
#include "CanIf_Cbk.h"
#include "PduR.h"
#include "EcuC.h"
#include "CanIf.h"


#include <string.h>

void Com_INF_Init(void);
void PduR_ComTransmit_Test(void);
void PduR_ComTransmit_Test2(void);

void Com_RxIndication(PduIdType, const PduInfoType *);
void Com_TxConfirmation(PduIdType, Std_ReturnType);
void Com_TpRxIndication(PduIdType, Std_ReturnType);
void Com_TpTxConfirmation(PduIdType, Std_ReturnType);

Std_ReturnType Com_TriggerTransmit(PduIdType, PduInfoType *);

BufReq_ReturnType Com_StartOfReception(PduIdType, const PduInfoType*,
    PduLengthType, PduLengthType*);
BufReq_ReturnType Com_CopyRxData(PduIdType, const PduInfoType*,
    PduLengthType*);
BufReq_ReturnType Com_CopyTxData(PduIdType, const PduInfoType*,
    RetryInfoType*, PduLengthType*);

Std_ReturnType Com_INF_GetPduHandleId (Pdu_Type *, PduIdType *);

#endif // COM_H_INCLUDED
