/**
 * \file	CanIf.c
 *
 * \version ..
 *
 * \brief	Contain functions implementation and internal global variable declaration of canIf
 *
 * \date 	..
 *
 * \author  MHmed Hatem
 *
 */

/* -------------------------------------------------------------------------- */
/*                             Include Files                                  */
/* -------------------------------------------------------------------------- */
#include "CanIf.h"
#include "CanIf_Cbk.h"

///Can headers
#include "Can.h"
#include "CanTrcv.h"

#include "EcuM.h"
#include "EcuC.h"
#include "CanSM_Cbk.h"

/** other external files
#include "Dem.h"
#include "Det.h"            //Optional
#include "MemMap.h"

#include "<Module>_CanIf.h"
#include "<Module>_Cbk.h"
#include "<Module>.h"       //Target PDU Ids
*/

/* -------------------------------------------------------------------------- */
/*                            Global Variables                                */
/* -------------------------------------------------------------------------- */
/**
pointer to a structure of this type to get access to its configuration data, which
is necessary for initialization.
*/
static const CanIf_ConfigType *CanIf_ConfigPtr;

///Hold PDU mode corresponding to controller
static CanIf_PduModeType CanIf_PduMode[CANIF_INF_CAN_DRIVER_0_CONTROLER_CNT];

/* -------------------------------------------------------------------------- */
/*                          Function Definitions                              */
/* -------------------------------------------------------------------------- */
/**
    Description  : this initialize internal and external interfaces of the CAN
                   Interface for the further processing .
                   shall initialize the global variables and data structures
                   of the CanIf including flags and buffers.
    inputs       : ConfigPtr | Pointer to post build configuration parameters .
    outputs      : None
    I/O          : None
    return value : None
*/
void CanIf_Init( const CanIf_ConfigType *ConfigPtr )
{
    /** When function CanIf_Init() is called, CanIf shall initialize
        every Transmit L-PDU Buffer assigned to CanIf.
    */
    if(ConfigPtr != NULL){
        CanIf_ConfigPtr = ConfigPtr;
    }else{
        ///Report error
    }
    uint8 i;
    for( i=0; i<CANIF_INF_CAN_DRIVER_0_CONTROLER_CNT; i++){
        CanIf_SetPduMode(i, CANIF_OFFLINE);
    }
}

/**
    Description  : De-initializes the CanIf module.
                   has to be sure there are no on-going transmissions/receptions,
                    nor any pending transmission confirmations.
    inputs       : None
    outputs      : None
    I/O          : None
    return value : None
*/
void CanIf_DeInit(void)
{
    if(CanIf_ConfigPtr){
        CanIf_ConfigPtr = NULL;
    }else{
        ///report an error
    }
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

    uint32 i;
    for ( i=0 ; i<CanIf_ConfigPtr->CanIfInitCfg->CanIfMaxTxPduCfg ; ++i ){
        if (CanIf_ConfigPtr->CanIfInitCfg->CanIfTxPduCfg[i].CanIfTxPduRef == Pdu){
            Std_Ret = E_OK;
            *PduHandleIdPtr = CanIf_ConfigPtr->CanIfInitCfg->CanIfTxPduCfg[i].CanIfTxPduId;
        }
    }
    return Std_Ret;
}

/**
    Description  : calls the corresponding CAN Driver service for changing of the CAN controller mode.
    inputs       : ControllerId   | is assigned to a CAN controller,
                                    which is requested for mode transition.
                   ControllerMode | Requested mode transition
    outputs      : None
    I/O          : None
    return value : Std_ReturnType | E_OK: Controller mode request has been accepted
                                    E_NOT_OK: Controller mode request has not been accepted
*/
Std_ReturnType CanIf_SetControllerMode( uint8 ControllerId, Can_ControllerStateType ControllerMode )
{
    /**
        - call Can_SetControllerMode(Controller, Transition) for the requested CAN controller.
        - If parameter ControllerId of has an invalid value, report development error
            code CANIF_E_PARAM_CONTROLLERID to the Det_ReportError service of the DET module .
        - If parameter ControllerMode of has an invalid value (not CAN_CS_STARTED,
            CAN_CS_SLEEP or CAN_CS_STOPPED), report development error code CANIF_E_PARAM_CTRLMODE
            to the Det_ReportError service of the DET module .
        - The CAN Driver module must be initialized after Power ON.
        - The CAN Interface module must be initialized after Power ON.
    */
//    for(uint8 i=0; i<CANIF_CAN_DRIVER_CNT; i++){
//        if(ControllerId <= CanIf_ConfigPtr->CanIfCtrlDrvCfg[i].CanIfMaxCtrlId_INF &&
//            ControllerId >= CanIf_ConfigPtr->CanIfCtrlDrvCfg[i].CanIfMinCtrlId_INF){
//            CanIf_INF_CanSetControllerMode(CanIf_ConfigPtr->CanIfCtrlDrvCfg[i].CanIfCtrlCfg[])
//        }
//    }
    /** assuming we use only one can driver thus canIf controller id
        the same as can controller id .
    */
    Std_ReturnType retVal = E_OK;
    if(ControllerId >= CANIF_INF_CAN_DRIVER_0_CONTROLER_CNT){
        ///report development error code CANIF_E_PARAM_CONTROLLERID
        retVal =  E_NOT_OK;
    }else{
        switch(ControllerMode){
        case CAN_CS_STARTED:
            retVal =  (Std_ReturnType)Can_SetControllerMode(ControllerId, ControllerMode);
            break;
        case CAN_CS_SLEEP:
        case CAN_CS_STOPPED:
            if(Can_SetControllerMode(ControllerId, ControllerMode) == E_OK){
                CanIf_SetPduMode(ControllerId, CANIF_OFFLINE);
                retVal = E_OK;
            }else{
                retVal = E_NOT_OK;
            }
            break;
        default:
            ///report development error code CANIF_E_PARAM_CONTROLLERID to the Det_ReportError service
            break;
        }
    }
    return retVal;

}

