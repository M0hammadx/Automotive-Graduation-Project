/**
 * \file	PduR_PbCfg.h
 *
 * \version ..
 *
 * \brief	Post build configuration file for PDUR selections
 *
 * \date 	..
 *
 * \author  ADAS
 *
 */

#ifndef PDUR_PBCFG_H_INCLUDED
#define PDUR_PBCFG_H_INCLUDED

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "PduR.h"
#include "PduR_Types.h"
#include "ECU_CONFIGURATION.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#ifdef ECU1_SENSORYNODE

#define PDUR_PDU_ID_COM_TX_CANIF_MESSAGE_2      1   //Ultra_Data1
#define PDUR_PDU_ID_COM_TX_CANIF_MESSAGE_8      2   //Encoder_Data
#define PDUR_PDU_ID_COM_TX_CANIF_MESSAGE_9      5   //Comp_Data

#define PDUR_PDU_ID_CANIF_RX_COM_MESSAGE_1      3   //Ultra_REQ
#define PDUR_PDU_ID_CANIF_RX_COM_MESSAGE_7      4   //Car_Task

#define PDUR_PDU_ID_CANTP_RX_COM_MESSAGE_3      10
#define PDUR_PDU_ID_COM_TX_CANTP_MESSAGE_4      11
#define PDUR_PDU_ID_CANTP_RX_DCM_MESSAGE_5      12
#define PDUR_PDU_ID_DCM_TX_CANTP_MESSAGE_6      13


#endif

#ifdef ECU2_ALGORITHMICNODE

#define PDUR_PDU_ID_COM_TX_CANIF_MESSAGE_2      1   //Car_Task
#define PDUR_PDU_ID_COM_TX_CANIF_MESSAGE_7      2   //Ultra_REQ

#define PDUR_PDU_ID_CANIF_RX_COM_MESSAGE_1      3   //Ultra_Data1
#define PDUR_PDU_ID_CANIF_RX_COM_MESSAGE_8      4   //Encoder_Data
#define PDUR_PDU_ID_CANIF_RX_COM_MESSAGE_9      5   //Comp_Data

#define PDUR_PDU_ID_CANTP_RX_COM_MESSAGE_3      10
#define PDUR_PDU_ID_COM_TX_CANTP_MESSAGE_4      11
#define PDUR_PDU_ID_CANTP_RX_DCM_MESSAGE_5      12
#define PDUR_PDU_ID_DCM_TX_CANTP_MESSAGE_6      13

#endif

#ifdef ECU3_ACTUATORNODE

#define PDUR_PDU_ID_COM_TX_CANIF_MESSAGE_2      1   //Steer_Encoder

#define PDUR_PDU_ID_CANIF_RX_COM_MESSAGE_1      3   //Car_Task
#define PDUR_PDU_ID_CANIF_RX_COM_MESSAGE_7      4   //Encoder_Data
#define PDUR_PDU_ID_CANIF_RX_COM_MESSAGE_8      5   //Comp_Data

#define PDUR_PDU_ID_CANTP_RX_COM_MESSAGE_3      10
#define PDUR_PDU_ID_COM_TX_CANTP_MESSAGE_4      11
#define PDUR_PDU_ID_CANTP_RX_DCM_MESSAGE_5      12
#define PDUR_PDU_ID_DCM_TX_CANTP_MESSAGE_6      13


#endif

/* ========================================================================== */
/*                         Global variables  Declarations                     */
/* ========================================================================== */
extern PduR_PBConfigType PBPduRConfig;

#endif // PDUR_PBCFG_H_INCLUDED
