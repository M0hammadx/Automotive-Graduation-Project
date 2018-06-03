/**
 * \file	CanIf_Types.h
 *
 * \version ..
 *
 * \brief	Type definitions for pre-compile and post build configuration.
 *
 * \date 	..
 *
 * \author  MHmed Hatem
 *
 */

#ifndef CANIF_TYPES_H_INCLUDED
#define CANIF_TYPES_H_INCLUDED

/* -------------------------------------------------------------------------- */
/*                             Include Files                                  */
/* -------------------------------------------------------------------------- */
#include "ComStack_Types.h"
#include "Can_GeneralTypes.h"
#include "EcuM_Types.h" ///not included in std CanIf_Types.h

/* -------------------------------------------------------------------------- */
/*                           Macros & Typedefs                                */
/* -------------------------------------------------------------------------- */
typedef void            (*CanIfRxPduUserRxIndicationNameType)   (PduIdType, const PduInfoType*);
typedef Std_ReturnType  (*CanIfTxPduUserTriggerTransmitNameType)(PduIdType, PduInfoType *);
typedef void            (*CanIfTxPduUserTxConfirmationNameType) (PduIdType, Std_ReturnType);
/**
    Description  : query global I-PDU reference in user configuration.
    inputs       : Pdu            | Reference to global PDU.
    output       : DestPduId      | Reference to identifier to local I-PDU .
    I/O          : None
    return value : Std_ReturnType | Determine if I-PDU is exist or not.
*/
typedef Std_ReturnType  (*CanIf_INF_GetPduHandleIdNameType) (void *, PduIdType *);
typedef struct CanIfCtrlCfg_t CanIfCtrlCfgType;
/* ------------- CanIfDispatchCfgType Typedefs ------------- */
typedef void (*CanIfDispatchUserCheckTrcvWakeFlagIndicationNameType)(uint8);
typedef void (*CanIfDispatchUserClearTrcvWufFlagIndicationNameType) (uint8);
typedef void (*CanIfDispatchUserConfirmPnAvailabilityNameType)      (uint8);
typedef void (*CanIfDispatchUserCtrlBusOffNameType)                 (uint8);
typedef void (*CanIfDispatchUserCtrlModeIndicationNameType)         (uint8, Can_ControllerStateType);
typedef void (*CanIfDispatchUserTrcvModeIndicationNameType)         (uint8, CanTrcv_TrcvModeType);
typedef void (*CanIfDispatchUserValidateWakeupEventNameType)        (EcuM_WakeupSourceType);
/* --------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/*                       Structures and Enumerations                          */
/* -------------------------------------------------------------------------- */
/**
    defines its transmit or receive activity.
    Communication direction (transmission and/or reception) of the channel can
    be controlled separately or together by upper layers
*/
typedef enum {
    /** Transmit and receive path of the corresponding channel
        are disabled => no communication mode */
    CANIF_OFFLINE=0,
    /** Transmit path is disabled. The receive path is enabled.*/
    CANIF_TX_OFFLINE,
    /** Transmit path is in offline active mode. The receive path
        is disabled. */
    CANIF_TX_OFFLINE_ACTIVE,
    /** Transmit and receive path are enabled */
    CANIF_ONLINE

}CanIf_PduModeType;

/**
    value of CAN L-PDU notification status.
*/
typedef enum {
    /** The requested Rx/Tx CAN L-PDU was successfully transmitted
        or received.*/
    CANIF_TX_RX_NOTIFICATION,
    /** No transmit or receive event occurred for the requested L-PDU */
    CANIF_NO_NOTIFICATION = 0

}CanIf_NotifStatusType;

/** CAN Identifier of receive CAN L-PDUs used by the CAN Driver for
    CAN L-PDU reception.
*/
typedef enum{
    /** CAN 2.0 or CAN FD frame with extended identifier (29 bits) */
    EXTENDED_CAN,
    /** CAN FD frame with extended identifier (29 bits) */
    EXTENDED_FD_CAN,
    /** CAN 2.0 frame with extended identifier (29 bits) */
    EXTENDED_NO_FD_CAN,
    /** CAN 2.0 or CAN FD frame with standard identifier (11 bits)*/
    STANDARD_CAN,
    /** CAN FD frame with standard identifier (11 bits)*/
    STANDARD_FD_CAN,
    /** CAN 2.0 frame with standard identifier (11 bits)*/
    STANDARD_NO_FD_CAN

}CanIfRxPduCanIdTypeType;

