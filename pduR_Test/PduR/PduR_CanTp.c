/**
 * \file	PduR_CanTp.c
 *
 * \version ..
 *
 * \brief   Configurable interfaces definitions for CanTp module .
 *
 * \date 	..
 *
 * \author  ADAS
 *
 */
/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "PduR_CanTp.h"

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
/**
    Description  : Called after an I-PDU has been received via the TP API, the result indicates
                   whether the transmission was successful or not.
    inputs       : id     | Identification of the received I-PDU.
                   result | Result of the reception.
    output       : None
    I/O          : None
    return value : None
*/
void PduR_CanTpRxIndication(PduIdType id, Std_ReturnType result){
    PduR_INF_TpRxIndication(id, result);
}

/**
    Description  : called after the I-PDU has been transmitted on its network, the
                   result indicates whether the transmission was successful or not.
    inputs       : id     | Identification of the transmitted I-PDU.
    output       : result | Result of the transmission of the I-PDU.
    I/O          : None
    return value : None
*/
void PduR_CanTpTxConfirmation(PduIdType id, Std_ReturnType result){
    PduR_INF_TpTxConfirmation(id, result);
}

/**
    Description  : called at the start of receiving an N-SDU .
    inputs       : id   | Identification of the I-PDU.
                   info | Pointer to a PduInfoType structure containing the payload
                        data and length of the first frame or single frame of TP I-PDU
                        reception, and the MetaData related to this PDU.
                        If neither first/single frame data nor MetaData are available,
                        this parameter is set to NULL_PTR.
                   TpSduLength       | Total length of the N-SDU to be received.
    output       : None
    I/O          : None
    return value : BufReq_ReturnType | Connection has been accepted, rejected, aborted.
*/
BufReq_ReturnType PduR_CanTpStartOfReception(PduIdType id, const PduInfoType* info,
    PduLengthType TpSduLength, PduLengthType* bufferSizePtr){

    return PduR_INF_StartOfReception(id, info, TpSduLength, bufferSizePtr);
}

/**
    Description  : provide the received data of an I-PDU segment (N-PDU) to the upper layer.
    inputs       : id            | Identification of the I-PDU.
                   info          | Provides the source buffer and the number of bytes to be copied.
    output       : bufferSizePtr | Available receive buffer after data has been copied.
    I/O          : None
    return value : BufReq_ReturnType | Data copied successfully or not.
*/
BufReq_ReturnType PduR_CanTpCopyRxData(PduIdType id, const PduInfoType* info,
    PduLengthType* bufferSizePtr){

    return PduR_INF_CopyRxData(id, info, bufferSizePtr);
}

/**
    Description  : acquire the transmit data of an I-PDU segment (N-PDU).
                   Each call to this function provides the next part of the I-PDU data.
    inputs       : id | Identification of the transmitted I-PDU.
                   info | Provides the destination buffer (SduDataPtr) and the number
                        of bytes to be copied (SduLength).
                   retry | This parameter is used to acknowledge transmitted data or
                        to retransmit data after transmission problems.
    output       : availableDataPtr | Indicates the remaining number of bytes that
                        are available in the upper layer module's Tx buffer.
    I/O          : None
    return value : BufReq_ReturnType | Data is copied or not.
*/
BufReq_ReturnType PduR_CanTpCopyTxData(PduIdType id, const PduInfoType* info,
    RetryInfoType* retry, PduLengthType* availableDataPtr){

    return PduR_INF_CopyTxData(id, info, retry, availableDataPtr);
}
