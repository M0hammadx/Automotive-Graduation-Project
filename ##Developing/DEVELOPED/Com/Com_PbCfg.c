/** incomplete Com configuration code file used as a test to PDUR module */

#include "Com.h"

/*
 * I-PDU definitions
 */


#ifdef ECU1_SENSORYNODE
const ComIPdu_type ComIPdu[] = {

    { // CanDB_Message_1
        //RX message
      //Ultra_REQ
        .IPduHandleId = COM_PDU_ID_CANIF_RX_COM_MESSAGE_1,
        .PduIdRef = &Pdus[0]   //like DST PDUR
    },
    { // CanDB_Message_2
            //RX message
      //Car_Task
            .IPduHandleId = COM_PDU_ID_CANIF_RX_COM_MESSAGE_2,
            .PduIdRef = &Pdus[6]   //like DST PDUR
    },
    { // CanDB_Message_6
        //TX message
      //Ultra_Data1
        .IPduHandleId = COM_PDU_ID_COM_TX_CANIF_MESSAGE_6,
        .PduIdRef = &Pdus[1]   //like SRC PDUR
    },
    { // CanDB_Message_7
            //TX message
      //Encoder_Data
            .IPduHandleId = COM_PDU_ID_COM_TX_CANIF_MESSAGE_7,
            .PduIdRef = &Pdus[7]   //like SRC PDUR
    },
    { // CanDB_Message_8
            //TX message
      //Comp_Data + temp
            .IPduHandleId = COM_PDU_ID_COM_TX_CANIF_MESSAGE_8,
            .PduIdRef = &Pdus[8]   //like SRC PDUR
    },
    { // CanDB_Message_3
        //RX message
        .IPduHandleId = COM_PDU_ID_CANTP_RX_COM_MESSAGE_3,
        .PduIdRef = &Pdus[2]   //like DST PDUR
    },
    { // CanDB_Message_4
        //TX message
        .IPduHandleId = COM_PDU_ID_COM_TX_CANTP_MESSAGE_4,
        .PduIdRef = &Pdus[3]   //like SRC PDUR
    },
    {
        //nothing
    }
};
const Com_ConfigType ComConfiguration = {
    .ComIPdu = ComIPdu,
    .ComMaxIPduCnt = 5
};

#endif

#ifdef ECU2_ALGORITHMICNODE
const ComIPdu_type ComIPdu[] = {

	{ // CanDB_Message_1
	    //RX message
	  //Ultra_Data1
		.IPduHandleId = COM_PDU_ID_CANIF_RX_COM_MESSAGE_1,
        .PduIdRef = &Pdus[0]   //like DST PDUR
	},
    { // CanDB_Message_1
        //RX message
        //Encoder_Data
        .IPduHandleId = COM_PDU_ID_CANIF_RX_COM_MESSAGE_5,
        .PduIdRef = &Pdus[7]   //like DST PDUR
    },
    { // CanDB_Message_1
        //RX message
      //Comp_Data
        .IPduHandleId = COM_PDU_ID_CANIF_RX_COM_MESSAGE_7,
        .PduIdRef = &Pdus[8]   //like DST PDUR
    },
	{ // CanDB_Message_2
	    //TX message
	  //Car_Task
		.IPduHandleId = COM_PDU_ID_COM_TX_CANIF_MESSAGE_2,
        .PduIdRef = &Pdus[1]   //like SRC PDUR
	},
	{ // CanDB_Message_6
	        //TX message
	  //Ultra_REQ
	        .IPduHandleId = COM_PDU_ID_COM_TX_CANIF_MESSAGE_6,
	        .PduIdRef = &Pdus[6]   //like SRC PDUR
    },

    //CAN TP
	{ // CanDB_Message_3
	    //RX message
		.IPduHandleId = COM_PDU_ID_CANTP_RX_COM_MESSAGE_3,
        .PduIdRef = &Pdus[2]   //like DST PDUR
	},
	{ // CanDB_Message_4
	    //TX message
		.IPduHandleId = COM_PDU_ID_COM_TX_CANTP_MESSAGE_4,
        .PduIdRef = &Pdus[3]   //like SRC PDUR
	},
	{
        //nothing
	}
};
const Com_ConfigType ComConfiguration = {
    .ComIPdu = ComIPdu,
    .ComMaxIPduCnt = 5
};

#endif


#ifdef ECU3_ACTUATORNODE
const ComIPdu_type ComIPdu[] = {

    { // CanDB_Message_1
        //RX message
      //Car_Task
        .IPduHandleId = COM_PDU_ID_CANIF_RX_COM_MESSAGE_1,
        .PduIdRef = &Pdus[0]   //like DST PDUR
    },
    { // CanDB_Message_2
            //RX message
      //Encoder_Data
            .IPduHandleId = COM_PDU_ID_CANIF_RX_COM_MESSAGE_2,
            .PduIdRef = &Pdus[6]   //like DST PDUR
    },
    { // CanDB_Message_2
            //RX message
      //Comp_Data
            .IPduHandleId = COM_PDU_ID_CANIF_RX_COM_MESSAGE_6,
            .PduIdRef = &Pdus[7]   //like DST PDUR
    },
    { // CanDB_Message_5
        //TX message
      //Steer_Encoder
        .IPduHandleId = COM_PDU_ID_COM_TX_CANIF_MESSAGE_5,
        .PduIdRef = &Pdus[1]   //like SRC PDUR
    },
    { // CanDB_Message_3
        //RX message
        .IPduHandleId = COM_PDU_ID_CANTP_RX_COM_MESSAGE_3,
        .PduIdRef = &Pdus[2]   //like DST PDUR
    },
    { // CanDB_Message_4
        //TX message
        .IPduHandleId = COM_PDU_ID_COM_TX_CANTP_MESSAGE_4,
        .PduIdRef = &Pdus[3]   //like SRC PDUR
    },
    {
        //nothing
    }
};
const Com_ConfigType ComConfiguration = {
    .ComIPdu = ComIPdu,
    .ComMaxIPduCnt = 4
};

#endif




