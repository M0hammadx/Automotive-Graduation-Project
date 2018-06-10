#ifndef PDUR_TEST_H_INCLUDED
#define PDUR_TEST_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include "PduR/pduR.h"
#include "PduR/EcuC.h"
#include "PduR/CanIf.h"
#include "PduR/Com.h"


void PduR_Init_Test(void);

//COM
void PduR_ComTransmit_Test(void);
void PduR_ComTransmit_Test2(void);
Std_ReturnType Com_TriggerTransmit_Test(PduIdType TxPduId, PduInfoType* PduInfoPtr);

void PduR_DcmTransmit_Test(void);

void PduR_CanIfRxIndication_Test(void);
void PduR_CanIfTxConfirmation_Test(void);
void PduR_CanIfTriggerTransmit_Test(void);
void PduR_CanTpStartOfReception_Test(void);
void PduR_CanTpStartOfReception_Test2(void);


#endif // PDUR_TEST_H_INCLUDED