/* ------------- CanIfDispatchCfgType enumerations ------------- */
typedef enum{
    CAN_SM,             ///CAN State Manager
    _CDD                 ///Complex Driver
}CanIfDispatchUserCtrlBusOffULType;
typedef CanIfDispatchUserCtrlBusOffULType CanIfDispatchUserClearTrcvWufFlagIndicationULType;
typedef CanIfDispatchUserCtrlBusOffULType CanIfDispatchUserConfirmPnAvailabilityULType;
typedef CanIfDispatchUserCtrlBusOffULType CanIfDispatchUserCheckTrcvWakeFlagIndicationULType;
typedef CanIfDispatchUserCtrlBusOffULType CanIfDispatchUserCtrlModeIndicationULType;
typedef CanIfDispatchUserCtrlBusOffULType CanIfDispatchUserTrcvModeIndicationULType;

typedef enum{
    ECUM,                 ///ECU State Manager
    CDD_                  ///Complex Driver
}CanIfDispatchUserValidateWakeupEventULType;
/* ------------------------------------------------------------- */

/** Type of CAN Identifier of the transmit CAN L-PDU used by the CAN
    Driver module for CAN L-PDU transmission
*/
typedef CanIfRxPduCanIdTypeType CanIfTxPduCanIdTypeType;
//typedef enum {
//    EXTENDED_CAN,       ///CAN frame with extended identifier (29bits)
//    EXTENDED_FD_CAN,    ///CAN FD frame with extended identifier(29 bits)
//    STANDARD_CAN,       ///CAN frame with standard identifier (11bits)
//    STANDARD_FD_CAN     ///CAN FD frame with standard identifier(11 bits)
//
//}CanIfTxPduCanIdTypeType;

/** upper layer (UL) module to which the indication of the successfully received or
    confirmation of the successfully transmitted CANRXPDUID has to be routed
*/
typedef enum{
    CAN_NM,
    CAN_TP,
    CAN_TSYN,   ///Global Time Synchronization over CAN
    CDD,
    J1939NM,
    J1939TP,
    PDUR,
    XCP         ///Extended Calibration Protocol

}CanIfRxPduUserRxIndicationULType;
typedef CanIfRxPduUserRxIndicationULType CanIfTxPduUserTxConfirmationULType;
typedef CanIfRxPduUserRxIndicationULType CanIfTxPduUserTriggerTransmitULType_INF;

/** Defines the type of each transmit CAN L-PDU */
typedef enum{
    DYNAMIC,        ///CAN ID is defined at runtime.
    STATIC,         ///CAN ID is defined at compile-time.
}CanIfTxPduTypeType;

/** Specifies whether a configured Range of CAN Ids shall only consider
    standard CAN Ids or extended CAN Ids */
typedef enum{
    EXTENDED,       ///All the CANIDs are of type extended only (29 bit).
    STANDARD        ///All the CANIDs are of type standard only (11bit).
}CanIfHrhRangeRxPduRangeCanIdTypeType;

/** implemented software filtering methods */
typedef enum{
    BINARY,         ///Binary Filter method.
    INDEX,          ///Index Filter method.
    LINEAR,         ///Linear Filter method.
    TABLE,          ///Table Filter method.
}CanIfPrivateSoftwareFilterTypeType;

/** used to configure the Can_HwHandleType. For CAN hardware units with more than
    255 HW objects the extended range shall be used (UINT16) */
typedef enum{
    UINT16,
    UINT8
}CanIfPublicHandleTypeEnumType;

/* ------------- CanIfHrhCfgType Containers ------------- */
/**
    parameters required for configurating multiple CANID ranges for a given same HRH.
*/
typedef struct{
/* ----------- Configuration Parameters ----------- */
/** CAN Identifier used as base value in combination with CanIfHrhRangeMask for
    a masked ID range in which all CAN Ids shall pass the software filtering
*/
    uint32 CanIfHrhRangeBaseId;
/** Used as mask value in combination with CanIfHrhRangeBaseId for a
    masked ID range in which all CAN Ids shall pass the software filtering
*/
    uint32 CanIfHrhRangeMask;
/** Lower CAN Identifier of a receive CAN L-PDU for identifier range
    definition, in which all CAN Ids shall pass the software filtering
*/
    uint32 CanIfHrhRangeRxPduLowerCanId;
/** Specifies whether a configured Range of CAN Ids shall only consider
    standard CAN Ids or extended CAN Ids
*/
    CanIfHrhRangeRxPduRangeCanIdTypeType CanIfHrhRangeRxPduRangeCanIdType;
/** Upper CAN Identifier of a receive CAN L-PDU for identifier range
    definition, in which all CAN Ids shall pass the software filtering
*/
    uint32 CanIfHrhRangeRxPduUpperCanId;
/* ------------- Included Containers ------------- */

}CanIfHrhRangeCfgType;
/* ------------------------------------------------------ */


