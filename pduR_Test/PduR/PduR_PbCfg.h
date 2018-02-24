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

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#define PDUR_PDU_ID_CANIF_RX_COM_MESSAGE_1      1
#define PDUR_PDU_ID_COM_TX_CANIF_MESSAGE_2      2
#define PDUR_PDU_ID_CANTP_RX_COM_MESSAGE_3      3
#define PDUR_PDU_ID_COM_TX_CANTP_MESSAGE_4      4
#define PDUR_PDU_ID_CANTP_RX_DCM_MESSAGE_5      5
#define PDUR_PDU_ID_DCM_TX_CANTP_MESSAGE_6      6

/* ========================================================================== */
/*                         Global variables  Declarations                     */
/* ========================================================================== */
extern PduR_PBConfigType PBPduRConfig;

#endif // PDUR_PBCFG_H_INCLUDED
