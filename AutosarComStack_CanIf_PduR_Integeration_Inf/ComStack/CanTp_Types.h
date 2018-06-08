/** incomplete CanTp types header file used as a test to PDUR module */

#ifndef CANTP_TYPES_H_
#define CANTP_TYPES_H_

#include "ComStack_Types.h"


typedef struct {
	const PduIdType CanTpRxNSduId;            // The polite PduR index.
    void*           CanTpRxNSduRef;           //by hajar
} CanTp_RxNSduType;

typedef struct {
	const PduIdType CanTpTxNSduId;               // The polite PduR index.
    void*           CanTpTxNSduRef;           //by hajar
} CanTp_TxNSduType;


typedef struct {
    CanTp_RxNSduType *CanTpRxNSdu;
    CanTp_TxNSduType *CanTpTxNSdu;
}CanTpChannelType;

typedef struct {
    const uint16_t CanTpMaxChannelCnt;
    CanTpChannelType *CanTpChannel;
}CanTpConfigType;


/** Top level config container for CANTP implementation. */
typedef struct {
    const CanTpConfigType *CanTpConfig;
} CanTp_Type;

#endif /* CANTP_TYPES_H_ */