/* ------------- CanIfInitHohCfgType Containers ------------- */
/**
    contains configuration parameters for each hardware receive object (HRH)
*/
typedef struct{
/* ----------- Configuration Parameters ----------- */
/** True: Software filtering is enabled False: Software filtering is enabled */
    const boolean CanIfHrhSoftwareFilter;
/** Reference to controller Id to which the HRH belongs to.
    A controller can contain one or more HRHs
*/
#if (CANIF_INF_RUNTIME_PDU_CONFIGURATION == STD_OFF)
    const CanIfCtrlCfgType * CanIfHrhCanCtrlIdRef;
#else
    CanIfCtrlCfgType * CanIfHrhCanCtrlIdRef;
#endif
/** refers to a particular HRH object in the CanDrv configuration
    (see CanHardwareObject ECUC_Can_00324)
*/
#if (CANIF_INF_RUNTIME_PDU_CONFIGURATION == STD_OFF)
    const CanHardwareObjectType *CanIfHrhIdSymRef;         ///CanHardwareObjectType
#else
    CanHardwareObjectType *CanIfHrhIdSymRef;
#endif
/* ------------- Included Containers ------------- */
/** Defines the parameters required for configurating
    multiple CANID ranges for a given same HRH
*/
#if (CANIF_INF_RUNTIME_PDU_CONFIGURATION == STD_OFF)
    const CanIfHrhRangeCfgType *CanIfHrhRangeCfg;
#else
    CanIfHrhRangeCfgType *CanIfHrhRangeCfg;
#endif

}CanIfHrhCfgType;

/**
    container contains parameters related to each HTH
*/
typedef struct{
/* ----------- Configuration Parameters ----------- */
/** Reference to controller Id to which the HTH belongs to.
    A controller can contain one or more HTHs
*/
    CanIfCtrlCfgType *CanIfHthCanCtrlIdRef;
/**
    The parameter refers to a particular HTH object in the CanDrv
    configuration (see CanHardwareObject ECUC_Can_00324).
*/
    const CanHardwareObjectType *CanIfHthIdSymRef;           ///CanHardwareObject

/* ------------- Included Containers ------------- */

}CanIfHthCfgType;
/* ---------------------------------------------------------- */

/* ------------- CanIfRxPduCfgType Containers ------------- */
/**
    Optional container that allows to map a range of CAN Ids to one PduId
*/
typedef struct{
/* ----------- Configuration Parameters ----------- */
/** Lower CAN Identifier of a receive CAN L-PDU for identifier range
    definition, in which all CAN Ids are mapped to one PduId
*/
    uint32 CanIfRxPduCanIdRangeLowerCanId;
/** Upper CAN Identifier of a receive CAN L-PDU for identifier range
    definition, in which all CAN Ids are mapped to one PduId
*/
    uint32 CanIfRxPduCanIdRangeUpperCanId;

/* ------------- Included Containers ------------- */

}CanIfRxPduCanIdRangeType;
/* -------------------------------------------------------- */

/* ------------- CanIfCtrlDrvCfgType Containers ------------- */
/**
    configuration (parameters) of an addressed CAN controller
    by an underlying CAN Driver module.
*/
struct CanIfCtrlCfg_t{
/* ----------- Configuration Parameters ----------- */
/** This parameter abstracts from the CAN Driver specific parameter
    Controller. Each controller of all connected CAN Driver modules shall
    be assigned to one specific ControllerId of the CanIf
*/
    uint8 CanIfCtrlId;
/** defines if a respective controller is queriable for wake up events */
    boolean CanIfCtrlWakeupSupport;
/** References to the logical handle of CAN controller from the CAN Driver
    module. The following parameters of CanController config container
    shall be referenced by this link: CanControllerId, CanWakeupSourceRef
*/
    void *CanIfCtrlCanCtrlRef;          ///Symbolic name reference to CanController

/* ------------- Included Containers ------------- */

};
/* ---------------------------------------------------------- */

