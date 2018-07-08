#include "Ultrasonic.h"

uint8_t ULTRASONIC;

//for testing
//static int x = 0;
//static int y = 0;

// flag = 1   ---> this ultrasonic has been activated
static uint8_t Front_Left_Ultrasonic_flag = 0;
static uint8_t Front_Right_Ultrasonic_flag = 0;
static uint8_t Right_Front_Ultrasonic_flag = 0;
static uint8_t Right_Back_Ultrasonic_flag = 0;
static uint8_t Back_Right_Ultrasonic_flag = 0;
static uint8_t Back_Left_Ultrasonic_flag = 0;
static uint8_t Left_Back_Ultrasonic_flag = 0;
static uint8_t Left_Front_Ultrasonic_flag = 0;

// if trig =1  ---> trig this ultrasonic	
static uint8_t Front_Left_Ultrasonic_Trig = 0;
static uint8_t Front_Right_Ultrasonic_Trig = 0;
static uint8_t Right_Front_Ultrasonic_Trig = 0;
static uint8_t Right_Back_Ultrasonic_Trig = 0;
static uint8_t Back_Right_Ultrasonic_Trig = 0;
static uint8_t Back_Left_Ultrasonic_Trig = 0;
static uint8_t Left_Back_Ultrasonic_Trig = 0;
static uint8_t Left_Front_Ultrasonic_Trig = 0;

static uint32_t Ultrasonic_Reading[8];

void Front_Left_Ultrasonic_Handler(void);
void Front_Right_Ultrasonic_Handler(void);
void Right_Front_Ultrasonic_Handler(void);
void Right_Back_Ultrasonic_Handler(void);
void Back_Right_Ultrasonic_Handler(void);
void Back_Left_Ultrasonic_Handler(void);
void Left_Back_Ultrasonic_Handler(void);
void Left_Front_Ultrasonic_Handler(void);
void Ultrasonic_Read_Routine(uint8_t ultrasonic);

//========================================================================================================
void Ultrasonic_Init()
{
#ifdef ULTRASONIC_4TIMER
    //port A , B ,D , E
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    while (ROM_SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA) != true)
        ;
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    while (ROM_SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB) != true)
        ;
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    while (ROM_SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOD) != true)
        ;
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    while (ROM_SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOE) != true)
        ;

    // WT4A(delay)& T2 & T3
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_WTIMER4);
    while (ROM_SysCtlPeripheralReady(SYSCTL_PERIPH_WTIMER4) != true)
        ;
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER2);
    while (ROM_SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER2) != true)
        ;
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER3);
    while (ROM_SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER3) != true)
        ;

    //WT 2
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_WTIMER2);
    while (ROM_SysCtlPeripheralReady(SYSCTL_PERIPH_WTIMER2) != true)
        ;

    //portA trigger
    //A4,5
    ROM_GPIODirModeSet(GPIO_PORTA_BASE, GPIO_PIN_4 | GPIO_PIN_5,
    GPIO_DIR_MODE_OUT);
    ROM_GPIOPadConfigSet(GPIO_PORTA_BASE, GPIO_PIN_4 | GPIO_PIN_5,
    GPIO_STRENGTH_8MA,
                         GPIO_PIN_TYPE_STD);
//portB trigger
//B6,7
    ROM_GPIODirModeSet(GPIO_PORTB_BASE, GPIO_PIN_6 | GPIO_PIN_7,
    GPIO_DIR_MODE_OUT);
    ROM_GPIOPadConfigSet(GPIO_PORTB_BASE, GPIO_PIN_6 | GPIO_PIN_7,
    GPIO_STRENGTH_8MA,
                         GPIO_PIN_TYPE_STD);
    //portE trigger
    ROM_GPIODirModeSet(GPIO_PORTE_BASE,
    GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3,
                       GPIO_DIR_MODE_OUT);
    ROM_GPIOPadConfigSet(GPIO_PORTE_BASE,
    GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3,
                         GPIO_STRENGTH_8MA, GPIO_PIN_TYPE_STD);

    //PortB echo

    //PB 0,2,3
    ROM_GPIOPinTypeTimer(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_2 | GPIO_PIN_3);
//					ROM_GPIOPadConfigSet(GPIO_PORTB_BASE, GPIO_PIN_0|GPIO_PIN_2|GPIO_PIN_3
//			,GPIO_STRENGTH_8MA, GPIO_PIN_TYPE_STD_WPD);
    ROM_GPIOPinConfigure(GPIO_PB0_T2CCP0);
    ROM_GPIOPinConfigure(GPIO_PB2_T3CCP0);
    ROM_GPIOPinConfigure(GPIO_PB3_T3CCP1);

    //PortD echo
    //PD1
    ROM_GPIOPinTypeTimer(GPIO_PORTD_BASE, GPIO_PIN_1);
    //			ROM_GPIOPadConfigSet(GPIO_PORTD_BASE, GPIO_PIN_1,GPIO_STRENGTH_8MA, GPIO_PIN_TYPE_STD_WPD);
    ROM_GPIOPinConfigure(GPIO_PD1_WT2CCP1);

    /**************Timer2,3_Init****************/

    ROM_TimerDisable(TIMER2_BASE, TIMER_A);    //disable Timer2 A
    ROM_TimerDisable(TIMER3_BASE, TIMER_BOTH);  //disable Timer3 A&B
    //select 16 bit timer configuration (for timer 2,3)
    ////capture mode + edge time count mode Timer2-A ,Timer3-A,B
    ROM_TimerConfigure(TIMER2_BASE,
    TIMER_CFG_SPLIT_PAIR | TIMER_CFG_A_CAP_TIME_UP);
    ROM_TimerConfigure(
            TIMER3_BASE,
            TIMER_CFG_SPLIT_PAIR | TIMER_CFG_A_CAP_TIME_UP
                    | TIMER_CFG_B_CAP_TIME_UP);
    ////both edges Timer2 (A)  ,Timer3 (A-B)
    ROM_TimerControlEvent(TIMER2_BASE, TIMER_A, TIMER_EVENT_BOTH_EDGES);
    ROM_TimerControlEvent(TIMER3_BASE, TIMER_BOTH, TIMER_EVENT_BOTH_EDGES);
    ROM_IntEnable(INT_TIMER2A);
    ROM_IntEnable(INT_TIMER3A);
    ROM_IntEnable(INT_TIMER3B);
    ROM_TimerIntEnable(TIMER2_BASE, TIMER_CAPA_EVENT);
    ROM_TimerIntEnable(TIMER3_BASE, TIMER_CAPA_EVENT | TIMER_CAPB_EVENT);

    /************** Wide Timer 2_Init****************/

    ROM_TimerDisable(WTIMER2_BASE, TIMER_B);  //disable WTimer2 B
    //select 32 bit timer configuration (for timer 2)
    //capture mode + edge time count mode	Timer2-B  count up
    ROM_TimerConfigure(WTIMER2_BASE,
    TIMER_CFG_SPLIT_PAIR | TIMER_CFG_B_CAP_TIME_UP);
    ROM_TimerControlEvent(WTIMER2_BASE, TIMER_B, TIMER_EVENT_BOTH_EDGES); //both edges Timer2 (B)
    ROM_IntEnable(INT_WTIMER2B);
    ROM_TimerIntEnable(WTIMER2_BASE, TIMER_CAPB_EVENT);