/**
    Description  : calls the corresponding CAN Driver service for obtaining
                   the current status of the CAN controller.
    inputs       : ControllerId      | is assigned to a CAN controller,
                                       which is requested for current operation mode .
    outputs      : ControllerModePtr | Pointer to a memory location, where the current
                                       mode of the CAN controller will be stored.
    I/O          : None
    return value : Std_ReturnType    | E_OK    : Controller mode request has been accepted.
                                       E_NOT_OK: Controller mode request has not been accepted.
*/
Std_ReturnType CanIf_GetControllerMode( uint8 ControllerId, Can_ControllerStateType *ControllerModePtr )
{
    /**
        - If parameter ControllerId of has an invalid value, report development error
            code CANIF_E_PARAM_CONTROLLERID to the Det_ReportError service of the DET module .
        - If parameter ControllerModePtr of has an invalid value,report development error
            code CANIF_E_PARAM_POINTER to the Det_ReportError service of the DET module .
        - The CAN Driver module must be initialized after Power ON.
        - The CAN Interface module must be initialized after Power ON.
    */
    if(ControllerId >= CANIF_INF_CAN_DRIVER_0_CONTROLER_CNT){
        ///report development error code CANIF_E_PARAM_CONTROLLERID
        return E_NOT_OK;
    }
    if(ControllerModePtr == NULL){
        ///report development error code CANIF_E_PARAM_POINTER to the Det
        return E_NOT_OK;
    }
    return Can_GetControllerMode(ControllerId, ControllerModePtr);
}

/**
    Description  : calls the corresponding CAN Driver service for obtaining the
                   error state of the CAN controller.
    inputs       : ControllerId   | is assigned to a CAN controller, which is requested for ErrorState.
    outputs      : ErrorStatePtr  | Pointer to a memory location, where the error state
                                    of the CAN controller will be stored.
    I/O          : None
    return value : Std_ReturnType | E_OK: Error state request has been accepted.
                                    E_NOT_OK: Error state request has not been accepted.
*/
Std_ReturnType CanIf_GetControllerErrorState( uint8 ControllerId, Can_ErrorStateType *ErrorStatePtr )
{
    /**
        - If parameter ControllerId of has an invalid value, report development error
            code CANIF_E_PARAM_CONTROLLERID to the Det_ReportError service of the DET module .
        - If parameter ErrorStatePtr is a null pointer, report development error code
            CANIF_E_PARAM_POINTER to the Det_ReportError service .
    */
    if(ControllerId >= CANIF_INF_CAN_DRIVER_0_CONTROLER_CNT){
        ///report development error code CANIF_E_PARAM_CONTROLLERID
        return E_NOT_OK;
    }
    if(ErrorStatePtr == NULL){
        ///report development error code CANIF_E_PARAM_POINTER to the Det
        return E_NOT_OK;
    }
    return Can_GetControllerErrorState(ControllerId, ErrorStatePtr);
}

/**
    Description  : Called within CanIf_Transmit function to get PDU configuration corresponding to TxPduId
    inputs       : TxPduId           | Identifier of the PDU
    outputs      : None
    I/O          : None
    return value : CanIfTxPduCfgType | Pointer to PDU configuration parameters
*/
#if ( CANIF_INF_RUNTIME_PDU_CONFIGURATION == STD_OFF)
static const CanIfTxPduCfgType * CanIf_INF_FindTxPduCfg(PduIdType TxPduId)
#else
static CanIfTxPduCfgType * CanIf_INF_FindTxPduCfg(PduIdType TxPduId)
#endif
{
	if (TxPduId >= CanIf_ConfigPtr->CanIfInitCfg->CanIfMaxTxPduCfg) {
		return NULL;
	} else {
		return  (const CanIfTxPduCfgType *)(&CanIf_ConfigPtr->CanIfInitCfg->CanIfTxPduCfg[TxPduId]);
	}
}

/**
    Description  : Requests transmission of a PDU.
    inputs       : TxPduId        | Identifier of the PDU to be transmitted
                   PduInfoPtr     | Length of and pointer to the PDU data and pointer to MetaData.
    outputs      : None
    I/O          : None
    return value : Std_ReturnType | E_OK: Transmit request has been accepted.
                                    E_NOT_OK: Transmit request has not been accepted.
*/
Std_ReturnType CanIf_Transmit( PduIdType TxPduId, const PduInfoType* PduInfoPtr )
{
    /**
        - Note: The corresponding CAN Controller and HTH have to be resolved by the Tx-PduId.
        - The service CanIf_Transmit() shall not accept a trans-mit request,
          if the controller mode referenced by ControllerId is different to CAN_CS_STARTED and
          the channel mode at least for the transmit path is not online or offline active.
        * (TxPduId) refers to (CanID, HTH/HRH of the CAN Con-troller)
        * the PduInfoPtr which specifies length and data pointer of the Transmit Request
        - the corresponding CanDrv and call the function Can_Write(Hth,* PduInfo)
        - PduInfoPtr is a pointer to a L-SDU user memory, CAN Identifier, L-SDU han-dle and Data Length
        -

    */
    const CanIfTxPduCfgType *TxPduCfgPtr;
    Can_PduType canPdu;
    Can_ControllerStateType ControllerState;
    CanIf_PduModeType PduMode;
    uint8 CtrlId;


    TxPduCfgPtr = CanIf_INF_FindTxPduCfg(TxPduId);
    if (TxPduCfgPtr == NULL)
    {
        ///Report an error CANIF_E_INVALID_TXPDUID to the Det_ReportError
        return E_NOT_OK;
    }

    CtrlId = TxPduCfgPtr->CanIfTxPduBufferRef->CanIfBufferHthRef->CanIfHthCanCtrlIdRef->CanIfCtrlId;
    if (CanIf_GetControllerMode( CtrlId, &ControllerState) == E_NOT_OK ){
        ///Report an error
        return E_NOT_OK;
    }
    if (ControllerState != CAN_CS_STARTED){
        ///Report an error
        return E_NOT_OK;
    }
    if (CanIf_GetPduMode( CtrlId, &PduMode) == E_NOT_OK ){
        ///Report an error
        return E_NOT_OK;
    }
    if ( !(PduMode == CANIF_ONLINE
#if (CANIF_INF_TX_OFFLINE_ACTIVE_SUPPORT == STD_ON)
           || PduMode == CANIF_TX_OFFLINE_ACTIVE
#endif
                                                  ) )
    {
        ///Clear the corresponding CanIf transmit buffers
        ///Report an error
        return E_NOT_OK;
    }
#if (CANIF_INF_TX_OFFLINE_ACTIVE_SUPPORT == STD_ON)
    if (PduMode == CANIF_TX_OFFLINE_ACTIVE){
        CanIf_TxConfirmation( TxPduId );
        return E_OK;
    }
#endif
    if (PduInfoPtr == NULL)
    {
        ///Report an error CANIF_E_PARAM_POINTER to the Det_ReportError
        return E_NOT_OK;
    }
    if (PduInfoPtr->SduDataPtr == NULL && TxPduCfgPtr->CanIfTxPduTriggerTransmit == STD_OFF)
    {
        ///Report an error
        return E_NOT_OK;
    }

    CanIfTxPduCanIdTypeType CanIdType = TxPduCfgPtr->CanIfTxPduCanIdType;
    if (PduInfoPtr->SduLength > 8 && (CanIdType == STANDARD_CAN || CanIdType == EXTENDED_CAN)){
        ///Report an error CANIF_E_DATA_LENGTH_MISMATCH to the Det_ReportError
        ///shall transmit as much data as possible and discard the rest.
        canPdu.length = 8;
    }
    else if (PduInfoPtr->SduLength > 64){
        ///Report an error CANIF_E_DATA_LENGTH_MISMATCH to the Det_ReportError
        ///shall transmit as much data as possible and discard the rest.
        canPdu.length = 64;
    }else{
        canPdu.length = PduInfoPtr->SduLength;
    }
    canPdu.id = TxPduCfgPtr->CanIfTxPduCanId & TxPduCfgPtr->CanIfTxPduCanIdMask;
    switch (CanIdType){
    case STANDARD_CAN:
        canPdu.id |= 0x00000000;
        break;
    case STANDARD_FD_CAN:
        canPdu.id |= 0x40000000;
        break;
    case EXTENDED_CAN:
        canPdu.id |= 0x80000000;
        break;
    case EXTENDED_FD_CAN:
        canPdu.id |= 0xC0000000;
        break;
    default :
        ///Report error
        break;
    }

    canPdu.sdu = PduInfoPtr->SduDataPtr;
    canPdu.swPduHandle = TxPduId;
    Can_ReturnType retVal = Can_Write(TxPduCfgPtr->CanIfTxPduBufferRef->CanIfBufferHthRef->CanIfHthIdSymRef->CanObjectId, &canPdu);
    if (retVal == E_NOT_OK){
        ///Report error
        return E_NOT_OK;
    }else if (retVal == CAN_BUSY){
        ///TX buffering , Not supported yet
        return E_NOT_OK;
    }
    return E_OK;
}