/* ------------- CanIfTrcvDrvCfgType Containers ------------- */
/**
    contains the configuration (parameters) of one addressed CAN
    transceiver by the underlying CAN Transceiver Driver module.
    For each CAN transceiver a seperate instance .
*/
typedef struct{
/* ----------- Configuration Parameters ----------- */
/** This parameter abstracts from the CAN Transceiver Driver specific
    parameter Transceiver. Each transceiver of all connected CAN
    Transceiver Driver modules shall be assigned to one specific
    TransceiverId of the CanIf */
    uint8 CanIfTrcvId;
/** defines if a respective transceiver of the referenced
    CAN Transceiver Driver modules is queriable for wake up events.
*/
    boolean CanIfTrcvWakeupSupport;
/** references to the logical handle of the underlying CAN transceiver */
    void *CanIfTrcvCanTrcvRef;      ///Symbolic name reference to CanTrcvChannel

/* ------------- Included Containers ------------- */

}CanIfTrcvCfgType;
/* ------------------------------------------------------- */

/* ------------- CanIfInitCfgType Containers ------------- */
/**
    Tx buffer configuration. Multiple buffers with different sizes could be configured
*/
typedef struct{
/* ----------- Configuration Parameters ----------- */
/** number of CanIf Tx L-PDUs which can be buffered in one Txbuffer */
    uint8 CanIfBufferSize;
/** Reference to CanIfHthCfg
    Reference to HTH, that defines the hardware object or the pool of
    hardware objects configured for transmission. All the CanIf Tx L-PDUs
    refer via the CanIfBufferCfg and this parameter to the HTHs if
    TxBuffering is enabled, or not
*/
#if (CANIF_INF_RUNTIME_PDU_CONFIGURATION == STD_OFF)
    const CanIfHthCfgType *CanIfBufferHthRef;
#else
    CanIfHthCfgType *CanIfBufferHthRef;
#endif

/* ------------- Included Containers ------------- */

}CanIfBufferCfgType;
/**
    references to the configuration setup of each underlying CAN Driver
*/
typedef struct{
/* ----------- Configuration Parameters ----------- */

/* ------------- Included Containers ------------- */
/** configuration parameters for each hardware receive object (HRH).*/
#if (CANIF_INF_RUNTIME_PDU_CONFIGURATION == STD_OFF)
    const CanIfHrhCfgType *CanIfHrhCfg;
#else
    CanIfHrhCfgType *CanIfHrhCfg;
#endif
/** contains parameters related to each HTH */
#if (CANIF_INF_RUNTIME_PDU_CONFIGURATION == STD_OFF)
    const CanIfHthCfgType *CanIfHthCfg;
#else
    CanIfHthCfgType *CanIfHthCfg;
#endif

}CanIfInitHohCfgType;

/**
     configuration (parameters) of each receive CAN L-PDU
*/
typedef struct{
/* ----------- Configuration Parameters ----------- */
/** CAN Identifier of Receive CAN L-PDUs used by the CAN Interface.
    Exa: Software Filtering. This parameter is used if exactly one Can
    Identifier is assigned to the Pdu.
*/
    uint32 CanIfRxPduCanId;
/** Identifier mask which denotes relevant bits in the CAN Identifier. This
    parameter defines a CAN Identifier range in an alternative way to
    CanIfRxPduCanIdRange. It identifies the bits of the configured CAN
    Identifier that must match the received CAN Identifier. Range: 11 bits
    for Standard CAN Identifier, 29 bits for Extended CAN Identifier.
*/
    uint32 CanIfRxPduCanIdMask;
/** CAN Identifier of receive CAN L-PDUs used by the CAN Driver for
    CAN L-PDU reception.
*/
    CanIfRxPduCanIdTypeType CanIfRxPduCanIdType;
/** Data length of the received CAN L-PDUs used by the CAN Interface.
    This information is used for Data Length Check.
*/
    uint8 CanIfRxPduDataLength;     //0 .. 64
/** ECU wide unique, symbolic handle for receive CAN L-SDU. It shall */
    const uint32 CanIfRxPduId;
/** Enables and disables the Rx buffering for reading of received L-SDU data */
    boolean CanIfRxPduReadData;
/** Enables and disables receive indication for each receive CAN L-SDU
    for reading its notification status.
*/
    boolean CanIfRxPduReadNotifyStatus;
/** This parameter defines the name of the <User_RxIndication> */
    CanIfRxPduUserRxIndicationNameType CanIfRxPduUserRxIndicationName;
/** This parameter defines the name of the <User_INF_GetPduHandleId> */
    CanIf_INF_GetPduHandleIdNameType CanIf_INF_GetPduHandleIdName;
/** upper layer (UL) module to which the indication of the successfully received
    CANRXPDUID has to be routed
*/
    const CanIfRxPduUserRxIndicationULType CanIfRxPduUserRxIndicationUL;
/** HRH to which Rx L-PDU belongs to, is referred through this parameter */
#if (CANIF_INF_RUNTIME_PDU_CONFIGURATION == STD_OFF)
    const CanIfHrhCfgType * CanIfRxPduHrhIdRef;
#else
    CanIfHrhCfgType * CanIfRxPduHrhIdRef;
#endif
/** Reference to the "global" Pdu structure to allow harmonization of
    handle IDs in the COM-Stack.
*/
    void *CanIfRxPduRef;

/* ------------- Included Containers ------------- */
/** Optional container that allows to map a range of CAN Ids to one PduId */
#if (CANIF_INF_RUNTIME_PDU_CONFIGURATION == STD_OFF)
    const CanIfRxPduCanIdRangeType *CanIfRxPduCanIdRange;
#else
    CanIfRxPduCanIdRangeType *CanIfRxPduCanIdRange;
#endif
/**  specified in the SWS TTCAN Interface and defines Frame trigger for TTCAN
    reception */
    //CanIfTTRxFrameTriggeringType *CanIfTTRxFrameTriggering;
}CanIfRxPduCfgType;

