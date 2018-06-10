/**
 * \file	PduR_Dcm.c
 *
 * \version ..
 *
 * \brief   Configurable interfaces definitions for Dcm module .
 *
 * \date 	..
 *
 * \author  ADAS
 *
 */
/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "PduR.h"

#if (PDUR_ZERO_COST_OPERATION == STD_OFF) && (PDUR_DCM_SUPPORT == STD_ON)

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
/**
    Description  : Requests transmission of a PDU.
    inputs       : TxPduId        | Identifier of the PDU to be transmitted
                   PduInfoPtr     | Length of and pointer to the PDU data and pointer to MetaData.
    output       : None
    I/O          : None
    return value : Std_ReturnType | Transmit request has been accepted or not .
*/
Std_ReturnType PduR_DcmTransmit( PduIdType TxPduId, const PduInfoType* PduInfoPtr ){

	return PduR_INF_RouteTransmit( TxPduId, PduInfoPtr );
}

/**
    Description  : cancellation of an ongoing transmission of a PDU in a lower layer.
    inputs       : TxPduId        | Identification of the PDU to be cancelled.
    output       : None
    I/O          : None
    return value : Std_ReturnType | Cancellation was executed successfully or not .
*/
Std_ReturnType PduR_DcmCancelTransmit( PduIdType TxPduId ){

	return PduR_INF_RouteCancleTransmit( TxPduId );
}

/**
    Description  : change a specific transport protocol parameter.
    inputs       : id          | Identification of the PDU which the parameter change shall affect.
                   parameter   | ID of the parameter that shall be changed.
                   value       | The new value of the parameter.
    output       : None
    I/O          : None
    return value : Std_ReturnType | The parameter was changed successfully or rejected.
*/
Std_ReturnType PduR_DcmChangeParameter( PduIdType id, TPParameterType parameter, uint16_t value ){

    return PduR_INF_RouteChangeParameter( id, parameter, value );
}

/**
    Description  : cancellation of an ongoing reception of a PDU in a lower layer
                    transport protocol module.
    inputs       : RxPduId | Identification of the PDU to be cancelled.
    output       : None
    I/O          : None
    return value : Std_ReturnType | Cancellation was executed successfully or rejected .
*/
Std_ReturnType PduR_DcmCancelReceive( PduIdType RxPduId ){
	return PduR_INF_RouteCancelReceive( RxPduId );
}

#endif