/**
    Description  : Requests cancellation of an ongoing transmission of a PDU in a lower layer
    inputs       : TxPduId        | Identification of the PDU to be cancelled.
    outputs      : None
    I/O          : None
    return value : Std_ReturnType | E_OK: Cancellation was executed successfully
                                    E_NOT_OK: Cancellation was rejected
*/
#if (CANIF_PUBLIC_CANCEL_TRANSMIT_SUPPORT == STD_ON)
Std_ReturnType CanIf_CancelTransmit( PduIdType TxPduId )
{
    ///Dummy
    return E_NOT_OK;
}
#endif

/**
    Description  : provides the Data Length and the received data of
                   the requested CanIfRxSduId to the calling upper layer.
    inputs       : CanIfRxSduId   | specifying the corresponding CAN L-SDU ID, CAN Driver, CAN controller .
    outputs      : CanIfRxInfoPtr | Contains the length, pointer to a buffer, MetaData related to this PDU.
    I/O          : None
    return value : Std_ReturnType | E_OK: Request for L-SDU data has been accepted
                                    E_NOT_OK: No valid data has been received
*/
#if (CANIF_PUBLIC_READRXPDU_DATA_API == STD_ON)
Std_ReturnType CanIf_ReadRxPduData( PduIdType CanIfRxSduId, PduInfoType* CanIfRxInfoPtr )
{
//    const CanIfRxPduCfgType *RxPduCfgPtr;
//    Can_ControllerStateType ControllerState;
//    CanIf_PduModeType PduMode;
//    uint8 CtrlId;
//
//    RxPduCfgPtr = CanIf_INF_FindRxPduCfg(CanIfRxSduId);
//    if (RxPduCfgPtr == NULL){
//        ///Report an error CANIF_E_INVALID_RXPDUID to the Det_ReportError
//        return E_NOT_OK;
//    }
//    if (RxPduCfgPtr->CanIfRxPduReadData == FALSE){
//        ///Report an error CANIF_E_INVALID_RXPDUID to the Det_ReportError
//        return E_NOT_OK;
//    }
//    if (CanIfRxInfoPtr == NULL || CanIfRxInfoPtr->SduDataPtr == NULL){
//        ///Report develop-ment error code CANIF_E_PARAM_POINTER to the Det_ReportError
//        return E_NOT_OK;
//    }
//    CtrlId = RxPduCfgPtr->CanIfRxPduHrhIdRef->CanIfHrhCanCtrlIdRef->CanIfCtrlId;
//    if (CanIf_GetControllerMode( CtrlId, &ControllerState) == E_NOT_OK ){
//        ///Report an error
//        return E_NOT_OK;
//    }
//    if (ControllerState != CAN_CS_STARTED){
//        ///Report an error
//        return E_NOT_OK;
//    }
//    if( CanIf_GetPduMode( Mailbox->ControllerId, &PduMode ) == E_NOT_OK ){
//        ///Report an error
//        return E_NOT_OK;
//    }
//    if( !(PduMode == CANIF_TX_OFFLINE || PduMode == CANIF_ONLINE) ){
//        ///Report an error
//        return E_NOT_OK;
//    }
    ///Retrieve recently received Sdu message corresponding to CanIfRxSduId from it buffer.
    ///incomplete
    return E_NOT_OK;
}
#endif

///**
//    Description  : None
//    inputs       : None
//    outputs      : None
//    I/O          : None
//    return value : None
//*/
//#if (CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API == STD_ON)
//CanIf_NotifStatusType CanIf_ReadTxNotifStatus( PduIdType CanIfTxSduId ){
// Not implemented
//}
//#endif
//
///**
//    Description  : None
//    inputs       : None
//    outputs      : None
//    I/O          : None
//    return value : None
//*/
//#if (CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON)
//CanIf_NotifStatusType CanIf_ReadRxNotifStatus( PduIdType CanIfRxSduId ){
// Not implemented
//}
//#endif

/**
    Description  : sets the requested mode at the L-PDUs of a predefined logical PDU channel.
    inputs       : ControllerId   | Identifier assigned to a physical CAN controller are addressed.
                   PduModeRequest | Requested PDU mode change
    outputs      : None
    I/O          : None
    return value : Std_ReturnType | E_OK: Request for mode transition has been accepted.
                                    E_NOT_OK: Request for mode transition has not been accepted.
*/
Std_ReturnType CanIf_SetPduMode( uint8 ControllerId, CanIf_PduModeType PduModeRequest )
{
    Can_ControllerStateType ControllerState;

    if(ControllerId >= CANIF_INF_CAN_DRIVER_0_CONTROLER_CNT){
        ///report development error code CANIF_E_PARAM_CONTROLLERID
        return E_NOT_OK;
    }

    if(!(PduModeRequest == CANIF_OFFLINE           ||
         PduModeRequest == CANIF_TX_OFFLINE        ||
#if (CANIF_INF_TX_OFFLINE_ACTIVE_SUPPORT == STD_ON)
         PduModeRequest == CANIF_TX_OFFLINE_ACTIVE ||
#endif
         PduModeRequest == CANIF_ONLINE) )
    {
        ///report development error code CANIF_E_PARAM_PDU_MODE to the Det
        return E_NOT_OK;
    }

    if (CanIf_GetControllerMode( ControllerId, &ControllerState) == E_NOT_OK ){
        ///Report an error
        return E_NOT_OK;
    }
    if (ControllerState != CAN_CS_STARTED){
        ///Report an error
        return E_NOT_OK;
    }

    CanIf_PduMode[ControllerId] = PduModeRequest;
    return E_OK;
}

