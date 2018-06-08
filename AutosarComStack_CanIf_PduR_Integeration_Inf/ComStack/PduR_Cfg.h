/**
 * \file	PduR_Cfg.h
 *
 * \version ..
 *
 * \brief	Configuration file for PduR selections
 *
 * \date 	..
 *
 * \author  ADAS
 *
 */

#ifndef PDUR_CFG_H_
#define PDUR_CFG_H_

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/**
*	What modules you need
*/
#define PDUR_CANIF_SUPPORT 			    STD_ON
#define PDUR_CANTP_SUPPORT			    STD_ON
#define PDUR_COM_SUPPORT				STD_ON
#define PDUR_DCM_SUPPORT				STD_ON

/** Zero cost operation */
#define PDUR_ZERO_COST_OPERATION	STD_OFF

/** If zero cost operation support is active */
#if PDUR_ZERO_COST_OPERATION == STD_ON

#if PDUR_CANIF_SUPPORT == STD_ON
#define PduR_CanIfRxIndication 		Com_RxIndication
#define PduR_CanIfTxConfirmation 	Com_TxConfirmation
#else
#define PduR_CanIfRxIndication(... )
#define PduR_CanIfTxConfirmation(...)
#endif

#if PDUR_CANTP_SUPPORT == STD_ON
#define PduR_CanTpProvideRxBuffer   Dcm_ProvideRxBuffer
#define PduR_CanTpRxIndication 		Dcm_RxIndication
#define PduR_CanTpProvideTxBuffer   Dcm_ProvideTxBuffer
#define PduR_CanTpTxConfirmation 	Dcm_TxConfirmation
#else
#define PduR_CanTpProvideRxBuffer(...)
#define PduR_CanTpRxIndication(...)
#define PduR_CanTpProvideTxBuffer(...)
#define PduR_CanTpTxConfirmation(...)
#endif

#if PDUR_COM_SUPPORT == STD_ON
#define PduR_ComTransmit CanIf_Transmit
#else
#define PduR_ComTransmit(... )	(E_OK)
#endif

#if PDUR_DCM_SUPPORT == STD_ON
#define PduR_DcmTransmit CanTp_Transmit
#else
#define PduR_DcmTransmit(... )	(E_OK)
#endif

#endif // PDUR_ZERO_COST_OPERATION

#endif //PDUR_CFG_H_
