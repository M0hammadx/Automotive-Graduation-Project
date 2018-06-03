/**
 * \file	PduR.h
 *
 * \version ..
 *
 * \brief	this file defines general functions provided by the PDU Router .
 *
 * \date 	..
 *
 * \author  ADAS
 *
 */

#ifndef PDUR_H_
#define PDUR_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "Std_Types.h"
#include "PduR_Cfg.h"
#include "PduR_PbCfg.h"
#include "PduR_Types.h"
#include "PduR_If.h"

#include <stdio.h>
/**
*   If you do not wanna use any module ,
*	you can turn it off from PduR_Cfg.h file .
*/
#if PDUR_COM_SUPPORT == STD_ON
#include "PduR_Com.h"
#endif
#if PDUR_CANIF_SUPPORT == STD_ON
#include "PduR_CanIf.h"
#endif
#if PDUR_CANTP_SUPPORT == STD_ON
#include "PduR_CanTp.h"
#endif
#if PDUR_DCM_SUPPORT == STD_ON
#include "PduR_Dcm.h"
#endif

/* ========================================================================== */
/*                         Global variables  Declarations                     */
/* ========================================================================== */
/*
* configuration of PduR , const val .
* we need it to identify which configuration already used .
*/
extern const PduR_PBConfigType* PduRConfig;
//State of PduR do we use pduR initialization or not .
extern PduR_StateType PduRState;

/* ========================================================================== */
/*                          Function declarations                             */
/* ========================================================================== */
/*
* Zero cost operation .
* if you need #defines to replace function names
* instead of using new functions to replacement .
*/
#if (ZERO_COST_OPERATION == STD_ON)
#define PduR_Init(...)
#define PduR_GetConfigurationId(...) 0

#else

void PduR_Init(const PduR_PBConfigType* ConfigPtr);
PduR_PBConfigIdType PduR_GetConfigurationId (void);

Std_ReturnType PduR_INF_GetSourcePduHandleId (Pdu_Type *, PduIdType *);
Std_ReturnType PduR_INF_GetDestPduHandleId (Pdu_Type *, PduIdType *);

#endif

#endif	//PDUR_H_
