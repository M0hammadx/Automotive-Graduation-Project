#ifndef CAN_H_
#define CAN_H_

#include "Can_GeneralTypes.h"
#include "ComStack_Types.h"
#include "Can_Cfg.h"
#include "CanIf_Cbk.h"
#include "ECU_CONFIGURATION.h"

//#include "Can_PbCfg.h"
#include "RAL/hw_can.h"
#include "HAL/sysctrl.h"
#include "RAL/hw_types.h"

#include "types.h"
#include "./SL/NVICInterruptHandler.h"

#define CAN_CLOCK 25000000
 
#define VALUEIF2CMSK     0xf3  
#define CANIF2MCTL       0x1488

#define VALUEIF1CMSK     0xF3
#define CANIF1MCTL       0x0888

#define ControllerNum 1 
#define BaudRateNumbers 1

#ifdef ECU1_SENSORYNODE

#define MAX_MSG_NUM     5

#endif

#ifdef ECU2_ALGORITHMICNODE

#define MAX_MSG_NUM     5

#endif

#ifdef ECU3_ACTUATORNODE

#define MAX_MSG_NUM     4

#endif

#define CMASKR 0xf3
#define MCTRLR 0x1088
#define CMASKT 0xB3
#define MCTRLT 0x180
#define MASKBITS 0xff


    

#define CAN_E_PARAM_POINTER 0x01
#define CAN_E_PARAM_HANDLE 0x02
#define CAN_E_PARAM_DATA_LENGTH 0x03
#define CAN_E_PARAM_CONTROLLER 0x04
#define CAN_E_UNINIT 0x05
#define CAN_E_TRANSITION 0x06
#define CAN_E_DATALOST 0x07
#define CAN_E_PARAM_BAUDRATE 0x08
#define CAN_E_ICOM_CONFIG_INVALID 0x09
#define CAN_E_INIT_FAILED 0x0A 

 

 
/////////////////***************************************
 typedef struct  CanControllerFdBaudrateConfigc{
    uint16  CanControllerFdBaudRate ;                   //min = 0 max = 16000
    boolean    CanControllerTxBitRateSwitch ;              //default false
    uint8   CanControllerPropSeg ;                      //min = 0 max = 255
    uint8   CanControllerSeg1  ;                        //min = 0 max = 255
    uint8   CanControllerSeg2  ;                        //min = 0 max = 255
    uint8   CanControllerSyncJumpWidth ;                //min = 0 max = 255
    uint16  CanControllerTrcvDelayCompensationOffset ;  //min = 0 max = 400
    
}CanControllerFdBaudrateConfig;

/*
 *This container contains bit timing related configuration parameters of the CAN controller(s).
 */
typedef struct CanControllerBaudRateConfigc{
    uint16 CanControllerBaudRate ;               //min = 0 max = 2000
    uint8  CanControllerPropSeg  ;               //min = 0 max = 255
    uint8  CanControllerSeg1     ;               //min = 0 max = 255
    uint8  CanControllerSeg2     ;               //min = 0 max = 255
    uint8 CanControllerSyncJumpWidth  ;          //min = 0 max = 255
    uint16 CanControllerBaudRateConfigID  ;      //min = 0 max = 65535
    CanControllerFdBaudrateConfig    obj;
    
}CanControllerBaudRateConfig; 
 

enum CanIcomLevelc{ CAN_ICOM_LEVEL_ONE,CAN_ICOM_LEVEL_TWO};
 enum CanIcomVariantc{ CAN_ICOM_VARIANT_NONE, CAN_ICOM_VARIANT_SW,CAN_ICOM_VARIANT_HW};


