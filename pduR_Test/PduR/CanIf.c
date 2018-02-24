//incomplete CanIf code file used as a test to PDUR module

#include "CanIf.h"

//function to test reception from CAN
void PduR_CanIfRxIndication_Test(void){
    printf("now in PduR_CanIfRxIndication_Test() function ... formulating message\n");

    /** in case of CAN module these lines exist in function that intend to confirm */
    /** formulating I-PDU */
    uint8_t distMsg[] = "123d";
    const PduInfoType distanceMsg = {
        .SduDataPtr = distMsg,
        .SduLength = sizeof(distMsg)/sizeof(distMsg[0])
    };

    /** query PDUR routing paths sources to find global pdu reference .
        inside CAN module &Pdus[0] will be reference associated with CanId .
    */
    PduIdType PduHandleId;

    if (PduR_INF_GetSourcePduHandleId (&Pdus[0] ,&PduHandleId) == E_OK){
        PduR_CanIfRxIndication(PduHandleId ,&distanceMsg);
    }
}

void PduR_CanIfTxConfirmation_Test(void){
    /** query PDUR routing paths destinations to find global pdu reference .
        inside CAN module &Pdus[3] will be reference associated with CanId .
    */
    PduIdType PduHandleId;
    if (PduR_INF_GetDestPduHandleId (&Pdus[1] ,&PduHandleId) == E_OK){
        PduR_CanIfTxConfirmation(PduHandleId , 100);
    }
    else{
        /** raise an error cause this I-PDU not associated with
            routing path in PDUR.
        */
    }
}

void PduR_CanIfTriggerTransmit_Test(void){
    uint8_t canMsgBuffer[20];
    PduInfoType pduCanMsg = {
        .SduDataPtr = canMsgBuffer,
        .SduLength  = sizeof(canMsgBuffer)/sizeof(canMsgBuffer[0])
    };
    PduIdType PduHandleId;

    if (PduR_INF_GetDestPduHandleId (&Pdus[1] ,&PduHandleId) == E_OK){
        Std_ReturnType retVal = PduR_CanIfTriggerTransmit(PduHandleId, &pduCanMsg);
        if(retVal == E_OK){
            printf("Message is received from upper layer and is %s\n", canMsgBuffer);
        }else{
            printf("Message not received from upper layer\n");
        }
    }else{
        /** raise an error cause this I-PDU not associated with
            routing path in PDUR.
        */
    }
    printf("router CANIF trigger transmit has finished\n");

}


Std_ReturnType CanIf_Transmit(PduIdType CanTxPduId, const PduInfoType *PduInfoPtr){
    printf("now in CanIf_transmit function and the value is %s \n",PduInfoPtr->SduDataPtr);
    printf("router COM Transmit has finished\n");
    return E_OK;
}

Std_ReturnType CanIf_CancelTransmit( PduIdType TxPduId ){

    printf("now in CanIf_CancelTransmit function \n");
    printf("router COM Cancel Transmit has finished\n");
    return E_OK;
}

Std_ReturnType CanIf_ChangeParameter( PduIdType id, TPParameterType parameter, uint16_t value ){

    printf("now in CanIf_ChangeParameter function\n");
    printf("router COM ChangeParameter has finished\n");
    return E_OK;
}

Std_ReturnType CanIf_CancelReceive( PduIdType RxPduId ){

    printf("now in CanIf_CancelReceive function\n");
    printf("router COM CancelReceive has finished\n");
    return E_OK;
}

/**
    Description  : query global I-PDU reference in CanIf configuration .
    inputs       : Pdu            | Reference to global PDU .
    output       : DestPduId      | Identifier to local I-PDU .
    I/O          : None
    return value : Std_ReturnType | Determine if I-PDU is exist or not.
*/
Std_ReturnType CanIf_INF_GetPduHandleId (Pdu_Type *Pdu, PduIdType *PduHandleIdPtr){
    Std_ReturnType Std_Ret = E_NOT_OK;

    for (uint8_t i=0 ; i<CanIf_Config.InitConfig->CanIfNumberOfCanTXPduIds ; i++ ){
        if (CanIf_Config.InitConfig->CanIfTxPduConfigPtr[i].PduIdRef == Pdu){
            Std_Ret = E_OK;
            *PduHandleIdPtr = CanIf_Config.InitConfig->CanIfTxPduConfigPtr[i].CanIfTxPduId;
        }
    }
    return Std_Ret;
}
