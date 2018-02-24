/** incomplete Dcm code file used as a test to PDUR module */

#include "Dcm.h"

void PduR_DcmTransmit_Test(void){
    /** in case of DCM module these lines exist in function that intend to transmit */
    /** formulating I-PDU */
    uint8_t distMsg[] = "DCMMessage1234";
    const PduInfoType distanceMsg = {
        .SduDataPtr = distMsg,
        .SduLength = sizeof(distMsg)/sizeof(distMsg[0])
    };

    /** query PDUR routing paths sources to find global pdu reference .
        inside COM module &Pdus[5] will be reference to related message .
    */
    PduIdType PduHandleId;

    if (PduR_INF_GetSourcePduHandleId (&Pdus[5] ,&PduHandleId) == E_OK){
        PduR_DcmTransmit(PduHandleId ,&distanceMsg);

        PduR_DcmCancelTransmit( PduHandleId );
        PduR_DcmChangeParameter( PduHandleId ,TP_STMIN , 0 );
        PduR_DcmCancelReceive( PduHandleId );
    }
}


void Dcm_TpRxIndication(PduIdType PduHandleId, Std_ReturnType result){
    printf("now in Dcm Rx Indication message received \n");
}

void Dcm_TpTxConfirmation(PduIdType PduHandleId, Std_ReturnType result){
    printf("now in Dcm Tx Confirmation message confirmed \n");
}


BufReq_ReturnType Dcm_StartOfReception(PduIdType id, const PduInfoType* info,
    PduLengthType TpSduLength, PduLengthType* bufferSizePtr){

    printf("now in Dcm start of reception\n");
    return BUFREQ_OK;
}

BufReq_ReturnType Dcm_CopyRxData(PduIdType id, const PduInfoType* info,
    PduLengthType* bufferSizePtr){

    printf("now in Dcm copy RX data\n");
    return BUFREQ_OK;
}

BufReq_ReturnType Dcm_CopyTxData(PduIdType id, const PduInfoType* info,
    RetryInfoType* retry, PduLengthType* availableDataPtr){

    printf("now in Dcm copy TX data\n");
    return BUFREQ_OK;
}

/**
    Description  : query global I-PDU reference in Dcm configuration .
    inputs       : Pdu            | Reference to global PDU .
    output       : DestPduId      | Identifier to local I-PDU .
    I/O          : None
    return value : Std_ReturnType | Determine if I-PDU is exist or not.
*/
Std_ReturnType Dcm_INF_GetPduHandleId (Pdu_Type *Pdu, PduIdType *PduHandleIdPtr){
    Std_ReturnType Std_Ret = E_NOT_OK;

//    for (uint8_t i=0 ; i<DCM_DSL_RX_PDU_ID_LIST_LENGTH ; i++ ){
//        if (DCM_Config.Dsl->DslProtocol.DslProtocolRowList[].
//            DslConnection[].DslMainConnection->DslProtocolRx->DcmDslProtocolRxPduRef == Pdu){
//
//            Std_Ret = E_OK;
//            *PduHandleIdPtr = DCM_Config.Dsl->DslProtocol.DslProtocolRowList[].
//                DslConnection[].DslMainConnection->DslProtocolRx->DcmDslProtocolRxPduId;
//        }
//    }
    /** only for test*/
    if (Pdu == &Pdus[4]){
        *PduHandleIdPtr = 11;
        Std_Ret = E_OK;
    }else if(Pdu == &Pdus[5]){
        *PduHandleIdPtr = 22;
        Std_Ret = E_OK;
    }else{
        Std_Ret = E_NOT_OK;
    }
    return Std_Ret;
}





