#ifndef COM_STACKTYPES_H_
#define COM_STACKTYPES_H_


//#include "ComStack_Cfg.h"
#include "Std_Types.h"

#define BUSTRCV_OK 0x00
#define BUSTRCV_E_ERROR 0x01

typedef uint8 PNCHandleType;
typedef uint8 BusTrcvErrorType;

typedef uint16 PduIdType;
typedef uint16 PduLengthType;

typedef struct CPduInfoType {

    uint8*        SduDataPtr;
    
    PduLengthType SduLength;

}PduInfoType;



typedef enum{
    TP_STMIN=0,
    TP_BS,
    TP_BC

}TPParameterType;

typedef enum{ 
    BUFREQ_OK=0,
    BUFREQ_NOT_OK,
    BUFREQ_E_BUSY,
    BUFREQ_E_OVFL

}BufReq_ReturnType;

typedef enum {
    TP_DATACONF,
    TP_DATARETRY,
    TP_CONFPENDING,
    TP_NORETRY
    
}TpDataStateType;

typedef struct CRetryInfoType{

    TpDataStateType TpDataState;
    PduLengthType   TxTpDataCnt;
    
}RetryInfoType;

typedef uint8 NetworkHandleType ;
typedef uint8 IcomConfigIdType ;

typedef enum{
    ICOM_SWITCH_E_OK,
    ICOM_SWITCH_E_FAILED

}IcomSwitch_ErrorType;
    
#endif
