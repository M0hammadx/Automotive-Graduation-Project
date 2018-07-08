/** incomplete CanTp code file used as a test to PDUR module */

#include "CanTp.h"

//function to test reception from CANTP to Com
void PduR_CanTpStartOfReception_Test(void){
    //printf("now in PduR_CanTpStartOfReception_Test() function\n");

    PduIdType PduHandleId;
    if (PduR_INF_GetSourcePduHandleId (&Pdus[2] ,&PduHandleId) == E_OK){
        PduR_CanTpStartOfReception(PduHandleId, NULL, 0, NULL);
        PduR_CanTpCopyRxData(PduHandleId, NULL, NULL);
        PduR_CanTpRxIndication(PduHandleId , (Std_ReturnType)1);
    }
}

//function to test reception from CANTP to Dcm
void PduR_CanTpStartOfReception_Test2(void){
    //printf("now in PduR_CanTpStartOfReception_Test() function\n");

    PduIdType PduHandleId;
    if (PduR_INF_GetSourcePduHandleId (&Pdus[4] ,&PduHandleId) == E_OK){
        PduR_CanTpStartOfReception(PduHandleId, NULL, 0, NULL);
        PduR_CanTpCopyRxData(PduHandleId, NULL, NULL);
        PduR_CanTpRxIndication(PduHandleId, (Std_ReturnType)1);
    }
}



Std_ReturnType CanTp_Transmit(PduIdType CanTxPduId, const PduInfoType *PduInfoPtr){
    //printf("now in CanTp_transmit function and the value is %s \n",PduInfoPtr->SduDataPtr);

    /** only for test */
    PduIdType PduHandleId;
    if (CanTxPduId == 1){   // in case of Com
        if (PduR_INF_GetDestPduHandleId (&Pdus[3] ,&PduHandleId) == E_OK){
            PduR_CanTpCopyTxData(PduHandleId, NULL, NULL, NULL);
            PduR_CanTpTxConfirmation(PduHandleId , (Std_ReturnType)100);
            //printf("router COM Transmit has finished\n");
        }else{
            /** raise an error cause this I-PDU not associated with
                routing path in PDUR.
            */
        }
    }else if (CanTxPduId == 2){ // in case of Dcm
        if (PduR_INF_GetDestPduHandleId (&Pdus[5] ,&PduHandleId) == E_OK){
            PduR_CanTpCopyTxData(PduHandleId, NULL, NULL, NULL);
            PduR_CanTpTxConfirmation(PduHandleId , (Std_ReturnType)100);
            //printf("router DCM Transmit has finished\n");
        }else{
            /** raise an error cause this I-PDU not associated with
                routing path in PDUR.
            */
        }
    }
    return E_OK;
}

Std_ReturnType CanTp_CancelTransmit( PduIdType TxPduId ){

    //printf("now in CanTp_CancelTransmit function\n ");
    return E_OK;
}

Std_ReturnType CanTp_ChangeParameter( PduIdType id, TPParameterType parameter, uint16 value ){

    //printf("now in CanTp_ChangeParameter function\n");
    return E_OK;
}

Std_ReturnType CanTp_CancelReceive( PduIdType RxPduId ){

    //printf("now in CanTp_CancelReceive function\n");
    return E_OK;
}

/**
    Description  : query global I-PDU reference in CanTp configuration .
    inputs       : Pdu            | Reference to global PDU .
    output       : DestPduId      | Identifier to local I-PDU .
    I/O          : None
    return value : Std_ReturnType | Determine if I-PDU is exist or not.
*/
Std_ReturnType CanTp_INF_GetPduHandleId (Pdu_Type *Pdu, PduIdType *PduHandleIdPtr){
    Std_ReturnType Std_Ret = E_NOT_OK;

//    for (uint8_t i=0 ; i < CANTP_RX_NSDU_LIST_CNT ; i++ ){
//        if (CanTp.CanTpConfig->CanTpChannel[].CanTpRxNSdu[].CanTpRxNSduRef == Pdu){
//            Std_Ret = E_OK;
//            *PduHandleIdPtr = CanTp.CanTpConfig->CanTpChannel[].CanTpRxNSdu[].CanTpRxNSduId;
//        }
//    }
    /** only for test*/
    if (Pdu == &Pdus[3]){
        *PduHandleIdPtr = 1;
        Std_Ret = E_OK;
    }else if(Pdu == &Pdus[5]){
        *PduHandleIdPtr = 2;
        Std_Ret = E_OK;
    }else{
        Std_Ret = E_NOT_OK;
    }
    return Std_Ret;
}