/**
    Description  : reports the current mode of a requested PDU channel.
    inputs       : ControllerId   | All PDUs of the own ECU connected to the corresponding CanIf
                                    ControllerId, which is assigned to a physical CAN controller
                                    are addressed.
    outputs      : PduModePtr     | Pointer to a memory location, where the current
                                    mode of the logical PDU channel will be stored.
    I/O          : None
    return value : Std_ReturnType | E_OK: PDU mode request has been accepted
                                    E_NOT_OK: PDU mode request has not been accepted
*/
Std_ReturnType CanIf_GetPduMode( uint8 ControllerId, CanIf_PduModeType * PduModePtr )
{
    if(ControllerId >= CANIF_INF_CAN_DRIVER_0_CONTROLER_CNT){
        ///report development error code CANIF_E_PARAM_CONTROLLERID
        return E_NOT_OK;
    }
    if(PduModePtr == NULL){
        ///report development error code CANIF_E_PARAM_POINTER
        return E_NOT_OK;
    }
    *PduModePtr = CanIf_PduMode[ControllerId];
    return E_OK;
}

///**
//    Description  : None
//    inputs       : None
//    outputs      : None
//    I/O          : None
//    return value : None
//*/
//void CanIf_GetVersionInfo( Std_VersionInfoType* VersionInfo ){}
//
/**
    Description  : This service reconfigures the corresponding CAN identifier
                   of the requested CAN L-PDU.
    inputs       : CanIfTxSduId | L-SDU handle to be transmitted.
                   CanId        | Standard/Extended CAN ID of CAN L-SDU that shall be transmitted
                                  as FD or conventional CAN frame.
    outputs      : None
    I/O          : None
    return value : None
*/
#if ( CANIF_INF_RUNTIME_PDU_CONFIGURATION == STD_ON )
void CanIf_SetDynamicTxId( PduIdType CanIfTxSduId, Can_IdType CanId )
{
    CanIfTxPduCfgType *TxPduCfgPtr;

    if(CanIf_ConfigPtr == NULL){
        ///report an error
        return;
    }
    TxPduCfgPtr = CanIf_INF_FindTxPduCfg(CanIfTxSduId);
    if (TxPduCfgPtr == NULL)
    {
        ///Report an error CANIF_E_INVALID_TXPDUID to the Det_ReportError
        return;
    }
    if( TxPduCfgPtr->CanIfTxPduType == STATIC ){
        ///Report an error
        return;
    }
    if( ((CanId&0x3FFFFFFF) > 0) &&
        ((CanId&TxPduCfgPtr->CanIfTxPduCanIdMask) == 0) ){
        ///Report an error CANIF_E_PARAM_CANID to the Det_ReportError
        return;
    }
    CanIfTxPduCanIdTypeType Type = TxPduCfgPtr->CanIfTxPduCanIdType;
    if( ((CanId&0x80000000)    && !(Type == EXTENDED_CAN || Type == EXTENDED_FD_CAN)) ||
        ((!(CanId&0x80000000)) && !(Type == STANDARD_CAN || Type == STANDARD_FD_CAN)) )
    {
        ///Report an error CANIF_E_PARAM_CANID to the Det_ReportError
        return;
    }
    TxPduCfgPtr->CanIfTxPduCanId = CanId & TxPduCfgPtr->CanIfTxPduCanIdMask;
}
#endif

/**
    Description  : changes the operation mode of the tansceiver TransceiverId.
    inputs       : TransceiverId   | Abstracted CanIf TransceiverId, which is assigned to a CAN
                                     transceiver .
                   TransceiverMode | Requested mode transition .
    outputs      : None
    I/O          : None
    return value : Std_ReturnType  | E_OK: Transceiver mode request has been accepted.
                                     E_NOT_OK: Transceiver mode request has not been accepted.
*/
Std_ReturnType CanIf_SetTrcvMode( uint8 TransceiverId, CanTrcv_TrcvModeType TransceiverMode )
{
    /**
        - TransceiverId Abstracted CanIf TransceiverId, which is assigned to a CAN transceiver,
          which is requested for mode transition TransceiverMode Requested mode transition
        - CanTrcv_SetOpMode(Transceiver, OpMode)
        -
    */
        /** assuming we use only one can driver thus canIf controller id
        the same as can controller id .
    */
#if (CANIF_INF_CAN_TRCV_SUPPORT == STD_ON)
    if(TransceiverId >= CANIF_INF_CAN_TRCV_DRIVER_0_TRANSCEIVER_CNT){
        ///report development error code CANIF_E_PARAM_TRCV
        return E_NOT_OK;
    }
    if( !(TransceiverMode == CANTRCV_TRCVMODE_NORMAL  ||
          TransceiverMode == CANTRCV_TRCVMODE_STANDBY ||
          TransceiverMode == CANTRCV_TRCVMODE_SLEEP) )
    {
        ///report development error code CANIF_E_PARAM_TRCVMODE
        return E_NOT_OK;
    }
    return CanTrcv_SetOpMode(TransceiverId, TransceiverMode);
#else
    return E_NOT_OK;
#endif
}

/**
    Description  : Get mode of can transciver.
    inputs       : TransceiverId      | Abstracted CanIf TransceiverId.
    outputs      : TransceiverModePtr | Requested mode of requested network the Transceiver.
    I/O          : None
    return value : Std_ReturnType     | E_OK: Transceiver mode request has been accepted.
                                        E_NOT_OK: Transceiver mode request has not been accepted.
*/
Std_ReturnType CanIf_GetTrcvMode( uint8 TransceiverId, CanTrcv_TrcvModeType * TransceiverModePtr )
{
#if (CANIF_INF_CAN_TRCV_SUPPORT == STD_ON)
    if( TransceiverId >= CANIF_INF_CAN_TRCV_DRIVER_0_TRANSCEIVER_CNT ){
        ///report development error code CANIF_E_PARAM_TRCV
        return E_NOT_OK;
    }
    if( TransceiverModePtr == NULL){
        ///report development error code CANIF_E_PARAM_POINTER
        return E_NOT_OK;
    }
    return CanTrcv_GetOpMode(TransceiverId, TransceiverModePtr);
#else
    return E_NOT_OK;
#endif
}

