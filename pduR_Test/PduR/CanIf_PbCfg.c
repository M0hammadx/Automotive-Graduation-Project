/** incomplete CanIf configuration code file used as a test to PDUR module */

#include "CanIf_PbCfg.h"


const CanIf_TxPduConfigType CanIfTxPduConfigData[] = {
  {
    .CanIfTxPduId = CANIF_PDU_ID_CAN_TX_MESSAGE_2,
    .CanIfCanTxPduIdCanId = 258,
    .PduIdRef = &Pdus[1],      //like DST PDUR
  },
};

const CanIf_RxPduConfigType CanIfRxPduConfigData[] = {
  {
    .CanIfCanRxPduId = CANIF_PDU_ID_CAN_RX_MESSAGE_1,
    .CanIfCanRxPduCanId = 256,
    .PduIdRef = &Pdus[0],   //like SRC CAN
  },
};

// This container contains the init parameters of the CAN
// Multiplicity 1..*
const CanIf_InitConfigType CanIfInitConfig =
{
  .CanIfNumberOfCanRxPduIds = 1,
  .CanIfNumberOfCanTXPduIds = 1,

  // Containers
  .CanIfRxPduConfigPtr = CanIfRxPduConfigData,
  .CanIfTxPduConfigPtr = CanIfTxPduConfigData,
};

// This container includes all necessary configuration sub-containers
// according the CAN Interface configuration structure.
CanIf_ConfigType CanIf_Config =
{
  .InitConfig = &CanIfInitConfig,
};