/**
    contains the configuration (parameters) of a transmit CAN L-PDU.
    It has to be configured as often as a transmit CAN L-PDU is needed.
*/
typedef struct{
/* ----------- Configuration Parameters ----------- */
/** CAN Identifier of transmit CAN L-PDUs used by the CAN Driver for
    CAN L-PDU transmission. Range: 11 Bit For Standard CAN Identifier
    ... 29 Bit For Extended CAN identifier
*/
    uint32 CanIfTxPduCanId;
/** Identifier mask which denotes relevant bits in the CAN Identifier */
    uint32 CanIfTxPduCanIdMask;
/** Type of CAN Identifier of the transmit CAN L-PDU used by the CAN
    Driver module for CAN L-PDU transmission
*/
    CanIfTxPduCanIdTypeType CanIfTxPduCanIdType;
/** ECU wide unique, symbolic handle for transmit CAN L-SDU */
    const uint32 CanIfTxPduId;
/** If CanIfPublicPnFilterSupport is enabled, by this parameter PDUs
    could be configured which will pass the CanIfPnFilter
*/
    boolean CanIfTxPduPnFilterPdu;
/** Enables and disables transmit confirmation for each transmit CAN
    L-SDU for reading its notification status
*/
    boolean CanIfTxPduReadNotifyStatus;
/** Determines if or if not CanIf shall use the trigger transmit API for this PDU */
    boolean CanIfTxPduTriggerTransmit;
/** Defines the type of each transmit CAN L-PDU */
    CanIfTxPduTypeType CanIfTxPduType;
/** This parameter defines the name of the <User_TriggerTransmit> */
    CanIfTxPduUserTriggerTransmitNameType const CanIfTxPduUserTriggerTransmitName;
/** This parameter defines the name of the <User_TxConfirmation> */
    CanIfTxPduUserTxConfirmationNameType const CanIfTxPduUserTxConfirmationName;
/** This parameter defines the name of the <User_INF_GetPduHandleId> */
    CanIf_INF_GetPduHandleIdNameType const CanIf_INF_GetPduHandleIdName;
/** confirmation of the successfully transmitted CANTXPDUID has to be
    routed via the <User_TxConfirmation>
*/
    const CanIfTxPduUserTxConfirmationULType CanIfTxPduUserTxConfirmationUL;
/** Configurable reference to a CanIf buffer configuration */
#if (CANIF_INF_RUNTIME_PDU_CONFIGURATION == STD_OFF)
    const CanIfBufferCfgType *CanIfTxPduBufferRef;
#else
    CanIfBufferCfgType *CanIfTxPduBufferRef;
#endif
/** Reference to the "global" Pdu structure to allow harmonization of
    handle IDs in the COM-Stack
*/
    void *CanIfTxPduRef;

/* ------------- Included Containers ------------- */
/** CanIfTTTxFrameTriggering is specified in the SWS TTCAN Interface and
    defines Frame trigger for TTCAN transmission */
    //CanIfTTTxFrameTriggeringType *CanIfTTTxFrameTriggering;

}CanIfTxPduCfgType;
/* ------------------------------------------------------- */

