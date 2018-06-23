#include "CAN.h"

#include "../inc/tm4c123gh6pm.h"
#include "CanIf_Cbk.h"

#include <string.h>

static uint8 Max_transmitObjects = 0, Max_ReceiveObjects = 0;
static uint32 BaseAddress[ControllerNum] = { 0 };
static uint8 Can_DisableInterruptCount[ControllerNum] = { 0 };

static uint8 dataReceived[8];
//static uint8 ControllerID[ControllerNum];
static Can_PduType TrnsmPDU[ControllerNum][MAX_MSG_NUM];
static uint8 i, j = 0;
static const Can_ConfigType* GlobalConfig;

static Can_StateTransitionType ControllerMode[ControllerNum];
static ModuleStateM moduleState = CAN_UNINT;

void Can_InterruptHandler(uint8 Controller)
{
    //CanHardwareObject *HardwareObject;
    Can_HwType Can_Receive;
    PduInfoType pduinfo;
    uint32 CANSTS, objectnum;
    //uint8 objType ;
    uint8 DLC;
    uint32 CANINT = HW_READ_REG_32BIT(
            BaseAddress[Controller]+CAN_CANINT_OFFSET);

    if (CANINT == 0x8000)
    {

        CANSTS = HW_READ_REG_32BIT(BaseAddress[Controller]+CAN_CANSTS_OFFSET);
        if (CANSTS & 0x80)
        {  // busoff

            Can_SetControllerMode(Controller, CAN_CS_STOPPED);
            CanIf_ControllerBusOff(Controller);
        }
    }
    else if (CANINT > 0 && CANINT <= 0x0020)
    {
        objectnum = HW_READ_REG_32BIT(
                BaseAddress[Controller]+CAN_CANINT_OFFSET);
        //transmit
        if (0 < objectnum && objectnum <= Max_transmitObjects)
        {

            //  HW_RESET_BIT(BaseAddress[Controller]+CAN_CANSTS_OFFSET,3);   // TXOK
            HW_WRITE_REG32_MASKED(BaseAddress[Controller]+CAN_CANIF1CMSK_OFFSET,
                                  0x08, 0xff);  //clearpnd
//               CANINT =  HW_READ_REG_32BIT(BaseAddress[Controller]+CAN_CANINT_OFFSET);     
//                HW_WRITE_REG32_MASKED(BaseAddress[Controller]+CAN_CANIF1CRQ_OFFSET,CANINT,0x3f);
            HW_WRITE_REG32_MASKED(BaseAddress[Controller]+CAN_CANIF1CRQ_OFFSET,
                                  objectnum, 0x3f);
            CanIf_TxConfirmation(TrnsmPDU[Controller][objectnum].swPduHandle);

        }
        objectnum = HW_READ_REG_32BIT(
                BaseAddress[Controller]+CAN_CANINT_OFFSET);
        //receive
        if (objectnum > 16 && objectnum <= 32)
        {

            //  HW_RESET_BIT(BaseAddress[Controller]+CAN_CANSTS_OFFSET,4);   // RXOK  
            HW_WRITE_REG32_MASKED(BaseAddress[Controller]+CAN_CANIF2CMSK_OFFSET,
                                  0x08, 0xff);  //clearpnd
//               CANINT =  HW_READ_REG_32BIT(BaseAddress[Controller]+CAN_CANINT_OFFSET);     
            HW_WRITE_REG32_MASKED(BaseAddress[Controller]+CAN_CANIF2CRQ_OFFSET,
                                  objectnum, 0x3f);

            HW_WRITE_REG_32BIT(BaseAddress[Controller]+CAN_CANIF2CMSK_OFFSET,
                               0x73);
            HW_WRITE_REG32_MASKED(BaseAddress[Controller]+CAN_CANIF2CRQ_OFFSET,
                                  CANINT, 0x3f);
            dataReceived[0] = HW_READ_REG32_MASKED(
                    BaseAddress[Controller]+CAN_CANIF2DA1_OFFSET, 0x00FF);
            dataReceived[1] =
                    (HW_READ_REG32_MASKED(
                            BaseAddress[Controller]+CAN_CANIF2DA1_OFFSET,
                            0xFF00)
                            >> 8);
            dataReceived[2] = (HW_READ_REG32_MASKED(
                    BaseAddress[Controller]+CAN_CANIF2DA2_OFFSET, 0x00ff));
            dataReceived[3] =
                    (HW_READ_REG32_MASKED(
                            BaseAddress[Controller]+CAN_CANIF2DA2_OFFSET,
                            0xFF00)
                            >> 8);
            dataReceived[4] = (HW_READ_REG32_MASKED(
                    BaseAddress[Controller]+CAN_CANIF2DB1_OFFSET, 0x00ff));
            dataReceived[5] =
                    ((HW_READ_REG32_MASKED(
                            BaseAddress[Controller]+CAN_CANIF2DB1_OFFSET,
                            0xFF00)) >> 8);
            dataReceived[6] = (HW_READ_REG32_MASKED(
                    BaseAddress[Controller]+CAN_CANIF2DB2_OFFSET, 0x00ff));
            dataReceived[7] =
                    ((HW_READ_REG32_MASKED(
                            BaseAddress[Controller]+CAN_CANIF2DB2_OFFSET,
                            0xFF00)) >> 8);
            DLC = HW_READ_REG32_MASKED(
                    BaseAddress[Controller]+CAN_CANIF2MCTL_OFFSET, 0x0f);

            Can_Receive.CanId =
                    HW_READ_REG32_MASKED(
                            BaseAddress[Controller]+CAN_CANIF2ARB2_OFFSET,
                            0x1ffc)
                            >> 2;
            Can_Receive.ControllerId = Controller;
            Can_Receive.Hoh = objectnum;

            pduinfo.SduDataPtr = dataReceived;
            pduinfo.SduLength = DLC;
            CanIf_RxIndication(&Can_Receive, &pduinfo);

        }

    }

}

