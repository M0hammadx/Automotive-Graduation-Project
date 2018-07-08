/** incomplete Com code file used as a test to PDUR module */
#include "../UART.h"
#include "Com.h"
#include "../inc/tm4c123gh6pm.h"
#include <xdc/std.h>

#include <xdc/runtime/System.h>

#include <ti/sysbios/BIOS.h>

#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Clock.h>

#include "../ECU_CONFIGURATION.h"
#define INVAILD_SIGNAL 0xAA
#define INVAILD_SIGNAL_ULTRASONIC_REQUEST 0

extern Clock_Handle clock1;

//functions to test transmission to CAN
uint8 x = 0;
typedef struct recivedData_t
{
    boolean flag;
    PduIdType PduHandleId;
    PduLengthType SduLength;
    uint8 SduData[8];
} recivedData;

recivedData rData = { .flag = FALSE };

void PduR_ComTransmit_Test(void)
{
    /** in case of COM module these lines exist in function that intend to transmit */
    /** formulating I-PDU */
    uint8 distMsg[8];
    int i;
    for (i = 0; i < 8; i++)
    {
        distMsg[i] = ++x;
        if (x == 255)
            x = 0;
    }
    const PduInfoType distanceMsg = { .SduDataPtr = distMsg, .SduLength = 8 };

    /** query PDUR routing paths sources to find global pdu reference .
     inside COM module &Pdus[1] will be reference to related message .
     */
    PduIdType PduHandleId;

    if (PduR_INF_GetSourcePduHandleId(&Pdus[1], &PduHandleId) == E_OK)
    {
        PduR_ComTransmit(PduHandleId, &distanceMsg);
        //PduR_ComCancelTransmit( PduHandleId );
    }
}

void PduR_ComTransmit_Test2(void)
{
    /** in case of COM module these lines exist in function that intend to transmit */
    /** formulating I-PDU */
    uint8 distMsg[] = "ComMessage1234";
    const PduInfoType distanceMsg = { .SduDataPtr = distMsg, .SduLength =
                                              sizeof(distMsg)
                                                      / sizeof(distMsg[0]) };

    /** query PDUR routing paths sources to find global pdu reference .
     inside COM module &Pdus[3] will be reference to related message .
     */
    PduIdType PduHandleId;

    if (PduR_INF_GetSourcePduHandleId(&Pdus[3], &PduHandleId) == E_OK)
    {
        PduR_ComTransmit(PduHandleId, &distanceMsg);

        PduR_ComCancelTransmit(PduHandleId);
        PduR_ComChangeParameter(PduHandleId, TP_STMIN, 0);
        PduR_ComCancelReceive(PduHandleId);
    }
}

Std_ReturnType Com_TriggerTransmit_Test(PduIdType TxPduId,
                                        PduInfoType* PduInfoPtr)
{
    /**
     the upper layer module (called module) shall check whether the
     available data fits into the buffer size reported by PduInfoPtr->SduLength.
     If it fits, it shall copy its data into the buffer provided by PduInfoPtr ->SduDataPtr
     and update the length of the actual copied data in PduInfoPtr->SduLength.
     If not, it returns E_NOT_OK without changing PduInfoPtr.
     */
    ////printf("\nnow in Com Trigger Transmit\n");
    Std_ReturnType retVal = E_OK;
    uint8 distMsg[] = "1234Msg";  //Message to be transmitted
    if (sizeof(distMsg) / sizeof(distMsg[0]) < PduInfoPtr->SduLength)
    {
        if (!memcpy((void *) PduInfoPtr->SduDataPtr, (void *) distMsg,
                    sizeof(distMsg) / sizeof(distMsg[0])))
        {
            retVal = E_NOT_OK;
        }
        else
        {
            PduInfoPtr->SduLength = sizeof(distMsg) / sizeof(distMsg[0]);
        }
    }
    else
    {
        retVal = E_NOT_OK;
    }
    return retVal;
}

void Com_INF_Init(void)
{
    SYSCTL_RCGCGPIO_R |= 0x02; // port B
    while (SYSCTL_PRGPIO_R & 0x02 == 0);
    SYSCTL_RCGCCAN_R |= 0x01;
    while (SYSCTL_PRGPIO_R & 0x01 == 0);
    GPIO_PORTB_LOCK_R |= 0x4C4F434B;
    GPIO_PORTB_CR_R |= 0x30;
    GPIO_PORTB_DIR_R |= 0x20;
    GPIO_PORTB_DIR_R &= ~0x10;
    GPIO_PORTB_DEN_R |= 0x30;
    GPIO_PORTB_AMSEL_R &= ~0x30;
    GPIO_PORTB_AFSEL_R |= 0x30;
    GPIO_PORTB_PCTL_R &= ~0x00FF0000;
    GPIO_PORTB_PCTL_R |= 0x00880000;

    Can_Init(&Confiobj);
    ///Initialization of router
    PduR_Init(&PBPduRConfig);
    ///Initialization of can interface
    CanIf_Init(&CanIf_Config);

    Can_DisableControllerInterrupts(0);
    ///Start controller 0
    CanIf_SetControllerMode(0, CAN_CS_STARTED);
    Can_EnableControllerInterrupts(0);

    ///Start channel 0
    CanIf_SetPduMode(0, CANIF_ONLINE);

}

void Com_TxConfirmation(PduIdType PduHandleId, Std_ReturnType result)
{
    UART_OutString("TX confirmation MSG no :\n");
    UART_OutUDec(PduHandleId);
//    System_flush();

}

void Com_TpRxIndication(PduIdType PduHandleId, Std_ReturnType result)
{
    ////printf("now in Com Tp Rx Indication\n ");
    ////printf("router CANTP reception indication has finished\n");
}

void Com_TpTxConfirmation(PduIdType PduHandleId, Std_ReturnType result)
{
    ////printf("now in Com Tp TX confirmation\n");
    ////printf("router CANTP confirmation has finished\n");
}

Std_ReturnType Com_TriggerTransmit(PduIdType TxPduId, PduInfoType* PduInfoPtr)
{
    return Com_TriggerTransmit_Test(TxPduId, PduInfoPtr);
}

BufReq_ReturnType Com_StartOfReception(PduIdType id, const PduInfoType* info,
                                       PduLengthType TpSduLength,
                                       PduLengthType* bufferSizePtr)
{

    ////printf("now in Com start of reception\n");
    return BUFREQ_OK;
}