/* ------------- CanIf_ConfigType Containers ------------- */
/**
    configuration (parameters) of all addressed CAN transceivers
    by each underlying CAN Transceiver Driver module.
*/
typedef struct{
/* ----------- Configuration Parameters ----------- */

/* ------------- Included Containers ------------- */
/** List of CAN transceivers configuration parameters */
    const CanIfTrcvCfgType *CanIfTrcvCfg;

}CanIfTrcvDrvCfgType;

/** public configuration (parameters) of the CAN Interface */
typedef struct{
/* ----------- Configuration Parameters ----------- */
/** Switches the development error detection and notification on or off */
    boolean CanIfDevErrorDetect;
/** Enable support for dynamic ID handling using L-SDU MetaData */
    boolean CanIfMetaDataSupport;
/** enable/disable dummy API for upper layer modules which allows
    to request the cancellation of an I-PDU */
    boolean CanIfPublicCancelTransmitSupport;
/** Defines header files for callback functions which shall be included
    in case of CDDs */
    uint8 *CanIfPublicCddHeaderFile;
/** For CAN hardware units with more than 255 HW objects
    the extended range shall be used (UINT16) */
    CanIfPublicHandleTypeEnumType CanIfPublicHandleTypeEnum;
/** Selects support of Pretended Network features in CanIf */
    boolean CanIfPublicIcomSupport;
/** Selects support for multiple CAN Drivers */
    boolean CanIfPublicMultipleDrvSupport;
/** Selects support of Partial Network features in CanIf */
    boolean CanIfPublicPnSupport;
/** Enables / Disables the API CanIf_ReadRxPduData() for reading received L-SDU data */
    boolean CanIfPublicReadRxPduDataApi;
/** Enables and disables the API for reading the notification status of
    receive L-PDUs */
    boolean CanIfPublicReadRxPduNotifyStatusApi;
/** Enables and disables the API for reading the notification status of
    transmit L-PDUs */
    boolean CanIfPublicReadTxPduNotifyStatusApi;
/** Enables and disables the API for reconfiguration of the CAN Identifier
    for each Transmit L-PDU */
    boolean CanIfPublicSetDynamicTxIdApi;
/** Enables and disables the buffering of transmit L-PDUs (rejected by the
    CanDrv) within the CAN Interface module */
    boolean CanIfPublicTxBuffering;
/** enable/disable the API to poll for Tx Confirmation state */
    boolean CanIfPublicTxConfirmPollingSupport;
/** If enabled, only NM messages shall validate a detected wake-up event in CanIf.
    If disabled, all received messages corresponding to a configured Rx PDU shall
    validate such a wake-up event */
    boolean CanIfPublicWakeupCheckValidByNM;
/** Selects support for wake up validation */
    boolean CanIfPublicWakeupCheckValidSupport;
/** enable/disable the CanIf_SetBaudrate API to change the baud rate of a CAN Controller */
    boolean CanIfSetBaudrateApi;
/** Enables the CanIf_TriggerTransmit API at Pre-Compile-Time */
    boolean CanIfTriggerTransmitSupport;
/** Determines wether TxOffLineActive feature is supported by CanIf */
    boolean CanIfTxOfflineActiveSupport;
/** Enables and disables the API for reading the version information about the CAN Interface */
    boolean CanIfVersionInfoApi;
/** Enables the CanIf_CheckWakeup API at Pre-Compile-Time */
    boolean CanIfWakeupSupport;

/* ------------- Included Containers ------------- */

}CanIfPublicCfgType;


/** contains the private configuration (parameters) of the CAN Interface */
typedef struct{
/* ----------- Configuration Parameters ----------- */
/** defines if the buffer element length shall be fixed to 8
    Bytes for buffers to which only PDUs < 8 Bytes are assigned.
    TRUE: Minimum buffer element length is fixed to 8 Bytes.
    FALSE: Buffer element length depends on the size of the referencing PDUs.
*/
    boolean CanIfFixedBuffer;
/** Selects whether Data Length Check is supported */
    boolean CanIfPrivateDataLengthCheck;    ///True: Enabled False: Disabled
/** software filter mechanism for reception only */
    CanIfPrivateSoftwareFilterTypeType CanIfPrivateSoftwareFilterType;
/** Defines whether TTCAN is supported */
    boolean CanIfSupportTTCAN;

/* ------------- Included Containers ------------- */
/** CanIfTTGeneral is specified in the SWS TTCAN Interface */
    //CanIfTTGeneralType *CanIfTTGeneral;

}CanIfPrivateCfgType;

