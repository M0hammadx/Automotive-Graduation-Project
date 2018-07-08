/*
*	\file 	hw_can.h
*              \brief	this file contains addresses of can module 
*
*
*	\date	13/10/2017
*	\Author 	 noha 
*/

#ifndef HW_CAN_H_
#define HW_CAN_H_
/*============================================================================================= */
/*				Include Files				                */
/*==============================================================================================*/

/* None */

/* ===============================================================================================*/
/*			Macros &Typedefs						      */
/*================================================================================================*/
#define BASE_CAN0     0x40040000	
#define BASE_CAN1     0x40041000

/************************** CAN register offsets *****************************/
#define CAN_CANCTL_OFFSET       0X000
#define CAN_CANSTS_OFFSET       0X004
#define CAN_CANERR_OFFSET       0X008

#define CAN_CANBIT_OFFSET       0X00C
#define CAN_CANINT_OFFSET       0X010
#define CAN_CANTST_OFFSET       0X014
#define CAN_CANBRPE_OFFSET      0X018
#define CAN_CANIF1CRQ_OFFSET    0X020
#define CAN_CANIF1CMSK_OFFSET   0X024
#define CAN_CANIF1MSK1_OFFSET   0X028
#define CAN_CANIF1MSK2_OFFSET   0X02C
#define CAN_CANIF1ARB1_OFFSET   0X030
#define CAN_CANIF1ARB2_OFFSET   0X034
#define CAN_CANIF1MCTL_OFFSET   0X038
#define CAN_CANIF1DA1_OFFSET    0X03C

#define CAN_CANIF1DA2_OFFSET    0X040
#define CAN_CANIF1DB1_OFFSET    0X044
#define CAN_CANIF1DB2_OFFSET    0X048
#define CAN_CANIF2CRQ_OFFSET    0X080
#define CAN_CANIF2CMSK_OFFSET   0X084
#define CAN_CANIF2MSK1_OFFSET   0X088
#define CAN_CANIF2MSK2_OFFSET   0X08C
#define CAN_CANIF2ARB1_OFFSET   0X090
#define CAN_CANIF2ARB2_OFFSET   0X094
#define CAN_CANIF2MCTL_OFFSET   0X098
#define CAN_CANIF2DA1_OFFSET    0X09C
#define CAN_CANIF2DA2_OFFSET    0X0A0
#define CAN_CANIF2DB1_OFFSET       0X0A4
#define CAN_CANIF2DB2_OFFSET       0X0A8
#define CAN_CANTXRQ1_OFFSET       0X100
#define CAN_CANTXRQ2_OFFSET       0X104
#define CAN_CANNWDA1_OFFSET       0X120
#define CAN_CANNWDA2_OFFSET       0X124
#define CAN_CANMSG1INT_OFFSET       0X140
#define CAN_CANMSG2INT_OFFSET       0X144
#define CAN_CANMSG1VAL_OFFSET       0X160
#define CAN_CANMSG2VAL_OFFSET       0X164




#endif