#endif 

#ifdef ULTRASONIC_8TIMER
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    while(ROM_SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF)!=true);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    while(ROM_SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA)!=true);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    while(ROM_SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB)!=true);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    while(ROM_SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOD)!=true);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    while(ROM_SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOE)!=true);

    // WT4A(delay)& T2 & T3 &T1
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_WTIMER4);
    while (ROM_SysCtlPeripheralReady(SYSCTL_PERIPH_WTIMER4) != true)
        ;
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER2);
    while(ROM_SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER2)!=true);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER3);
    while(ROM_SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER3)!=true);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);
    while(ROM_SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER1)!=true);

    //WT 2 & WT3
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_WTIMER2);
    while(ROM_SysCtlPeripheralReady(SYSCTL_PERIPH_WTIMER2)!=true);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_WTIMER3);
    while(ROM_SysCtlPeripheralReady(SYSCTL_PERIPH_WTIMER3)!=true);

    //portA trigger
    //A4,5
    ROM_GPIODirModeSet(GPIO_PORTA_BASE, GPIO_PIN_4|GPIO_PIN_5
            ,GPIO_DIR_MODE_OUT);
    ROM_GPIOPadConfigSet(GPIO_PORTA_BASE, GPIO_PIN_4|GPIO_PIN_5
            ,GPIO_STRENGTH_8MA, GPIO_PIN_TYPE_STD);
//portB trigger
//B6,7
    ROM_GPIODirModeSet(GPIO_PORTB_BASE, GPIO_PIN_6|GPIO_PIN_7
            ,GPIO_DIR_MODE_OUT);
    ROM_GPIOPadConfigSet(GPIO_PORTB_BASE, GPIO_PIN_6|GPIO_PIN_7
            ,GPIO_STRENGTH_8MA, GPIO_PIN_TYPE_STD);

    //portE trigger
    ROM_GPIODirModeSet(GPIO_PORTE_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
            ,GPIO_DIR_MODE_OUT);
    ROM_GPIOPadConfigSet(GPIO_PORTE_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
            ,GPIO_STRENGTH_8MA, GPIO_PIN_TYPE_STD);

//PortB echo

    //PB 0,2,3
    ROM_GPIOPinTypeTimer(GPIO_PORTB_BASE, GPIO_PIN_0|GPIO_PIN_2|GPIO_PIN_3);
//			ROM_GPIOPadConfigSet(GPIO_PORTB_BASE, GPIO_PIN_0|GPIO_PIN_2|GPIO_PIN_3
//			,GPIO_STRENGTH_8MA, GPIO_PIN_TYPE_STD_WPD);		
    ROM_GPIOPinConfigure(GPIO_PB0_T2CCP0);
    ROM_GPIOPinConfigure(GPIO_PB2_T3CCP0);
    ROM_GPIOPinConfigure(GPIO_PB3_T3CCP1);

    //PortD echo
    //PD1,2,3
    ROM_GPIOPinTypeTimer(GPIO_PORTD_BASE, GPIO_PIN_1 |GPIO_PIN_2 |GPIO_PIN_3 );
//		ROM_GPIOPadConfigSet(GPIO_PORTD_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
//		 															,GPIO_STRENGTH_8MA, GPIO_PIN_TYPE_STD_WPD);
    ROM_GPIOPinConfigure(GPIO_PD1_WT2CCP1);
    ROM_GPIOPinConfigure(GPIO_PD2_WT3CCP0);
    ROM_GPIOPinConfigure(GPIO_PD3_WT3CCP1);

    //PortF echo
    //PF2,3
    ROM_GPIOPinTypeTimer(GPIO_PORTF_BASE,GPIO_PIN_2 |GPIO_PIN_3 );