void CAN0_Handler()
{
    Can_InterruptHandler(CAN0ID);

}
void CAN1_Handler()
{
    Can_InterruptHandler(CAN1ID);
}

void Can_Init(const Can_ConfigType* Config)
{
    uint32 mask, ID;
    uint16 msgNumb;
    uint32 CanBase = 0;
    CanController CanControllerobj;
    if (moduleState != CAN_UNINT)
    {
        //CAN_E_TRANSITION
    }
    GlobalConfig = Config;

    for (i = 0; i < ControllerNum; i++)
    {

        ControllerMode[i] = CAN_CS_STOPPED;

        CanControllerobj = (GlobalConfig->canControllers[i]);
        CanBase = CanControllerobj.CanControllerBaseAddress;
        //ControllerID[i] = CanControllerobj.CanControllerId ;
        BaseAddress[i] = CanBase;
        HW_SET_BIT(CanBase+CAN_CANCTL_OFFSET, 0); // set init bit to enter init mode
        ///////////loopback
//        HW_SET_BIT(CanBase+CAN_CANCTL_OFFSET,7);
//        HW_SET_BIT(CanBase+CAN_CANTST_OFFSET,4);
        Can_SetBaudrate(
                CanControllerobj.CanControllerId,
                CanControllerobj.CanControllerBaudRateConfigobj->CanControllerBaudRateConfigID);

        //installNIVCISRFunction(CanControllerobj.CanControllerId+39, &Can_InterruptHandler ); ///////////////////////////////////////////////////
        NVICInterruptEnable((g_ISRVirIdx_t) (39 + i), 0, 0);

        for (j = 0; j < MAX_MSG_NUM; j++)
        {

            if (CanBase
                    == Config->HOH[j].CanControllerRef->CanControllerBaseAddress)
            {

                //initialize transmitted messages
                if (Config->HOH[j].CanObjectType == 0)
                {
                    Max_transmitObjects++;
                    HW_WRITE_REG32_MASKED(CanBase+CAN_CANIF1CMSK_OFFSET,
                                          VALUEIF1CMSK, 0xff);
                    if (Config->HOH[j].CanIdType == STANDARD)
                    {            // 11 bit

                        mask = ((Config->HOH[j].CanHwFilterptr->CanHwFilterMask)
                                << 2);
                        HW_WRITE_REG_32BIT(CanBase+CAN_CANIF1MSK2_OFFSET, mask);
                        HW_SET_BIT(CanBase+CAN_CANIF1MSK2_OFFSET, 14);    //MDIR
                        HW_RESET_BIT(CanBase+CAN_CANIF1MSK2_OFFSET, 15);
                        ID = ((Config->HOH[j].CanHwFilterptr->CanHwFilterCode)
                                << 2) | (1 << 13) | (1 << 15);  // ID and msgval
                        HW_WRITE_REG32_MASKED(CanBase+CAN_CANIF1ARB2_OFFSET, ID,
                                              0xffff);
                    }
                    else if (Config->HOH[j].CanIdType == EXTENDED)
                    {
                        mask = (Config->HOH[j].CanHwFilterptr->CanHwFilterMask); //29 bit
                        HW_WRITE_REG_32BIT(CanBase+CAN_CANIF1MSK1_OFFSET,
                                           mask & 0x0000ffff);
                        HW_WRITE_REG_32BIT(CanBase+CAN_CANIF1MSK2_OFFSET,
                                           ((mask & 0x1fff0000) >> 16));
                        HW_WRITE_REG32_MASKED(CanBase+CAN_CANIF1MSK2_OFFSET,0xC000,0xC000); //MXTD-MDIR
                        ID = Config->HOH[j].CanHwFilterptr->CanHwFilterCode; // ID
                        HW_WRITE_REG_32BIT(CanBase+CAN_CANIF1ARB1_OFFSET,
                                           ID & 0x0000FFFF);
                        HW_WRITE_REG32_MASKED(CanBase+CAN_CANIF1ARB2_OFFSET,
                                              (ID & 0x1FFF0000 >> 16), 0x1FFF);
                        HW_SET_BIT(CanBase+CAN_CANIF1ARB2_OFFSET, 13); // TRansmit message
                        HW_WRITE_REG32_MASKED(CanBase+CAN_CANIF1ARB2_OFFSET,0xC000,0xC000); //MSGVAL-XTD
                    }
                    HW_WRITE_REG_32BIT(CanBase+CAN_CANIF1MCTL_OFFSET,
                                       CANIF1MCTL);       //TxIE-UMASK-EOB-DLC=8
                    msgNumb = Config->HOH[j].CanObjectId;
                    HW_WRITE_REG32_MASKED(CanBase+CAN_CANIF1CRQ_OFFSET, msgNumb,
                                          0x3f);       // message number
                }
                //initialize received messages
                else if (Config->HOH[j].CanObjectType == 1)
                {
                    Max_ReceiveObjects++;
                    HW_WRITE_REG32_MASKED(CanBase+CAN_CANIF2CMSK_OFFSET,
                                          VALUEIF2CMSK, 0xff);
                    if (Config->HOH[j].CanIdType == STANDARD)
                    {            // 11 bit
                        mask = ((Config->HOH[j].CanHwFilterptr->CanHwFilterMask)
                                << 2);
                        HW_WRITE_REG_32BIT(CanBase+CAN_CANIF2MSK2_OFFSET, mask);
                        HW_SET_BIT(CanBase+CAN_CANIF2MSK2_OFFSET, 14);    //MDIR
                        ID = ((Config->HOH[j].CanHwFilterptr->CanHwFilterCode)
                                << 2) | (1 << 15);  // ID and msgval
                        HW_WRITE_REG32_MASKED(CanBase+CAN_CANIF2ARB2_OFFSET, ID,
                                              0xffff);
                    }
                    else if (Config->HOH[j].CanIdType == EXTENDED)
                    {
                        mask = (Config->HOH[j].CanHwFilterptr->CanHwFilterMask); //29 bit
                        HW_WRITE_REG_32BIT(CanBase+CAN_CANIF2MSK1_OFFSET,
                                           mask & 0x0000ffff);

                        HW_WRITE_REG_32BIT(CanBase+CAN_CANIF2MSK2_OFFSET,
                                           ((mask & 0x1fff0000) >> 16));
                        HW_WRITE_REG32_MASKED(CanBase+CAN_CANIF2MSK2_OFFSET,0xC000,0xC000); //MXTD-MDIR
                        ID = Config->HOH[j].CanHwFilterptr->CanHwFilterCode; // ID
                        HW_WRITE_REG_32BIT(CanBase+CAN_CANIF2ARB1_OFFSET,
                                           ID & 0x0000FFFF);
                        HW_WRITE_REG32_MASKED(CanBase+CAN_CANIF2ARB2_OFFSET,
                                              (ID & 0x1FFF0000 >> 16), 0x1FFF);
                        HW_RESET_BIT(CanBase+CAN_CANIF2ARB2_OFFSET, 13); // receive message
                        HW_WRITE_REG32_MASKED(CanBase+CAN_CANIF2ARB2_OFFSET,0xC000,0xC000); //MSGVAL-XTD
                    }
                    HW_WRITE_REG_32BIT(CanBase+CAN_CANIF2MCTL_OFFSET,
                                       CANIF2MCTL);       //RxIE-UMASK-EOB-DLC=8
                    msgNumb = Config->HOH[j].CanObjectId;
                    HW_WRITE_REG32_MASKED(CanBase+CAN_CANIF2CRQ_OFFSET, msgNumb,
                                          0x3f);       // message number
                }

            }

        }

    }
    moduleState = CAN_READY;

}

