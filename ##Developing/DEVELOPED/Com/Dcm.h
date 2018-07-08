/** incomplete Dcm header file used as a test to PDUR module */

#ifndef DCM_H_INCLUDED
#define DCM_H_INCLUDED

#include "Dcm_Lcfg.h"

#include "PduR.h"
#include "EcuC.h"

#define DCM_DSL_RX_PDU_ID_LIST_LENGTH 1     //no of elements in DcmDslProtocolRx array

void Dcm_TpRxIndication(PduIdType, Std_ReturnType);
void Dcm_TpTxConfirmation(PduIdType, Std_ReturnType);



BufReq_ReturnType Dcm_StartOfReception(PduIdType, const PduInfoType*,
    PduLengthType, PduLengthType*);
BufReq_ReturnType Dcm_CopyRxData(PduIdType, const PduInfoType*,
    PduLengthType*);
BufReq_ReturnType Dcm_CopyTxData(PduIdType, const PduInfoType*,
    RetryInfoType*, PduLengthType*);

Std_ReturnType Dcm_INF_GetPduHandleId (Pdu_Type *, PduIdType *);

#endif // DCM_H_INCLUDED
