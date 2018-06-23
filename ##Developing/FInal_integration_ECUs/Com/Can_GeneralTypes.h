#ifndef CAN_GENERAL_TYPES_H_
#define CAN_GENERAL_TYPES_H_


#include "types.h"
#include "ComStack_Types.h"

#define NUM_HTH     16  	// 16 hardware transmit handle 
#define NUM_HRH     16   	// 16 receive receive handle 

// uint16 : standard IDS
// uint32 : Extended IDS
typedef uint16 Can_IdType ;

// uint8 : For CAN hardware units with less than 255 HW objects
//uint16 :For CAN hardware units with more than 255 HW objects
typedef uint8 Can_HwHandleType ;

 

typedef struct CCan_PduType{
    PduIdType swPduHandle ;
    uint8 length;
    Can_IdType id;
    uint8* sdu ;
}Can_PduType;

typedef struct CCan_HwType{
    Can_IdType CanId;
    Can_HwHandleType Hoh;
    uint8 ControllerId ;

}Can_HwType;                          

typedef enum{
   
    CAN_OK  ,
    CAN_NOT_OK ,
    CAN_BUSY

}Can_ReturnType;

typedef enum {

    CAN_ERRORSTATE_ACTIVE , 
    CAN_ERRORSTATE_PASSIVE ,
    CAN_ERRORSTATE_BUSOFF

}Can_ErrorStateType;


typedef enum {

    CAN_CS_UNINIT ,
    CAN_CS_STARTED ,
    CAN_CS_STOPPED ,
    CAN_CS_SLEEP

}Can_ControllerStateType,Can_StateTransitionType;

 

typedef struct CanControllerBaudRate{
   
    uint16 CanControllerBaudRate;           //in kbps
    uint16 BaudRateConfigID ;            //Uniquely identifies a specific baud rate configuration. This ID is used by SetBaudrate API 
    uint8 CanControllerPropSeg ;          // Specifies propagation delay in time quantas. 
    uint8 CanControllerSeg1 ;            //Specifies phase segment 1 in time quantas.
    uint8 CanControllerSeg2 ;            //Specifies phase segment 2 in time quantas.
    uint8 CanControllerSyncJumpWidth ;   //Specifies the synchronization jump width for the controller in time quantas.
    
}Can_ControllerBaudRate ;

typedef enum{
    
    Rx_Interrupt,
    Tx_Interrupt,
    Error_InterruptEnable,
    status_InterruptEnable
    
}can_InterruptType ;



////////////////////////////////////////
typedef enum{
    CANTRCV_TRCVMODE_NORMAL=0,
    CANTRCV_TRCVMODE_STANDBY,
    CANTRCV_TRCVMODE_SLEEP
}CanTrcv_TrcvModeType;

typedef enum{
    CANTRCV_WUMODE_ENABLE=0,
    CANTRCV_WUMODE_DISABLE=1,
    CANTRCV_WUMODE_CLEAR=2,
}CanTrcv_TrcvWakeupModeType;

typedef enum{
    CANTRCV_WU_ERROR=0,
    CANTRCV_WU_NOT_SUPPORTED=1,
    CANTRCV_WU_BY_BUS=2,
    CANTRCV_WU_INTERNALLY=3,
    CANTRCV_WU_RESET=4,
    CANTRCV_WU_POWER_ON=5,
    CANTRCV_WU_BY_PIN=6,
    CANTRCV_WU_BY_SYSERR=7
}CanTrcv_TrcvWakeupReasonType;
////////////////////////////////////////



#endif 