void Can_DeInit(void)
{
    uint32 canbase;
    if (moduleState != CAN_READY)
    {
        //CAN_E_TRANSITION
    }
    moduleState = CAN_UNINT;

    for (i = 0; i < ControllerNum; i++)
    {
        if (ControllerMode[i] == CAN_CS_STARTED)
        {
            //CAN_E_TRANSITION
        }
        canbase = (GlobalConfig->canControllers[i].CanControllerBaseAddress);

        HW_WRITE_REG_32BIT(canbase+CAN_CANCTL_OFFSET,0x00000001);
        HW_WRITE_REG_32BIT(canbase+CAN_CANSTS_OFFSET,0x00000000);
        HW_WRITE_REG_32BIT(canbase+CAN_CANERR_OFFSET,0x00000000);
        HW_WRITE_REG_32BIT(canbase+CAN_CANBIT_OFFSET,0x00002301);
        HW_WRITE_REG_32BIT(canbase+CAN_CANINT_OFFSET,0x00000000);
        HW_WRITE_REG_32BIT(canbase+CAN_CANTST_OFFSET,0x00000000);
        HW_WRITE_REG_32BIT(canbase+CAN_CANBRPE_OFFSET,0x00000000);
        //reset IF1
        HW_WRITE_REG_32BIT(canbase+CAN_CANIF1CRQ_OFFSET,0x00000001);
        HW_WRITE_REG_32BIT(canbase+CAN_CANIF1CMSK_OFFSET,0x00000000);
        HW_WRITE_REG_32BIT(canbase+CAN_CANIF1MSK1_OFFSET,0x0000FFFF);
        HW_WRITE_REG_32BIT(canbase+CAN_CANIF1MSK2_OFFSET,0x0000FFFF);
        HW_WRITE_REG_32BIT(canbase+CAN_CANIF1ARB1_OFFSET,0x00000000);
        HW_WRITE_REG_32BIT(canbase+CAN_CANIF1ARB2_OFFSET,0x00000000);
        HW_WRITE_REG_32BIT(canbase+CAN_CANIF1MCTL_OFFSET,0x00000000);
        HW_WRITE_REG_32BIT(canbase+CAN_CANIF1DA1_OFFSET,0x00000000);
        HW_WRITE_REG_32BIT(canbase+CAN_CANIF1DA2_OFFSET,0x00000000);
        HW_WRITE_REG_32BIT(canbase+CAN_CANIF1DB1_OFFSET,0x00000000);
        HW_WRITE_REG_32BIT(canbase+CAN_CANIF1DB2_OFFSET,0x00000000);
        //reset IF2
        HW_WRITE_REG_32BIT(canbase+CAN_CANIF2CRQ_OFFSET,0x00000001);
        HW_WRITE_REG_32BIT(canbase+CAN_CANIF2CMSK_OFFSET,0x00000000);
        HW_WRITE_REG_32BIT(canbase+CAN_CANIF2MSK1_OFFSET,0x0000FFFF);
        HW_WRITE_REG_32BIT(canbase+CAN_CANIF2MSK2_OFFSET,0x0000FFFF);
        HW_WRITE_REG_32BIT(canbase+CAN_CANIF2ARB1_OFFSET,0x00000000);
        HW_WRITE_REG_32BIT(canbase+CAN_CANIF2ARB2_OFFSET,0x00000000);
        HW_WRITE_REG_32BIT(canbase+CAN_CANIF2MCTL_OFFSET,0x00000000);
        HW_WRITE_REG_32BIT(canbase+CAN_CANIF2DA1_OFFSET,0x00000000);
        HW_WRITE_REG_32BIT(canbase+CAN_CANIF2DA2_OFFSET,0x00000000);
        HW_WRITE_REG_32BIT(canbase+CAN_CANIF2DB1_OFFSET,0x00000000);
        HW_WRITE_REG_32BIT(canbase+CAN_CANIF2DB2_OFFSET,0x00000000);
    }

}

