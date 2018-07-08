/** incomplete COM post build header file used as a test to PDUR module */

#ifndef COM_PBCFG_H_INCLUDED
#define COM_PBCFG_H_INCLUDED

#include "ECU_CONFIGURATION.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#ifdef ECU1_SENSORYNODE

#define COM_PDU_ID_COM_TX_CANIF_MESSAGE_6      3   //Ultra_Data1
#define COM_PDU_ID_COM_TX_CANIF_MESSAGE_7      4   //Encoder_Data
#define COM_PDU_ID_COM_TX_CANIF_MESSAGE_8      5   //Comp_Data

#define COM_PDU_ID_CANIF_RX_COM_MESSAGE_1      1   //Ultra_REQ
#define COM_PDU_ID_CANIF_RX_COM_MESSAGE_2      2   //Car_Task

#define COM_PDU_ID_CANTP_RX_COM_MESSAGE_3  10
#define COM_PDU_ID_COM_TX_CANTP_MESSAGE_4  11


#endif

#ifdef ECU2_ALGORITHMICNODE

#define COM_PDU_ID_COM_TX_CANIF_MESSAGE_2      2   //Car_Task
#define COM_PDU_ID_COM_TX_CANIF_MESSAGE_6      3   //Ultra_REQ

#define COM_PDU_ID_CANIF_RX_COM_MESSAGE_1      1   //Ultra_Data1
#define COM_PDU_ID_CANIF_RX_COM_MESSAGE_5      4   //Encoder_Data
#define COM_PDU_ID_CANIF_RX_COM_MESSAGE_7      5   //Comp_Data

#define COM_PDU_ID_CANTP_RX_COM_MESSAGE_3  10
#define COM_PDU_ID_COM_TX_CANTP_MESSAGE_4  11

#endif

#ifdef ECU3_ACTUATORNODE

#define COM_PDU_ID_COM_TX_CANIF_MESSAGE_5      3   //Steer_Encoder

#define COM_PDU_ID_CANIF_RX_COM_MESSAGE_1      1   //Car_Task
#define COM_PDU_ID_CANIF_RX_COM_MESSAGE_2      2   //Encoder_Data
#define COM_PDU_ID_CANIF_RX_COM_MESSAGE_6      4   //Comp_Data

#define COM_PDU_ID_CANTP_RX_COM_MESSAGE_3  10
#define COM_PDU_ID_COM_TX_CANTP_MESSAGE_4  11


#endif



extern const Com_ConfigType ComConfiguration;

#endif // COM_PBCFG_H_INCLUDED
