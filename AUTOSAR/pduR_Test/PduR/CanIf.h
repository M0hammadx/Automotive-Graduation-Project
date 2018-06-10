/** incomplete CanIf header file used as a test to PDUR module */

#ifndef CANIF_H_INCLUDED
#define CANIF_H_INCLUDED

#include "CanIf_Types.h"
#include "CanIf_PbCfg.h"

#include "PduR.h"
#include "EcuC.h"


Std_ReturnType CanIf_Transmit(PduIdType , const PduInfoType *);
Std_ReturnType CanIf_CancelTransmit( PduIdType );
Std_ReturnType CanIf_ChangeParameter( PduIdType, TPParameterType, uint16_t );
Std_ReturnType CanIf_CancelReceive( PduIdType );

Std_ReturnType CanIf_INF_GetPduHandleId (Pdu_Type *, PduIdType *);

#endif // CANIF_H_INCLUDED