//					ROM_GPIOPadConfigSet(GPIO_PORTF_BASE,GPIO_PIN_2|GPIO_PIN_3
//			,GPIO_STRENGTH_8MA, GPIO_PIN_TYPE_STD_WPD);
    ROM_GPIOPinConfigure(GPIO_PF2_T1CCP0);
    ROM_GPIOPinConfigure(GPIO_PF3_T1CCP1);

    /**************Timer1,2,3_Init****************/
    ROM_TimerDisable(TIMER1_BASE, TIMER_BOTH);    //disable Timer1 A&B
    ROM_TimerDisable(TIMER2_BASE, TIMER_A);//disable Timer2 A
    ROM_TimerDisable(TIMER3_BASE, TIMER_BOTH);//disable Timer3 A&B
    //select 16 bit timer configuration (for timer 2,3)
    //capture mode + edge time count mode Timer2-A ,Timer3-A,B
    ROM_TimerConfigure(TIMER1_BASE, TIMER_CFG_SPLIT_PAIR |TIMER_CFG_A_CAP_TIME_UP | TIMER_CFG_B_CAP_TIME_UP);
    ROM_TimerConfigure(TIMER2_BASE, TIMER_CFG_SPLIT_PAIR |TIMER_CFG_A_CAP_TIME_UP);
    ROM_TimerConfigure(TIMER3_BASE, TIMER_CFG_SPLIT_PAIR |TIMER_CFG_A_CAP_TIME_UP | TIMER_CFG_B_CAP_TIME_UP);
    //both edges Timer2 (A)  ,Timer3 (A-B)
    ROM_TimerControlEvent(TIMER1_BASE, TIMER_BOTH,TIMER_EVENT_BOTH_EDGES);
    ROM_TimerControlEvent(TIMER2_BASE, TIMER_A,TIMER_EVENT_BOTH_EDGES);
    ROM_TimerControlEvent(TIMER3_BASE, TIMER_BOTH,TIMER_EVENT_BOTH_EDGES);
    ROM_IntEnable(INT_TIMER1A);
    ROM_IntEnable(INT_TIMER1B);
    ROM_IntEnable(INT_TIMER2A);
    ROM_IntEnable(INT_TIMER3A);
    ROM_IntEnable(INT_TIMER3B);
    ROM_TimerIntEnable(TIMER1_BASE, TIMER_CAPA_EVENT | TIMER_CAPB_EVENT);
    ROM_TimerIntEnable(TIMER2_BASE, TIMER_CAPA_EVENT);
    ROM_TimerIntEnable(TIMER3_BASE, TIMER_CAPA_EVENT | TIMER_CAPB_EVENT);

    /************** Wide Timer 2,3_Init****************/
    ROM_TimerDisable(WTIMER2_BASE, TIMER_B);  //disable WTimer2 B
    ROM_TimerDisable(WTIMER3_BASE, TIMER_BOTH);//disable WTimer3 A&B
    //select 32 bit timer configuration (for timer 2,3)
    //capture mode + edge time count mode	Timer2-B ,Timer3 A&B  count up
    ROM_TimerConfigure(WTIMER2_BASE, TIMER_CFG_SPLIT_PAIR |TIMER_CFG_B_CAP_TIME_UP);
    ROM_TimerConfigure(WTIMER3_BASE, TIMER_CFG_SPLIT_PAIR |TIMER_CFG_A_CAP_TIME_UP |TIMER_CFG_B_CAP_TIME_UP);

    //both edges Timer2 (B) ,Timer3 (A-B) 
    ROM_TimerControlEvent(WTIMER2_BASE, TIMER_B,TIMER_EVENT_BOTH_EDGES);
    ROM_TimerControlEvent(WTIMER3_BASE, TIMER_BOTH,TIMER_EVENT_BOTH_EDGES);

    IntEnable(INT_WTIMER2B);
    IntEnable(INT_WTIMER3A);
    IntEnable(INT_WTIMER3B);

    ROM_TimerIntEnable(WTIMER2_BASE, TIMER_CAPB_EVENT);
    ROM_TimerIntEnable(WTIMER3_BASE, TIMER_CAPA_EVENT |TIMER_CAPB_EVENT);
