/** incomplete Dcm configuration header file used as a test to PDUR module */

#ifndef DCM_LCFG_H_
#define DCM_LCFG_H_

#include "ComStack_Types.h"

/*******
 * DSL *
 *******/

/* Makes it possible to cross-reference structures. */
typedef struct Dcm_DslMainConnectionType_t Dcm_DslMainConnectionType;
typedef struct Dcm_DslProtocolRxType_t Dcm_DslProtocolRxType;

struct Dcm_DslProtocolRxType_t {
	const PduIdType					DcmDslProtocolRxPduId;					// (1)
    /** Reference to a Pdu in EcuC that is used for this reception channel. */
	const void *                    DcmDslProtocolRxPduRef;
};

/* Makes it possible to cross-reference structures. */
typedef struct Dcm_DslProtocolTxType_t Dcm_DslProtocolTxType;

struct Dcm_DslProtocolTxType_t {
	const PduIdType					DcmDslProtocolTxPduId;		// (1)
	/** Reference to a Pdu in EcuC that is used for this transmission channel. */
	const void *                    DcmDslProtocolTxPduRef;
};

/* Make it possible to cross reference. */
typedef struct Dcm_DslConnectionType_t Dcm_DslConnectionType;

// 10.2.12
struct Dcm_DslMainConnectionType_t { // Cross referenced from Dcm_DslProtocolRxType_t.
	// Containers
	const Dcm_DslProtocolRxType				*DslProtocolRx;					// (1..*) Remove?
	const Dcm_DslProtocolTxType				*DslProtocolTx;					// (1)
};

/* Make it possible to cross reference. */
typedef struct Dcm_DslProtocolRowType_t Dcm_DslProtocolRowType;

struct Dcm_DslConnectionType_t {
	// Containers
	const Dcm_DslMainConnectionType			*DslMainConnection;			// (1)
};

struct Dcm_DslProtocolRowType_t { // Cross referenced from Dcm_DslConnectionType_t.
	// Containers
	const Dcm_DslConnectionType				*DslConnection; // (1..*)
};

typedef struct {
	// Containers
	const Dcm_DslProtocolRowType	*DslProtocolRowList;		// (1..*)
} Dcm_DslProtocolType;

typedef struct {
	// Containers
	const Dcm_DslProtocolType					*DslProtocol;					// (1)
} Dcm_DslType;

typedef struct {
	// Containers
	const Dcm_DslType *Dsl; //	(1)
} Dcm_ConfigType;

/*
 * Make the DCM_Config visible for others.
 */


extern const Dcm_ConfigType DCM_Config;


#endif /*DCM_LCFG_H_*/