//this container contains the parameters related each CAN Driver Unit
typedef struct CanGeneralc{
   
    boolean   CanDevErrorDetect ;                //Switches the development error detection and notification on or off
    boolean   CanMultiplexedTransmission ;            //Specifies if multiplexed transmission shall be supported.ON or OFF
    float  CanTimeoutDuration   ;                 //Specifies the maximum time for blocking function until a timeout is detected. min = 0.000001 max = 65.535
    float  CanMainFunctionWakeupPeriod ;          //This parameter describes the period for cyclic call to Can_MainFunction_Wakeup.
    float  CanMainFunctionModePeriod  ;           //This parameter describes the period for cyclic call to Can_MainFunction_Mode.
    uint8  CanIndex ;                             //Specifies the InstanceId of this module instance. If only one instance is present it shall have the Id 0
    boolean   CanVersionInfoApi  ;                   //Switches the Can_GetVersionInfo() API ON or OFF.
    boolean   CanPublicIcomSupport ;                 //Selects support of Pretended Network features in Can driver..true/false
     
   /*
    *This container contains the parameter for configuring the period for cyclic call to Can_MainFunction_Read or
    * Can_MainFunction_Write depending on the referring item.
    *
    */
    struct CanMainFunctionRWPeriodsc{
        float  CanMainFunctionPeriod;             //min = 0 max = INF
    }CanMainFunctionRWPeriods;
   /*
    *This container contains the general configuration parameters of the ICOM Configuration.
    */
    struct CanIcomGeneralc{
        enum CanIcomLevelc CanIcomLevel ;
        enum CanIcomVariantc CanIcomVariant ;
   
    }CanIcomGeneral;
    
    float CanMainFunctionBusOffPeriod ;     //This parameter describes the period for cyclic call to Can_MainFunction_Busoff.
    boolean CanSetBaudrateApi    ;                     //If this parameter is set to true the Can_SetBaudrate API shall be supported. Otherwise the API is not supported.
    // OsCounter  *CanOsCounterRef  ;                //This parameter contains a reference to the OsCounter, which is used by the CAN driver.
   //void (*CanLPduReceiveCalloutFunction)(void);  //the name of a callout function that is called after a successful reception If this parameter is omitted no callout shall take place.
   // CanIfPrivateCfg  *CanSupportTTCANRef ;   //The parameter refers to CanIfSupportTTCAN parameter in the CAN Interface Module configuration.The CanIfSupportTTCAN parameter defines whether TTCAN is supported
}CanGeneral;

enum CanIcomSignalOperationc{AND,XOR,GREATER,SMALLER,EQUAL};
 
   /*
    *This container contains the configuration parameters for the wakeup
    *causes for matching received messages. It has to be configured as often
    *as received messages are defined as wakeup cause.
    */
typedef struct CanIcomRxMessagec{
        uint32  CanIcomMessageId;                  //This parameter defines the message ID the wakeup causes of this CanIcomRxMessage are configured for.
        uint32  CanIcomMessageIdMask ;             //Describes a mask for filtering of CAN identifiers.
        uint16  CanIcomCounterValue ;              //This parameter defines that the MCU shall wake if the message with the ID is received n times on the communication channel.
        float  CanIcomMissingMessageTimerValue ;   //This parameter defines that the MCU shall wake if the message with the ID is not received for a specific time
        boolean    CanIcomPayloadLengthError ;        //This parameter defines that the MCU shall wake if a payload error occurs
    /*
     *This container contains the configuration parameters for the wakeup causes for matching signals.
    */   
    struct CanIcomRxMessageSignalConfigc{
        uint8 CanIcomSignalMask ;   //This parameter shall be used to mask a signal in the payload of a CAN message.
        uint8 CanIcomSignalValue ;
        enum CanIcomSignalOperationc CanIcomSignalOperation;  //This parameter defines the operation, which shall be used to verify the signal value creates a wakeup condition.
     //ComSignal *CanIcomSignalRef ; 
    }CanIcomRxMessageSignalConfig;
 }CanIcomRxMessage;
/*
 *This container contains the configuration parameters of the wakeup causes to leave the power saving mode.
 */
typedef struct CanIcomWakeupCausesc{
    
    CanIcomRxMessage CanIcomRxMessageobj;

}CanIcomWakeupCauses;

typedef struct CanIcomc{
    struct CanIcomConfigc{
        uint8  CanIcomConfigId ;            //min = 1 max = 255
        boolean   CanIcomWakeOnBusOff ;        // default true
        CanIcomWakeupCauses  CanIcomWakeupCausesobj ;
    
    }CanIcomConfig;
}CanIcom;




enum CanProcessing{INTERRUPT, POLLING };