Std_ReturnType Can_SetBaudrate(uint8 Controller, uint16 BaudRateConfigID)
{
    CanControllerBaudRateConfig *BaudRateConfig;
    uint8 BRP, TSEG2, TSEG1, SJW, n;
    uint32 x;
    if (ControllerMode[Controller] != CAN_CS_STOPPED)
        return E_NOT_OK;

    for (j = 0; j < ControllerNum; j++)
    {

        if (GlobalConfig->canControllers[j].CanControllerId == Controller)
        {
            HW_SET_BIT(
                    GlobalConfig->canControllers[j].CanControllerBaseAddress+CAN_CANCTL_OFFSET,
                    6);    // set CCE bit to write in CANBIT register

            if (GlobalConfig->canControllers[j].CanControllerBaudRateConfigobj->CanControllerBaudRateConfigID
                    == BaudRateConfigID)
            {
                BaudRateConfig =
                        (GlobalConfig->canControllers[j].CanControllerBaudRateConfigobj);
                n = BaudRateConfig->CanControllerSeg2
                        + BaudRateConfig->CanControllerSeg1
                        + BaudRateConfig->CanControllerPropSeg + 1;
                BRP = (CAN_CLOCK
                        / ((BaudRateConfig->CanControllerBaudRate) * 1000 * n))
                        - 1;
                TSEG2 = (BaudRateConfig->CanControllerSeg2) - 1; //Time Segment after Sample Point
                TSEG1 = ((BaudRateConfig->CanControllerSeg1)
                        + BaudRateConfig->CanControllerPropSeg) - 1;
                SJW = (BaudRateConfig->CanControllerSyncJumpWidth) - 1; //Synchronization Jump Width
                x = ((TSEG2 << 12) & 0x7000) | ((TSEG1 << 8) & 0xf00)
                        | ((SJW << 6) & 0xC0) | BRP;
                HW_WRITE_REG32_MASKED(
                        GlobalConfig->canControllers[i].CanControllerBaseAddress+CAN_CANBIT_OFFSET,
                        x, 0x3FFF);
                HW_RESET_BIT(
                        GlobalConfig->canControllers[j].CanControllerBaseAddress+CAN_CANCTL_OFFSET,
                        6);     // reset CCE
                break;

            }
        }
    }

    return E_OK;
}

