#define TARGET_IS_BLIZZARD_RB0
#include "ultrasonic.h"

#ifdef Ultrasonic_Polling_mode
static void delay_mSec(int time);
#endif
static void delay_microSec(int time);
//static void delay_mSec(int time);
int flag_1 = 0, flag_2 = 0, flag_3 = 0, flag_4 = 0;
uint32_t Dis1, Dis2, Dis3, Dis4;
void Ultrasonic_init(void)
{

    /*************PortA,B_Init*************/
    SYSCTL_RCGC2_R |= 0x03;
    while (SYSCTL_PRGPIO_R & 0x03 != 0x03)
        ;
    SYSCTL_RCGCTIMER_R |= 0x0C | 0x01;        // T0(delay)& T2 & T3
    while (SYSCTL_PRTIMER_R & 0x0D != 0x0D)
        ;

    //portA trigger
    GPIO_PORTA_LOCK_R = 0x4C4F434B;
    GPIO_PORTA_CR_R |= 0xF0;   //A4,5,6,7
    GPIO_PORTA_DIR_R |= 0xF0;
    GPIO_PORTA_DEN_R |= 0xF0;
    GPIO_PORTA_AFSEL_R &= ~0xF0;
    GPIO_PORTA_AMSEL_R &= ~0xF0;
    GPIO_PORTA_PCTL_R &= ~0xFFFF0000;
    GPIO_PORTA_DR8R_R |= 0xF0;

    //PortB echo
    GPIO_PORTB_LOCK_R = 0x4C4F434B;
    GPIO_PORTB_CR_R |= 0x0F;
    GPIO_PORTB_DIR_R &= ~0x0F;
    GPIO_PORTB_DEN_R |= 0x0F;
    GPIO_PORTB_AFSEL_R |= 0x0F;
    GPIO_PORTB_AMSEL_R &= ~0x0F;
    GPIO_PORTB_PCTL_R &= ~0x0000FFFF;
    GPIO_PORTB_PCTL_R |= 0x00007777;
    GPIO_PORTB_DR8R_R |= 0x0F;
    GPIO_PORTB_PDR_R |= 0x0F;

    /**************Timer2,3_Init****************/

    TIMER2_CTL_R &= ~0x0101;    //disable Timer2 A&B
    TIMER3_CTL_R &= ~0x0101; 	 //disable Timer3 A&B
    TIMER2_CFG_R = 0x04;       //select 16 bit timer configuration (for timer 2)
    TIMER3_CFG_R = 0x04;	//select 16 bit timer configuration (for timer 3)

    TIMER2_TAMR_R &= ~0xFFFF;	//clears all register bits	Timer2-A
    TIMER3_TAMR_R &= ~0xFFFF;   //clears all register bits	Timer3-A

    TIMER2_TAMR_R |= 0x17;		//capture mode + edge time count mode Timer2-A
    TIMER3_TAMR_R |= 0x17;		//capture mode + edge time count mode Timer3-A

    TIMER2_TBMR_R &= ~0xFFFF;    //clears all register bits Timer2-B
    TIMER3_TBMR_R &= ~0xFFFF;    //clears all register bits	Timer3-B

    TIMER2_TBMR_R |= 0x17;		//capture mode + edge time count mode	Timer2-B
    TIMER3_TBMR_R |= 0x17;    //capture mode + edge time count mode	Timer3-B

    TIMER2_CTL_R |= 0x0C0C;    //both edges Timer2 (A-B)
    TIMER3_CTL_R |= 0x0C0C;		//both edges Timer3 (A-B)

    // TIMER2_IMR_R |= (1 << 10) | (1 << 2); //enable Interrupts //CBEIM //CAEIM for Timer2
    // TIMER3_IMR_R |= (1 << 10) | (1 << 2); //enable Interrupts //CBEIM //CAEIM for Timer3
    IntEnable(INT_TIMER2A);
    IntEnable(INT_TIMER2B);
    IntEnable(INT_TIMER3A);
    IntEnable(INT_TIMER3B);

    TimerIntEnable(TIMER2_BASE, TIMER_CAPA_EVENT | TIMER_CAPB_EVENT);
    //TimerIntEnable(TIMER2_BASE, TIMER_CAPB_EVENT);
    TimerIntEnable(TIMER3_BASE, TIMER_CAPA_EVENT | TIMER_CAPB_EVENT);
    //TimerIntEnable(TIMER3_BASE, TIMER_CAPB_EVENT);
    IntMasterEnable();
}