BufReq_ReturnType Com_CopyRxData(PduIdType id, const PduInfoType* info,
                                 PduLengthType* bufferSizePtr)
{

    ////printf("now in Com copy RX data\n");
    return BUFREQ_OK;
}

BufReq_ReturnType Com_CopyTxData(PduIdType id, const PduInfoType* info,
                                 RetryInfoType* retry,
                                 PduLengthType* availableDataPtr)
{

    ////printf("now in Com copy TX data\n");
    return BUFREQ_OK;
}

/**
 Description  : query global I-PDU reference in Com configuration .
 inputs       : Pdu            | Reference to global PDU .
 output       : DestPduId      | Identifier to local I-PDU .
 I/O          : None
 return value : Std_ReturnType | Determine if I-PDU is exist or not.
 */
Std_ReturnType Com_INF_GetPduHandleId(Pdu_Type *Pdu, PduIdType *PduHandleIdPtr)
{
    Std_ReturnType Std_Ret = E_NOT_OK;

    uint8 i;
    for (i = 0; i < ComConfiguration.ComMaxIPduCnt; i++)
    {
        if (ComConfiguration.ComIPdu[i].PduIdRef == Pdu)
        {
            Std_Ret = E_OK;
            *PduHandleIdPtr = ComConfiguration.ComIPdu[i].IPduHandleId;
        }
    }
    return Std_Ret;
}

#ifdef ECU1_SENSORYNODE
#include "../rte/Ultrasonic_requests_rte.h"
#include "../rte/Ultrasonic_data_rte.h"
#include "../rte/Car_temperature_rte.h"
#include "../rte/Car_angle_data_rte.h"
#include "../rte/Motor_speed_data_rte.h"
#include "../rte/Distance_elapsed_rte.h"
#include "../rte/Actual_Car_speed_rte.h"
#include "../rte/Actual_Car_direction_rte.h"
#include "../rte/Car_temperature_rte.h"
#include <xdc/runtime/Timestamp.h>

#define COMFRAME0_MATURE_TIMEOUT 10
#define COMFRAME1_MATURE_TIMEOUT 10
#define COMFRAME1_MATURE_MOTORSPEED_TIMEOUT 10
#define COMFRAME1_MATURE_ACTUAL_CARSPEED_TIMEOUT 10
#define COMFRAME1_MATURE_ACTUAL_CARDIRECTION_TIMEOUT 10
#define COMFRAME1_DISTANCEELAPSED_TIMEOUT 10
#define COMFRAME2_CARANGLE_MATURE_TIMEOUT 10
#define COMFRAME2_TEMP_MATURE_TIMEOUT 10

static uint8_t ComFrame0_UltrasonicData_MatureTimeout = COMFRAME0_MATURE_TIMEOUT;

static uint8_t ComFrame1_MotorSpeed_MatureTimeout =
COMFRAME1_MATURE_MOTORSPEED_TIMEOUT;
static uint8_t ComFrame1_Actual_CarSpeed_MatureTimeout =
COMFRAME1_MATURE_ACTUAL_CARSPEED_TIMEOUT;
static uint8_t ComFrame1_Actual_CarDirection_MatureTimeout =
COMFRAME1_MATURE_ACTUAL_CARDIRECTION_TIMEOUT;
static uint8_t ComFrame1_DistanceElapsed_MatureTimeout =
COMFRAME1_DISTANCEELAPSED_TIMEOUT;

static uint8_t ComFrame2_CarAngleData_MatureTimeout =
COMFRAME2_CARANGLE_MATURE_TIMEOUT;
static uint8_t ComFrame2_Temp_MatureTimeout = COMFRAME2_TEMP_MATURE_TIMEOUT;

extern Semaphore_Handle Com_Binary_Semaphore_Timeout_Frame0_UltrasonicData_Handle;

extern Semaphore_Handle Com_ECU1_Binary_Semaphore_Timeout_Frame1_MotorSpeed_Handle; //2 byte
extern Semaphore_Handle Com_ECU1_Binary_Semaphore_Timeout_Frame1_Actual_CarSpeed_Handle;//2 byte
extern Semaphore_Handle Com_ECU1_Binary_Semaphore_Timeout_Frame1_Actual_CarDirection_Handle;//1 byte
extern Semaphore_Handle Com_ECU1_Binary_Semaphore_Timeout_Frame1_DistanceElapsed_Handle;//2 byte

extern Semaphore_Handle Com_ECU1_Binary_Semaphore_Timeout_Frame2_CarAngle_Handle;
extern Semaphore_Handle Com_ECU1_Binary_Semaphore_Timeout_Frame2_Temp_Handle;
typedef struct ComFrame_0
{
    uint8_t ultrasonicData[8];
}Com_Frame0_M6;

typedef struct ComFrame_2
{
    uint8_t motor_right_speed;
    uint8_t motor_left_speed;
    uint8_t actual_car_speed_lsb;
    uint8_t actual_car_speed_msb;
    uint8_t actual_car_direction;
    uint8_t distance_elapsed_lsb;
    uint8_t distance_elapsed_msb;
    uint8_t unused[1];
}Com_Frame1_M7;

typedef struct ComFrame_1
{
    uint8_t carAngle_lsb;
    uint8_t carAngle_msb;
    uint8_t ecu1_temp;
    uint8_t unused[5];
}Com_Frame2_M8;

typedef struct Com_Frame3_Message_2_t
{
    uint8_t Cartask;
    uint8_t speed_lsb;
    uint8_t speed_msb;
    uint8_t direction;
    uint8_t desired_steeringAngle;
    uint8_t unused[3];
}Com_Frame3_Message_2, *Com_Frame3_Message_2_Ptr;

typedef struct Com_Frame4_Message_1_t
{
    uint8_t UltraSonicRequest;
    uint8_t Ecu2Temp;
    uint8_t unused[6];
}Com_Frame4_Message_1, *Com_Frame4_Message_1_Ptr;

/********************* global Com frames Tx ************************/
Com_Frame0_M6 Ecu1_ComFrame0_M6; //ultra data
Com_Frame1_M7 Ecu1_ComFrame1_M7;//encoder data
Com_Frame2_M8 Ecu1_ComFrame2_M8;// compass + temp data