//
//    TimerIntRegister (TIMER2_BASE, TIMER_A,Front_Left_Ultrasonic_Handler);
//    TimerIntRegister (TIMER3_BASE, TIMER_A,Front_Right_Ultrasonic_Handler);
//    TimerIntRegister (TIMER3_BASE, TIMER_B,Right_Front_Ultrasonic_Handler);
//    TimerIntRegister (WTIMER2_BASE, TIMER_B,Right_Back_Ultrasonic_Handler);
//    TimerIntRegister (WTIMER3_BASE, TIMER_A,Back_Right_Ultrasonic_Handler);
//    TimerIntRegister (WTIMER3_BASE, TIMER_B,Back_Left_Ultrasonic_Handler);
//    TimerIntRegister (TIMER1_BASE, TIMER_A,Left_Back_Ultrasonic_Handler);
//    TimerIntRegister (TIMER1_BASE, TIMER_B,Left_Front_Ultrasonic_Handler);
#endif

}
//========================================================================================================
void Ultrasonic_Trig(uint8_t ultrasonic)
{

#ifdef ULTRASONIC_4TIMER
//you cant read two ultrasonic in one side Front,Right,Left or Back
//front  Echo->PB0   Left Trig->PE0     Right Trig->PE1
//Righ   Ech0->PB2   Front Trig->PE2    Back  Trig->PE3
//Back   Echo->PB3   Right Trig->PA4    Left  Trig->PA5
//Left   Echo->PD1   Back Trig->PB6    Front  Trig->PB7
    if ((ultrasonic & ((ultrasonic >> 1) & 0x55)) != 0)
    {

//error

    }
    else
    {
        ULTRASONIC |= ultrasonic;
        Ultrasonic_Read_Routine(ULTRASONIC);
//delay_mSec(30);
    }

#endif

#ifdef ULTRASONIC_8TIMER
    ULTRASONIC |= ultrasonic;
//front_Left    Echo->PB0    Trig->PE0   
//front_Right   Echo->pB2    Trig->PE1
//Righ_Front    Ech0->PB3    Trig->PE2
//Righ_Back     Echo->pD1    Trig->PE3
//Back_Right    Echo->PD2    Trig->PA4 
//Back_Left     Echo->pD3    Trig->PA5
//Left_Back     Echo->PF2    Trigh->PB6  
//Left_Front    Echo->pF3    Trig->PB7
    if((ULTRASONIC & Front_Left_Ultrasonic)&&(Front_Left_Ultrasonic_flag ==0))
    {
        Front_Left_Ultrasonic_flag =1;
        Front_Left_Ultrasonic_Trig =1;
        ROM_TimerEnable(TIMER2_BASE,TIMER_A);
    }

    if((ULTRASONIC &Front_Right_Ultrasonic)&&(Front_Right_Ultrasonic_flag ==0))
    {
        Front_Right_Ultrasonic_flag = 1;
        Front_Right_Ultrasonic_Trig = 1;
        ROM_TimerEnable(TIMER3_BASE,TIMER_A);
    }

    if((ULTRASONIC &Right_Front_Ultrasonic)&&(Right_Front_Ultrasonic_flag ==0))
    {
        Right_Front_Ultrasonic_flag = 1;
        Right_Front_Ultrasonic_Trig = 1;
        ROM_TimerEnable(TIMER3_BASE,TIMER_B);
    }

    if((ULTRASONIC &Right_Back_Ultrasonic)&&(Right_Back_Ultrasonic_flag ==0))
    {
        Right_Back_Ultrasonic_flag = 1;
        Right_Back_Ultrasonic_Trig = 1;
        ROM_TimerEnable(WTIMER2_BASE,TIMER_B);
    }

    if((ULTRASONIC &Back_Right_Ultrasonic)&&(Back_Right_Ultrasonic_flag ==0))
    {
        Back_Right_Ultrasonic_flag = 1;
        Back_Right_Ultrasonic_Trig = 1;
        ROM_TimerEnable(WTIMER3_BASE,TIMER_A);
    }

    if((ULTRASONIC &Back_Left_Ultrasonic)&&(Back_Left_Ultrasonic_flag ==0))
    {
        Back_Left_Ultrasonic_flag = 1;
        Back_Left_Ultrasonic_Trig = 1;
        ROM_TimerEnable(WTIMER3_BASE,TIMER_B);
    }

    if((ULTRASONIC &Left_Back_Ultrasonic)&&(Left_Back_Ultrasonic_flag ==0))
    {
        Left_Back_Ultrasonic_flag = 1;
        Left_Back_Ultrasonic_Trig = 1;
        ROM_TimerEnable(TIMER1_BASE,TIMER_A);
    }

    if((ULTRASONIC &Left_Front_Ultrasonic)&&(Left_Front_Ultrasonic_flag ==0))
    {
        Left_Front_Ultrasonic_flag = 1;
        Left_Front_Ultrasonic_Trig = 1;
        ROM_TimerEnable(TIMER1_BASE,TIMER_B);
    }

    if(Front_Left_Ultrasonic_Trig)
    {
        ROM_GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5, GPIO_PIN_5);
    }
    if(Front_Right_Ultrasonic_Trig)
    {   ROM_GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_0, GPIO_PIN_0);}
    if(Right_Front_Ultrasonic_Trig)
    {   ROM_GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_4, GPIO_PIN_4);}
    if(Right_Back_Ultrasonic_Trig)
    {   ROM_GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_3, GPIO_PIN_3);}
    if(Back_Right_Ultrasonic_Trig)
    {   ROM_GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_2, GPIO_PIN_2);}
    if(Back_Left_Ultrasonic_Trig)
    {   ROM_GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1, GPIO_PIN_1);}
    if(Left_Back_Ultrasonic_Trig)
    {   ROM_GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_6, GPIO_PIN_6);}
    if(Left_Front_Ultrasonic_Trig)
    {   ROM_GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_7, GPIO_PIN_7);}

    if(Front_Left_Ultrasonic_Trig | Front_Right_Ultrasonic_Trig
            | Right_Front_Ultrasonic_Trig |Right_Back_Ultrasonic_Trig
            | Back_Right_Ultrasonic_Trig | Back_Left_Ultrasonic_Trig
            | Left_Back_Ultrasonic_Trig | Left_Front_Ultrasonic_Trig)
    {
        delay_microSec(10);

    }

    ROM_GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_0 |GPIO_PIN_1 |GPIO_PIN_2 |GPIO_PIN_3, 0x00);
    ROM_GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_4 |GPIO_PIN_5 , 0x00);
    ROM_GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_6 |GPIO_PIN_7 , 0x00);
    Front_Left_Ultrasonic_Trig=0;
    Front_Right_Ultrasonic_Trig=0;
    Right_Front_Ultrasonic_Trig=0;
    Right_Back_Ultrasonic_Trig=0;
    Back_Right_Ultrasonic_Trig=0;
    Back_Left_Ultrasonic_Trig=0;
    Left_Back_Ultrasonic_Trig=0;
    Left_Front_Ultrasonic_Trig=0;
#endif

}