void Can_EnableControllerInterrupts(uint8 Controller)
{

    if (moduleState == CAN_UNINT)
    {
        //CAN_E_UNINIT
        //return ;
    }
    if (Controller > ControllerNum)
    {
        /* CAN_E_PARAM_CONTROLLER
         return; */
    }

    if (Can_DisableInterruptCount[Controller] == 1)
    {
        HW_SET_BIT(BaseAddress[Controller]+CAN_CANCTL_OFFSET,2);   // Enable SIE
        HW_SET_BIT(BaseAddress[Controller]+CAN_CANCTL_OFFSET,3);  // Enable EIE
        HW_SET_BIT(BaseAddress[Controller]+CAN_CANCTL_OFFSET,1);   // Enable IE
        Can_DisableInterruptCount[Controller]--;
    }
    else if (Can_DisableInterruptCount[Controller] > 1)
    {

        Can_DisableInterruptCount[Controller]--;

    }

}

Std_ReturnType Can_GetControllerErrorState(uint8 ControllerId,
                                           Can_ErrorStateType* ErrorStatePtr)
{

    if (HW_READ_BIT(BaseAddress[ControllerId] + CAN_CANSTS_OFFSET, 7))
    {

        *ErrorStatePtr = CAN_ERRORSTATE_BUSOFF;
        return E_OK;
    }
    else if (HW_READ_BIT(BaseAddress[ControllerId] + CAN_CANSTS_OFFSET, 5))
    {

        *ErrorStatePtr = CAN_ERRORSTATE_PASSIVE;
        return E_OK;
    }
    else if (!(HW_READ_BIT(BaseAddress[ControllerId] + CAN_CANSTS_OFFSET, 5)))
    {

        *ErrorStatePtr = CAN_ERRORSTATE_ACTIVE;
        return E_OK;

    }

    return E_NOT_OK;
}

