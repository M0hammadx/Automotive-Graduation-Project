/** incomplete ECUC types file used as a test to PDUR module */

#ifndef ECUC_TYPES_H_INCLUDED
#define ECUC_TYPES_H_INCLUDED

#include "Std_Types.h"


/** Global PDU
    This PDU is used by all Com-Stack modules to agree on
    referencing the same PDU .
*/
typedef struct {
    //Length of the Pdu in bytes
    const uint8 PduLength;
}Pdu_Type;

/** ECU Configuration PDU Collection
    Collection of all PDU objects flowing through the
    Com-Stack.
*/
typedef struct {
    //Array of global PDU's
    Pdu_Type *Pdus;

}EcucPduCollection_Type;

/** ECU Configuration set
    This container contains the configuration parameters and sub
    containers of the global PDU Collection.
*/
typedef struct {
    //Collection of all global PDU's
    EcucPduCollection_Type EcucPduCollection;

}EcucConfigSet_Type;

/** ECU Configuration
    Virtual module to collect ECU Configuration specific / global
    configuration information.
*/
typedef struct{
    EcucConfigSet_Type EcucConfigSet;
}EcuC_PBConfigType;

#endif // ECUC_TYPES_H_INCLUDED
