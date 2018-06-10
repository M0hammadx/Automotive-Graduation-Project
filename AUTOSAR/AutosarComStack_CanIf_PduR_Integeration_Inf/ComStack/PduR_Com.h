/**
 * \file	PduR_Com.h
 *
 * \version ..
 *
 * \brief   Configurable interfaces declarations for Com module .
 *
 * \date 	..
 *
 * \author  ADAS
 *
 */

#ifndef PDUR_COM_H_INCLUDED
#define PDUR_COM_H_INCLUDED

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "PduR.h"

#if PDUR_ZERO_COST_OPERATION == STD_OFF

/* ========================================================================== */
/*                          Function declarations                             */
/* ========================================================================== */
Std_ReturnType PduR_ComTransmit(PduIdType ,const PduInfoType*);
Std_ReturnType PduR_ComCancelTransmit( PduIdType );
Std_ReturnType PduR_ComChangeParameter( PduIdType, TPParameterType, uint16_t );
Std_ReturnType PduR_ComCancelReceive( PduIdType );

#endif // PDUR_ZERO_COST_OPERATION

#endif // PDUR_COM_H_INCLUDED