void distance_in_cm(uint32_t* dis)
{
#ifdef Ultrasonic_Polling_mode
    static unsigned long high, low;
    // ultrasonic 1  Trig=> A7  Echo => B0
    delay_mSec(10);
    GPIO_PORTA_DATA_R |= 0x80;
    delay_microSec(10);
    GPIO_PORTA_DATA_R &= ~0x80;
//echo
    TIMER2_CTL_R |= 0x0001;
    TIMER2_ICR_R |= 0x04;
    while ((TIMER2_RIS_R & 0x04) == 0)
    ;
    high = (TIMER2_TAR_R);
    TIMER2_ICR_R |= 0x04;
    while ((TIMER2_RIS_R & 0x04) == 0)
    ;

    low = TIMER2_TAR_R;
    TIMER2_ICR_R |= 0x04;
    TIMER2_CTL_R &= ~0x0001;
    dis[0] = (low - high) / 1000;
    delay_mSec(10);
    // ultrasonic 2  Trig=> A6  Echo => B1
    GPIO_PORTA_DATA_R |= 0x40;
    delay_microSec(10);
    GPIO_PORTA_DATA_R &= ~0x40;

//echo	

    TIMER2_CTL_R |= 0x0100;
    TIMER2_ICR_R |= 0x400;
    while ((TIMER2_RIS_R & 0x400) == 0)
    ;
    high = (TIMER2_TBR_R);
    TIMER2_ICR_R |= 0x400;
    while ((TIMER2_RIS_R & 0x400) == 0)
    ;

    low = TIMER2_TBR_R;
    TIMER2_ICR_R |= 0x400;
    TIMER2_CTL_R &= ~0x0100;
    dis[1] = (low - high) / 1000;
    delay_mSec(10);
    // ultrasonic 3  Trig=> A5  Echo => B2
    GPIO_PORTA_DATA_R |= 0x20;
    delay_microSec(10);
    GPIO_PORTA_DATA_R &= ~0x20;

//echo

    TIMER3_CTL_R |= 0x0001;
    TIMER3_ICR_R |= 0x04;
    while ((TIMER3_RIS_R & 0x04) == 0)
    ;
    high = (TIMER3_TAR_R);
    TIMER3_ICR_R |= 0x04;
    while ((TIMER3_RIS_R & 0x04) == 0)
    ;

    low = TIMER3_TAR_R;
    TIMER3_ICR_R |= 0x04;
    TIMER3_CTL_R &= ~0x0001;
    dis[2] = (low - high) / 1000;
    delay_mSec(10);
    // ultrasonic 4  Trig=> A4  Echo => B3
    GPIO_PORTA_DATA_R |= 0x10;
    delay_microSec(10);
    GPIO_PORTA_DATA_R &= ~0x10;

//echo
    TIMER3_CTL_R |= 0x0100;
    TIMER3_ICR_R |= 0x400;
    while ((TIMER3_RIS_R & 0x400) == 0)
    ;
    high = (TIMER3_TBR_R);
    TIMER3_ICR_R |= 0x400;
    while ((TIMER3_RIS_R & 0x400) == 0)
    ;
    TIMER3_ICR_R |= 0x400;
    low = TIMER3_TBR_R;
    TIMER3_CTL_R &= ~0x0100;
    dis[3] = (low - high) / 1000;
    delay_mSec(10);
#endif

#ifdef Ultrasonic_Interrupt_mode
    TIMER2_CTL_R |= 0x0101;
    TIMER3_CTL_R |= 0x0101;
    GPIO_PORTA_DATA_R |= 0xF0;
    delay_microSec(10);
    GPIO_PORTA_DATA_R &= ~0xF0;
 //   delay_mSec(20);
/*    GPIO_PORTA_DATA_R |= 0x20;
    delay_microSec(10);
    GPIO_PORTA_DATA_R &= ~0x20;
  //  delay_mSec(20);
    GPIO_PORTA_DATA_R |= 0x40;
    delay_microSec(10);
    GPIO_PORTA_DATA_R &= ~0x40;
 //   delay_mSec(20);
    GPIO_PORTA_DATA_R |= 0x80;
    delay_microSec(10);
    GPIO_PORTA_DATA_R &= ~0x80;*/
    delay_mSec(30);
//    TIMER2_CTL_R |= 0x0101;
//    TIMER3_CTL_R |= 0x0101;

  //  while (flag_1 & flag_2 & flag_3 & flag_4)
    //    ; //semaphores in RTOS
    dis[0] = Dis1;
    dis[1] = Dis2;
    dis[2] = Dis3;
    dis[3] = Dis4;
#endif
}

