/** incomplete Com code file used as a test to PDUR module */

#include "Com.h"
#include "../inc/tm4c123gh6pm.h"

#include "../ECU_CONFIGURATION.h"
//functions to test transmission to CAN
uint8 x = 0;
void PduR_ComTransmit_Test(void)
{
    /** in case of COM module these lines exist in function that intend to transmit */
    /** formulating I-PDU */
    uint8 distMsg[8];
    int i;
    for (i = 0; i < 8; i++)
    {
        distMsg[i] = ++x;
        if (x == 255)
            x = 0;
    }
    const PduInfoType distanceMsg = { .SduDataPtr = distMsg, .SduLength = 8 };

    /** query PDUR routing paths sources to find global pdu reference .
     inside COM module &Pdus[1] will be reference to related message .
     */
    PduIdType PduHandleId;

    if (PduR_INF_GetSourcePduHandleId(&Pdus[1], &PduHandleId) == E_OK)
    {
        PduR_ComTransmit(PduHandleId, &distanceMsg);
        //PduR_ComCancelTransmit( PduHandleId );
    }
}

void PduR_ComTransmit_Test2(void)
{
    /** in case of COM module these lines exist in function that intend to transmit */
    /** formulating I-PDU */
    uint8 distMsg[] = "ComMessage1234";
    const PduInfoType distanceMsg = { .SduDataPtr = distMsg, .SduLength =
                                              sizeof(distMsg)
                                                      / sizeof(distMsg[0]) };

    /** query PDUR routing paths sources to find global pdu reference .
     inside COM module &Pdus[3] will be reference to related message .
     */
    PduIdType PduHandleId;

    if (PduR_INF_GetSourcePduHandleId(&Pdus[3], &PduHandleId) == E_OK)
    {
        PduR_ComTransmit(PduHandleId, &distanceMsg);

        PduR_ComCancelTransmit(PduHandleId);
        PduR_ComChangeParameter(PduHandleId, TP_STMIN, 0);
        PduR_ComCancelReceive(PduHandleId);
    }
}

Std_ReturnType Com_TriggerTransmit_Test(PduIdType TxPduId,
                                        PduInfoType* PduInfoPtr)
{
    /**
     the upper layer module (called module) shall check whether the
     available data fits into the buffer size reported by PduInfoPtr->SduLength.
     If it fits, it shall copy its data into the buffer provided by PduInfoPtr ->SduDataPtr
     and update the length of the actual copied data in PduInfoPtr->SduLength.
     If not, it returns E_NOT_OK without changing PduInfoPtr.
     */
    ////printf("\nnow in Com Trigger Transmit\n");
    Std_ReturnType retVal = E_OK;
    uint8 distMsg[] = "1234Msg";  //Message to be transmitted
    if (sizeof(distMsg) / sizeof(distMsg[0]) < PduInfoPtr->SduLength)
    {
        if (!memcpy((void *) PduInfoPtr->SduDataPtr, (void *) distMsg,
                    sizeof(distMsg) / sizeof(distMsg[0])))
        {
            retVal = E_NOT_OK;
        }
        else
        {
            PduInfoPtr->SduLength = sizeof(distMsg) / sizeof(distMsg[0]);
        }
    }
    else
    {
        retVal = E_NOT_OK;
    }
    return retVal;
}

void Com_INF_Init(void)
{
    int delay =0;
    SYSCTL_RCGCGPIO_R |= 0x02; // port B
    delay = SYSCTL_RCGCGPIO_R;
    SYSCTL_RCGCCAN_R |= 0x01;
    delay = SYSCTL_RCGCCAN_R;
    GPIO_PORTB_LOCK_R |= 0x4C4F434B;
    GPIO_PORTB_CR_R |= 0x30;
    GPIO_PORTB_DIR_R |= 0x20;
    GPIO_PORTB_DIR_R &= ~0x10;
    GPIO_PORTB_DEN_R |= 0x30;
    GPIO_PORTB_AMSEL_R &= ~0x30;
    GPIO_PORTB_AFSEL_R |= 0x30;
    GPIO_PORTB_PCTL_R &= ~0x00FF0000;
    GPIO_PORTB_PCTL_R |= 0x00880000;

    Can_Init(&Confiobj);
    ///Initialization of router
    PduR_Init(&PBPduRConfig);
    ///Initialization of can interface
    CanIf_Init(&CanIf_Config);

    Can_DisableControllerInterrupts(0);
    ///Start controller 0
    CanIf_SetControllerMode(0, CAN_CS_STARTED);
    Can_EnableControllerInterrupts(0);

    ///Start channel 0
    CanIf_SetPduMode(0, CANIF_ONLINE);

}

