

/**
 * main.c
 */
#include "DriverIncludes.h"
#include "motor/MotorIF.h"
#include "encoder/Encoder.h"
#include "servo/Servo.h"
#include "UART.h"
#include "user_data_frames.h"
#define PWM_FREQUENCY   400 

//#define SYSTEM_CLOCK_16_MHZ
#define SYSTEM_CLOCK_80_MHZ


void PWM1_0_init(void);
void PWM1_0_enable(void);



void delay_mSec(int time);


g_IncomeFrame_t Uart_Frame;
uint8_t* UartData_Frame_Ptr;
uint8_t ServoAngle=90;
uint16_t Motors_Speed=0;

typedef struct Motor_Speed_Data{
	g_Motor_Direction Motors_Direction;
	uint8_t Data[6];
	
}s_Motor_Speed_Data_t;


int main(){
   
	 ROM_SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN); //80 MHZ
	 Servo_Init();
	 UART_Init();
	 Motor_Init();
	 
/*	 ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
   while(!ROM_SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF));
   ROM_GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_3);
	*/
   ROM_IntMasterEnable();
	while(1){
	/*	UART_InString((char*)&Uart_Frame,sizeof(g_IncomeFrame_t));
		if(Uart_Frame.Frame_ID=='d' || Uart_Frame.Frame_ID=='D' ){ //D
				ServoAngle=0;
		   	UartData_Frame_Ptr= Uart_Frame.Data;
				while(*UartData_Frame_Ptr != '#'){
					ServoAngle = ServoAngle*10 + (*UartData_Frame_Ptr-'0');
					++UartData_Frame_Ptr;
				}
		Servo_Go(ServoAngle);
		}
		else if(Uart_Frame.Frame_ID=='s' || Uart_Frame.Frame_ID=='S' ){ //S625#*
    s_Motor_Speed_Data_t* UartFrame_MotorSpeed;
		UartFrame_MotorSpeed = (s_Motor_Speed_Data_t*)Uart_Frame.Data;
		Motor_Set_Direction((g_Motor_Direction)((char)UartFrame_MotorSpeed->Motors_Direction -'0'));
		Motors_Speed =0;	
		UartData_Frame_Ptr= UartFrame_MotorSpeed->Data;
		while(*UartData_Frame_Ptr != '#'){
				Motors_Speed = Motors_Speed*10 + (*UartData_Frame_Ptr-'0');
				++UartData_Frame_Ptr;
		   }
	  Motor_Change_Speed(Motors_Speed,Motors_Speed);
	  }
*/
		
		 Motor_Change_Speed(120,120);
		 delay_mSec(1000);
		 Motor_Change_Speed(0,0);
		 delay_mSec(1000);
		 Motor_Change_Speed(500,500);
		 delay_mSec(1000);
		 Motor_Change_Speed(625,625);
		 delay_mSec(1000);
		 
		 
		
	}
	
}



#ifdef SYSTEM_CLOCK_16_MHZ
#define TIMER_DELAY_MS_LOAD 16000  // 16000===> 1ms
#endif
#ifdef SYSTEM_CLOCK_80_MHZ
#define TIMER_DELAY_MS_LOAD 80000  // 80000===> 1ms
#endif 


void delay_mSec(int time)
{
	  SYSCTL_RCGCTIMER_R |= 0x01;        // T0(delay)& T2 & T3
    while ((SYSCTL_PRTIMER_R & 0x01 )!= 0x01);
   
    TIMER0_CTL_R = 0;    // disable timer while init
    TIMER0_CFG_R &=~ 0x7;// 16 bit mode
    TIMER0_TAMR_R |= 0x02;//  periodic mode
    TIMER0_TAMR_R &= ~0x10;// count down
    TIMER0_TAR_R = 0x00;//reset count
    TIMER0_ICR_R |= 0x01;//clear flag (acknowledge) during init
    TIMER0_TAILR_R = TIMER_DELAY_MS_LOAD - 1;

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