uint8_t Com_Main_Transmit_Errors = 0;//debug
void Com_Main(void)
{
    /************* vars to pull rte data***************/
    uint16_t CarAngle;
    uint8_t CarTemp;
    uint8_t motor_speed[2];
    uint16_t Distance_elapsed_data;
    uint16_t Actual_car_speed;
    uint8_t Actual_car_direction;
    uint8_t UltrasonicData[8];
    while (1) // get data from rte
    {

        if (Rte_Ultrasonic_data_iread(UltrasonicData) == 0)
        {

        }
        else
        {

            //  Clock_stop(clock1);
            for (uint8_t i = 0; i < 8; i++)
            {
                Ecu1_ComFrame0_M6.ultrasonicData[i] = UltrasonicData[i];
            }
            //post binary timeout
            Semaphore_post(
                    Com_Binary_Semaphore_Timeout_Frame0_UltrasonicData_Handle);
            // Clock_start(clock1);
        }

//Construct Car_Angle + temp Frame

        if (Rte_Car_angle_data_iread(&CarAngle) == 0)
        {

        }
        else
        {
            // Clock_stop(clock1);
            Ecu1_ComFrame2_M8.carAngle_lsb = CarAngle & 0xFF;
            Ecu1_ComFrame2_M8.carAngle_msb = (CarAngle >> 8) & 0xFF;
// post timeout
            Semaphore_post(
                    Com_ECU1_Binary_Semaphore_Timeout_Frame2_CarAngle_Handle);
            // Clock_start(clock1);
        }
//temp

        if (Rte_Car_temperature_iread(&CarTemp) == 0)
        {

        }
        else
        {
            Ecu1_ComFrame2_M8.ecu1_temp = CarTemp;
            // post timeout
            Semaphore_post(
                    Com_ECU1_Binary_Semaphore_Timeout_Frame2_Temp_Handle);
        }
//        /*********** new frame *************/
//// Motors RPM - (speed)
        if (Rte_Motor_speed_data_iread(motor_speed) == 0)
        {

        }
        else
        {
            // Clock_stop(clock1);
            Ecu1_ComFrame1_M7.motor_left_speed = motor_speed[0];
            Ecu1_ComFrame1_M7.motor_right_speed = motor_speed[1];
            Semaphore_post(
                    Com_ECU1_Binary_Semaphore_Timeout_Frame1_MotorSpeed_Handle);
            //Clock_start(clock1);

        }

//Distance elpased
        if (Rte_Distance_elapsed_iread(&Distance_elapsed_data) == 0)
        {

        }
        else
        {
            // Clock_stop(clock1);
            Ecu1_ComFrame1_M7.distance_elapsed_lsb = Distance_elapsed_data
            & 0xFF;
            Ecu1_ComFrame1_M7.distance_elapsed_msb =
            (Distance_elapsed_data >> 8) & 0xFF;
            Semaphore_post(
                    Com_ECU1_Binary_Semaphore_Timeout_Frame1_DistanceElapsed_Handle);
            // Clock_start(clock1);

        }
// Actual car speed
        if (Rte_Actual_Car_speed_iread(&Actual_car_speed) == 0)
        {

        }
        else
        {
            //   Clock_stop(clock1);
            Ecu1_ComFrame1_M7.actual_car_speed_lsb = Actual_car_speed & 0xFF;
            Ecu1_ComFrame1_M7.actual_car_speed_msb = (Actual_car_speed >> 8)
            & 0xFF;
            Semaphore_post(
                    Com_ECU1_Binary_Semaphore_Timeout_Frame1_Actual_CarSpeed_Handle);
            // Clock_start(clock1);

        }
//Actual motor Direction
        if (Rte_Actual_Car_direction_iread(&Actual_car_direction) == 0)
        {

        }
        else
        {
            Ecu1_ComFrame1_M7.actual_car_direction = Actual_car_direction;
            Semaphore_post(
                    Com_ECU1_Binary_Semaphore_Timeout_Frame1_Actual_CarDirection_Handle);
        }
    }
}

/***************************************************************************************/
/****************************** Com_ClockHandler ***************************************/
/***************************************************************************************/