/**
    Description  : Get reason for the wake up of the transceiver.
    inputs       : TransceiverId   | Abstracted CanIf TransceiverId.
    outputs      : TrcvWuReasonPtr | provided pointer to where the requested transceiver
                                     wake up reason shall be returned
    I/O          : None
    return value : Std_ReturnType  | E_OK: Transceiver wake up reason request has been accepted.
                                     E_NOT_OK: Transceiver wake up reason request has not been accepted.
*/
Std_ReturnType CanIf_GetTrcvWakeupReason( uint8 TransceiverId, CanTrcv_TrcvWakeupReasonType * TrcvWuReasonPtr )
{
#if (CANIF_INF_CAN_TRCV_SUPPORT == STD_ON)
    if( TransceiverId >= CANIF_INF_CAN_TRCV_DRIVER_0_TRANSCEIVER_CNT ){
        ///report development error code CANIF_E_PARAM_TRCV
        return E_NOT_OK;
    }
    if( TrcvWuReasonPtr == NULL){
        ///report development error code CANIF_E_PARAM_POINTER
        return E_NOT_OK;
    }
    return CanTrcv_GetBusWuReason(TransceiverId, TrcvWuReasonPtr);
#else
    return E_NOT_OK;
#endif
}

/**
    Description  : Set can transceiver wakeup mode .
    inputs       : TransceiverId  | Abstracted CanIf TransceiverId.
                   TrcvWakeupMode | Requested transceiver wake up notification mode.
    outputs      : None
    I/O          : None
    return value : Std_ReturnType | E_OK: If the wake up notifications state has been changed.
                                    E_NOT_OK: If the wake up notifications state change has failed or
                                              the parameter is out of the allowed range.
*/
Std_ReturnType CanIf_SetTrcvWakeupMode( uint8 TransceiverId, CanTrcv_TrcvWakeupModeType TrcvWakeupMode )
{
#if (CANIF_INF_CAN_TRCV_SUPPORT == STD_ON)
    if( TransceiverId >= CANIF_INF_CAN_TRCV_DRIVER_0_TRANSCEIVER_CNT ){
        ///report development error code CANIF_E_PARAM_TRCV
        return E_NOT_OK;
    }
    if( !(TrcvWakeupMode == CANTRCV_WUMODE_ENABLE  ||
          TrcvWakeupMode == CANTRCV_WUMODE_DISABLE ||
          TrcvWakeupMode == CANTRCV_WUMODE_CLEAR) )
    {
        ///report development error code CANIF_E_PARAM_TRCVWAKEUPMODE
    }
    return CanTrcv_SetWakeupMode(TransceiverId, TrcvWakeupMode);
#else
    return E_NOT_OK;
#endif
}

/**
    Description  : Checks whether an underlying CAN driver or a CAN
                   transceiver driver already signals a wakeup event.
    inputs       : WakeupSource   | Source device, which initiated the wake up event:
                                    CAN controller or CAN transceiver
    outputs      : None
    I/O          : None
    return value : Std_ReturnType | E_OK: If the check wake up request has been accepted.
                                    E_NOT_OK: If the check wake up request has not been accepted.
*/
#if (CANIF_INF_WAKEUP_SUPPORT == STD_ON)
Std_ReturnType CanIf_CheckWakeup( EcuM_WakeupSourceType WakeupSource )
{
    if( CanIf_ConfigPtr == NULL ){
        return E_NOT_OK;
    }
    CanTrcv_CheckWakeFlag( WakeupSource );
    return E_OK;
}
#endif

/**
    Description  : Validate a previous wakeup event.
    inputs       : WakeupSource   | Source device which initiated the wakeup event.
    outputs      : None
    I/O          : None
    return value : Std_ReturnType | E_OK: If the check validation request has been accepted.
                                    E_NOT_OK: If the check validation request has not been accepted.
*/
#if (CANIF_PUBLIC_WAKEUP_CHECK_VALIDATION_SUPPORT == STD_ON)
Std_ReturnType CanIf_CheckValidation( EcuM_WakeupSourceType WakeupSource )
{
    if( CanIf_ConfigPtr == NULL ){
        return E_NOT_OK;
    }
    (CanIf_ConfigPtr->CanIfDispatchCfg->CanIfDispatchUserValidateWakeupEventName)(WakeupSource);
    return E_OK;
}
#endif

/**
    Description  : Reports if any TX confirmation has been done for the whole CAN controller since
                            the last CAN controller start.
    inputs       : ControllerId | Abstracted CanIf ControllerId which is assigned to a CAN controller
    outputs      : None
    I/O          : None
    return value : CanIf_NotifStatusType | Combined TX confirmation status for all TX PDUs of the CAN controller
*/
#if ( CANIF_INF_PUBLIC_TX_CONFIRMATION_POLLING_SUPPORT == STD_ON )
CanIf_NotifStatusType CanIf_GetTxConfirmationState( uint8 ControllerId )
{
    ///Not implemented
    return CANIF_TX_RX_NOTIFICATION;
}
#endif

/**
    Description  : Requests the CanIf module to clear the WUF flag of the designated CAN transceiver.
    inputs       : TransceiverId  | Abstract CanIf TransceiverId, which is assigned to
                                    the designated CAN transceiver.
    outputs      : None
    I/O          : None
    return value : Std_ReturnType | E_OK: Request has been accepted
                                    E_NOT_OK: Request has not been accepted
*/
#if (CANIF_INF_CAN_TRCV_SUPPORT == STD_ON && CANIF_PUBLIC_PN_SUPPORT == STD_ON)
Std_ReturnType CanIf_ClearTrcvWufFlag( uint8 TransceiverId )
{
    if( TransceiverId >= CANIF_INF_CAN_TRCV_DRIVER_0_TRANSCEIVER_CNT ){
        ///report development error code CANIF_E_PARAM_TRCV
        return E_NOT_OK;
    }
    if( CanIf_ConfigPtr == NULL ){
        return E_NOT_OK;
    }
    return CanTrcv_ClearTrcvWufFlag(TransceiverId);
}
#endif

