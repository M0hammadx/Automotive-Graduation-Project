/**
 * \file	CanIf_Cfg.c
 *
 * \version ..
 *
 * \brief	Defining configuration of CanIf.
 *
 * \date 	..
 *
 * \author  MHmed Hatem
 *
 */

/** external files
#include "CanNm_Cfg.h"
#include "CanTp_Cfg.h"

//v stands for vendor
#include "Can_<vID>_<v Specific name>_Cfg.h"        //optional
#include "CanTrcv_<vID>_<v Specific name>_Cfg.h"    //optional
#include "Can_<vID>_<V specific name>.h"
#include "CanTrcv_<vID>_<V specific name>.h"
*/
#include "CanIf.h"
#include "Can_PbCfg.h"
#include "CanTrcv.h"

#include "PduR_CanIf.h"         ///INF
#include "PduR_Cfg.h"
#include "CanSM_Cbk.h"
#include "EcuC.h"               ///INF
#include "EcuM.h"               ///INF

//const CanIfHrhRangeCfgType CanIfHrhRangeCfg[] =
//{
//    {
//    /* ----------- Configuration Parameters ----------- */
//        .CanIfHrhRangeBaseId = ,
//        .CanIfHrhRangeMask = ,
//        .CanIfHrhRangeRxPduLowerCanId = ,
//        .CanIfHrhRangeRxPduRangeCanIdType = ,
//        .CanIfHrhRangeRxPduUpperCanId = ,
//    /* ------------- Included Containers ------------- */
//    },
//};

 CanIfCtrlCfgType CanIfCtrlCfg[] =
{
    {
    /* ----------- Configuration Parameters ----------- */
        .CanIfCtrlId = CANIF_INF_CAN_DRIVER_0_CONTROLER_0,
        .CanIfCtrlWakeupSupport = FALSE,
        .CanIfCtrlCanCtrlRef = NULL,          ///Symbolic name reference to CanController

    /* ------------- Included Containers ------------- */
    },
};

const CanIfHrhCfgType CanIfHrhCfg[] =
{
    {
    /* ----------- Configuration Parameters ----------- */
        .CanIfHrhSoftwareFilter = FALSE,
        .CanIfHrhCanCtrlIdRef = &CanIfCtrlCfg[0],
        .CanIfHrhIdSymRef = CAN_INF_HARDWARE_OBJECT_REF_1,         ///CanHardwareObjectType

    /* ------------- Included Containers ------------- */
        .CanIfHrhRangeCfg = NULL,

    },
    {
    /* ----------- Configuration Parameters ----------- */
        .CanIfHrhSoftwareFilter = FALSE,
        .CanIfHrhCanCtrlIdRef = &CanIfCtrlCfg[0],
        .CanIfHrhIdSymRef = CAN_INF_HARDWARE_OBJECT_REF_2,         ///CanHardwareObjectType

    /* ------------- Included Containers ------------- */
        .CanIfHrhRangeCfg = NULL,

    },
};

const CanIfHthCfgType CanIfHthCfg[] =
{
    {
    /* ----------- Configuration Parameters ----------- */
        .CanIfHthCanCtrlIdRef = &CanIfCtrlCfg[0],
        .CanIfHthIdSymRef = CAN_INF_HARDWARE_OBJECT_REF_0,           ///CanHardwareObject

    /* ------------- Included Containers ------------- */
    },
};

//const CanIfRxPduCanIdRangeType CanIfRxPduCanIdRange =
//{
///* ----------- Configuration Parameters ----------- */
//    .CanIfRxPduCanIdRangeLowerCanId = ,
//    .CanIfRxPduCanIdRangeUpperCanId = ,
//
///* ------------- Included Containers ------------- */
//};

#if (CANIF_INF_CAN_TRCV_SUPPORT == STD_ON)
const CanIfTrcvCfgType CanIfTrcvCfg[] =
{
    {
    /* ----------- Configuration Parameters ----------- */
        .CanIfTrcvId = CANIF_INF_CAN_TRCV_DRIVER_0_TRANSCEIVER_0,
        .CanIfTrcvWakeupSupport = FALSE,
        .CanIfTrcvCanTrcvRef = NULL,      ///Symbolic name reference to CanTrcvChannel

    /* ------------- Included Containers ------------- */
    },
};
#endif

 const CanIfBufferCfgType CanIfBufferCfg[] =
{
    {
    /* ----------- Configuration Parameters ----------- */
        .CanIfBufferSize = 0,
        .CanIfBufferHthRef = &CanIfHthCfg[0],

    /* ------------- Included Containers ------------- */

    },
};

const CanIfInitHohCfgType CanIfInitHohCfg[] =
{
    {
    /* ----------- Configuration Parameters ----------- */

    /* ------------- Included Containers ------------- */
        .CanIfHrhCfg = &CanIfHrhCfg[0],
        .CanIfHrhCfg = &CanIfHrhCfg[1],
        .CanIfHthCfg = &CanIfHthCfg[0],
    },
};

