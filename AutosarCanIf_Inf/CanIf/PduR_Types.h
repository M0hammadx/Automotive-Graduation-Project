/**
 * \file	PduR_Types.h
 *
 * \version ..
 *
 * \brief	data types used by PDUR module
 *
 * \date 	..
 *
 * \author  ADAS
 *
 */

#ifndef PDUR_TYPES_H_
#define PDUR_TYPES_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "ComStack_Types.h"
#include "EcuC_Types.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
typedef uint16_t PduR_PBConfigIdType;

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */
/** States of the PDU Router
    PDUR_UNINIT  --  PDU Router not initialized
    PDUR_ONLINE  --  PDU Router initialized successfully
*/
typedef enum{
	PDUR_UNINIT,
	PDUR_ONLINE
}PduR_StateType;

/** specifies one source for the PDU to be routed */
typedef struct{
    /** PDU identifier assigned by PDU Router. */
	const PduIdType SourcePduHandleId;      // ComStack_Types

	/** Source PDU reference; reference to unique PDU identifier which shall be
		 used for the requested PDU Router operation
	*/
	Pdu_Type * SrcPduRef;
}PduRSrcPdu_type;

/** specifies one destination for the PDU to be routed */
typedef struct{
    /**
        PDU identifier assigned by PDU Router. Used by communication interface
        and transport protocol modules for confirmation
    */
	const PduIdType DestPduHandleId;

	/**
        unique identifier which shall be used by the PDU Router
        when calling the related function of the destination module.
	*/
    Pdu_Type * DestPduRef;
}PduRDestPdu_type;

/** specifies the routing path of a PDU */
typedef struct{
	/** reference to source of path */
    PduRSrcPdu_type * PduRSrcPduRef;

	/** reference to  destination of path */
    PduRDestPdu_type * PduRDestPduRef;
}PduRRoutingPath_type;

/** Configuration of the PduR */
typedef struct PduR_PBConfig{
	/** Identification of the configuration of the PduR configuration */
	PduR_PBConfigIdType PduRConfigurationId;

	/** Max number of routing paths in all tables */
	const uint16_t PduRMaxRoutingPathCnt;

	/** Array of pointers to routing paths ,routing table */
    PduRRoutingPath_type ** RoutingPaths;
}PduR_PBConfigType;

#endif //PDUR_TYPES_H_