/**
    container contains the init parameters of the CAN Interface.
*/
typedef struct{
/* ----------- Configuration Parameters ----------- */
/** String 1–32
    CAN Interface specific configuration setup. This type of the
    external data structure shall contain the post build initialization data for
    the CAN Interface for all underlying CAN Drivers.
*/
#if (CANIF_INF_RUNTIME_PDU_CONFIGURATION == STD_OFF)
    const uint8 *CanIfInitCfgSet;
#else
    uint8 *CanIfInitCfgSet;
#endif
/** Total size of all Tx buffers */
    const uint32 CanIfMaxBufferSize;
/** Maximum number of Pdus. */
    const uint32 CanIfMaxRxPduCfg;
/** Maximum number of Pdus. */
    const uint32 CanIfMaxTxPduCfg;

/* ------------- Included Containers ------------- */
/**
    Tx buffer configuration. Multiple buffers with different sizes
    could be configured. If CanIfBufferSize equals 0, the CanIf
    Tx L-PDU only refers via this canIfBufferCfg the corresponding CanIfHthCfg.
*/
#if (CANIF_INF_RUNTIME_PDU_CONFIGURATION == STD_OFF)
    const CanIfBufferCfgType *CanIfBufferCfg;
#else
    CanIfBufferCfgType *CanIfBufferCfg;
#endif
/** contains the references to the config setup of each underlying CAN Driver */
    const CanIfInitHohCfgType *CanIfInitHohCfg;
/** configuration (parameters) of each receive CAN L-PDU */
#if (CANIF_INF_RUNTIME_PDU_CONFIGURATION == STD_OFF)
    const CanIfRxPduCfgType *CanIfRxPduCfg;
#else
    CanIfRxPduCfgType *CanIfRxPduCfg;
#endif
/** contains the configuration (parameters) of a transmit CAN L-PDU */
#if (CANIF_INF_RUNTIME_PDU_CONFIGURATION == STD_OFF)
    const CanIfTxPduCfgType *CanIfTxPduCfg;
#else
    CanIfTxPduCfgType *CanIfTxPduCfg;
#endif

}CanIfInitCfgType;

/**
    Callback functions provided by upper layer modules of the CanIf.
    The callback functions defined in this container are common to all
    configured CAN Driver / CAN Transceiver Driver modules.
*/
typedef struct{
/* ----------- Configuration Parameters ----------- */
/** defines the name of <User_ClearTrcvWufFlagIndication> */
    CanIfDispatchUserCheckTrcvWakeFlagIndicationNameType
        CanIfDispatchUserCheckTrcvWakeFlagIndicationName;
/** defines the upper layer module to which the CheckTrcvWakeFlagIndication
    from the Driver modules have to be routed
*/
    CanIfDispatchUserCheckTrcvWakeFlagIndicationULType
        CanIfDispatchUserCheckTrcvWakeFlagIndicationUL;
/** defines the name of <User_ClearTrcvWufFlagIndication> */
    CanIfDispatchUserClearTrcvWufFlagIndicationNameType
        CanIfDispatchUserClearTrcvWufFlagIndicationName;
/** defines the upper layer module to which the ClearTrcvWufFlagIndication
    from the Driver modules have to be routed */
    CanIfDispatchUserClearTrcvWufFlagIndicationULType
        CanIfDispatchUserClearTrcvWufFlagIndicationUL;
/** defines the name of <User_ConfirmPnAvailability> */
    CanIfDispatchUserConfirmPnAvailabilityNameType
        CanIfDispatchUserConfirmPnAvailabilityName;
/** defines the upper layer module to which the ConfirmPnAvailability
    notification from the Driver modules have to be routed */
    CanIfDispatchUserConfirmPnAvailabilityULType
        CanIfDispatchUserConfirmPnAvailabilityUL;
/** defines the name of <User_ControllerBusOff> */
    CanIfDispatchUserCtrlBusOffNameType CanIfDispatchUserCtrlBusOffName;
/** defines the upper layer (UL) module to which the notifications of all
    ControllerBusOff events from the CAN Driver modules have to be routed */
    CanIfDispatchUserCtrlBusOffULType CanIfDispatchUserCtrlBusOffUL;
/** defines the name of <User_ControllerModeIndication> */
    CanIfDispatchUserCtrlModeIndicationNameType
        CanIfDispatchUserCtrlModeIndicationName;
/** defines the upper layer (UL) module to which the notifications of all
    ControllerTransition events from the CAN Driver modules have to be routed */
    CanIfDispatchUserCtrlModeIndicationULType
        CanIfDispatchUserCtrlModeIndicationUL;
/** defines the name of <User_TrcvModeIndication> */
    CanIfDispatchUserTrcvModeIndicationNameType
        CanIfDispatchUserTrcvModeIndicationName;
/** defines the upper layer (UL) module to which the notifications of all
    TransceiverTransition events from the CAN Transceiver Driver modules
    have to be routed */
    CanIfDispatchUserTrcvModeIndicationULType
        CanIfDispatchUserTrcvModeIndicationUL;
/** defines the name of <User_ValidateWakeupEvent> */
    CanIfDispatchUserValidateWakeupEventNameType
        CanIfDispatchUserValidateWakeupEventName;
/** defines the upper layer (UL) module to which the notifications about
    positive former requested wake up sources have to be routed */
    CanIfDispatchUserValidateWakeupEventULType
        CanIfDispatchUserValidateWakeupEventUL;

/* ------------- Included Containers ------------- */

}CanIfDispatchCfgType;

