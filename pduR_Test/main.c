#include <stdio.h>
#include <stdlib.h>
#include "pduR_test.h"
int main()
{
    //this file is built to test autosar router
    printf("PDU Router test\n");

    printf("\nrouter initialization\n");
    PduR_Init_Test();

    printf("\nrouter CANIF -> COM . TX confirmation\n");
    PduR_CanIfTxConfirmation_Test();

    printf("\nrouter CANIF -> COM . RX indication\n");
    PduR_CanIfRxIndication_Test();

    printf("\nrouter CANIF -> COM . trigger transmit  \n");
    PduR_CanIfTriggerTransmit_Test();

    /** ---------------------------------------------------------- */
    printf("\nrouter COM -> CANIF . transmit, CancelTransmit, ChangeParameter &CancelReceive functions \n");
    PduR_ComTransmit_Test();

    /** ---------------------------------------------------------- */
    printf("\nrouter COM -> CANTP . transmit, Copy TX Data, TX confirmation functions and\nCancelTransmit, ChangeParameter, CancelReceive functions \n");
    PduR_ComTransmit_Test2();

    printf("\nrouter CANTP -> COM . StartOfReception , CopyRxData, RX indication  functions \n");
    PduR_CanTpStartOfReception_Test();

    /** ---------------------------------------------------------- */
    printf("\nrouter DCM -> CANTP . transmit, Copy TX Data, TX confirmation functions and\nCancelTransmit, ChangeParameter, CancelReceive functions \n");
    PduR_DcmTransmit_Test();

    printf("\nrouter CANTP -> DCM . StartOfReception , CopyRxData, RX indication  functions \n");
    PduR_CanTpStartOfReception_Test2();

    /** ---------------------------------------------------------- */
    return 0;
}