void Com_ClockHandler(void)
{
    PduInfoType ComFrame;
    PduIdType PduHandleId;
    UART_OutString("Com_ClockHandler \n");
    /************************** Ultrasonic data (frame0) ************************************/
    static uint8_t BeginSendFlag_Ecu1_ComFrame0_M6 = 0;
//    static uint8_t Frame1 = 0, Frame2 = 0;
//
//    Frame1++;
//    Frame2++;

    if (Semaphore_pend(
                    Com_Binary_Semaphore_Timeout_Frame0_UltrasonicData_Handle,
                    BIOS_NO_WAIT) == 0)
    {
        ComFrame0_UltrasonicData_MatureTimeout--;
        if (ComFrame0_UltrasonicData_MatureTimeout == 0)
        {
            //Set DTC callout
            for (uint8_t i = 0; i < 8; i++)
            Ecu1_ComFrame0_M6.ultrasonicData[i] = INVAILD_SIGNAL;
        }
    }
    else
    {
        //reset timeout
        BeginSendFlag_Ecu1_ComFrame0_M6 = 1;
        ComFrame0_UltrasonicData_MatureTimeout =
        COMFRAME0_MATURE_TIMEOUT;
        //send can frame
        if (BeginSendFlag_Ecu1_ComFrame0_M6)
        {
            ComFrame.SduDataPtr = (uint8_t*) &Ecu1_ComFrame0_M6;
            ComFrame.SduLength = Pdus[1].PduLength;
            if (PduR_INF_GetSourcePduHandleId(&Pdus[1], &PduHandleId) == E_OK)
            {
                if (PduR_ComTransmit(PduHandleId, &ComFrame) == E_NOT_OK)
                {
                    Com_Main_Transmit_Errors++;
                }            //transmit ultrasonic data
            }
        }

    }
    UART_OutString("Com_Main_Transmit_Errors :");
    UART_OutUDec(Com_Main_Transmit_Errors);

//    /************************** Compass-Temp data (frame2) ******************************************/
//          static uint8_t BeginSendFlag_Ecu1_ComFrame2_M8 =0;
//        if (Semaphore_pend(Com_ECU1_Binary_Semaphore_Timeout_Frame2_CarAngle_Handle,
//        BIOS_NO_WAIT) == 0)
//        {
//            ComFrame2_CarAngleData_MatureTimeout--;
//            if (ComFrame2_CarAngleData_MatureTimeout == 0)
//            {
//                //Set DTC callout
//                Ecu1_ComFrame2_M8.carAngle_lsb = INVAILD_SIGNAL;
//                Ecu1_ComFrame2_M8.carAngle_msb = INVAILD_SIGNAL;
//
//            }
//        }
//        else
//        {
//        BeginSendFlag_Ecu1_ComFrame2_M8=1;
//            //reset timeout
//            ComFrame2_CarAngleData_MatureTimeout =
//            COMFRAME2_CARANGLE_MATURE_TIMEOUT;
//        }
//
//        /********* Temp *************/
//
//        if (Semaphore_pend(Com_ECU1_Binary_Semaphore_Timeout_Frame2_Temp_Handle,
//        BIOS_NO_WAIT) == 0)
//        {
//            ComFrame2_Temp_MatureTimeout--;
//            if (ComFrame2_Temp_MatureTimeout == 0)
//            {
//                //Set DTC callout
//                Ecu1_ComFrame2_M8.ecu1_temp = INVAILD_SIGNAL;
//
//            }
//        }
//        else
//        {
//            //reset timeout
//            ComFrame2_Temp_MatureTimeout =
//            COMFRAME2_TEMP_MATURE_TIMEOUT;
//        }
//    //send can frame here
//
////        if(BeginSendFlag_Ecu1_ComFrame2_M8){
////            ComFrame.SduDataPtr = (uint8_t*) &Ecu1_ComFrame2_M8;
////            ComFrame.SduLength = Pdus[8].PduLength;
////            if (PduR_INF_GetSourcePduHandleId(&Pdus[8], &PduHandleId) == E_OK)
////            {
////                if (PduR_ComTransmit(PduHandleId, &ComFrame) == E_NOT_OK)
////                {
////                    Com_Main_Transmit_Errors++;
////                }            //transmit ultrasonic data
////            }
////        }

    //    /************************** Encoder data (frame1) ******************************************/
    static uint8_t BeginSendFlag_Ecu1_ComFrame1_M7 = 0;

    // Motors RPM - (speed)
    if (Semaphore_pend(
                    Com_ECU1_Binary_Semaphore_Timeout_Frame1_MotorSpeed_Handle,
                    BIOS_NO_WAIT) == 0)
    {
        ComFrame1_MotorSpeed_MatureTimeout--;
        if (ComFrame1_MotorSpeed_MatureTimeout == 0)
        {
            //Set DTC callout
            Ecu1_ComFrame1_M7.motor_left_speed = INVAILD_SIGNAL;
            Ecu1_ComFrame1_M7.motor_right_speed = INVAILD_SIGNAL;
        }
    }
    else
    {
        BeginSendFlag_Ecu1_ComFrame1_M7 = 1;
        //reset timeout
        ComFrame1_MotorSpeed_MatureTimeout =
        COMFRAME1_MATURE_MOTORSPEED_TIMEOUT;
    }

    //Distance elpased
    if (Semaphore_pend(
                    Com_ECU1_Binary_Semaphore_Timeout_Frame1_DistanceElapsed_Handle,
                    BIOS_NO_WAIT) == 0)
    {
        ComFrame1_DistanceElapsed_MatureTimeout--;
        if (ComFrame1_DistanceElapsed_MatureTimeout == 0)
        {
            //Set DTC callout
            Ecu1_ComFrame1_M7.distance_elapsed_lsb = INVAILD_SIGNAL;
            Ecu1_ComFrame1_M7.distance_elapsed_msb = INVAILD_SIGNAL;
        }
    }
    else
    {
        //reset timeout
        BeginSendFlag_Ecu1_ComFrame1_M7 = 1;
        ComFrame1_DistanceElapsed_MatureTimeout =
        COMFRAME1_DISTANCEELAPSED_TIMEOUT;
    }

    // Actual car speed
    if (Semaphore_pend(
                    Com_ECU1_Binary_Semaphore_Timeout_Frame1_Actual_CarSpeed_Handle,
                    BIOS_NO_WAIT) == 0)
    {
        ComFrame1_Actual_CarSpeed_MatureTimeout--;
        if (ComFrame1_Actual_CarSpeed_MatureTimeout == 0)
        {
            //Set DTC callout
            Ecu1_ComFrame1_M7.actual_car_speed_lsb = INVAILD_SIGNAL;
            Ecu1_ComFrame1_M7.actual_car_speed_msb = INVAILD_SIGNAL;
        }
    }
    else
    {
        //reset timeout
        BeginSendFlag_Ecu1_ComFrame1_M7 = 1;
        ComFrame1_Actual_CarSpeed_MatureTimeout =
        COMFRAME1_MATURE_ACTUAL_CARSPEED_TIMEOUT;
    }
    //Actual motor Direction
    if (Semaphore_pend(
                    Com_ECU1_Binary_Semaphore_Timeout_Frame1_Actual_CarDirection_Handle,
                    BIOS_NO_WAIT) == 0)
    {
        ComFrame1_Actual_CarDirection_MatureTimeout--;
        if (ComFrame1_Actual_CarDirection_MatureTimeout == 0)
        {
            //Set DTC callout
            Ecu1_ComFrame1_M7.actual_car_direction = INVAILD_SIGNAL;
        }
    }
    else
    {
        //reset timeout
        BeginSendFlag_Ecu1_ComFrame1_M7 = 1;
        ComFrame1_Actual_CarDirection_MatureTimeout =
        COMFRAME1_MATURE_ACTUAL_CARDIRECTION_TIMEOUT;
    }

    //send can frame here
    if (BeginSendFlag_Ecu1_ComFrame1_M7 == 1)
    {
        ComFrame.SduDataPtr = (uint8_t*) &Ecu1_ComFrame1_M7;
        ComFrame.SduLength = Pdus[7].PduLength;
        if (PduR_INF_GetSourcePduHandleId(&Pdus[7], &PduHandleId) == E_OK)
        {
            if (PduR_ComTransmit(PduHandleId, &ComFrame) == E_NOT_OK)
            {
                Com_Main_Transmit_Errors++;
            }            //transmit encoder data
        }
    }
}