/**
    Description  : Requests the CanIf module to check the Wake flag of the designated CAN transceiver.
    inputs       : TransceiverId  | Abstract CanIf TransceiverId, which is assigned to
                                    the designated CAN transceiver.
    outputs      : None
    I/O          : None
    return value : Std_ReturnType | E_OK: Request has been accepted
                                    E_NOT_OK: Request has not been accepted
*/
#if (CANIF_INF_CAN_TRCV_SUPPORT == STD_ON && CANIF_PUBLIC_PN_SUPPORT == STD_ON)
Std_ReturnType CanIf_CheckTrcvWakeFlag( uint8 TransceiverId )
{
    if( TransceiverId >= CANIF_INF_CAN_TRCV_DRIVER_0_TRANSCEIVER_CNT ){
        ///report development error code CANIF_E_PARAM_TRCV
        return E_NOT_OK;
    }
    return CanTrcv_CheckWakeFlag(TransceiverId);
}
#endif

/**
    Description  : Set the baud rate configuration of the CAN controller.
    inputs       : ControllerId     | Abstract CanIf ControllerId which is assigned to a
                                      CAN controller, whose baud rate shall be set.
                   BaudRateConfigID | references a baud rate configuration by ID.
    outputs      : None
    I/O          : None
    return value : Std_ReturnType   | E_OK: Service request accepted, setting of (new) baud rate started
                                      E_NOT_OK: Service request not accepted
*/
#if(CANIF_SET_BAUDRATE_API == STD_ON)
Std_ReturnType CanIf_SetBaudrate( uint8 ControllerId, uint16 BaudRateConfigID )
{
    if(ControllerId >= CANIF_INF_CAN_DRIVER_0_CONTROLER_CNT){
        ///report development error code CANIF_E_PARAM_CONTROLLERID
        return E_NOT_OK;
    }
    return Can_SetBaudrate(ControllerId, BaudRateConfigID);
}
#endif

/**
    Description  : Change the Icom Configuration of a CAN controller to the requested one.
    inputs       : ControllerId    | Abstracted CanIf Controller Id which is assigned to a CAN controller.
                   ConfigurationId | Requested Configuration
    outputs      : None
    I/O          : None
    return value : Std_ReturnType  | E_OK: Request accepted
                                     E_NOT_OK: Request denied
*/
#if(CANIF_PUBLIC_ICOM_SUPPORT == STD_ON)
Std_ReturnType CanIf_SetIcomConfiguration( uint8 ControllerId, IcomConfigIdType ConfigurationId )
{
    if(ControllerId >= CANIF_INF_CAN_DRIVER_0_CONTROLER_CNT){
        ///report development error code CANIF_E_PARAM_CONTROLLERID
        return E_NOT_OK;
    }
    return Can_SetIcomConfiguration(ControllerId, ConfigurationId);
}
#endif

///Callbacks
/**
    Description  : API used by upper layer module (called module) shall copy its data
                   into the buffer provided by PduInfoPtr->SduDataPtr .
    inputs       : TxPduId    | ID of the SDU that is requested to be transmitted.
    outputs      : PduInfoPtr | Contains a pointer to a buffer to where data shall be copied,
                                and the available buffer size in SduLengh.
    I/O          : None
    return value : Std_ReturnType | E_OK: SDU has been copied .
                                    E_NOT_OK: No SDU data has been copied.
*/
Std_ReturnType CanIf_TriggerTransmit( PduIdType TxPduId, PduInfoType * PduInfoPtr ){
    /**
        - and SduLength indicates the number of copied bytes.
    */
    const CanIfTxPduCfgType *TxPduCfgPtr;

    TxPduCfgPtr = CanIf_INF_FindTxPduCfg(TxPduId);
    if (TxPduCfgPtr == NULL)
    {
        ///Report an error CANIF_E_INVALID_TXPDUID to the Det_ReportError
        return E_NOT_OK;
    }
    if ( TxPduCfgPtr->CanIfTxPduTriggerTransmit == STD_OFF ||
         TxPduCfgPtr->CanIfTxPduUserTriggerTransmitName == NULL ||
         TxPduCfgPtr->CanIf_INF_GetPduHandleIdName == NULL )
    {
        ///Report an error
        return E_NOT_OK;
    }
    /// TxPduId variable will be changed to pdu id inside user configuration parameters using global pdu
    if ( ((TxPduCfgPtr->CanIf_INF_GetPduHandleIdName)(TxPduCfgPtr->CanIfTxPduRef, &TxPduId)) == E_NOT_OK )
    {
        ///Report an error
        return E_NOT_OK;    ///this pdu does not exist in user configuration
    }
    return ((TxPduCfgPtr->CanIfTxPduUserTriggerTransmitName)( TxPduId, PduInfoPtr ));
}

/**
    Description  : This service confirms a previously successfully processed
                   transmission of a CAN TxPDU.
    inputs       : CanTxPduId | L-PDU handle of CAN L-PDU successfully transmitted.
                                This ID specifies the corresponding CAN L-PDU ID.
    outputs      : None
    I/O          : None
    return value : None
*/
void CanIf_TxConfirmation( PduIdType CanTxPduId )
{
    const CanIfTxPduCfgType *TxPduCfgPtr;
    CanIf_PduModeType PduMode = CANIF_OFFLINE;
    uint8 CtrlId;

    TxPduCfgPtr = CanIf_INF_FindTxPduCfg(CanTxPduId);
    if (TxPduCfgPtr == NULL)
    {
        ///Report an error CANIF_E_PARAM_LPDU to the Det_ReportError
        return;
    }

#if (CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON)
    if ( TxPduCfgPtr->CanIfTxPduReadNotifyStatus == STD_ON )
    {
        ///Set the notification status for the Transmitted L-PDU .
        ///Buffering the status
        ///Not implemented yet
    }
#endif

    if ( TxPduCfgPtr->CanIfTxPduUserTxConfirmationName == NULL ||
         TxPduCfgPtr->CanIf_INF_GetPduHandleIdName == NULL )
    {
        ///Report an error
        return;
    }

    CtrlId = TxPduCfgPtr->CanIfTxPduBufferRef->CanIfBufferHthRef->CanIfHthCanCtrlIdRef->CanIfCtrlId;
    if ( CanIf_GetPduMode( CtrlId, &PduMode ) == E_NOT_OK ){
        ///Report an error
        return;

    }
    if ( !(PduMode == CANIF_ONLINE
#if (CANIF_INF_TX_OFFLINE_ACTIVE_SUPPORT == STD_ON)
                     || PduMode == CANIF_TX_OFFLINE_ACTIVE
#endif
                                                           ) )
    {
        ///Report an error
        return;
    }

    /// CanTxPduId variable will be changed to pdu id inside user configuration parameters using global pdu
    if ( ((TxPduCfgPtr->CanIf_INF_GetPduHandleIdName)(TxPduCfgPtr->CanIfTxPduRef, &CanTxPduId)) == E_NOT_OK )
    {
        ///Report an error
        return;    ///this pdu does not exist in user configuration
    }

    (TxPduCfgPtr->CanIfTxPduUserTxConfirmationName)( CanTxPduId, E_OK );
}

