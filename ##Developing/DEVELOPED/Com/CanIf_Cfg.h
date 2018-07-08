/**
 * \file	CanIf_Cfg.h
 *
 * \version ..
 *
 * \brief	Defines configuration parameters.
 *
 * \date 	..
 *
 * \author  MHmed Hatem
 *
 */

#ifndef CANIF_CFG_H_INCLUDED
#define CANIF_CFG_H_INCLUDED

#include "ECU_CONFIGURATION.h"
/* -------------------------------------------------------------------------- */
/*                           Macros & Typedefs                                */
/* -------------------------------------------------------------------------- */
/** CANIF_INF_RUNTIME_PDU_CONFIGURATION
    STD_OFF ->  Pre-compile time configuration
    STD_ON  ->  Post build time configuration
*/
#define CANIF_INF_RUNTIME_PDU_CONFIGURATION      STD_OFF
#define CANIF_INF_CAN_TRCV_SUPPORT               STD_ON

/** service CanIf_CancelTransmit() shall be pre-compile time
    configurable On/Off
*/
#define CANIF_PUBLIC_CANCEL_TRANSMIT_SUPPORT     STD_ON

/** CanIf_ReadRxPduData(): This API can
    be enabled or disabled at pre-compile time
*/
#define CANIF_PUBLIC_READRXPDU_DATA_API          STD_OFF
#define CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API STD_OFF
#define CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API STD_OFF

#define CANIF_INF_WAKEUP_SUPPORT                         STD_ON
#define CANIF_PUBLIC_WAKEUP_CHECK_VALIDATION_SUPPORT     STD_ON
#define CANIF_INF_PUBLIC_TX_CONFIRMATION_POLLING_SUPPORT STD_ON
#define CANIF_PUBLIC_PN_SUPPORT                  STD_ON
#define CANIF_SET_BAUDRATE_API                   STD_ON
#define CANIF_PUBLIC_ICOM_SUPPORT                STD_ON

/** Enables and disables the API for reading the notification
    status of transmit L-PDUs.
*/
#define CANIF_READTXPDU_NOTIFY_STATUS_API        STD_OFF
#define CANIF_PUBLIC_SETDYNAMICTXID_API          STD_OFF

#define CANIF_INF_PRIVATE_DATA_LENGTH_CHECK      STD_ON

#define CANIF_INF_TX_OFFLINE_ACTIVE_SUPPORT      STD_ON

/** Max number of can driver controllers */
#define CANIF_INF_CAN_DRIVER_0_CONTROLER_CNT         1
#define CANIF_INF_CAN_DRIVER_0_CONTROLER_0           0

/** Max number of can tranceiver  driver tranceivers  */
#define CANIF_INF_CAN_TRCV_DRIVER_0_TRANSCEIVER_CNT  1
#define CANIF_INF_CAN_TRCV_DRIVER_0_TRANSCEIVER_0    0

//#define CANIF_INF_USE_CAN_NM                    STD_OFF
//#define CANIF_INF_USE_CAN_TP                    STD_OFF
//#define CANIF_INF_USE_CAN_TSYN                  STD_OFF
//#define CANIF_INF_USE_CDD                       STD_OFF
//#define CANIF_INF_USE_J1939NM                   STD_OFF
//#define CANIF_INF_USE_J1939TP                   STD_OFF
//#define CANIF_INF_USE_PDUR                      STD_OFF
//#define CANIF_INF_USE_XCP                       STD_OFF

#ifdef ECU1_SENSORYNODE

#define CANIF_INF_RX_PDU_0_CAN_ID   10  //Car_Task
#define CANIF_INF_RX_PDU_1_CAN_ID   12  //Ultra_REQ

#define CANIF_INF_TX_PDU_0_CAN_ID   11  //Encoder_Data
#define CANIF_INF_TX_PDU_1_CAN_ID   13  //Ultra_Data1
#define CANIF_INF_TX_PDU_2_CAN_ID   15  //Comp_Data

/* -------------------------------------------------------------------------- */
/*                       Structures and Enumerations                          */
/* -------------------------------------------------------------------------- */
typedef enum {
    CANIF_INF_RX_PDU_0=0,
    CANIF_INF_RX_PDU_1=1,
    CANIF_INF_RX_CNT  =2
}CanIf_INF_Rx_Pdus;

typedef enum {
    CANIF_INF_TX_PDU_0=0,
    CANIF_INF_TX_PDU_1=1,
    CANIF_INF_TX_PDU_2=2,
    CANIF_INF_TX_CNT  =3
}CanIf_INF_Tx_Pdus;
//CanIf_Rx_Pdus;

#endif

#ifdef ECU2_ALGORITHMICNODE

#define CANIF_INF_RX_PDU_0_CAN_ID   13  //Ultra_Data1
#define CANIF_INF_RX_PDU_1_CAN_ID   11  //Encoder_Data
#define CANIF_INF_RX_PDU_2_CAN_ID   15  //Comp_Data

#define CANIF_INF_TX_PDU_0_CAN_ID   10  //Car_Task
#define CANIF_INF_TX_PDU_1_CAN_ID   12  //Ultra_REQ

/* -------------------------------------------------------------------------- */
/*                       Structures and Enumerations                          */
/* -------------------------------------------------------------------------- */
typedef enum {
    CANIF_INF_RX_PDU_0=0,
    CANIF_INF_RX_PDU_1=1,
    CANIF_INF_RX_PDU_2=2,
    CANIF_INF_RX_CNT  =3
}CanIf_INF_Rx_Pdus;

typedef enum {
    CANIF_INF_TX_PDU_0=0,
    CANIF_INF_TX_PDU_1=1,
    CANIF_INF_TX_CNT  =2
}CanIf_INF_Tx_Pdus;
//CanIf_Rx_Pdus;

#endif

#ifdef ECU3_ACTUATORNODE

#define CANIF_INF_RX_PDU_0_CAN_ID   10  //Car_Task
#define CANIF_INF_RX_PDU_1_CAN_ID   11  //Encoder_Data
#define CANIF_INF_RX_PDU_2_CAN_ID   15  //Comp_Data

#define CANIF_INF_TX_PDU_0_CAN_ID   14  //Steer_Encoder

/* -------------------------------------------------------------------------- */
/*                       Structures and Enumerations                          */
/* -------------------------------------------------------------------------- */
typedef enum {
    CANIF_INF_RX_PDU_0=0,
    CANIF_INF_RX_PDU_1=1,
    CANIF_INF_RX_PDU_2=2,
    CANIF_INF_RX_CNT  =3
}CanIf_INF_Rx_Pdus;

typedef enum {
    CANIF_INF_TX_PDU_0=0,
    CANIF_INF_TX_CNT  =1
}CanIf_INF_Tx_Pdus;
//CanIf_Rx_Pdus;

#endif

/* -------------------------------------------------------------------------- */
/*                      Global variables  Declarations	                      */
/* -------------------------------------------------------------------------- */

extern const CanIf_ConfigType CanIf_Config;

#endif // CANIF_CFG_H_INCLUDED