void Com_ClockHandler2(void)
{
    PduInfoType ComFrame;
    PduIdType PduHandleId;
    /************************** Compass-Temp data (frame2) ******************************************/
    static uint8_t BeginSendFlag_Ecu1_ComFrame2_M8 = 0;
    if (Semaphore_pend(Com_ECU1_Binary_Semaphore_Timeout_Frame2_CarAngle_Handle,
                    BIOS_NO_WAIT) == 0)
    {
        ComFrame2_CarAngleData_MatureTimeout--;
        if (ComFrame2_CarAngleData_MatureTimeout == 0)
        {
            //Set DTC callout
            Ecu1_ComFrame2_M8.carAngle_lsb = INVAILD_SIGNAL;
            Ecu1_ComFrame2_M8.carAngle_msb = INVAILD_SIGNAL;

        }
    }
    else
    {
        BeginSendFlag_Ecu1_ComFrame2_M8 = 1;
        //reset timeout
        ComFrame2_CarAngleData_MatureTimeout =
        COMFRAME2_CARANGLE_MATURE_TIMEOUT;
    }

    /********* Temp *************/

    if (Semaphore_pend(Com_ECU1_Binary_Semaphore_Timeout_Frame2_Temp_Handle,
                    BIOS_NO_WAIT) == 0)
    {
        ComFrame2_Temp_MatureTimeout--;
        if (ComFrame2_Temp_MatureTimeout == 0)
        {
            //Set DTC callout
            Ecu1_ComFrame2_M8.ecu1_temp = INVAILD_SIGNAL;

        }
    }
    else
    {
        //reset timeout
        ComFrame2_Temp_MatureTimeout =
        COMFRAME2_TEMP_MATURE_TIMEOUT;
    }
    //send can frame here

    if (BeginSendFlag_Ecu1_ComFrame2_M8)
    {
        ComFrame.SduDataPtr = (uint8_t*) &Ecu1_ComFrame2_M8;
        ComFrame.SduLength = Pdus[8].PduLength;
        if (PduR_INF_GetSourcePduHandleId(&Pdus[8], &PduHandleId) == E_OK)
        {
            if (PduR_ComTransmit(PduHandleId, &ComFrame) == E_NOT_OK)
            {
                Com_Main_Transmit_Errors++;
            }            //transmit Comp and Temp
        }
    }

}

#endif

#ifdef ECU2_ALGORITHMICNODE
#include "../rte/Ultrasonic_requests_rte.h"
#include "../rte/Ultrasonic_data_rte.h"
#include "../rte/Desired_Car_speed_direction_rte.h"
#include "../rte/Desired_Steering_Angle_rte.h"
#include "../rte/Actual_Car_direction_rte.h"
#include "../rte/Actual_Car_speed_rte.h"
#include "../rte/Car_angle_data_rte.h"
#include "../rte/Distance_elapsed_rte.h"
#include "../rte/Motor_speed_data_rte.h"

extern Semaphore_Handle Com_Binary_Semaphore_Timeout_Frame0_SpeedDirection_Handle;
extern Semaphore_Handle Com_Binary_Semaphore_Timeout_Frame0_SteeringAngle_Handle;

extern Semaphore_Handle Com_Binary_Semaphore_Timeout_Frame1_UltrasonicReq_Handle;
extern Semaphore_Handle Com_Binary_Semaphore_Timeout_Frame1_Temp_Handle;

#define COMFRAME0_SPEED_DIRECTION_MATURE_TIMEOUT  10   //10 * clock period
#define COMFRAME0_STEERING_ANGLE_MATURE_TIMEOUT   10   //10 * clock period
#define COMFRAME1_ULTRASONICREQ_MATURE_TIMEOUT    2
#define COMFRAME1_TEMP_MATURE_TIMEOUT               10

//Main_DesiredCarSpeedDirectionSteering_DATA
typedef struct Com_Frame0_RelatedData_Message_2_New_t
{
    uint8_t speed_lsb;
    uint8_t speed_msb;
    uint8_t direction;
}Com_Frame0_RelatedData_Message_2_New;

typedef struct Com_Frame0_Message_2_t
{
    uint8_t Cartask;
    uint8_t speed_lsb;
    uint8_t speed_msb;
    uint8_t direction;
    uint8_t desired_steeringAngle;
    uint8_t unused[3];
}Com_Frame0_Message_2;            //real can frame structure

typedef struct Com_Frame1_Message_6_t
{
    uint8_t UltraSonicRequest;
    uint8_t Ecu2Temp;
    uint8_t unused[6];
}Com_Frame1_Message_6; //real can frame structure

typedef struct Com_Frame2_Message5_t
{
    uint8_t motor_right_speed;
    uint8_t motor_left_speed;
    uint8_t actual_car_speed_lsb;
    uint8_t actual_car_speed_msb;
    uint8_t actual_car_direction;
    uint8_t distance_elapsed_lsb;
    uint8_t distance_elapsed_msb;
    uint8_t unused[1];
}Com_Frame2_Message5, *Com_Frame2_Message5_Ptr;

typedef struct Com_Frame3_Message7_t
{
    uint8_t carAngle_lsb;
    uint8_t carAngle_msb;
    uint8_t ecu1_temp;
    uint8_t unused[5];
}Com_Frame3_Message7, *Com_Frame3_Message7_Ptr;

static Com_Frame0_RelatedData_Message_2_New ComFrame0_M2_SpeedDirection; //for related indexed data updates
static Com_Frame0_Message_2 ComFrame0_M2;//clock sends this
static Com_Frame1_Message_6 ComFrame1_M6;//ultrasonic

static uint8_t ComFrame0_SpeedDirection_MatureTimeout =
COMFRAME0_SPEED_DIRECTION_MATURE_TIMEOUT;
static uint8_t ComFrame0_SteeringAngle_MatureTimeout =
COMFRAME0_STEERING_ANGLE_MATURE_TIMEOUT;

static uint8_t ComFrame1_UltrasonicReq_MatureTimeout =
COMFRAME1_ULTRASONICREQ_MATURE_TIMEOUT;

static uint8_t ComFrame1_Temp_MatureTimeout =
COMFRAME1_TEMP_MATURE_TIMEOUT;