Can_ReturnType Can_SetControllerMode(uint8 Controller,
                                     Can_StateTransitionType Transition)
{
    uint32 CanBase;
    if ((Transition == CAN_CS_STARTED
            && (ControllerMode[Controller] != CAN_CS_STOPPED))
            || (Transition == CAN_CS_STOPPED
                    && (ControllerMode[Controller] != CAN_CS_SLEEP
                            || ControllerMode[Controller] != CAN_CS_STARTED))
            || (Transition == CAN_CS_SLEEP
                    && ControllerMode[Controller] != CAN_CS_STOPPED))
    {
        return CAN_NOT_OK;
    }

    for (i = 0; i < ControllerNum; i++)
    {
        if (GlobalConfig->canControllers[i].CanControllerId == Controller)
        {

            CanBase = GlobalConfig->canControllers[i].CanControllerBaseAddress;
            break;
        }
    }

    if (Transition == CAN_CS_STARTED)
    {
        ControllerMode[Controller] = CAN_CS_STARTED;
        HW_RESET_BIT(CanBase+CAN_CANCTL_OFFSET, 0);    // reset init bit

        //CanIf_ControllerModeIndication(Controller,CAN_CS_STARTED);
    }
    else if (Transition == CAN_CS_STOPPED)
    {
        ControllerMode[Controller] = CAN_CS_STOPPED;
        HW_SET_BIT(CanBase+CAN_CANCTL_OFFSET, 0); // set init bit to enter init mode

        //CanIf_ControllerModeIndication(Controller,CAN_CS_STOPPED);
    }
    else if (Transition == CAN_CS_SLEEP)
    {
        ControllerMode[Controller] = CAN_CS_SLEEP;
        HW_SET_BIT(CanBase+CAN_CANCTL_OFFSET, 0); // set init bit to enter init mode

        // CanIf_ControllerModeIndication(Controller,CAN_CS_SLEEP);
    }
    else
    {
        return CAN_NOT_OK;
    }

    return CAN_OK;
}

void Can_GetVersionInfo(Std_VersionInfoType* versioninfo)
{
    versioninfo = GlobalConfig->canversioninfo;
    if (versioninfo == NULL)
    {

    }
}

void Can_DisableControllerInterrupts(uint8 Controller)
{

    if (moduleState == CAN_UNINT)
    {
        //CAN_E_UNINIT
        //return ;
    }
    if (Controller > ControllerNum)
    {
        /* CAN_E_PARAM_CONTROLLER
         return; */
    }
    HW_RESET_BIT(BaseAddress[Controller]+CAN_CANCTL_OFFSET,2);   //disable SIE
    HW_RESET_BIT(BaseAddress[Controller]+CAN_CANCTL_OFFSET,3);   // diable EIE
    HW_RESET_BIT(BaseAddress[Controller]+CAN_CANCTL_OFFSET,1);   // disable IE

    Can_DisableInterruptCount[Controller]++;

}

Std_ReturnType Can_GetControllerMode(uint8 Controller,
                                     Can_ControllerStateType* ControllerModePtr)
{
    *ControllerModePtr = CAN_CS_STARTED;
    return E_OK;
}

Std_ReturnType Can_SetIcomConfiguration(uint8 ControllerId,
                                        IcomConfigIdType ConfigurationId)
{
    return E_OK;
}