//========================================================================================================
#ifdef ULTRASONIC_4TIMER
void Ultrasonic_Read_Routine(uint8_t ultrasonic)
{

    x++;

    if ((ultrasonic & Front_Left_Ultrasonic)
            && (Front_Left_Ultrasonic_flag == 0)
            && (Front_Right_Ultrasonic_flag == 0))
    {
        Front_Left_Ultrasonic_flag = 1;
        Front_Left_Ultrasonic_Trig = 1;
        ROM_TimerEnable(TIMER2_BASE, TIMER_A);
        TimerIntRegister(TIMER2_BASE, TIMER_A, Front_Left_Ultrasonic_Handler);
    }

    if ((ultrasonic & Front_Right_Ultrasonic)
            && (Front_Left_Ultrasonic_flag == 0)
            && (Front_Right_Ultrasonic_flag == 0))
    {
        Front_Right_Ultrasonic_flag = 1;
        Front_Right_Ultrasonic_Trig = 1;
        ROM_TimerEnable(TIMER2_BASE, TIMER_A);
        TimerIntRegister(TIMER2_BASE, TIMER_A, Front_Right_Ultrasonic_Handler);
    }

    if ((ultrasonic & Right_Front_Ultrasonic)
            && (Right_Front_Ultrasonic_flag == 0)
            && (Right_Back_Ultrasonic_flag == 0))
    {
        Right_Front_Ultrasonic_flag = 1;
        Right_Front_Ultrasonic_Trig = 1;
        ROM_TimerEnable(TIMER3_BASE, TIMER_A);
        TimerIntRegister(TIMER3_BASE, TIMER_A, Right_Front_Ultrasonic_Handler);
    }

    if ((ultrasonic & Right_Back_Ultrasonic)
            && (Right_Front_Ultrasonic_flag == 0)
            && (Right_Back_Ultrasonic_flag == 0))
    {
        Right_Back_Ultrasonic_flag = 1;
        Right_Back_Ultrasonic_Trig = 1;
        ROM_TimerEnable(TIMER3_BASE, TIMER_A);
        TimerIntRegister(TIMER3_BASE, TIMER_A, Right_Back_Ultrasonic_Handler);
    }

    if ((ultrasonic & Back_Right_Ultrasonic)
            && (Back_Right_Ultrasonic_flag == 0)
            && (Back_Left_Ultrasonic_flag == 0))
    {
        Back_Right_Ultrasonic_flag = 1;
        Back_Right_Ultrasonic_Trig = 1;
        ROM_TimerEnable(TIMER3_BASE, TIMER_B);
        TimerIntRegister(TIMER3_BASE, TIMER_B, Back_Right_Ultrasonic_Handler);
    }

    if ((ultrasonic & Back_Left_Ultrasonic) && (Back_Right_Ultrasonic_flag == 0)
            && (Back_Left_Ultrasonic_flag == 0))
    {
        Back_Left_Ultrasonic_flag = 1;
        Back_Left_Ultrasonic_Trig = 1;
        ROM_TimerEnable(TIMER3_BASE, TIMER_B);
        TimerIntRegister(TIMER3_BASE, TIMER_B, Back_Left_Ultrasonic_Handler);
    }

    if ((ultrasonic & Left_Back_Ultrasonic) && (Left_Back_Ultrasonic_flag == 0)
            && (Left_Front_Ultrasonic_flag == 0))
    {
        Left_Back_Ultrasonic_flag = 1;
        Left_Back_Ultrasonic_Trig = 1;
        ROM_TimerEnable(WTIMER2_BASE, TIMER_B);
        TimerIntRegister(WTIMER2_BASE, TIMER_B, Left_Back_Ultrasonic_Handler);
    }

    if ((ultrasonic & Left_Front_Ultrasonic) && (Left_Back_Ultrasonic_flag == 0)
            && (Left_Front_Ultrasonic_flag == 0))
    {
        Left_Front_Ultrasonic_flag = 1;
        Left_Front_Ultrasonic_Trig = 1;
        ROM_TimerEnable(WTIMER2_BASE, TIMER_B);
        TimerIntRegister(WTIMER2_BASE, TIMER_B, Left_Front_Ultrasonic_Handler);
    }

    if (Front_Left_Ultrasonic_Trig)
    {
        ROM_GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_0, 0x01);
    }
    if (Front_Right_Ultrasonic_Trig)
    {
        ROM_GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1, 0x02);
    }
    if (Right_Front_Ultrasonic_Trig)
    {
        ROM_GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_2, 0x04);
    }
    if (Right_Back_Ultrasonic_Trig)
    {
        ROM_GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_3, 0x08);
    }
    if (Back_Right_Ultrasonic_Trig)
    {
        ROM_GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_4, 0x10);
    }
    if (Back_Left_Ultrasonic_Trig)
    {
        ROM_GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5, 0x20);
    }
    if (Left_Back_Ultrasonic_Trig)
    {
        ROM_GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_6, 0x40);
    }
    if (Left_Front_Ultrasonic_Trig)
    {
        ROM_GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_7, 0x80);
    }

    if (Front_Left_Ultrasonic_Trig | Front_Right_Ultrasonic_Trig
            | Right_Front_Ultrasonic_Trig | Right_Back_Ultrasonic_Trig
            | Back_Right_Ultrasonic_Trig | Back_Left_Ultrasonic_Trig
            | Left_Back_Ultrasonic_Trig | Left_Front_Ultrasonic_Trig)
    {
        delay_microSec(10);
    }

    ROM_GPIOPinWrite(GPIO_PORTE_BASE,
    GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3,
                     0x00);
    ROM_GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_4 | GPIO_PIN_5, 0x00);
    ROM_GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_6 | GPIO_PIN_7, 0x00);
    Front_Left_Ultrasonic_Trig = 0;
    Front_Right_Ultrasonic_Trig = 0;
    Right_Front_Ultrasonic_Trig = 0;
    Right_Back_Ultrasonic_Trig = 0;
    Back_Right_Ultrasonic_Trig = 0;
    Back_Left_Ultrasonic_Trig = 0;
    Left_Back_Ultrasonic_Trig = 0;
    Left_Front_Ultrasonic_Trig = 0;

    if ((ULTRASONIC & ((ULTRASONIC >> 1) & 0x55)) != 0)
    {
        int s = ULTRASONIC;
        while ((ULTRASONIC & ((ULTRASONIC >> 1) & 0x55)) != 0)
        {
            if (s != ULTRASONIC)
            {
                Ultrasonic_Read_Routine(ULTRASONIC);
            }
        }
    }

}
#endif
//========================================================================================================
uint32_t Ultrasonic_Get_Distant(uint8_t distant)
{
    static int devisor;
    if (distant < 8)
    {
        devisor = 2 * SysCtlClockGet() / 34000;
        return Ultrasonic_Reading[distant] / devisor;
    }
    else
    {
//error
        return 0;
    }
}
void Ultrasonic_Get_Distant_Batch(uint8_t* distantances)
{
    static int devisor;

        devisor = 2 * SysCtlClockGet() / 34000;
        for(int i =0 ; i<8 ; i++)
        distantances[i]  = (uint8_t)(Ultrasonic_Reading[i] / devisor);
//error
        //return 0;

}

