/** incomplete CanTp header file used as a test to PDUR module */

#ifndef CANTP_H_
#define CANTP_H_

#include "CanTp_Cfg.h"
#include "PduR.h"
#include "EcuC.h"

/*
 * Implemented functions
 ****************************/

Std_ReturnType CanTp_Transmit(PduIdType , const PduInfoType *);
Std_ReturnType CanTp_CancelTransmit( PduIdType );
Std_ReturnType CanTp_ChangeParameter( PduIdType, TPParameterType, uint16_t );
Std_ReturnType CanTp_CancelReceive( PduIdType );

Std_ReturnType CanTp_INF_GetPduHandleId (Pdu_Type *, PduIdType *);

#endif /* CANTP_H_ */
