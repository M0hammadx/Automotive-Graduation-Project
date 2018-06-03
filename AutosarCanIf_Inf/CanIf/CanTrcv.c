#include "CanTrcv.h"

Std_ReturnType CanTrcv_SetOpMode( uint8 Transceiver, CanTrcv_TrcvModeType OpMode )
{
    printf("\n CanTrcv_SetOpMode done");
    return E_OK;
}

Std_ReturnType CanTrcv_GetOpMode( uint8 Transceiver, CanTrcv_TrcvModeType* OpMode )
{
    *OpMode = CANTRCV_TRCVMODE_NORMAL;
    printf("\n CanTrcv_SetOpMode done");
    return E_OK;
}

Std_ReturnType CanTrcv_GetBusWuReason( uint8 Transceiver, CanTrcv_TrcvWakeupReasonType* reason )
{
    *reason = CANTRCV_WU_POWER_ON;
    printf("\n CanTrcv_GetBusWuReason done");
    return E_OK;
}

Std_ReturnType CanTrcv_SetWakeupMode( uint8 Transceiver, CanTrcv_TrcvWakeupModeType TrcvWakeupMode )
{
    printf("\n CanTrcv_SetWakeupMode done");
    return E_OK;
}

Std_ReturnType CanTrcv_ClearTrcvWufFlag( uint8 Transceiver )
{
    printf("\n CanTrcv_ClearTrcvWufFlag done");
    return E_OK;
}

Std_ReturnType CanTrcv_CheckWakeFlag( uint8 Transceiver )
{
    printf("\n CanTrcv_CheckWakeFlag done");
    return E_OK;
}

