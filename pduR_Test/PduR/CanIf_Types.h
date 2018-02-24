/** incomplete CanIf types header file used as a test to PDUR module */

#ifndef CANIF_TYPES_H_INCLUDED
#define CANIF_TYPES_H_INCLUDED

#include "ComStack_Types.h"

//-------------------------------------------------------------------
/*
 * CanIfTxPduConfig container
 */

/** Definition of Tx PDU (Protocol Data Unit). */
typedef struct {
	/** ECU wide unique, symbolic handle for transmit CAN L-PDU. The
	 *  CanIfCanTxPduId is configurable at pre-compile and post-built time.
	 *  Range: 0..max. number of CantTxPduIds  	PduIdType 	CanTxPduId; */
	PduIdType CanIfTxPduId;

	/** CAN Identifier of transmit CAN L-PDUs used by the CAN Driver for CAN L-
	 *  PDU transmission. Range: 11 Bit For Standard CAN Identifier ... 29 Bit For
	 *  Extended CAN identifier */
	uint32_t  CanIfCanTxPduIdCanId;

	/** Reference to the "global" Pdu structure to allow harmonization of handle
	 *  IDs in the COM-Stack. */
	void *PduIdRef;
} CanIf_TxPduConfigType;

//-------------------------------------------------------------------
/*
 * CanIfRxPduConfig container
 */


/** Definition of Rx PDU (Protocol Data Unit). */
typedef struct {
  /** ECU wide unique, symbolic handle for receive CAN L-PDU. The
   *  CanRxPduId is configurable at pre-compile and post-built time. It shall fulfill
   *  ANSI/AUTOSAR definitions for constant defines. Range: 0..max. number
   *  of defined CanRxPduIds */
    PduIdType CanIfCanRxPduId;

  /** CAN Identifier of Receive CAN L-PDUs used by the CAN Interface. Exa:
   *  Software Filtering. Range: 11 Bit For Standard CAN Identifier ... 29 Bit For
   *  Extended CAN identifier */
	uint32_t 		CanIfCanRxPduCanId;

  /** Reference to the "global" Pdu structure to allow harmonization of handle
   *  IDs in the COM-Stack. */
	void *PduIdRef;

} CanIf_RxPduConfigType;

typedef struct {
	/** Size of Rx PDU list. */
	uint32_t CanIfNumberOfCanRxPduIds;
	/** Size of Tx PDU list. */
	uint32_t CanIfNumberOfCanTXPduIds;

  /** Rx PDU's list */
	const CanIf_RxPduConfigType *CanIfRxPduConfigPtr;

  /** Tx PDU's list */
	const CanIf_TxPduConfigType *CanIfTxPduConfigPtr;

} CanIf_InitConfigType;

/** Top level configuration container. */
typedef struct {
	/** This container contains the init parameters of the CAN Interface. */
	const CanIf_InitConfigType 		*InitConfig;

} CanIf_ConfigType;


#endif // CANIF_TYPES_H_INCLUDED
