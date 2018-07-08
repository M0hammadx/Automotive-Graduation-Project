/**
 * \file	PduR_PbCfg.h
 *
 * \version ..
 *
 * \brief	Post build configuration file for PDUR selections
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
#include "EcuC.h"
#include "ECU_CONFIGURATION.h"

#ifdef  ECU1_SENSORYNODE
//****************************************************************
//Receive PDU path from CanIf to Com
//1st creation of path source
 PduRSrcPdu_type PduR_Message_1_Src = {
    .SourcePduHandleId = PDUR_PDU_ID_CANIF_RX_COM_MESSAGE_1,
    .SrcPduRef = &Pdus[0]       //like CAN
};
//2nd creation of path destination
 PduRDestPdu_type PduR_Message_1_Dest = {
    .DestPduHandleId = PDUR_PDU_ID_CANIF_RX_COM_MESSAGE_1,
    .DestPduRef = &Pdus[0]      //like COM
};
//3rd creation of routing path
 PduRRoutingPath_type PduRRoutingPath_CanIf_Rx_Com_Pdu_Message1 = {
    .PduRSrcPduRef = &PduR_Message_1_Src,
    .PduRDestPduRef = &PduR_Message_1_Dest
};
//****************************************************************

 //****************************************************************
 //Receive PDU path from CanIf to Com
 //1st creation of path source
  PduRSrcPdu_type PduR_Message_7_Src = {
     .SourcePduHandleId = PDUR_PDU_ID_CANIF_RX_COM_MESSAGE_7,
     .SrcPduRef = &Pdus[6]       //like CAN
 };
 //2nd creation of path destination
  PduRDestPdu_type PduR_Message_7_Dest = {
     .DestPduHandleId = PDUR_PDU_ID_CANIF_RX_COM_MESSAGE_7,
     .DestPduRef = &Pdus[6]      //like COM
 };
 //3rd creation of routing path
  PduRRoutingPath_type PduRRoutingPath_CanIf_Rx_Com_Pdu_Message7 = {
     .PduRSrcPduRef = &PduR_Message_7_Src,
     .PduRDestPduRef = &PduR_Message_7_Dest
 };
 //****************************************************************

//****************************************************************
//Transmit PDU path from Com to CanIf
//1st creation of path source
 PduRSrcPdu_type PduR_Message_2_Src = {
    .SourcePduHandleId = PDUR_PDU_ID_COM_TX_CANIF_MESSAGE_2,
    .SrcPduRef = &Pdus[1]   //like COM
};
//2nd creation of path destination
 PduRDestPdu_type PduR_Message_2_Dest = {
    .DestPduHandleId = PDUR_PDU_ID_COM_TX_CANIF_MESSAGE_2,
    .DestPduRef = &Pdus[1]      //like CAN
};
//3rd creation of routing path
 PduRRoutingPath_type PduRRoutingPath_Com_Tx_CanIf_Pdu_Message2 = {
    .PduRSrcPduRef = &PduR_Message_2_Src,
    .PduRDestPduRef = &PduR_Message_2_Dest
};
//****************************************************************
 //****************************************************************
 //Transmit PDU path from Com to CanIf
 //1st creation of path source
  PduRSrcPdu_type PduR_Message_8_Src = {
     .SourcePduHandleId = PDUR_PDU_ID_COM_TX_CANIF_MESSAGE_8,
     .SrcPduRef = &Pdus[7]   //like COM
 };
 //2nd creation of path destination
  PduRDestPdu_type PduR_Message_8_Dest = {
     .DestPduHandleId = PDUR_PDU_ID_COM_TX_CANIF_MESSAGE_8,
     .DestPduRef = &Pdus[7]      //like CAN
 };
 //3rd creation of routing path
  PduRRoutingPath_type PduRRoutingPath_Com_Tx_CanIf_Pdu_Message8 = {
     .PduRSrcPduRef = &PduR_Message_8_Src,
     .PduRDestPduRef = &PduR_Message_8_Dest
 };
 //****************************************************************

  //****************************************************************
   //Transmit PDU path from Com to CanIf
   //1st creation of path source
    PduRSrcPdu_type PduR_Message_9_Src = {
       .SourcePduHandleId = PDUR_PDU_ID_COM_TX_CANIF_MESSAGE_9,
       .SrcPduRef = &Pdus[8]   //like COM
   };
   //2nd creation of path destination
    PduRDestPdu_type PduR_Message_9_Dest = {
       .DestPduHandleId = PDUR_PDU_ID_COM_TX_CANIF_MESSAGE_9,
       .DestPduRef = &Pdus[8]      //like CAN
   };
   //3rd creation of routing path
    PduRRoutingPath_type PduRRoutingPath_Com_Tx_CanIf_Pdu_Message9 = {
       .PduRSrcPduRef = &PduR_Message_9_Src,
       .PduRDestPduRef = &PduR_Message_9_Dest
   };
   //****************************************************************

//****************************************************************
//Receive PDU path from CanTp to Com
//1st creation of path source
 PduRSrcPdu_type PduR_Message_3_Src = {
    .SourcePduHandleId = PDUR_PDU_ID_CANTP_RX_COM_MESSAGE_3,
    .SrcPduRef = &Pdus[2]       //like CAN
};
//2nd creation of path destination
 PduRDestPdu_type PduR_Message_3_Dest = {
    .DestPduHandleId = PDUR_PDU_ID_CANTP_RX_COM_MESSAGE_3,
    .DestPduRef = &Pdus[2]      //like COM
};
//3rd creation of routing path
 PduRRoutingPath_type PduRRoutingPath_CanTp_Rx_Com_Pdu_Message3 = {
    .PduRSrcPduRef = &PduR_Message_3_Src,
    .PduRDestPduRef = &PduR_Message_3_Dest
};
//****************************************************************

//****************************************************************
//Transmit PDU path from Com to CanTp
//1st creation of path source
 PduRSrcPdu_type PduR_Message_4_Src = {
    .SourcePduHandleId = PDUR_PDU_ID_COM_TX_CANTP_MESSAGE_4,
    .SrcPduRef = &Pdus[3]   //like COM
};
//2nd creation of path destination
 PduRDestPdu_type PduR_Message_4_Dest = {
    .DestPduHandleId = PDUR_PDU_ID_COM_TX_CANTP_MESSAGE_4,
    .DestPduRef = &Pdus[3]      //like CAN
};
//3rd creation of routing path
 PduRRoutingPath_type PduRRoutingPath_Com_Tx_CanTp_Pdu_Message4 = {
    .PduRSrcPduRef = &PduR_Message_4_Src,
    .PduRDestPduRef = &PduR_Message_4_Dest
};
//****************************************************************

//****************************************************************
//Receive PDU path from CanTp to Dcm
//1st creation of path source
 PduRSrcPdu_type PduR_Message_5_Src = {
    .SourcePduHandleId = PDUR_PDU_ID_CANTP_RX_DCM_MESSAGE_5,
    .SrcPduRef = &Pdus[4]       //like CAN
};
//2nd creation of path destination
 PduRDestPdu_type PduR_Message_5_Dest = {
    .DestPduHandleId = PDUR_PDU_ID_CANTP_RX_DCM_MESSAGE_5,
    .DestPduRef = &Pdus[4]      //like DCM
};
//3rd creation of routing path
 PduRRoutingPath_type PduRRoutingPath_CanTp_Rx_Dcm_Pdu_Message5 = {
    .PduRSrcPduRef = &PduR_Message_5_Src,
    .PduRDestPduRef = &PduR_Message_5_Dest
};
//****************************************************************

//****************************************************************
//Transmit PDU path from Dcm to CanTp
//1st creation of path source
 PduRSrcPdu_type PduR_Message_6_Src = {
    .SourcePduHandleId = PDUR_PDU_ID_DCM_TX_CANTP_MESSAGE_6,
    .SrcPduRef = &Pdus[5]   //like DCM
};
//2nd creation of path destination
 PduRDestPdu_type PduR_Message_6_Dest = {
    .DestPduHandleId = PDUR_PDU_ID_DCM_TX_CANTP_MESSAGE_6,
    .DestPduRef = &Pdus[5]      //like CAN
};
//3rd creation of routing path
 PduRRoutingPath_type PduRRoutingPath_Dcm_Tx_CanTp_Pdu_Message6 = {
    .PduRSrcPduRef = &PduR_Message_6_Src,
    .PduRDestPduRef = &PduR_Message_6_Dest
};
//****************************************************************

//Assign paths pointers in routing table
 PduRRoutingPath_type * RoutingPaths[] = {
    &PduRRoutingPath_Com_Tx_CanIf_Pdu_Message2,
    &PduRRoutingPath_Com_Tx_CanIf_Pdu_Message8,
    &PduRRoutingPath_Com_Tx_CanIf_Pdu_Message9,
    &PduRRoutingPath_CanIf_Rx_Com_Pdu_Message1,
    &PduRRoutingPath_CanIf_Rx_Com_Pdu_Message7,

    &PduRRoutingPath_CanTp_Rx_Com_Pdu_Message3,
    &PduRRoutingPath_Com_Tx_CanTp_Pdu_Message4,
    &PduRRoutingPath_CanTp_Rx_Dcm_Pdu_Message5,
    &PduRRoutingPath_Dcm_Tx_CanTp_Pdu_Message6,
    NULL
};

//Assign routing table in router configuration
PduR_PBConfigType PBPduRConfig = {
    .PduRConfigurationId = 0,
    .PduRMaxRoutingPathCnt = 5,
    .RoutingPaths = RoutingPaths
};

#endif

#ifdef  ECU2_ALGORITHMICNODE
//****************************************************************
//Receive PDU path from CanIf to Com
//1st creation of path source
 PduRSrcPdu_type PduR_Message_1_Src = {
    .SourcePduHandleId = PDUR_PDU_ID_CANIF_RX_COM_MESSAGE_1,
    .SrcPduRef = &Pdus[0]       //like CAN
};
//2nd creation of path destination
 PduRDestPdu_type PduR_Message_1_Dest = {
    .DestPduHandleId = PDUR_PDU_ID_CANIF_RX_COM_MESSAGE_1,
    .DestPduRef = &Pdus[0]      //like COM
};
//3rd creation of routing path
 PduRRoutingPath_type PduRRoutingPath_CanIf_Rx_Com_Pdu_Message1 = {
    .PduRSrcPduRef = &PduR_Message_1_Src,
    .PduRDestPduRef = &PduR_Message_1_Dest
};
//****************************************************************

 //****************************************************************
 //Receive PDU path from CanIf to Com
 //1st creation of path source
  PduRSrcPdu_type PduR_Message_8_Src = {
     .SourcePduHandleId = PDUR_PDU_ID_CANIF_RX_COM_MESSAGE_8,
     .SrcPduRef = &Pdus[7]       //like CAN
 };
 //2nd creation of path destination
  PduRDestPdu_type PduR_Message_8_Dest = {
     .DestPduHandleId = PDUR_PDU_ID_CANIF_RX_COM_MESSAGE_8,
     .DestPduRef = &Pdus[7]      //like COM
 };
 //3rd creation of routing path
  PduRRoutingPath_type PduRRoutingPath_CanIf_Rx_Com_Pdu_Message8 = {
     .PduRSrcPduRef = &PduR_Message_8_Src,
     .PduRDestPduRef = &PduR_Message_8_Dest
 };
 //****************************************************************

  //****************************************************************
  //Receive PDU path from CanIf to Com
  //1st creation of path source
   PduRSrcPdu_type PduR_Message_9_Src = {
      .SourcePduHandleId = PDUR_PDU_ID_CANIF_RX_COM_MESSAGE_9,
      .SrcPduRef = &Pdus[8]       //like CAN
  };
  //2nd creation of path destination
   PduRDestPdu_type PduR_Message_9_Dest = {
      .DestPduHandleId = PDUR_PDU_ID_CANIF_RX_COM_MESSAGE_9,
      .DestPduRef = &Pdus[8]      //like COM
  };
  //3rd creation of routing path
   PduRRoutingPath_type PduRRoutingPath_CanIf_Rx_Com_Pdu_Message9 = {
      .PduRSrcPduRef = &PduR_Message_9_Src,
      .PduRDestPduRef = &PduR_Message_9_Dest
  };
  //****************************************************************

//****************************************************************
//Transmit PDU path from Com to CanIf
//1st creation of path source
 PduRSrcPdu_type PduR_Message_2_Src = {
    .SourcePduHandleId = PDUR_PDU_ID_COM_TX_CANIF_MESSAGE_2,
    .SrcPduRef = &Pdus[1]   //like COM
};
//2nd creation of path destination
 PduRDestPdu_type PduR_Message_2_Dest = {
    .DestPduHandleId = PDUR_PDU_ID_COM_TX_CANIF_MESSAGE_2,
    .DestPduRef = &Pdus[1]      //like CAN
};
//3rd creation of routing path
 PduRRoutingPath_type PduRRoutingPath_Com_Tx_CanIf_Pdu_Message2 = {
    .PduRSrcPduRef = &PduR_Message_2_Src,
    .PduRDestPduRef = &PduR_Message_2_Dest
};
//****************************************************************
 //****************************************************************
 //Transmit PDU path from Com to CanIf
 //1st creation of path source
  PduRSrcPdu_type PduR_Message_7_Src = {
     .SourcePduHandleId = PDUR_PDU_ID_COM_TX_CANIF_MESSAGE_7,
     .SrcPduRef = &Pdus[6]   //like COM
 };
 //2nd creation of path destination
  PduRDestPdu_type PduR_Message_7_Dest = {
     .DestPduHandleId = PDUR_PDU_ID_COM_TX_CANIF_MESSAGE_7,
     .DestPduRef = &Pdus[6]      //like CAN
 };
 //3rd creation of routing path
  PduRRoutingPath_type PduRRoutingPath_Com_Tx_CanIf_Pdu_Message7 = {
     .PduRSrcPduRef = &PduR_Message_7_Src,
     .PduRDestPduRef = &PduR_Message_7_Dest
 };
 //****************************************************************

//****************************************************************
//Receive PDU path from CanTp to Com
//1st creation of path source
 PduRSrcPdu_type PduR_Message_3_Src = {
    .SourcePduHandleId = PDUR_PDU_ID_CANTP_RX_COM_MESSAGE_3,
    .SrcPduRef = &Pdus[2]       //like CAN
};
//2nd creation of path destination
 PduRDestPdu_type PduR_Message_3_Dest = {
    .DestPduHandleId = PDUR_PDU_ID_CANTP_RX_COM_MESSAGE_3,
    .DestPduRef = &Pdus[2]      //like COM
};
//3rd creation of routing path
 PduRRoutingPath_type PduRRoutingPath_CanTp_Rx_Com_Pdu_Message3 = {
    .PduRSrcPduRef = &PduR_Message_3_Src,
    .PduRDestPduRef = &PduR_Message_3_Dest
};
//****************************************************************

//****************************************************************
//Transmit PDU path from Com to CanTp
//1st creation of path source
 PduRSrcPdu_type PduR_Message_4_Src = {
    .SourcePduHandleId = PDUR_PDU_ID_COM_TX_CANTP_MESSAGE_4,
    .SrcPduRef = &Pdus[3]   //like COM
};
//2nd creation of path destination
 PduRDestPdu_type PduR_Message_4_Dest = {
    .DestPduHandleId = PDUR_PDU_ID_COM_TX_CANTP_MESSAGE_4,
    .DestPduRef = &Pdus[3]      //like CAN
};
//3rd creation of routing path
 PduRRoutingPath_type PduRRoutingPath_Com_Tx_CanTp_Pdu_Message4 = {
    .PduRSrcPduRef = &PduR_Message_4_Src,
    .PduRDestPduRef = &PduR_Message_4_Dest
};
//****************************************************************

//****************************************************************
//Receive PDU path from CanTp to Dcm
//1st creation of path source
 PduRSrcPdu_type PduR_Message_5_Src = {
    .SourcePduHandleId = PDUR_PDU_ID_CANTP_RX_DCM_MESSAGE_5,
    .SrcPduRef = &Pdus[4]       //like CAN
};
//2nd creation of path destination
 PduRDestPdu_type PduR_Message_5_Dest = {
    .DestPduHandleId = PDUR_PDU_ID_CANTP_RX_DCM_MESSAGE_5,
    .DestPduRef = &Pdus[4]      //like DCM
};
//3rd creation of routing path
 PduRRoutingPath_type PduRRoutingPath_CanTp_Rx_Dcm_Pdu_Message5 = {
    .PduRSrcPduRef = &PduR_Message_5_Src,
    .PduRDestPduRef = &PduR_Message_5_Dest
};
//****************************************************************

//****************************************************************
//Transmit PDU path from Dcm to CanTp
//1st creation of path source
 PduRSrcPdu_type PduR_Message_6_Src = {
    .SourcePduHandleId = PDUR_PDU_ID_DCM_TX_CANTP_MESSAGE_6,
    .SrcPduRef = &Pdus[5]   //like DCM
};
//2nd creation of path destination
 PduRDestPdu_type PduR_Message_6_Dest = {
    .DestPduHandleId = PDUR_PDU_ID_DCM_TX_CANTP_MESSAGE_6,
    .DestPduRef = &Pdus[5]      //like CAN
};
//3rd creation of routing path
 PduRRoutingPath_type PduRRoutingPath_Dcm_Tx_CanTp_Pdu_Message6 = {
    .PduRSrcPduRef = &PduR_Message_6_Src,
    .PduRDestPduRef = &PduR_Message_6_Dest
};
//****************************************************************

//Assign paths pointers in routing table
 PduRRoutingPath_type * RoutingPaths[] = {
    &PduRRoutingPath_Com_Tx_CanIf_Pdu_Message2,
    &PduRRoutingPath_Com_Tx_CanIf_Pdu_Message7,
    &PduRRoutingPath_CanIf_Rx_Com_Pdu_Message1,
    &PduRRoutingPath_CanIf_Rx_Com_Pdu_Message8,
    &PduRRoutingPath_CanIf_Rx_Com_Pdu_Message9,

    &PduRRoutingPath_CanTp_Rx_Com_Pdu_Message3,
    &PduRRoutingPath_Com_Tx_CanTp_Pdu_Message4,
    &PduRRoutingPath_CanTp_Rx_Dcm_Pdu_Message5,
    &PduRRoutingPath_Dcm_Tx_CanTp_Pdu_Message6,
    NULL
};

//Assign routing table in router configuration
PduR_PBConfigType PBPduRConfig = {
    .PduRConfigurationId = 0,
    .PduRMaxRoutingPathCnt = 5,
    .RoutingPaths = RoutingPaths
};

#endif

#ifdef  ECU3_ACTUATORNODE
//****************************************************************
//Receive PDU path from CanIf to Com
//1st creation of path source
 PduRSrcPdu_type PduR_Message_1_Src = {
    .SourcePduHandleId = PDUR_PDU_ID_CANIF_RX_COM_MESSAGE_1,
    .SrcPduRef = &Pdus[0]       //like CAN
};
//2nd creation of path destination
 PduRDestPdu_type PduR_Message_1_Dest = {
    .DestPduHandleId = PDUR_PDU_ID_CANIF_RX_COM_MESSAGE_1,
    .DestPduRef = &Pdus[0]      //like COM
};
//3rd creation of routing path
 PduRRoutingPath_type PduRRoutingPath_CanIf_Rx_Com_Pdu_Message1 = {
    .PduRSrcPduRef = &PduR_Message_1_Src,
    .PduRDestPduRef = &PduR_Message_1_Dest
};
//****************************************************************

 //****************************************************************
 //Receive PDU path from CanIf to Com
 //1st creation of path source
  PduRSrcPdu_type PduR_Message_7_Src = {
     .SourcePduHandleId = PDUR_PDU_ID_CANIF_RX_COM_MESSAGE_7,
     .SrcPduRef = &Pdus[6]       //like CAN
 };
 //2nd creation of path destination
  PduRDestPdu_type PduR_Message_7_Dest = {
     .DestPduHandleId = PDUR_PDU_ID_CANIF_RX_COM_MESSAGE_7,
     .DestPduRef = &Pdus[6]      //like COM
 };
 //3rd creation of routing path
  PduRRoutingPath_type PduRRoutingPath_CanIf_Rx_Com_Pdu_Message7 = {
     .PduRSrcPduRef = &PduR_Message_7_Src,
     .PduRDestPduRef = &PduR_Message_7_Dest
 };
 //****************************************************************

  //****************************************************************
  //Receive PDU path from CanIf to Com
  //1st creation of path source
   PduRSrcPdu_type PduR_Message_8_Src = {
      .SourcePduHandleId = PDUR_PDU_ID_CANIF_RX_COM_MESSAGE_8,
      .SrcPduRef = &Pdus[7]       //like CAN
  };
  //2nd creation of path destination
   PduRDestPdu_type PduR_Message_8_Dest = {
      .DestPduHandleId = PDUR_PDU_ID_CANIF_RX_COM_MESSAGE_8,
      .DestPduRef = &Pdus[7]      //like COM
  };
  //3rd creation of routing path
   PduRRoutingPath_type PduRRoutingPath_CanIf_Rx_Com_Pdu_Message8 = {
      .PduRSrcPduRef = &PduR_Message_8_Src,
      .PduRDestPduRef = &PduR_Message_8_Dest
  };
  //****************************************************************

//****************************************************************
//Transmit PDU path from Com to CanIf
//1st creation of path source
 PduRSrcPdu_type PduR_Message_2_Src = {
    .SourcePduHandleId = PDUR_PDU_ID_COM_TX_CANIF_MESSAGE_2,
    .SrcPduRef = &Pdus[1]   //like COM
};
//2nd creation of path destination
 PduRDestPdu_type PduR_Message_2_Dest = {
    .DestPduHandleId = PDUR_PDU_ID_COM_TX_CANIF_MESSAGE_2,
    .DestPduRef = &Pdus[1]      //like CAN
};
//3rd creation of routing path
 PduRRoutingPath_type PduRRoutingPath_Com_Tx_CanIf_Pdu_Message2 = {
    .PduRSrcPduRef = &PduR_Message_2_Src,
    .PduRDestPduRef = &PduR_Message_2_Dest
};
//****************************************************************

//****************************************************************
//Receive PDU path from CanTp to Com
//1st creation of path source
 PduRSrcPdu_type PduR_Message_3_Src = {
    .SourcePduHandleId = PDUR_PDU_ID_CANTP_RX_COM_MESSAGE_3,
    .SrcPduRef = &Pdus[2]       //like CAN
};
//2nd creation of path destination
 PduRDestPdu_type PduR_Message_3_Dest = {
    .DestPduHandleId = PDUR_PDU_ID_CANTP_RX_COM_MESSAGE_3,
    .DestPduRef = &Pdus[2]      //like COM
};
//3rd creation of routing path
 PduRRoutingPath_type PduRRoutingPath_CanTp_Rx_Com_Pdu_Message3 = {
    .PduRSrcPduRef = &PduR_Message_3_Src,
    .PduRDestPduRef = &PduR_Message_3_Dest
};
//****************************************************************

//****************************************************************
//Transmit PDU path from Com to CanTp
//1st creation of path source
 PduRSrcPdu_type PduR_Message_4_Src = {
    .SourcePduHandleId = PDUR_PDU_ID_COM_TX_CANTP_MESSAGE_4,
    .SrcPduRef = &Pdus[3]   //like COM
};
//2nd creation of path destination
 PduRDestPdu_type PduR_Message_4_Dest = {
    .DestPduHandleId = PDUR_PDU_ID_COM_TX_CANTP_MESSAGE_4,
    .DestPduRef = &Pdus[3]      //like CAN
};
//3rd creation of routing path
 PduRRoutingPath_type PduRRoutingPath_Com_Tx_CanTp_Pdu_Message4 = {
    .PduRSrcPduRef = &PduR_Message_4_Src,
    .PduRDestPduRef = &PduR_Message_4_Dest
};
//****************************************************************

//****************************************************************
//Receive PDU path from CanTp to Dcm
//1st creation of path source
 PduRSrcPdu_type PduR_Message_5_Src = {
    .SourcePduHandleId = PDUR_PDU_ID_CANTP_RX_DCM_MESSAGE_5,
    .SrcPduRef = &Pdus[4]       //like CAN
};
//2nd creation of path destination
 PduRDestPdu_type PduR_Message_5_Dest = {
    .DestPduHandleId = PDUR_PDU_ID_CANTP_RX_DCM_MESSAGE_5,
    .DestPduRef = &Pdus[4]      //like DCM
};
//3rd creation of routing path
 PduRRoutingPath_type PduRRoutingPath_CanTp_Rx_Dcm_Pdu_Message5 = {
    .PduRSrcPduRef = &PduR_Message_5_Src,
    .PduRDestPduRef = &PduR_Message_5_Dest
};
//****************************************************************

//****************************************************************
//Transmit PDU path from Dcm to CanTp
//1st creation of path source
 PduRSrcPdu_type PduR_Message_6_Src = {
    .SourcePduHandleId = PDUR_PDU_ID_DCM_TX_CANTP_MESSAGE_6,
    .SrcPduRef = &Pdus[5]   //like DCM
};
//2nd creation of path destination
 PduRDestPdu_type PduR_Message_6_Dest = {
    .DestPduHandleId = PDUR_PDU_ID_DCM_TX_CANTP_MESSAGE_6,
    .DestPduRef = &Pdus[5]      //like CAN
};
//3rd creation of routing path
 PduRRoutingPath_type PduRRoutingPath_Dcm_Tx_CanTp_Pdu_Message6 = {
    .PduRSrcPduRef = &PduR_Message_6_Src,
    .PduRDestPduRef = &PduR_Message_6_Dest
};
//****************************************************************

//Assign paths pointers in routing table
 PduRRoutingPath_type * RoutingPaths[] = {
    &PduRRoutingPath_Com_Tx_CanIf_Pdu_Message2,
    &PduRRoutingPath_CanIf_Rx_Com_Pdu_Message1,
    &PduRRoutingPath_CanIf_Rx_Com_Pdu_Message7,
    &PduRRoutingPath_CanIf_Rx_Com_Pdu_Message8,

    &PduRRoutingPath_CanTp_Rx_Com_Pdu_Message3,
    &PduRRoutingPath_Com_Tx_CanTp_Pdu_Message4,
    &PduRRoutingPath_CanTp_Rx_Dcm_Pdu_Message5,
    &PduRRoutingPath_Dcm_Tx_CanTp_Pdu_Message6,
    NULL
};

//Assign routing table in router configuration
PduR_PBConfigType PBPduRConfig = {
    .PduRConfigurationId = 0,
    .PduRMaxRoutingPathCnt = 4,
    .RoutingPaths = RoutingPaths
};

#endif  //ECU3_ACTUATORNODE