const CanIfRxPduCfgType CanIfRxPduCfg[] =
{
    {
    /* ----------- Configuration Parameters ----------- */
        .CanIfRxPduCanId = CANIF_INF_RX_PDU_0_CAN_ID,
        .CanIfRxPduCanIdMask = 0x7FF,   ///STANDARD_CAN;
        .CanIfRxPduCanIdType = STANDARD_CAN,
        .CanIfRxPduDataLength = 8,    //0 .. 64
        .CanIfRxPduId = CANIF_INF_RX_PDU_0,
        .CanIfRxPduReadData = FALSE,
        .CanIfRxPduReadNotifyStatus = FALSE,
        .CanIfRxPduUserRxIndicationName = PduR_CanIfRxIndication,
        .CanIf_INF_GetPduHandleIdName = (CanIf_INF_GetPduHandleIdNameType)PduR_INF_GetSourcePduHandleId,
        .CanIfRxPduUserRxIndicationUL = PDUR,
        .CanIfRxPduHrhIdRef = &CanIfHrhCfg[0],
        .CanIfRxPduRef = &Pdus[0],

    /* ------------- Included Containers ------------- */
        .CanIfRxPduCanIdRange = NULL,
    },
    {
    /* ----------- Configuration Parameters ----------- */
        .CanIfRxPduCanId = CANIF_INF_RX_PDU_0_CAN_ID,
        .CanIfRxPduCanIdMask = 0x7FF,   ///STANDARD_CAN;
        .CanIfRxPduCanIdType = STANDARD_CAN,
        .CanIfRxPduDataLength = 8,    //0 .. 64
        .CanIfRxPduId = CANIF_INF_RX_PDU_0,
        .CanIfRxPduReadData = FALSE,
        .CanIfRxPduReadNotifyStatus = FALSE,
        .CanIfRxPduUserRxIndicationName = PduR_CanIfRxIndication,
        .CanIf_INF_GetPduHandleIdName = (CanIf_INF_GetPduHandleIdNameType)PduR_INF_GetSourcePduHandleId,
        .CanIfRxPduUserRxIndicationUL = PDUR,
        .CanIfRxPduHrhIdRef = &CanIfHrhCfg[1],
        .CanIfRxPduRef = &Pdus[6],

    /* ------------- Included Containers ------------- */
        .CanIfRxPduCanIdRange = NULL,
    },
};

const CanIfTxPduCfgType CanIfTxPduCfg[] =
{
    {
    /* ----------- Configuration Parameters ----------- */
        .CanIfTxPduCanId = CANIF_INF_TX_PDU_0_CAN_ID,
        .CanIfTxPduCanIdMask = 0x7FF,   ///STANDARD_CAN
        .CanIfTxPduCanIdType = STANDARD_CAN,
        .CanIfTxPduId = CANIF_INF_TX_PDU_0,
        .CanIfTxPduPnFilterPdu = FALSE,
        .CanIfTxPduReadNotifyStatus = FALSE,
        .CanIfTxPduTriggerTransmit = TRUE,
        .CanIfTxPduType = STATIC,
        .CanIfTxPduUserTriggerTransmitName = PduR_CanIfTriggerTransmit,
        .CanIfTxPduUserTxConfirmationName = PduR_CanIfTxConfirmation,
        .CanIf_INF_GetPduHandleIdName = (CanIf_INF_GetPduHandleIdNameType)PduR_INF_GetDestPduHandleId,
        .CanIfTxPduUserTxConfirmationUL = PDUR,
        .CanIfTxPduBufferRef = &CanIfBufferCfg[0],
        .CanIfTxPduRef = &Pdus[1],

    /* ------------- Included Containers ------------- */
    },
};

#if (CANIF_INF_CAN_TRCV_SUPPORT == STD_ON)
const CanIfTrcvDrvCfgType CanIfTrcvDrvCfg[] =
{
    {
    /* ----------- Configuration Parameters ----------- */

    /* ------------- Included Containers ------------- */
        .CanIfTrcvCfg = CanIfTrcvCfg,
    },
};
#endif