//========================================================================================================
void delay_microSec(int time)
{
    int i;
    // 16 bit mode   periodic mode   count down
    ROM_TimerConfigure(WTIMER4_BASE,
    TIMER_CFG_SPLIT_PAIR | TIMER_CFG_A_PERIODIC);
    //clear flag (acknowledge) during init
    ROM_TimerIntClear(WTIMER4_BASE, TIMER_TIMA_TIMEOUT);
    // 1 microSec = SysCtlClock / 10^6
    ROM_TimerLoadSet(WTIMER4_BASE, TIMER_A, SysCtlClockGet() / 1000000);
    ROM_TimerEnable(WTIMER4_BASE, TIMER_A);

    for (i = 0; i < time; i++)
    {
        while (ROM_TimerIntStatus(WTIMER4_BASE, false) == 0)
            ;
        ROM_TimerIntClear(WTIMER4_BASE, TIMER_TIMA_TIMEOUT);
    }
    ROM_TimerDisable(WTIMER4_BASE, TIMER_A);    // disable timer
}
//========================================================================================================
void delay_mSec(int time)
{


    int i;
    // 16 bit mode   periodic mode   count down
    ROM_TimerConfigure(WTIMER4_BASE,
    TIMER_CFG_SPLIT_PAIR | TIMER_CFG_A_PERIODIC);
    //clear flag (acknowledge) during init
    ROM_TimerIntClear(WTIMER4_BASE, TIMER_TIMA_TIMEOUT);
    // 1ms  SysCtlClock / 10^3
    ROM_TimerLoadSet(WTIMER4_BASE, TIMER_A, SysCtlClockGet() / 1000);
    ROM_TimerEnable(WTIMER4_BASE, TIMER_A);

    for (i = 0; i < time; i++)
    {
        while (ROM_TimerIntStatus(WTIMER4_BASE, false) == 0)
            ;
        ROM_TimerIntClear(WTIMER4_BASE, TIMER_TIMA_TIMEOUT);
    }
    ROM_TimerDisable(WTIMER4_BASE, TIMER_A);    // disable timer
}
//========================================================================================================
#ifdef ULTRASONIC_4TIMER
void Front_Left_Ultrasonic_Handler(void)                     //TIMER2A_Handler
{
    static uint32_t high = 0, low = 0;
    ROM_TimerIntClear(TIMER2_BASE, TIMER_CAPA_EVENT);
    if ((ROM_GPIOPinRead(GPIO_PORTB_BASE, GPIO_PIN_0) & 0x01) == 0x01)
    {
        high = ROM_TimerValueGet(TIMER2_BASE, TIMER_A);
    }
    else if ((ROM_GPIOPinRead(GPIO_PORTB_BASE, GPIO_PIN_0) & 0x01) == 0x00)
    {
        low = ROM_TimerValueGet(TIMER2_BASE, TIMER_A);
        Ultrasonic_Reading[Front_Left] = (low - high);
        ROM_TimerDisable(TIMER2_BASE, TIMER_A);
        ULTRASONIC &= ~Front_Left_Ultrasonic;
        Front_Left_Ultrasonic_flag = 0;
    }
}
//========================================================================================================
void Front_Right_Ultrasonic_Handler(void)                    //TIMER2A_Handler
{
    static uint32_t high = 0, low = 0;
    ROM_TimerIntClear(TIMER2_BASE, TIMER_CAPA_EVENT);
    if ((ROM_GPIOPinRead(GPIO_PORTB_BASE, GPIO_PIN_0) & 0x01) == 0x01)
    {
        high = ROM_TimerValueGet(TIMER2_BASE, TIMER_A);
    }
    else if ((ROM_GPIOPinRead(GPIO_PORTB_BASE, GPIO_PIN_0) & 0x01) == 0x00)
    {
        low = ROM_TimerValueGet(TIMER2_BASE, TIMER_A);
        Ultrasonic_Reading[Front_Right] = (low - high);
        ROM_TimerDisable(TIMER2_BASE, TIMER_A);
        ULTRASONIC &= ~Front_Right_Ultrasonic;
        Front_Right_Ultrasonic_flag = 0;
    }
}
//============================================================================================================