Can_ReturnType Can_Write(Can_HwHandleType Hth, const Can_PduType* PduInfo)
{
    uint32 CanBase;
    uint8 DLC;
    boolean HthValid = false;
    //CanHardwareObject  msgObj;
    for (j = 0; j < Max_transmitObjects; j++)
    {
        if (GlobalConfig->HOH[j].CanObjectType == TRANSMIT
                && GlobalConfig->HOH[j].CanObjectId == Hth)
        {

            CanBase =
                    GlobalConfig->HOH[j].CanControllerRef->CanControllerBaseAddress;
            //  msgObj =    ( GlobalConfig->HOH[j]);
            HthValid = TRUE;
            break;
        }

    }
    if (HthValid == false || PduInfo == NULL)
        return CAN_NOT_OK;

    DLC = PduInfo->length;
    if (!(HW_READ_BIT(CanBase + CAN_CANTXRQ1_OFFSET, Hth)))
    {               // if The message object is not waiting for transmission
        TrnsmPDU[GlobalConfig->HOH[j].CanControllerRef->CanControllerId][Hth] =
                *PduInfo;

        if (PduInfo->id == GlobalConfig->HOH[j].CanHwFilterptr->CanHwFilterCode)
        {
            if (DLC <= 4)
            {
                HW_WRITE_REG32_MASKED(CanBase+CAN_CANIF1CMSK_OFFSET, 0x92,
                                      0xff);    //WRNR-CONTROL-DATAA-
            }
            else if (DLC > 4 && DLC <= 8)
            {
                HW_WRITE_REG32_MASKED(CanBase+CAN_CANIF1CMSK_OFFSET, 0x93,
                                      0xff);    //WRNR-CONTROL-DATAA-DATAB
            }
            HW_WRITE_REG32_MASKED(CanBase+CAN_CANIF1MCTL_OFFSET, (0x1080 | DLC),
                                  0x0F);        // DLC

            HW_WRITE_REG_32BIT(CanBase+CAN_CANIF1DA1_OFFSET,
                               ((PduInfo->sdu[1] << 8) + (PduInfo->sdu[0])));
            HW_WRITE_REG_32BIT(CanBase+CAN_CANIF1DA2_OFFSET,
                               ((PduInfo->sdu[3] << 8) + (PduInfo->sdu[2])));
            HW_WRITE_REG_32BIT(CanBase+CAN_CANIF1DB1_OFFSET,
                               ((PduInfo->sdu[5] << 8) + (PduInfo->sdu[4])));
            HW_WRITE_REG_32BIT(CanBase+CAN_CANIF1DB2_OFFSET,
                               ((PduInfo->sdu[7] << 8) + (PduInfo->sdu[6])));

            if (GlobalConfig->HOH[j].CanTriggerTransmitEnable == TRUE)
            {
                HW_SET_BIT(CanBase+CAN_CANIF1CMSK_OFFSET, 2);            //TXRQT
            }
            while (HW_READ_BIT(CanBase + CAN_CANIF1CRQ_OFFSET, 15))
                ;
            HW_WRITE_REG32_MASKED(CanBase+CAN_CANIF1CRQ_OFFSET, Hth, 0x3f); // message number

        }
        return CAN_OK;
    }
    else
        return CAN_BUSY;

}

/**   
 *     \name       Can_MainFunction_Write
 *     
 *     \breif      This function performs the polling of TX confirmation when CAN_TX_PROCESSING is set to POLLING
 *    
 */
void Can_MainFunction_Write(void)
{

}

/**
 *   \name         Can_MainFunction_Read
 * 
 *   \breif        This function performs the polling of RX indications when CAN_RX_PROCESSING is set to POLLING
 */
void Can_MainFunction_Read(void)
{

}

/**
 *   \name        Can_MainFunction_BusOff
 *
 *   \breif       This function performs the polling of bus-off events that are configured statically as to be polled
 */
void Can_MainFunction_BusOff(void)
{
    //fe hna moshkla lw kr2t el sts register
    for (i = 0; i < ControllerNum; i++)
    {
        uint32 cansts = HW_READ_BIT(
                GlobalConfig->canControllers[i].CanControllerBaseAddress
                        + CAN_CANSTS_OFFSET,
                7);
        if (cansts == 1)
        {
            ControllerMode[GlobalConfig->canControllers[i].CanControllerId] =
                    CAN_CS_STOPPED;
            //  CanIf_ControllerBusOff(GlobalConfig->canControllers[i].CanControllerId);

        }
    }
}

/**
 *   \name       Can_MainFunction_Wakeup
 * 
 *   \breif      This function performs the polling of wake-up events that are configured statically as to be polled
 */
void Can_MainFunction_Wakeup(void)
{

}
/**
 *   \name      Can_MainFunction_Mode
 * 
 *   \breif     This function performs the polling of CAN controller mode transitions.
 */
void Can_MainFunction_Mode(void)
{

}