uint8_t Com_Main_Transmit_Errors = 0;//debug
void Com_Main(void)
{
    uint8_t Com_Main_UltrasonicTrigRequestes;
    uint16_t Com_Main_DesiredCarSpeed;
    uint8_t Com_Main_DesiredCarDirection;
    uint8_t Com_Main_DesiredSteeringAngle;
    while (1)
    {
        if (Rte_Ultrasonic_requests_iread(&Com_Main_UltrasonicTrigRequestes)
                == 0)
        {

        }
        else
        {
            //read ecu2 temperature
            //configure Can ID => send requests set ID for send - receive can.c
            // global pdu data configure  ==> PduR.c CanIF.c  HOH? (Ecuc.c)
            //can frame requests
            ComFrame1_M6.UltraSonicRequest = Com_Main_UltrasonicTrigRequestes;//global frame
            Semaphore_post(
                    Com_Binary_Semaphore_Timeout_Frame1_UltrasonicReq_Handle);

        }
        if (Rte_Desired_Car_Direction_signalGroup_iread(
                        &Com_Main_DesiredCarDirection) == 0)
        {

        }
        else
        {

            ComFrame0_M2_SpeedDirection.direction =
            Com_Main_DesiredCarDirection; //global
            if (Rte_Desired_Car_speed_groupSignal_iread(
                            &Com_Main_DesiredCarSpeed) == 0)
            {

            }
            else
            {
                ComFrame0_M2_SpeedDirection.speed_lsb = Com_Main_DesiredCarSpeed
                & 0xFF;
                ComFrame0_M2_SpeedDirection.speed_msb =
                (Com_Main_DesiredCarSpeed >> 8) & 0xFF;
            }
//            Clock_stop(clock1);
            //Transfer new to old
            ComFrame0_M2.direction = ComFrame0_M2_SpeedDirection.direction;
            ComFrame0_M2.speed_lsb = ComFrame0_M2_SpeedDirection.speed_lsb;//old data may be written
            ComFrame0_M2.speed_msb = ComFrame0_M2_SpeedDirection.speed_msb;
            Semaphore_post(
                    Com_Binary_Semaphore_Timeout_Frame0_SpeedDirection_Handle);//time out
//            Clock_start(clock1);

        }
        if (Rte_Desired_Steering_Angle_iread(&Com_Main_DesiredSteeringAngle)
                == 0)
        {

        }
        else
        {

            ComFrame0_M2.desired_steeringAngle = Com_Main_DesiredSteeringAngle;
            Semaphore_post(
                    Com_Binary_Semaphore_Timeout_Frame0_SteeringAngle_Handle);
        }
        //.....rest of messages
    }
}
/***************************************************************************************/
/****************************** Com_ClockHandler ***************************************/
/***************************************************************************************/

void Com_ClockHandler(void)
{

    static char BeginSendFlag_ComFrame0_M2 = 0;
    static char BeginSendFlag_ComFrame1_M6 = 0;
    PduInfoType ComFrame;
    PduIdType PduHandleId;
#ifdef DEBUG
//    System_printf("Com_ClockHandler\n");
//    System_flush();
#endif

    if (Semaphore_pend(
                    Com_Binary_Semaphore_Timeout_Frame0_SpeedDirection_Handle,
                    BIOS_NO_WAIT) == 0)
    {
        ComFrame0_SpeedDirection_MatureTimeout--;
        if (ComFrame0_SpeedDirection_MatureTimeout == 0)
        {
            //Set DTC callout

            ComFrame0_M2.direction = INVAILD_SIGNAL;
            ComFrame0_M2.speed_lsb = INVAILD_SIGNAL;
            ComFrame0_M2.speed_msb = INVAILD_SIGNAL;

        }
    }
    else
    {
        //reset timeout
        BeginSendFlag_ComFrame0_M2 = 1;
        ComFrame0_SpeedDirection_MatureTimeout =
        COMFRAME0_SPEED_DIRECTION_MATURE_TIMEOUT;
    }
    if (Semaphore_pend(Com_Binary_Semaphore_Timeout_Frame0_SteeringAngle_Handle,
                    BIOS_NO_WAIT) == 0)
    {
        ComFrame0_SteeringAngle_MatureTimeout--;
        if (ComFrame0_SteeringAngle_MatureTimeout == 0)
        {
            //Set DTC
            ComFrame0_M2.desired_steeringAngle = INVAILD_SIGNAL;

        }
    }
    else
    {
        //reset time out
        BeginSendFlag_ComFrame0_M2 = 1;
        ComFrame0_SteeringAngle_MatureTimeout =
        COMFRAME0_STEERING_ANGLE_MATURE_TIMEOUT;
    }
//send can frames
    if(BeginSendFlag_ComFrame0_M2==1)
    {
        ComFrame.SduDataPtr = (uint8_t*) &ComFrame0_M2;
        ComFrame.SduLength = Pdus[1].PduLength;
        if (PduR_INF_GetSourcePduHandleId(&Pdus[1], &PduHandleId) == E_OK)
        {
            if (PduR_ComTransmit(PduHandleId, &ComFrame) == E_NOT_OK)
            {
                Com_Main_Transmit_Errors++;
            }            //car task + transmit speed + direction + steering
        }

    }

    /**************************** Frame1_Message6 (UltraReq+Ecu2Temp) *******************************/
//ultrasonic
    if (Semaphore_pend(Com_Binary_Semaphore_Timeout_Frame1_UltrasonicReq_Handle,
                    BIOS_NO_WAIT) == 0)
    {
        ComFrame1_UltrasonicReq_MatureTimeout--;
        if (ComFrame1_UltrasonicReq_MatureTimeout == 0)
        {
            //Set DTC callout

            ComFrame1_M6.UltraSonicRequest = INVAILD_SIGNAL_ULTRASONIC_REQUEST;
        }
    }
    else
    {
        //reset timeout
        BeginSendFlag_ComFrame1_M6 = 1;
        ComFrame1_UltrasonicReq_MatureTimeout =
        COMFRAME1_ULTRASONICREQ_MATURE_TIMEOUT;
    }

//tempEcu2
    if (Semaphore_pend(Com_Binary_Semaphore_Timeout_Frame1_Temp_Handle,
                    BIOS_NO_WAIT) == 0)
    {
        ComFrame1_Temp_MatureTimeout--;
        if (ComFrame1_Temp_MatureTimeout == 0)
        {
            //Set DTC callout

            ComFrame1_M6.UltraSonicRequest = INVAILD_SIGNAL;
        }
    }
    else
    {
        //reset timeout
        BeginSendFlag_ComFrame1_M6 = 1;
        ComFrame1_Temp_MatureTimeout =
        INVAILD_SIGNAL;
    }
//send CanFrame1
    if (BeginSendFlag_ComFrame1_M6 == 1)
    {
#ifdef DEBUG
//        System_printf("SendUltrasonicReQ\n");
//        System_flush();
#endif
//        System_printf("SendUltrasonicReQ\n");
//        System_flush();

        ComFrame.SduDataPtr = (uint8_t*) &ComFrame1_M6;
        ComFrame.SduLength = Pdus[6].PduLength;
        if (PduR_INF_GetSourcePduHandleId(&Pdus[6], &PduHandleId) == E_OK)
        {
            if (PduR_ComTransmit(PduHandleId, &ComFrame) == E_NOT_OK)
            {
                Com_Main_Transmit_Errors++;
            }            //transmit ultrasonic+temp
        }
    }
}

