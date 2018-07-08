/**
 * \file	PduR_Dcm.h
 *
 * \version ..
 *
 * \brief   Configurable interfaces declarations for Dcm module .
 *
 * \date 	..
 *
 * \author  ADAS
 *
 */

#ifndef PDUR_DCM_H_INCLUDED
#define PDUR_DCM_H_INCLUDED

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "PduR.h"

#if PDUR_ZERO_COST_OPERATION == STD_OFF

/* ========================================================================== */
/*                          Function declarations                             */
/* ========================================================================== */
Std_ReturnType PduR_DcmTransmit( PduIdType, const PduInfoType* );
Std_ReturnType PduR_DcmCancelTransmit( PduIdType );
Std_ReturnType PduR_DcmChangeParameter( PduIdType, TPParameterType, uint16 );
Std_ReturnType PduR_DcmCancelReceive( PduIdType );

#endif

#endif // PDUR_DCM_H_INCLUDED