void Right_Front_Ultrasonic_Handler(void)                      //TIMER3A_Handler
{
    static uint32_t high = 0, low = 0;
    ROM_TimerIntClear(TIMER3_BASE, TIMER_CAPA_EVENT);
    if ((ROM_GPIOPinRead(GPIO_PORTB_BASE, GPIO_PIN_2) & 0x04) == 0x04)
    {
        high = ROM_TimerValueGet(TIMER3_BASE, TIMER_A);
    }
    else if ((ROM_GPIOPinRead(GPIO_PORTB_BASE, GPIO_PIN_2) & 0x04) == 0x00)
    {
        low = ROM_TimerValueGet(TIMER3_BASE, TIMER_A);
        Ultrasonic_Reading[Right_Front] = (low - high);
        ROM_TimerDisable(TIMER3_BASE, TIMER_A);
        ULTRASONIC &= ~Right_Front_Ultrasonic;
        Right_Front_Ultrasonic_flag = 0;
    }

}
//========================================================================================================
void Right_Back_Ultrasonic_Handler(void)                       //TIMER3A_Handler
{
    static uint32_t high = 0, low = 0;
    ROM_TimerIntClear(TIMER3_BASE, TIMER_CAPA_EVENT);
    if ((ROM_GPIOPinRead(GPIO_PORTB_BASE, GPIO_PIN_2) & 0x04) == 0x04)
    {
        high = ROM_TimerValueGet(TIMER3_BASE, TIMER_A);
    }
    else if ((ROM_GPIOPinRead(GPIO_PORTB_BASE, GPIO_PIN_2) & 0x04) == 0x00)
    {
        low = ROM_TimerValueGet(TIMER3_BASE, TIMER_A);
        Ultrasonic_Reading[Right_Back] = (low - high);
        ROM_TimerDisable(TIMER3_BASE, TIMER_A);
        ULTRASONIC &= ~Right_Back_Ultrasonic;
        Right_Back_Ultrasonic_flag = 0;
    }
}
//========================================================================================================
void Back_Right_Ultrasonic_Handler(void)                       //TIMER3B_Handler
{
    static uint32_t high = 0, low = 0;
    ROM_TimerIntClear(TIMER3_BASE, TIMER_CAPB_EVENT);

    if ((ROM_GPIOPinRead(GPIO_PORTB_BASE, GPIO_PIN_3) & 0x08) == 0x08)
    {
        high = ROM_TimerValueGet(TIMER3_BASE, TIMER_B);
    }
    else if ((ROM_GPIOPinRead(GPIO_PORTB_BASE, GPIO_PIN_3) & 0x08) == 0x00)
    {
        low = ROM_TimerValueGet(TIMER3_BASE, TIMER_B);
        Ultrasonic_Reading[Back_Right] = (low - high);
        ROM_TimerDisable(TIMER3_BASE, TIMER_B);
        ULTRASONIC &= ~Back_Right_Ultrasonic;
        Back_Right_Ultrasonic_flag = 0;
    }
}
//========================================================================================================
void Back_Left_Ultrasonic_Handler(void)                        //TIMER3B_Handler
{
    static uint32_t high = 0, low = 0;
    ROM_TimerIntClear(TIMER3_BASE, TIMER_CAPB_EVENT);

    if ((ROM_GPIOPinRead(GPIO_PORTB_BASE, GPIO_PIN_3) & 0x08) == 0x08)
    {
        high = ROM_TimerValueGet(TIMER3_BASE, TIMER_B);
    }
    else if ((ROM_GPIOPinRead(GPIO_PORTB_BASE, GPIO_PIN_3) & 0x08) == 0x00)
    {
        low = ROM_TimerValueGet(TIMER3_BASE, TIMER_B);
        Ultrasonic_Reading[Back_Left] = (low - high);
        ROM_TimerDisable(TIMER3_BASE, TIMER_B);
        ULTRASONIC &= ~Back_Left_Ultrasonic;
        Back_Left_Ultrasonic_flag = 0;
    }
}
//========================================================================================================
void Left_Back_Ultrasonic_Handler(void)                    //WTIMER2B_Handler
{
    static uint32_t high = 0, low = 0;
    ROM_TimerIntClear(WTIMER2_BASE, TIMER_CAPB_EVENT);
    if ((ROM_GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_1) & 0x02) == 0x02)
    {
        high = ROM_TimerValueGet(WTIMER2_BASE, TIMER_B);
    }
    else if ((ROM_GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_1) & 0x02) == 0x00)
    {
        low = ROM_TimerValueGet(WTIMER2_BASE, TIMER_B);
        Ultrasonic_Reading[Left_Back] = (low - high);
        ROM_TimerDisable(WTIMER2_BASE, TIMER_B);
        ULTRASONIC &= ~Left_Back_Ultrasonic;
        Left_Back_Ultrasonic_flag = 0;
    }
}
//========================================================================================================
void Left_Front_Ultrasonic_Handler(void)                      //WTIMER2B_Handler
{
    static uint32_t high = 0, low = 0;
    ROM_TimerIntClear(WTIMER2_BASE, TIMER_CAPB_EVENT);
    if ((ROM_GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_1) & 0x02) == 0x02)
    {
        high = ROM_TimerValueGet(WTIMER2_BASE, TIMER_B);
    }
    else if ((ROM_GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_1) & 0x02) == 0x00)
    {
        low = ROM_TimerValueGet(WTIMER2_BASE, TIMER_B);
        Ultrasonic_Reading[Left_Front] = (low - high);
        ROM_TimerDisable(WTIMER2_BASE, TIMER_B);
        ULTRASONIC &= ~Left_Front_Ultrasonic;
        Left_Front_Ultrasonic_flag = 0;
    }
}
#endif
//========================================================================================================
#ifdef ULTRASONIC_8TIMER
void Front_Left_Ultrasonic_Handler(void)                     //TIMER2A_Handler
 {
 static uint32_t high = 0, low = 0;
 ROM_TimerIntClear(TIMER2_BASE, TIMER_CAPA_EVENT);
 if ((ROM_GPIOPinRead(GPIO_PORTB_BASE, GPIO_PIN_0)&0x01)==0x01)
 {
 high = ROM_TimerValueGet(TIMER2_BASE, TIMER_A);
 }
 else if ((ROM_GPIOPinRead(GPIO_PORTB_BASE, GPIO_PIN_0)&0x01)==0x00)
 {  low = ROM_TimerValueGet(TIMER2_BASE, TIMER_A);
 Ultrasonic_Reading[Front_Left] = (low - high);
 ROM_TimerDisable(TIMER2_BASE, TIMER_A);
 ULTRASONIC &=~Front_Left_Ultrasonic;
 Front_Left_Ultrasonic_flag = 0 ;
 }
 }