void Com_ClockHandler2(void)
{
//empty
}

#endif

#ifdef ECU3_ACTUATORNODE
#include "../rte/Car_angle_data_rte.h"
#include "../rte/Desired_Car_speed_direction_rte.h"
#include "../rte/Desired_Steering_Angle_rte.h"
#include "../rte/Distance_elapsed_rte.h"
#include "../rte/Motor_speed_data_rte.h"
#include "../rte/Actual_Car_speed_rte.h"
#include "../rte/Actual_Car_direction_rte.h"

typedef struct Com_Frame0_Message5_t
{
    uint8_t motor_right_speed;
    uint8_t motor_left_speed;
    uint8_t actual_car_speed_lsb;
    uint8_t actual_car_speed_msb;
    uint8_t actual_car_direction;
    uint8_t distance_elapsed_lsb;
    uint8_t distance_elapsed_msb;
    uint8_t unused[1];
} Com_Frame0_Message2, *Com_Frame0_Message2_Ptr;

typedef struct Com_Frame1_Message7_t
{
    uint8_t carAngle_lsb;
    uint8_t carAngle_msb;
    uint8_t ecu1_temp;
    uint8_t unused[5];
} Com_Frame1_Message6, *Com_Frame1_Message6_Ptr;

typedef struct Com_Frame2_Message_1_t
{
    uint8_t Cartask;
    uint8_t speed_lsb;
    uint8_t speed_msb;
    uint8_t direction;
    uint8_t desired_steeringAngle;
    uint8_t unused[3];
} Com_Frame2_Message_1, *Com_Frame2_Message_1_Ptr;

//Com_Main()

void Com_ClockHandler(void)
{

}

void Com_ClockHandler2(void)
{
//empty
}

#endif

#ifdef ECU1_SENSORYNODE
void Com_RxIndication(PduIdType PduHandleId, const PduInfoType *PduInfoPtr)
{
    if (PduHandleId == COM_PDU_ID_CANIF_RX_COM_MESSAGE_1)
    {
        Com_Frame4_Message_1_Ptr Msg1Ptr =
        (Com_Frame4_Message_1_Ptr) PduInfoPtr->SduDataPtr;
        if (Msg1Ptr->UltraSonicRequest == INVAILD_SIGNAL_ULTRASONIC_REQUEST)
        {
            //Raise an indication
//            System_printf("Invalid data 1\n");
//            System_flush();
        }
        else
        {
            UART_OutString("RX Indication Valid MSG  UltraReq :\n");
            Rte_Ultrasonic_requests_iwrite(Msg1Ptr->UltraSonicRequest); //if signal equals INVAILD_SIGNAL
        }
        if (Msg1Ptr->Ecu2Temp == INVAILD_SIGNAL)
        {
            //Raise an indication
//            System_printf("Invalid data 2\n");
//            System_flush();
        }
        else
        {
            UART_OutString("RX Indication Valid MSG  Ecu2Temp :\n");
            Rte_Car_temperature_iwrite(Msg1Ptr->Ecu2Temp);
            //Temp to be added
        }
    }
    /************************* task  *******************************/
    if (PduHandleId == COM_PDU_ID_CANIF_RX_COM_MESSAGE_2)
    {
//            Com_Frame3_Message_2_Ptr Msg2Ptr = (Com_Frame3_Message_2_Ptr)PduInfoPtr->SduDataPtr;
        //to be added
    }
}
#endif

#ifdef ECU2_ALGORITHMICNODE
//can interrupt
void Com_RxIndication(PduIdType PduHandleId, const PduInfoType *PduInfoPtr)
{
    /************** Ultra_Data1 **********************/
//    System_printf("Com rx indication \n");
//    System_flush();
    if (PduHandleId == COM_PDU_ID_CANIF_RX_COM_MESSAGE_1)
    {
        if (PduInfoPtr->SduDataPtr[0] == INVAILD_SIGNAL)
        {
            //Raise an indication
//            System_printf("Invalid data 1\n");
//            System_flush();
        }
        else
        {
            UART_OutString("RX Indication Valid MSG  Ultra_Data1 :\n");
            Rte_Ultrasonic_data_iwrite(PduInfoPtr->SduDataPtr);
        }
    }
    /************** Encoder_Data **********************/
    if (PduHandleId == COM_PDU_ID_CANIF_RX_COM_MESSAGE_5)
    {
        Com_Frame2_Message5_Ptr Msg5Ptr =
        (Com_Frame2_Message5_Ptr) PduInfoPtr->SduDataPtr;
        uint8_t motorSpeed[2];
        uint16_t distanceElapsed;
        uint16_t actualCarSpeed;

        // Motors RPM - (speed)
        if (Msg5Ptr->motor_right_speed == INVAILD_SIGNAL)
        {
            //Raise an indication
//            System_printf("Invalid data 2\n");
//            System_flush();
        }
        else
        {
            UART_OutString("RX Indication Valid MSG  Motors RPM :\n");
            motorSpeed[0] = Msg5Ptr->motor_right_speed;
            motorSpeed[1] = Msg5Ptr->motor_left_speed;
            Rte_Motor_speed_data_iwrite(motorSpeed);
        }
        //Distance elpased
        if (Msg5Ptr->distance_elapsed_lsb == INVAILD_SIGNAL)
        {
            //Raise an indication
//            System_printf("Invalid data 3\n");
//            System_flush();
        }
        else
        {
            UART_OutString("RX Indication Valid MSG  distanceElapsed :\n");
            distanceElapsed = 0;
            distanceElapsed |= Msg5Ptr->distance_elapsed_lsb;
            distanceElapsed |= (Msg5Ptr->distance_elapsed_msb) << 8;
            Rte_Distance_elapsed_iwrite(distanceElapsed);
        }
        // Actual car speed
        if (Msg5Ptr->actual_car_speed_lsb == INVAILD_SIGNAL)
        {
            //Raise an indication
//            System_printf("Invalid data 4\n");
//            System_flush();
        }
        else
        {
            UART_OutString("RX Indication Valid MSG  actualCarSpeed :\n");
            actualCarSpeed = 0;
            actualCarSpeed |= Msg5Ptr->actual_car_speed_lsb;
            actualCarSpeed |= (Msg5Ptr->actual_car_speed_msb) << 8;
            Rte_Actual_Car_speed_iwrite(actualCarSpeed);
        }
        //Actual motor Direction
        if (Msg5Ptr->actual_car_direction == INVAILD_SIGNAL)
        {
            //Raise an indication
//            System_printf("Invalid data 5\n");
//            System_flush();
        }
        else
        {
            UART_OutString("RX Indication Valid MSG  actual_car_direction :\n");
            Rte_Actual_Car_direction_iwrite(Msg5Ptr->actual_car_direction);
        }
    }
    /************** CompassAndTemp **********************/
    if (PduHandleId == COM_PDU_ID_CANIF_RX_COM_MESSAGE_7)
    {
        Com_Frame3_Message7_Ptr Msg7Ptr =
        (Com_Frame3_Message7_Ptr) PduInfoPtr->SduDataPtr;
        uint16_t carAngle;
        // Compass
        if (Msg7Ptr->carAngle_lsb == INVAILD_SIGNAL)
        {
            //Raise an indication
//            System_printf("Invalid data 5\n");
//            System_flush();
        }
        else
        {
            UART_OutString("RX Indication Valid MSG  Compass :\n");
            carAngle = 0;
            carAngle |= Msg7Ptr->carAngle_lsb;
            carAngle |= (Msg7Ptr->carAngle_msb) << 8;
            Rte_Car_angle_data_iwrite(carAngle);
        }
        // Temperature
    }
}
#endif