void Com_RxIndication(PduIdType PduHandleId, const PduInfoType *PduInfoPtr)
{
    ////printf("now in Com Rx Indication & message received is %s\n", PduInfoPtr->SduDataPtr);
    ////printf("Can -> Com reception indication has finished\n");

}

void Com_TxConfirmation(PduIdType PduHandleId, Std_ReturnType result)
{
    ////printf("\nnow in Com TX confirmation\n");
    ////printf("Can -> Com confirmation has finished\n");
}

void Com_TpRxIndication(PduIdType PduHandleId, Std_ReturnType result)
{
    ////printf("now in Com Tp Rx Indication\n ");
    ////printf("router CANTP reception indication has finished\n");
}

void Com_TpTxConfirmation(PduIdType PduHandleId, Std_ReturnType result)
{
    ////printf("now in Com Tp TX confirmation\n");
    ////printf("router CANTP confirmation has finished\n");
}

Std_ReturnType Com_TriggerTransmit(PduIdType TxPduId, PduInfoType* PduInfoPtr)
{
    return Com_TriggerTransmit_Test(TxPduId, PduInfoPtr);
}

BufReq_ReturnType Com_StartOfReception(PduIdType id, const PduInfoType* info,
                                       PduLengthType TpSduLength,
                                       PduLengthType* bufferSizePtr)
{

    ////printf("now in Com start of reception\n");
    return BUFREQ_OK;
}

BufReq_ReturnType Com_CopyRxData(PduIdType id, const PduInfoType* info,
                                 PduLengthType* bufferSizePtr)
{

    ////printf("now in Com copy RX data\n");
    return BUFREQ_OK;
}

BufReq_ReturnType Com_CopyTxData(PduIdType id, const PduInfoType* info,
                                 RetryInfoType* retry,
                                 PduLengthType* availableDataPtr)
{

    ////printf("now in Com copy TX data\n");
    return BUFREQ_OK;
}

/**
 Description  : query global I-PDU reference in Com configuration .
 inputs       : Pdu            | Reference to global PDU .
 output       : DestPduId      | Identifier to local I-PDU .
 I/O          : None
 return value : Std_ReturnType | Determine if I-PDU is exist or not.
 */
Std_ReturnType Com_INF_GetPduHandleId(Pdu_Type *Pdu, PduIdType *PduHandleIdPtr)
{
    Std_ReturnType Std_Ret = E_NOT_OK;

    uint8 i;
    for (i = 0; i < ComConfiguration.ComMaxIPduCnt; i++)
    {
        if (ComConfiguration.ComIPdu[i].PduIdRef == Pdu)
        {
            Std_Ret = E_OK;
            *PduHandleIdPtr = ComConfiguration.ComIPdu[i].IPduHandleId;
        }
    }
    return Std_Ret;
}





#ifdef ECU2_ALGORITHMICNODE
#include "../rte/Ultrasonic_requests_rte.h"
#include "../rte/Ultrasonic_data_rte.h"
void Com_Main(void){  //insert into RTOS main thread
    uint8_t Ultrasonic_Trig_Requestes ;
    while(1){
        Ultrasonic_Trig_Requestes=Rte_Ultrasonic_requests_iread();
//configure Can ID => send requests set ID for send - receive can.c
// global pdu data configure  ==> PduR.c CanIF.c  HOH? (Ecuc.c)


    }
}


#endif