/**
    Description  : Called within CanIf_RxIndication function to get PDU configuration corresponding to Hoh
    inputs       : Hoh               | Identifier of the PDU
    outputs      : None
    I/O          : None
    return value : CanIfRxPduCfgType | Pointer to PDU configuration parameters
*/
#if ( CANIF_INF_RUNTIME_PDU_CONFIGURATION == STD_OFF )
static const CanIfRxPduCfgType * CanIf_INF_FindRxPduCfg(Can_HwHandleType Hoh)
#else
static CanIfRxPduCfgType * CanIf_INF_FindRxPduCfg(Can_HwHandleType Hoh)
#endif
{
    uint32 i;
    for ( i = 0 ; i != CanIf_ConfigPtr->CanIfInitCfg->CanIfMaxRxPduCfg ; ++i){
        if (Hoh == CanIf_ConfigPtr->CanIfInitCfg->CanIfRxPduCfg[i].CanIfRxPduHrhIdRef->
            CanIfHrhIdSymRef->CanObjectId)
        {
            return ( const CanIfRxPduCfgType *)(&CanIf_ConfigPtr->CanIfInitCfg->CanIfRxPduCfg[i]);
        }
    }
    return NULL;
}

/**
    Description  : Indicates a successful reception of a received CAN Rx L-PDU to the CanIf
                   after passing all filters and validation checks .
    inputs       : Mailbox    | Identifies the HRH and its corresponding CAN Controller
                   PduInfoPtr | Pointer to the received L-PDU
    outputs      : None
    I/O          : None
    return value : None
*/
void CanIf_RxIndication( const Can_HwType *Mailbox, const PduInfoType *PduInfoPtr )
{
    const CanIfRxPduCfgType *RxPduCfgPtr;
    CanIf_PduModeType PduMode;
    PduIdType RxPduId;

    if( Mailbox == NULL || PduInfoPtr == NULL ){
        ///Report an error CANIF_E_PARAM_POINTER to the Det_ReportError
        return;
    }
    /** assuming we use only one can driver thus canIf controller id
        the same as can controller id .
    */
    if( Mailbox->ControllerId >= CANIF_INF_CAN_DRIVER_0_CONTROLER_CNT){
        ///report an error
        return;
    }
    if( CanIf_GetPduMode( Mailbox->ControllerId, &PduMode ) == E_NOT_OK ){
        ///Report an error
        return;
    }
    if( !(PduMode == CANIF_TX_OFFLINE || PduMode == CANIF_ONLINE) ){
        ///Report an error
        return;
    }
    RxPduCfgPtr = CanIf_INF_FindRxPduCfg(Mailbox->Hoh);
    if( RxPduCfgPtr == NULL ){
        ///report development error code CANIF_E_PARAM_HOH to the Det
        return;
    }
#if (CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API == STD_ON)
    if ( RxPduCfgPtr->CanIfRxPduReadNotifyStatus == STD_ON )
    {
        ///Set the notification status for the Received L-PDU .
        ///Not implemented yet
    }
#endif
    if ( RxPduCfgPtr->CanIfRxPduUserRxIndicationName == NULL ||
         RxPduCfgPtr->CanIf_INF_GetPduHandleIdName   == NULL )
    {
        ///Report an error
        return;
    }
#if (CANIF_INF_PRIVATE_DATA_LENGTH_CHECK == STD_ON)
    ///Data Length Check
    if ( PduInfoPtr->SduLength != RxPduCfgPtr->CanIfRxPduDataLength ){
        ///report development error code CANIF_E_INVALID_DATA_LENGTH to the Det
        return;
    }
#endif
    /// RxPduId variable will be set to pdu id inside user configuration parameters using global pdu
    if ( ((RxPduCfgPtr->CanIf_INF_GetPduHandleIdName)(RxPduCfgPtr->CanIfRxPduRef, &RxPduId)) == E_NOT_OK )
    {
        ///Report an error
        return;    ///this PDU does not exist in user configuration
    }

    (RxPduCfgPtr->CanIfRxPduUserRxIndicationName)( RxPduId, PduInfoPtr );
}

/**
    Description  : Indicates a Controller BusOff event referring to the corresponding CAN Controller
    inputs       : ControllerId | Abstract CanIf ControllerId which is assigned to a CAN controller,
                                  where a BusOff occurred .
    outputs      : None
    I/O          : None
    return value : None
*/
void CanIf_ControllerBusOff( uint8 ControllerId )
{
    /**
        - called by can driver & implemented by can interface .
        - CanIf shall set the PDU channel mode of the corresponding channel to CANIF_TX_OFFLINE.
        - The BusOff notification is implicitly suppressed in case of CANIF_OFFLINE and
            CANIF_TX_OFFLINE due to the fact, that no L-PDUs can be transmitted and thus
            the CAN Controller is not able to go in BusOff mode by newly requested L-PDUs
            for transmission.
        -
    */
    CanIf_PduModeType PduMode;
    /** assuming we use only one can driver thus canIf controller id
        the same as can controller id .
    */
    if(ControllerId >= CANIF_INF_CAN_DRIVER_0_CONTROLER_CNT){
        ///report development error code CANIF_E_PARAM_CONTROLLER
        return;
    }
    if(CanIf_ConfigPtr == NULL){
        ///report an error
        return;
    }
    if( CanIf_GetPduMode( ControllerId, &PduMode ) == E_NOT_OK ){
        ///Report an error
        return;
    }
    if( PduMode == CANIF_TX_OFFLINE || PduMode == CANIF_OFFLINE ){
        /// The BusOff notification is implicitly suppressed.
        return;
    }
    if( CanIf_ConfigPtr->CanIfDispatchCfg->CanIfDispatchUserCtrlBusOffName == NULL){
        /// Report an error
        return;
    }
    (CanIf_ConfigPtr->CanIfDispatchCfg->CanIfDispatchUserCtrlBusOffName)(ControllerId);
}