#ifdef ECU3_ACTUATORNODE
void Com_RxIndication(PduIdType PduHandleId, const PduInfoType *PduInfoPtr)
{
//uint16_t Com_DesiredCarSpeed;
//uint8_t Com_DesiredCarDirection;
//uint8_t Com_DesiredSteeringAngle;

    /************** CompassAndTemp **********************/
    if (PduHandleId == COM_PDU_ID_CANIF_RX_COM_MESSAGE_6)
    {
        Com_Frame1_Message6_Ptr Msg6Ptr =
                (Com_Frame1_Message6_Ptr) PduInfoPtr->SduDataPtr;
        uint16_t carAngle;
        // Compass
        if (Msg6Ptr->carAngle_lsb == INVAILD_SIGNAL)
        {
            //Raise an indication
//            System_printf("Invalid data 1\n");
//            System_flush();
        }
        else
        {
            UART_OutString("RX Indication Valid MSG  Compass :\n");
            carAngle = 0;
            carAngle |= Msg6Ptr->carAngle_lsb;
            carAngle |= (Msg6Ptr->carAngle_msb) << 8;
            Rte_Car_angle_data_iwrite(carAngle);
        }
        // Temperature
    }
    if (PduHandleId == COM_PDU_ID_CANIF_RX_COM_MESSAGE_2)
    {
        Com_Frame0_Message2_Ptr Msg2Ptr =
                (Com_Frame0_Message2_Ptr) PduInfoPtr->SduDataPtr;
        uint8_t motorSpeed[2];
//    uint16_t distanceElapsed;
        uint16_t actualCarSpeed;

        // Motors RPM - (speed)
        if (Msg2Ptr->motor_right_speed == INVAILD_SIGNAL)
        {
            //Raise an indication
//            System_printf("Invalid data 2\n");
//            System_flush();
        }
        else
        {
            UART_OutString("RX Indication Valid MSG  Motors RPM :\n");
            motorSpeed[0] = Msg2Ptr->motor_right_speed;
            motorSpeed[1] = Msg2Ptr->motor_left_speed;
            Rte_Motor_speed_data_iwrite(motorSpeed);
        }
        // Actual car speed
        if (Msg2Ptr->actual_car_speed_lsb == INVAILD_SIGNAL)
        {
            //Raise an indication
//            System_printf("Invalid data 3\n");
//            System_flush();
        }
        else
        {
            UART_OutString("RX Indication Valid MSG  actualCarSpeed :\n");
            actualCarSpeed = 0;
            actualCarSpeed |= Msg2Ptr->actual_car_speed_lsb;
            actualCarSpeed |= (Msg2Ptr->actual_car_speed_msb) << 8;
            Rte_Actual_Car_speed_iwrite(actualCarSpeed);
        }
        //Actual motor Direction
        if (Msg2Ptr->actual_car_direction == INVAILD_SIGNAL)
        {
            //Raise an indication
//            System_printf("Invalid data 4\n");
//            System_flush();
        }
        else
        {
            UART_OutString("RX Indication Valid MSG  actual_car_direction :\n");
            Rte_Actual_Car_direction_iwrite(Msg2Ptr->actual_car_direction);
        }
    }
    /************************* task + Desired steering angle, direction, speed *******************************/
    if (PduHandleId == COM_PDU_ID_CANIF_RX_COM_MESSAGE_1)
    {
        Com_Frame2_Message_1_Ptr Msg1Ptr =
                (Com_Frame2_Message_1_Ptr) PduInfoPtr->SduDataPtr;
        uint16_t desiredCarSpeed = 0;
        // Desired steering angle
        if (Msg1Ptr->desired_steeringAngle == INVAILD_SIGNAL)
        {
            //Raise an indication
//            System_printf("Invalid data 5\n");
//            System_flush();
        }
        else
        {
            UART_OutString(
                    "RX Indication Valid MSG  desired_steeringAngle :\n");
            Rte_Desired_Steering_Angle_iwrite(Msg1Ptr->desired_steeringAngle);
        }
        // Desired car direction
        if (Msg1Ptr->direction == INVAILD_SIGNAL)
        {
            //Raise an indication
//            System_printf("Invalid data 6\n");
//            System_flush();
        }
        else
        {
            UART_OutString("RX Indication Valid MSG  desired_direction :\n");
            Rte_Desired_Car_Direction_iwrite(Msg1Ptr->direction);
        }
        // Desired car speed
        if (Msg1Ptr->speed_lsb == INVAILD_SIGNAL)
        {
//            //Raise an indication
//            System_printf("Invalid data 7\n");
//            System_flush();
        }
        else
        {
            UART_OutString("RX Indication Valid MSG  desiredCarSpeed :\n");
            desiredCarSpeed = 0;
            desiredCarSpeed |= Msg1Ptr->speed_lsb;
            desiredCarSpeed |= (Msg1Ptr->speed_msb) << 8;
            Rte_Desired_Car_speed_iwrite(desiredCarSpeed);
        }

    }

}
#endif
