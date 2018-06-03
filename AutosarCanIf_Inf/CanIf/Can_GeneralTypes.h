#ifndef CAN_GENERALTYPES_H_INCLUDED
#define CAN_GENERALTYPES_H_INCLUDED

#include "ComStack_Types.h"


typedef uint32 Can_IdType;
typedef uint16 Can_HwHandleType;

/// this type not declared here
typedef struct {
    uint16 CanObjectId;
}CanHardwareObjectType;


typedef enum {
    CAN_CS_UNINIT=0,
    CAN_CS_STARTED=1,
    CAN_CS_STOPPED=2,
    CAN_CS_SLEEP=3
}Can_ControllerStateType;

typedef enum {
    CAN_ERRORSTATE_ACTIVE,
    CAN_ERRORSTATE_PASSIVE,
    CAN_ERRORSTATE_BUSOFF
}Can_ErrorStateType;

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




typedef struct {
    Can_IdType  CanId;
    Can_HwHandleType  Hoh;
    uint8  ControllerId;
}Can_HwType;

typedef struct {
    PduIdType  swPduHandle;
    uint8      length;
    Can_IdType id;
    uint8*     sdu;
}Can_PduType;

#endif // CAN_GENERALTYPES_H_INCLUDED
