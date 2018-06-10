/**
 * \file	PduR.c
 *
 * \version ..
 *
 * \brief	this file defines general functions provided by the PDU Router
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

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
/** State of pdu router, global */
PduR_StateType PduRState = PDUR_UNINIT;

/** Pointer to config of pdu router, global */
const PduR_PBConfigType* PduRConfig;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
/**
    Description  : Initializes the PDU Router .
    inputs       : ConfigPtr | Pointer to post build configuration parameters .
    output       : None
    I/O          : None
    return value : None
*/
void PduR_Init(const PduR_PBConfigType* ConfigPtr){
	//Check if the PDU router is uninitialized
	if(PduRState != PDUR_UNINIT){
		//Raise error and return
	}else if(ConfigPtr == NULL){
		//Raise error and return
	}else{
		//Successful initialization
		PduRConfig = ConfigPtr;
		PduRState = PDUR_ONLINE;
	}
}

/**
    Description  : Returns the unique identifier of the post-build time configuration of the PDU Router.
    inputs       : None
    output       : None
    I/O          : None
    return value : PduR_PBConfigIdType | Identifier of the post-build time configuration .
*/
PduR_PBConfigIdType PduR_GetConfigurationId (void){
	return PduRConfig->PduRConfigurationId;
}

/**
    Description  : query global I-PDU reference in PDUR configuration (routing paths sources)
    inputs       : Pdu            | Reference to global PDU .
    output       : PduHandleIdPtr | Identifier to local I-PDU .
    I/O          : None
    return value : Std_ReturnType | Determine if I-PDU is exist or not .
*/
Std_ReturnType PduR_INF_GetSourcePduHandleId (Pdu_Type *Pdu, PduIdType *PduHandleIdPtr){
    Std_ReturnType Std_Ret = E_NOT_OK;

    if (PduRConfig->RoutingPaths[0] == NULL || Pdu == NULL){
        //detect error
        return E_NOT_OK;
    }
    for (uint8_t i=0 ; PduRConfig->RoutingPaths[i] != NULL ; i++){
        if ( PduRConfig->RoutingPaths[i]->PduRSrcPduRef->SrcPduRef == Pdu){
            Std_Ret = E_OK;
            *PduHandleIdPtr = PduRConfig->RoutingPaths[i]->PduRSrcPduRef->SourcePduHandleId;
        }
    }
    return Std_Ret;
}

/**
    Description  : query global I-PDU reference in PDUR configuration (routing paths destinations)
    inputs       : Pdu            | Reference to global PDU .
    output       : DestPduId      | Identifier to local I-PDU .
    I/O          : None
    return value : Std_ReturnType | Determine if I-PDU is exist or not.
*/
Std_ReturnType PduR_INF_GetDestPduHandleId (Pdu_Type *Pdu, PduIdType *PduHandleIdPtr){
    Std_ReturnType Std_Ret = E_NOT_OK;

    PduRRoutingPath_type ** routes = PduRConfig->RoutingPaths;
    if (routes[0] == NULL || Pdu == NULL){
        //detect error
        return E_NOT_OK;
    }
    for (uint8_t i=0 ; routes[i] != NULL ; i++){
        if ( routes[i]->PduRDestPduRef->DestPduRef == Pdu){
            Std_Ret = E_OK;
            *PduHandleIdPtr = routes[i]->PduRDestPduRef->DestPduHandleId;
        }
    }
    return Std_Ret;
}