/**
    Configuration parameters for all the underlying CAN Driver modules
*/
typedef struct{
/* ----------- Configuration Parameters ----------- */
/** Reference to the Init Hoh Configuration */
#if (CANIF_INF_RUNTIME_PDU_CONFIGURATION == STD_OFF)
    const CanIfInitHohCfgType *CanIfCtrlDrvInitHohConfigRef;
#else
    CanIfInitHohCfgType *CanIfCtrlDrvInitHohConfigRef;
#endif
/** This reference can be used to get any information (Ex. Driver Name,
    Vendor ID) from the CAN driver */
#if (CANIF_INF_RUNTIME_PDU_CONFIGURATION == STD_OFF)
    const void *CanIfCtrlDrvNameRef;                 ///Reference to CanGeneral
#else
    void *CanIfCtrlDrvNameRef;
#endif
///** Minimum identifier CanIfCtrlId in can driver */
//    uint8 CanIfMinCtrlId_INF;
///** Maximum identifier CanIfCtrlId in can driver */
//    uint8 CanIfMaxCtrlId_INF;

/* ------------- Included Containers ------------- */
/** List of can controllers configurations for each can driver .
    This container contains the configuration (parameters) of
    an addressed CAN controller by an underlying CAN Driver module
*/
    const CanIfCtrlCfgType *CanIfCtrlCfg;

}CanIfCtrlDrvCfgType;
/* ------------------------------------------------------- */

/**
    Post build / Pre-compile parameters of the CAN interface
    for all underlying CAN drivers .
*/
typedef struct{
/* ----------- Configuration Parameters ----------- */

/* ------------- Included Containers ------------- */
    /** List of CAN Driver modules
        For each CAN Driver module a seperate instance of this container has to be provided.
    */
    const CanIfCtrlDrvCfgType *CanIfCtrlDrvCfg;
    /**
        Callback functions provided by upper layer modules of the CanIf.
        The callback functions defined in this container are common to
        all configured CAN Driver / CAN Transceiver Driver modules.
    */
    const CanIfDispatchCfgType *CanIfDispatchCfg;
    /**
        This container contains the init parameters of the CAN Interface.
    */
#if (CANIF_INF_RUNTIME_PDU_CONFIGURATION == STD_OFF)
    const CanIfInitCfgType *CanIfInitCfg;
#else
    CanIfInitCfgType *CanIfInitCfg;
#endif
    /**
        This container contains the private configuration (parameters) of the CAN Interface.
    */
    const CanIfPrivateCfgType *CanIfPrivateCfg;
    /**
        This container contains the public configuration (parameters) of the CAN Interface.
    */
    const CanIfPublicCfgType *CanIfPublicCfg;
    /** List of CAN transceivers
        This container contains the configuration (parameters) of all addressed CAN transceivers
        by each underlying CAN Transceiver Driver module. For each CAN transceiver Driver
        a seperate instance of this container shall be provided.
    */
    const CanIfTrcvDrvCfgType *CanIfTrcvDrvCfg;

}CanIf_ConfigType;

#endif // CANIF_TYPES_H_INCLUDED
