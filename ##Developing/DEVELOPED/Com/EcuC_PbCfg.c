/** incomplete ECUC post build configuration code file used as a test to PDUR module */

#include "EcuC.h"
#include "ECU_CONFIGURATION.h"
/**
    an array of global PDUs one for each message in your system
    reference of this array is assigned to ECU configuration
*/
#ifdef ECU1_SENSORYNODE
Pdu_Type Pdus[] = {
    {//0
        .PduLength = 2  // global RX PDU between CanIf -> Com, Ultra_REQ
    },
    {//1
        .PduLength = 8  // global TX PDU between Com -> CanIf, Ultra_Data1
    },
    {//2
        .PduLength = 8  // global RX PDU between CanTP -> Com,
    },
    {//3
        .PduLength = 8  // global TX PDU between Com -> CanTP,  T
    },
    {//4
        .PduLength = 8  // global RX between CanTP -> DCM,
    },
    {//5
        .PduLength = 8  // global TX PDU between DCM & CanTP,
    },
    {//6
        .PduLength = 5  // global RX PDU between CanIf -> Com,  Car_Task
    },
    {//7
        .PduLength = 7  // global TX PDU between Com -> CanIf, Encoder_Data
    },
    {//8
        .PduLength = 3  // global TX PDU between Com -> CanIf, Comp_Data
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
#endif

#ifdef ECU2_ALGORITHMICNODE
Pdu_Type Pdus[] = {
    {//0
        .PduLength = 8  // global RX PDU between CanIf -> Com, Ultra_Data1
    },
    {//1
        .PduLength = 5  // global TX PDU between Com -> CanIf, Car_Task
    },
    {//2
        .PduLength = 8  // global RX PDU between CanTP -> Com,
    },
    {//3
        .PduLength = 8  // global TX PDU between Com -> CanTP,  T
    },
    {//4
        .PduLength = 8  // global RX between CanTP -> DCM,
    },
    {//5
        .PduLength = 8  // global TX PDU between DCM & CanTP,
    },
    {//6
       .PduLength = 2  // global TX PDU between Com -> CanIf, Ultra_REQ
    },
    {//7
        .PduLength = 7  // global RX PDU between CanIf -> Com,  Encoder_Data
    },
    {//8
        .PduLength = 3  // global RX PDU between CanIf -> Com,  Comp_Data
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
#endif  //ECU2_ALGORITHMICNODE

#ifdef ECU3_ACTUATORNODE
Pdu_Type Pdus[] = {
    {//0
        .PduLength = 5  // global RX PDU between CanIf -> Com,  Car_Task
    },
    {//1
        .PduLength = 2  // global TX PDU between Com -> CanIf,  Steer_Encoder
    },
    {//2
        .PduLength = 8  // global RX PDU between CanTP -> Com,
    },
    {//3
        .PduLength = 8  // global TX PDU between Com -> CanTP,  T
    },
    {//4
        .PduLength = 8  // global RX between CanTP -> DCM,
    },
    {//5
        .PduLength = 8  // global TX PDU between DCM & CanTP,
    },
    {//6
        .PduLength = 7  // global RX PDU between CanIf -> Com,  Encoder_Data
    },
    {//7
        .PduLength = 3  // global RX PDU between CanIf -> Com,  Comp_Data
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
#endif  //ECU3_ACTUATORNODE