//========================================================================================================
void Front_Right_Ultrasonic_Handler(void)                    //TIMER3A_Handler
 {
 static uint32_t high = 0, low = 0;
 ROM_TimerIntClear(TIMER3_BASE, TIMER_CAPA_EVENT);
 if ((ROM_GPIOPinRead(GPIO_PORTB_BASE, GPIO_PIN_2)&0x04)==0x04)
 {
 high = ROM_TimerValueGet(TIMER3_BASE, TIMER_A);
 }
 else if ((ROM_GPIOPinRead(GPIO_PORTB_BASE, GPIO_PIN_2)&0x04)==0x00)
 {  low = ROM_TimerValueGet(TIMER3_BASE, TIMER_A);
 Ultrasonic_Reading[Front_Right] = (low - high);
 ROM_TimerDisable(TIMER3_BASE, TIMER_A);
 ULTRASONIC &=~Front_Right_Ultrasonic;
 Front_Right_Ultrasonic_flag = 0 ;
 }
 }


//========================================================================================================
void Right_Front_Ultrasonic_Handler(void)//TIMER3B_Handler
{
    static uint32_t high = 0, low = 0;
    ROM_TimerIntClear(TIMER3_BASE, TIMER_CAPB_EVENT);
    if ((ROM_GPIOPinRead(GPIO_PORTB_BASE, GPIO_PIN_3)&0x08)==0x08)
    {
        high = ROM_TimerValueGet(TIMER3_BASE, TIMER_B);
    }
    else if ((ROM_GPIOPinRead(GPIO_PORTB_BASE, GPIO_PIN_3)&0x08)==0x00)
    {   low = ROM_TimerValueGet(TIMER3_BASE, TIMER_B);
        Ultrasonic_Reading[Right_Front] = (low - high);
        ROM_TimerDisable(TIMER3_BASE, TIMER_B);
        ULTRASONIC &=~Right_Front_Ultrasonic;
        Right_Front_Ultrasonic_flag = 0;
    }
}
//========================================================================================================
void Right_Back_Ultrasonic_Handler(void)//WTIMER2B_Handler
{
    static uint32_t high = 0, low = 0;
    ROM_TimerIntClear(WTIMER2_BASE, TIMER_CAPB_EVENT);
    if ((ROM_GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_1)&0x02)==0x02)
    {
        high = ROM_TimerValueGet(WTIMER2_BASE, TIMER_B);
    }
    else if ((ROM_GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_1)&0x02)==0x00)
    {
        low = ROM_TimerValueGet(WTIMER2_BASE, TIMER_B);
        Ultrasonic_Reading[Right_Back] = (low - high);
        ROM_TimerDisable(WTIMER2_BASE, TIMER_B);
        ULTRASONIC &=~Right_Back_Ultrasonic;
        Right_Back_Ultrasonic_flag = 0;
    }
}
//========================================================================================================
void Back_Right_Ultrasonic_Handler(void)//WTIMER3A_Handler
{
    static uint32_t high = 0, low = 0;
    ROM_TimerIntClear(WTIMER3_BASE, TIMER_CAPA_EVENT);

    if ((ROM_GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_2)&0x04)==0x04)
    {
        high = ROM_TimerValueGet(WTIMER3_BASE, TIMER_A);
    }
    else if ((ROM_GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_2)&0x04)==0x00)
    {
        low =ROM_TimerValueGet(WTIMER3_BASE, TIMER_A);
        Ultrasonic_Reading[Back_Right] =(low - high);
        ROM_TimerDisable(WTIMER3_BASE, TIMER_A);
        ULTRASONIC &=~Back_Right_Ultrasonic;
        Back_Right_Ultrasonic_flag = 0;
    }
}
//========================================================================================================
void Back_Left_Ultrasonic_Handler(void)//WTIMER3B_Handler
{
    static uint32_t high = 0, low = 0;
    ROM_TimerIntClear(WTIMER3_BASE, TIMER_CAPB_EVENT);

    if ((ROM_GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_3)&0x08)==0x08)
    {
        high = ROM_TimerValueGet(WTIMER3_BASE, TIMER_B);
    }
    else if ((ROM_GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_3)&0x08)==0x00)
    {
        low =ROM_TimerValueGet(WTIMER3_BASE, TIMER_B);
        Ultrasonic_Reading[Back_Left] = (low - high);
        ROM_TimerDisable(WTIMER3_BASE, TIMER_B);
        ULTRASONIC &=~Back_Left_Ultrasonic;
        Back_Left_Ultrasonic_flag = 0;
    }
}
//========================================================================================================
void Left_Back_Ultrasonic_Handler(void)//TIMER1A_Handler
{   static uint32_t high = 0, low = 0;
    ROM_TimerIntClear(TIMER1_BASE, TIMER_CAPA_EVENT);
    if ((ROM_GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_2)&0x04)==0x04)
    {
        high =ROM_TimerValueGet(TIMER1_BASE, TIMER_A);
    }
    else if ((ROM_GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_2)&0x04)==0x00)
    {
        low =ROM_TimerValueGet(TIMER1_BASE, TIMER_A);
        Ultrasonic_Reading[Left_Back] = (low - high);
        ROM_TimerDisable(TIMER1_BASE, TIMER_A);
        ULTRASONIC &=~Left_Back_Ultrasonic;
        Left_Back_Ultrasonic_flag = 0;
    }
}
//========================================================================================================
void Left_Front_Ultrasonic_Handler(void)//TIMER1B_Handler
{   static uint32_t high = 0, low = 0;
    ROM_TimerIntClear(TIMER1_BASE, TIMER_CAPB_EVENT);
    if ((ROM_GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_3)&0x08)==0x08)
    {
        high =ROM_TimerValueGet(TIMER1_BASE, TIMER_B);
    }
    else if ((ROM_GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_3)&0x08)==0x00)
    {
        low =ROM_TimerValueGet(TIMER1_BASE, TIMER_B);
        Ultrasonic_Reading[Left_Front] = (low - high);
        ROM_TimerDisable(TIMER1_BASE, TIMER_B);
        ULTRASONIC &=~Left_Front_Ultrasonic;
        Left_Front_Ultrasonic_flag = 0;
    }
}

#endif	