typedef struct CanControllerc{
    uint8 CanControllerId ;                      //This parameter provides the controller ID which is unique in a given CAN Driver. min = 0 max = 255
    boolean CanControllerActivation   ;              //Defines if a CAN controller is used in the configuration.
    uint32 CanControllerBaseAddress ;            //Specifies the CAN controller base address.
    boolean  CanWakeupSupport  ;                     //CAN driver support for wakeup over CAN Bus.
    boolean CanWakeupFunctionalityAPI  ;            // Adds / removes the service Can_CheckWakeup() from the code.True: Can_CheckWakeup can be used. False: Can_CheckWakeup cannot be used.
   // EcuMWakeupSource       *CanWakeupSourceRef ;   //a reference to the Wakeup Source for this controller as defined in the ECU State Manager.
   // McuClockReferencePoint     *CanCpuClockRef ;  //Reference to the CPU clock configuration, which is set in the MCU driver configuration
    enum CanProcessing  CanTxProcessing;         //Enables / disables API Can_MainFunction_Write() for handling PDU transmission events in polling mode.
    enum CanProcessing  CanRxProcessing;        //Enables / disables API Can_MainFunction_Read() for handling PDU reception events in polling mode.
    enum CanProcessing  CanBusoffProcessing;    //Enables / disables API Can_MainFunction_BusOff() for handling busoff events in polling mode.
    enum CanProcessing  CanWakeupProcessing ;    //Enables / disables API Can_MainFunction_Wakeup() for handling wakeup events in polling mode.
    
    CanControllerBaudRateConfig *CanControllerBaudRateConfigobj ;
    
     
    }CanController; 

    enum CanIdTypec{
        STANDARD,
        EXTENDED,
        MIXED
    } ;
    
   typedef enum {
        TRANSMIT,
        RECEIVE
    }CanObjectTypec;
    
    enum CanHandleTypec{
        FULL,
        BASIC
    };
typedef struct CanHwFilterc{
    uint32  CanHwFilterMask ;                     //min = 0 max = 4294967295
    uint32  CanHwFilterCode ;                     //min = 0 max = 4294967295
        
    }CanHwFilter;

typedef struct CanHardwareObjectc{
    
    uint16          CanObjectId   ;               //min = 0 max = 65535
    uint8           CanFdPaddingValue ;           //min=0  max =255
   
    CanHwFilter *CanHwFilterptr ;
    
    CanController    *CanControllerRef ;
    
    uint16          CanHwObjectCount ;             //min = 1 max = 65535 default 1
    boolean            CanTriggerTransmitEnable ;
    
    enum CanIdTypec CanIdType;
    CanObjectTypec CanObjectType;
    enum CanHandleTypec CanHandleType;              //FULL or BASIC
    
    
    }CanHardwareObject;

typedef struct CanConfigSetc{
    
     
     
    CanIcom      CanIcomobj;
    CanHardwareObject *canHardwareObject ;
    CanController    *CanControllerobj;
    
    
}CanConfigSet;
    
//CAN container holds the configuration of a single CAN Driver.
typedef struct CANC{
    
    CanConfigSet CanConfigSetObj ;
    CanGeneral   CanGeneralObj ;
 
}CAN;


/////
typedef struct CanConfigType{
    
    CanController *canControllers ;
   
    CanHardwareObject *HOH ;
    
    CanIcomRxMessage *CanIcomRxMessageptr ; 
    
    Std_VersionInfoType* canversioninfo ;
     
    can_InterruptType     InterruptType ;     

}Can_ConfigType;

typedef enum {
    CAN_UNINT,
    CAN_READY
}ModuleStateM;

 

////////////////////////////////////////////

void Can_Init( const Can_ConfigType* Config );

void Can_GetVersionInfo( Std_VersionInfoType* versioninfo );

void Can_DeInit( void );

Std_ReturnType Can_SetBaudrate( uint8 Controller, uint16 BaudRateConfigID);  // uint8 Controller *****

Can_ReturnType Can_SetControllerMode( uint8 Controller, Can_StateTransitionType Transition );  

void Can_DisableControllerInterrupts( uint8 Controller );

void Can_EnableControllerInterrupts( uint8 Controller );

Can_ReturnType Can_CheckWakeup( uint8 Controller );

Std_ReturnType Can_GetControllerErrorState( uint8 ControllerId, Can_ErrorStateType* ErrorStatePtr );

Std_ReturnType Can_GetControllerMode( uint8 Controller, Can_ControllerStateType* ControllerModePtr );
Std_ReturnType Can_SetIcomConfiguration( uint8 ControllerId, IcomConfigIdType ConfigurationId );

Can_ReturnType Can_Write( Can_HwHandleType Hth, const Can_PduType* PduInfo );
 void Can_InterruptHandler(uint8 Controller);
void Can_MainFunction_Write( void );
void Can_MainFunction_BusOff( void );

#endif
