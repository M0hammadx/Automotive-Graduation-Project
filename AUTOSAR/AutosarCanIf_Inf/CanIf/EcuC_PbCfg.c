/** incomplete ECUC post build configuration code file used as a test to PDUR module */

#include "EcuC.h"

/**
    an array of global PDUs one for each message in your system
    reference of this array is assigned to ECU configuration
*/
Pdu_Type Pdus[] = {
    {
        .PduLength = 8  // global RX PDU between CanIf -> Com,  Tested
    },
    {
        .PduLength = 8  // global TX PDU between Com -> CanIf,  Tested
    },
    {
        .PduLength = 8  // global RX PDU between CanTP -> Com,
    },
    {
        .PduLength = 8  // global TX PDU between Com -> CanTP,  T
    },
    {
        .PduLength = 8  // global RX between CanTP -> DCM,
    },
    {
        .PduLength = 8  // global TX PDU between DCM & CanTP,
    },
};

/** Incomplete ECU configuration */
EcuC_PBConfigType EcuC_PBConfig = {
    .EcucConfigSet = {
        .EcucPduCollection = {
            .Pdus = Pdus
        }
    }
};