static void delay_microSec(int time)
{

    TIMER0_CTL_R = 0;    // disable timer while init
    TIMER0_CFG_R |= 0x4;     // 16 bit mode
    TIMER0_TAMR_R |= 0x02; //  periodic mode
    TIMER0_TAMR_R &= ~0x10; // count down
    TIMER0_TAR_R = 0x00; //reset count
    TIMER0_ICR_R |= 0x01;   //clear flag (acknowledge) during init
    TIMER0_TAILR_R = 16 - 1;      // 16000===> 1ms

    TIMER0_CTL_R |= 0x01;      // enable timer0

    int i;
    for (i = 0; i < time; i++)
    {
        while ((TIMER0_RIS_R & 0x01) == 0)
            ;
        TIMER0_ICR_R |= 0x01;
    }
    TIMER0_CTL_R = 0;    // disable timer
}
//#ifdef Ultrasonic_Polling_mode
void delay_mSec(int time)
{
    TIMER0_CTL_R = 0;    // disable timer while init
    TIMER0_CFG_R |= 0x4;// 16 bit mode
    TIMER0_TAMR_R |= 0x02;//  periodic mode
    TIMER0_TAMR_R &= ~0x10;// count down
    TIMER0_TAR_R = 0x00;//reset count
    TIMER0_ICR_R |= 0x01;//clear flag (acknowledge) during init
    TIMER0_TAILR_R = 16000 - 1;// 16000===> 1ms

    TIMER0_CTL_R |= 0x01;// enable timer0

    int i;
    for (i = 0; i < time; i++)
    {
        while ((TIMER0_RIS_R & 0x01) == 0)
        ;
        TIMER0_ICR_R |= 0x01;
    }
    TIMER0_CTL_R = 0;    // disable timer
}
//#endif

#ifdef Ultrasonic_Interrupt_mode
void Timer2A_Handler(void)
{
    TIMER2_ICR_R |= 0x04;
    static char count = 0;
    static uint32_t high = 0, low = 0;
    count++;
    if (count == 1)
    {
        high = (TIMER2_TAR_R);
    }
    else if (count == 2)
    {
        count = 0;
        low = (TIMER2_TAR_R);
        Dis1 = (low - high) / 1000;
        flag_1 |= (1 << 0);
        TIMER2_CTL_R &=~ 0x01;
    }

}

void Timer2B_Handler(void)
{
    TIMER2_ICR_R |= 0x400;
    static char count = 0;
    static uint32_t high = 0, low = 0;
    count++;
    if (count == 1)
    {
        high = (TIMER2_TBR_R);
    }
    else if (count == 2)
    {
        count = 0;
        low = (TIMER2_TBR_R);
        Dis2 = (low - high) / 1000;
        flag_1 |= (1 << 1);
        TIMER2_CTL_R &=~ 0x100;
    }
    // flag_2+=1;

}

void Timer3A_Handler(void)
{
    TIMER3_ICR_R |= 0x04;
    static char count = 0;
    static uint32_t high = 0, low = 0;
    count++;
    if (count == 1)
    {
        high = (TIMER3_TAR_R);
    }
    else if (count == 2)
    {
        count = 0;
        low = (TIMER3_TAR_R);
        Dis3 = (low - high) / 1000;
        flag_1 |= (1 << 2);
        TIMER3_CTL_R &=~ 0x01;

    }
//    flag_3+=1;


}
void Timer3B_Handler(void)
{
    TIMER3_ICR_R |= 0x400;
    static char count = 0;
    static uint32_t high = 0, low = 0;
    count++;
    if (count == 1)
    {
        high = (TIMER3_TBR_R);
    }
    else if (count == 2)
    {
        count = 0;
        low = (TIMER3_TBR_R);
        Dis4 = (low - high) / 1000;
        flag_1 |= (1 << 3);
        TIMER3_CTL_R &=~ 0x100;
    }
    // flag_4+=1;

}
#endif