/**
    Description  : Indicates that the transceiver is running in PN communication mode referring to
                   the corresponding CAN transceiver with the abstract CanIf TransceiverId.
    inputs       : TransceiverId | Abstract CanIf TransceiverId, which is assigned to a
                                   CAN transceiver, which was checked for PN availability.
    outputs      : None
    I/O          : None
    return value : None
*/
#if (CANIF_PUBLIC_PN_SUPPORT == STD_ON)
void CanIf_ConfirmPnAvailability( uint8 TransceiverId )
{
    if( TransceiverId >= CANIF_INF_CAN_TRCV_DRIVER_0_TRANSCEIVER_CNT ){
        ///report development error code CANIF_E_PARAM_TRCV
        return;
    }
    if( CanIf_ConfigPtr == NULL ){
        ///Report an error
        return;
    }
    if( CanIf_ConfigPtr->CanIfDispatchCfg->CanIfDispatchUserConfirmPnAvailabilityName == NULL){
        ///Report an error
        return;
    }
    (CanIf_ConfigPtr->CanIfDispatchCfg->CanIfDispatchUserConfirmPnAvailabilityName)(TransceiverId);
}
#endif

/**
    Description  : Indicates that the CAN transceiver has cleared the WufFlag.
    inputs       : TransceiverId | Abstracted CanIf TransceiverId, for which this function was called.
    outputs      : None
    I/O          : None
    return value : None
*/
#if (CANIF_PUBLIC_PN_SUPPORT == STD_ON)
void CanIf_ClearTrcvWufFlagIndication( uint8 TransceiverId )
{
    if( TransceiverId >= CANIF_INF_CAN_TRCV_DRIVER_0_TRANSCEIVER_CNT ){
        ///report development error code CANIF_E_PARAM_TRCV
        return;
    }
    if( CanIf_ConfigPtr == NULL ){
        ///Report an error
        return;
    }
    if( CanIf_ConfigPtr->CanIfDispatchCfg->CanIfDispatchUserClearTrcvWufFlagIndicationName == NULL){
        ///Report an error
        return;
    }
    (CanIf_ConfigPtr->CanIfDispatchCfg->CanIfDispatchUserClearTrcvWufFlagIndicationName)(TransceiverId);
}
#endif

/**
    Description  : Indicates that the wake up flag in the CAN transceiver is set.
    inputs       : Abstracted | CanIf TransceiverId, for which this func-tion was called.
    outputs      : None
    I/O          : None
    return value : None
*/
#if (CANIF_PUBLIC_PN_SUPPORT == STD_ON)
void CanIf_CheckTrcvWakeFlagIndication( uint8 TransceiverId )
{
    if( TransceiverId >= CANIF_INF_CAN_TRCV_DRIVER_0_TRANSCEIVER_CNT ){
        ///report development error code CANIF_E_PARAM_TRCV
        return;
    }
    if( CanIf_ConfigPtr == NULL ){
        ///Report an error
        return;
    }
    if( CanIf_ConfigPtr->CanIfDispatchCfg->CanIfDispatchUserCheckTrcvWakeFlagIndicationName == NULL){
        ///Report an error
        return;
    }
    (CanIf_ConfigPtr->CanIfDispatchCfg->CanIfDispatchUserCheckTrcvWakeFlagIndicationName)(TransceiverId);
}
#endif

/**
    Description  : Indicates a controller state transition referring to the corresponding CAN controller.
    inputs       : ControllerId   | Abstract CanIf ControllerId which is assigned to a CAN controller,
                                    which state has been transitioned.
                   ControllerMode | Mode to which the CAN controller transitioned
    outputs      : None
    I/O          : None
    return value : None
*/
void CanIf_ControllerModeIndication( uint8 ControllerId, Can_ControllerStateType ControllerMode )
{
    /** assuming we use only one can driver thus canIf controller id
        the same as can controller id .
    */
    if(ControllerId >= CANIF_INF_CAN_DRIVER_0_CONTROLER_CNT){
        ///report development error code CANIF_E_PARAM_CONTROLLER
        return;
    }
    if(CanIf_ConfigPtr == NULL){
        ///report an error
        return;
    }
    if( CanIf_ConfigPtr->CanIfDispatchCfg->CanIfDispatchUserCtrlModeIndicationName == NULL ){
        ///report an error
        return;
    }
    (CanIf_ConfigPtr->CanIfDispatchCfg->CanIfDispatchUserCtrlModeIndicationName)(ControllerId, ControllerMode);
}

/**
    Description  : Indicates a transceiver state transition referring to the corresponding CAN transceiver.
    inputs       : TransceiverId   | Abstract CanIf TransceiverId, which is assigned to a CAN transceiver,
                                     which state has been transitioned.
                   TransceiverMode | Mode to which the CAN transceiver transitioned
    outputs      : None
    I/O          : None
    return value : None
*/
#if (CANIF_INF_CAN_TRCV_SUPPORT == STD_ON)
void CanIf_TrcvModeIndication( uint8 TransceiverId, CanTrcv_TrcvModeType TransceiverMode )
{
    /** assuming we use only one can transceiver driver thus canIf transceiver id
        the same as can transceiver id .
    */
    if( TransceiverId >= CANIF_INF_CAN_TRCV_DRIVER_0_TRANSCEIVER_CNT ){
        ///report development error code CANIF_E_PARAM_TRCV
        return;
    }
    if(CanIf_ConfigPtr == NULL){
        ///report an error
        return;
    }
    if( CanIf_ConfigPtr->CanIfDispatchCfg->CanIfDispatchUserTrcvModeIndicationName == NULL ){
        ///report an error
        return;
    }
    (CanIf_ConfigPtr->CanIfDispatchCfg->CanIfDispatchUserTrcvModeIndicationName)(TransceiverId, TransceiverMode);
}
#endif

/**
    Description  : Inform about the change of the Icom Configuration of a CAN controller.
    inputs       : ControllerId    | Abstract CanIf ControllerId which is assigned to a CAN controller,
                                     which informs about the Configuration Id.
                   ConfigurationId | Active Configuration Id.
                   Error           | ICOM_SWITCH_E_OK: No Error
                                     ICOM_SWITCH_E_FAILED: Switch to requested Configuration failed. Severe Error.
    outputs      : None
    I/O          : None
    return value : None
*/
#if(CANIF_PUBLIC_ICOM_SUPPORT == STD_ON)
void CanIf_CurrentIcomConfiguration( uint8 ControllerId, IcomConfigIdType ConfigurationId, IcomSwitch_ErrorType Error )
{
    /** assuming we use only one can driver thus canIf controller id
        the same as can controller id .
    */
    if(ControllerId >= CANIF_INF_CAN_DRIVER_0_CONTROLER_CNT){
        ///report development error code CANIF_E_PARAM_CONTROLLER
        return;
    }
    CanSM_CurrentIcomConfiguration( ControllerId, ConfigurationId, Error );
}
#endif

