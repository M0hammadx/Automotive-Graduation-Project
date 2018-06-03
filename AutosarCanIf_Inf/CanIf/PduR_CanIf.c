/**
 * \file	PduR_CanIf.c
 *
 * \version ..
 *
 * \brief   Configurable interfaces definitions for CanIf module .
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

#if (PDUR_ZERO_COST_OPERATION == STD_OFF) && (PDUR_CANIF_SUPPORT == STD_ON)

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
/**
    Description  : Indication of a received PDU from a CanIf module
    inputs       : RxPduId    | ID of the received PDU.
                   PduInfoPtr | Contains the length, Data and MetaData related to this PDU.
    output       : None
    I/O          : None
    return value : None
*/
void PduR_CanIfRxIndication(PduIdType RxPduId, const PduInfoType* PduInfoPtr){
	//PduR_INF_RxIndication(RxPduId, PduInfoPtr);
		printf("\nPduR_CanIfRxIndication done and data is : %s",PduInfoPtr->SduDataPtr);
}

/**
    Description  : CanIf module confirms the transmission of a PDU, or the failure to transmit a PDU.
    inputs       : TxPduId | ID of the PDU that has been transmitted.
                   result  | The PDU was transmitted or failed.
    output       : None
    I/O          : None
    return value : None
*/
void PduR_CanIfTxConfirmation(PduIdType TxPduId, Std_ReturnType result){
	//PduR_INF_TxConfirmation(TxPduId, result);
	printf("\nPduR_CanIfTxConfirmation done and result is : %d",result);
}

/**
    Description  : Upper layer module copy its data into the buffer .
    inputs       : TxPduId        | ID of the SDU that is requested to be transmitted.
    output       : None
    I/O          : PduInfoPtr     | Contains a pointer to a buffer to where the SDU data shall be copied
    return value : Std_ReturnType | Indicate whether SDU has been copied or not .
*/
Std_ReturnType PduR_CanIfTriggerTransmit(PduIdType TxPduId, PduInfoType* PduInfoPtr){
    printf("\nPduR_CanIfTriggerTransmit done ");
	return E_OK; //PduR_INF_TriggerTransmit(TxPduId, PduInfoPtr);
}

#endif //PDUR_ZERO_COST_OPERATION , PDUR_CANIF_SUPPORT