const CanIfPublicCfgType CanIfPublicCfg =
{
/* ----------- Configuration Parameters ----------- */
    .CanIfDevErrorDetect                 = FALSE,
    .CanIfMetaDataSupport                = FALSE,
    .CanIfPublicCancelTransmitSupport    = FALSE,
    .CanIfPublicCddHeaderFile            = NULL,
    .CanIfPublicHandleTypeEnum           = UINT16,
    .CanIfPublicIcomSupport              = CANIF_PUBLIC_ICOM_SUPPORT,
    .CanIfPublicMultipleDrvSupport       = FALSE,
    .CanIfPublicPnSupport                = CANIF_PUBLIC_PN_SUPPORT,
    .CanIfPublicReadRxPduDataApi         = CANIF_PUBLIC_READRXPDU_DATA_API,
    .CanIfPublicReadRxPduNotifyStatusApi = CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API,
    .CanIfPublicReadTxPduNotifyStatusApi = CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API,
    .CanIfPublicSetDynamicTxIdApi        = CANIF_PUBLIC_SETDYNAMICTXID_API,
    .CanIfPublicTxBuffering              = FALSE,
    .CanIfPublicTxConfirmPollingSupport  = CANIF_INF_PUBLIC_TX_CONFIRMATION_POLLING_SUPPORT,
    .CanIfPublicWakeupCheckValidByNM     = FALSE,
    .CanIfPublicWakeupCheckValidSupport  = CANIF_PUBLIC_WAKEUP_CHECK_VALIDATION_SUPPORT,
    .CanIfSetBaudrateApi                 = CANIF_SET_BAUDRATE_API,
    .CanIfTriggerTransmitSupport         = FALSE,
    .CanIfTxOfflineActiveSupport         = FALSE,
    .CanIfVersionInfoApi                 = FALSE,
    .CanIfWakeupSupport                  = CANIF_INF_WAKEUP_SUPPORT,

/* ------------- Included Containers ------------- */
};

const CanIfPrivateCfgType CanIfPrivateCfg =
{
/* ----------- Configuration Parameters ----------- */
    .CanIfFixedBuffer               = FALSE,
    .CanIfPrivateDataLengthCheck    = CANIF_INF_PRIVATE_DATA_LENGTH_CHECK,
    .CanIfPrivateSoftwareFilterType = BINARY,
    .CanIfSupportTTCAN              = FALSE,

/* ------------- Included Containers ------------- */

};

const CanIfDispatchCfgType CanIfDispatchCfg =
{
/* ----------- Configuration Parameters ----------- */
    .CanIfDispatchUserCheckTrcvWakeFlagIndicationName = CanSM_CheckTransceiverWakeFlagIndication,
    .CanIfDispatchUserCheckTrcvWakeFlagIndicationUL = CAN_SM,
    .CanIfDispatchUserClearTrcvWufFlagIndicationName = CanSM_ClearTrcvWufFlagIndication,
    .CanIfDispatchUserClearTrcvWufFlagIndicationUL = CAN_SM,
    .CanIfDispatchUserConfirmPnAvailabilityName = CanSM_ConfirmPnAvailability,
    .CanIfDispatchUserConfirmPnAvailabilityUL = CAN_SM,
    .CanIfDispatchUserCtrlBusOffName = CanSM_ControllerBusOff,
    .CanIfDispatchUserCtrlBusOffUL = CAN_SM,
    .CanIfDispatchUserCtrlModeIndicationName = CanSM_ControllerModeIndication,
    .CanIfDispatchUserCtrlModeIndicationUL = CAN_SM,
    .CanIfDispatchUserTrcvModeIndicationName = CanSM_TransceiverModeIndication,
    .CanIfDispatchUserTrcvModeIndicationUL = CAN_SM,
    .CanIfDispatchUserValidateWakeupEventName = EcuM_CheckValidation,
    .CanIfDispatchUserValidateWakeupEventUL = ECUM,

/* ------------- Included Containers ------------- */
};

const CanIfCtrlDrvCfgType CanIfCtrlDrvCfg[] =
{
    {
    /* ----------- Configuration Parameters ----------- */
        .CanIfCtrlDrvInitHohConfigRef = &CanIfInitHohCfg[0],
        .CanIfCtrlDrvNameRef          = NULL,          ///Reference to CanGeneral

    /* ------------- Included Containers ------------- */
        .CanIfCtrlCfg = CanIfCtrlCfg,

    },
};

const CanIfInitCfgType CanIfInitCfg =
{
/* ----------- Configuration Parameters ----------- */
    .CanIfInitCfgSet    = NULL,
    .CanIfMaxBufferSize = 0,
    .CanIfMaxRxPduCfg   = CANIF_INF_RX_CNT,
    .CanIfMaxTxPduCfg   = CANIF_INF_TX_CNT,

/* ------------- Included Containers ------------- */
    .CanIfBufferCfg     = CanIfBufferCfg,
    .CanIfInitHohCfg    = CanIfInitHohCfg,
    .CanIfRxPduCfg      = CanIfRxPduCfg,
    .CanIfTxPduCfg      = CanIfTxPduCfg,

};

const CanIf_ConfigType CanIf_Config =
{
    .CanIfPrivateCfg  = &CanIfPrivateCfg,
    .CanIfPublicCfg   = &CanIfPublicCfg,
    .CanIfInitCfg     = &CanIfInitCfg,
    .CanIfDispatchCfg = &CanIfDispatchCfg,
    .CanIfCtrlDrvCfg  = CanIfCtrlDrvCfg,
    .CanIfTrcvDrvCfg  =
#if (CANIF_INF_CAN_TRCV_SUPPORT == STD_ON)
                        CanIfTrcvDrvCfg,
#else
                        NULL,
#endif
};
