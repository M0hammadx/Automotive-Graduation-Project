

/**
 * main.c
 */
#include "DriverIncludes.h"
#include "motor/MotorIF.h"
#include "encoder/Encoder.h"
#include "servo/Servo.h"

#define PWM_FREQUENCY   400 

void PWM1_0_init(void);
void PWM1_0_enable(void);

static uint32_t ui32Period_PWM1_0;
static volatile uint16_t ui16Adjust_PWM1_0 = 0;

void PWM_Init(void);
void Motor_Duty(unsigned long duty0,unsigned long duty1,unsigned long duty2,unsigned long duty3);
int main(void)
{
    ROM_SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN); //80 MHZ
	 // Motor_Init();
	    PWM1_0_init();
		//Encoders_Init();
		//Servo_Init();
		//PWM_Init();
	  PWM1_0_enable();
	ui16Adjust_PWM1_0=100;
    while(1){
			Motor_Set_Direction(MOTOR_FORWARD);
		//	Motor_Change_Speed(50,50);
			
				ROM_PWMPulseWidthSet(PWM1_BASE, PWM_OUT_0, ui16Adjust_PWM1_0 * ui32Period_PWM1_0 / 100);
			SysCtlDelay(8888888);
			ui16Adjust_PWM1_0-=20;
			ROM_PWMPulseWidthSet(PWM1_BASE, PWM_OUT_0, 50* ui32Period_PWM1_0/ 100);
			SysCtlDelay(8888888);
						ROM_PWMPulseWidthSet(PWM1_BASE, PWM_OUT_0, 20*ui32Period_PWM1_0/ 100);
			SysCtlDelay(8888888);
			
						ROM_PWMPulseWidthSet(PWM1_BASE, PWM_OUT_0, 10*ui32Period_PWM1_0/ 100);
			SysCtlDelay(8888888);
			
		/*	Motor_Duty(7000,7000,7000,7000);
			SysCtlDelay(10000);
			Motor_Duty(5000,5000,5000,5000);
			SysCtlDelay(10000);
			Motor_Duty(1000,1000,1000,1000);
			SysCtlDelay(10000);
			*/
			
		}


}


void Motor_Duty(unsigned long duty0,unsigned long duty1,unsigned long duty2,unsigned long duty3){
	
  PWM0_0_CMPB_R=duty0-2;      // DECIDE DUTY PB7	
	PWM0_0_CMPA_R=duty1-2 ;      // DECIDE DUTY PB6 	
	PWM0_1_CMPB_R=duty2-2;      // DECIDE DUTY PB5	
	PWM0_1_CMPA_R=duty3-2 ;      // DECIDE DUTY PB4 
	PWM0_0_CTL_R=0X00000001 ;  // START PWM 
	PWM0_1_CTL_R=0X00000001 ;  // START PWM 
  PWM0_ENABLE_R=0X0000000F;  // ENABLE PWM 
	
}

void PWM_Init(void){
	                  
                            //**** Init PWM0 & PWM1 on PB6 & PB7 ****//
	int delay;
 SYSCTL_RCGC0_R|=0x00100000;               // Enable PWM Clock
	delay=SYSCTL_RCGC0_R;
	SYSCTL_RCGC2_R|=0X02;                    //Enable the clock to PORT B
	delay=SYSCTL_RCGC2_R;
	GPIO_PORTB_LOCK_R=0X4C4F434B;
	GPIO_PORTB_CR_R|=0XF0;
	GPIO_PORTB_DIR_R|=0XF0;                // Output signal
	GPIO_PORTB_DEN_R|=0XF0;                // Enable Digital
	GPIO_PORTB_AMSEL_R&=~0XF0;             // Disable Analog
	GPIO_PORTB_AFSEL_R|=0XF0;              // Alternative Function
	GPIO_PORTB_PCTL_R&=~0XFFFF0000;
	GPIO_PORTB_PCTL_R|= 0X44440000;
	GPIO_PORTB_DR8R_R |=0XF0;
	SYSCTL_RCC_R &=~0x00100000;           // Disable PWM divider clock and use system clock 
	PWM0_0_CTL_R=0 ;  	                  // COUNT DOWN MODE, disable during config
	PWM0_1_CTL_R=0 ;
	PWM0_0_GENA_R |=0XC8 ;                // LOW ON LOAD , HIGH ON CMPA
	PWM0_0_GENB_R |=0XC08 ;               // LOW ON LOAD , HIGH ON CMPB
	PWM0_1_GENA_R |=0XC8 ;                // LOW ON LOAD , HIGH ON CMPA
	PWM0_1_GENB_R |=0XC08 ;               // LOW ON LOAD , HIGH ON CMPB
	PWM0_0_LOAD_R=8000-1 ;                // PWM FREQUENCY= 2000 HZ
	PWM0_1_LOAD_R=8000-1 ;
	
	//Direction_Init >>PORTD&&PORTE<<
	SYSCTL_RCGC2_R|=0X19;  
	delay=SYSCTL_RCGC2_R;
	GPIO_PORTE_LOCK_R=0X4C4F434B;
	GPIO_PORTE_CR_R|=0X30;
	GPIO_PORTE_DIR_R|=0X30;                // Output signal
	GPIO_PORTE_DEN_R|=0X30;                // Enable Digital
	GPIO_PORTE_AMSEL_R&=~0X30;             // Disable Analog
	GPIO_PORTE_AFSEL_R&=~0X30;              
	GPIO_PORTE_PCTL_R=0;
		//postD pins>>0,1,2,3<<
	GPIO_PORTD_LOCK_R=0X4C4F434B;
	GPIO_PORTD_CR_R|=0X0F;
	GPIO_PORTD_DIR_R|=0X0F;                // Output signal
	GPIO_PORTD_DEN_R|=0X0F;                // Enable Digital
	GPIO_PORTD_AMSEL_R&=~0X0F;             // Disable Analog
	GPIO_PORTD_AFSEL_R&=~0X0F;              
	GPIO_PORTD_PCTL_R=0;
	
			//postA pins>>2,3<<
	GPIO_PORTA_LOCK_R=0X4C4F434B;
	GPIO_PORTA_CR_R|=0X0C;
	GPIO_PORTA_DIR_R|=0X0C;                // Output signal
	GPIO_PORTA_DEN_R|=0X0C;                // Enable Digital
	GPIO_PORTA_AMSEL_R&=~0X0C;             // Disable Analog
	GPIO_PORTA_AFSEL_R&=~0X0C;              
	GPIO_PORTA_PCTL_R=0;
	
	
}




void PWM1_0_init(void){
    ROM_SysCtlPWMClockSet(SYSCTL_PWMDIV_64);

    // Enable the clock for peripherals PortD and PWM1
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);

    // Configure the PD0 for PWM signal (PWM module 1 generator 0)
    ROM_GPIOPinTypePWM(GPIO_PORTD_BASE, GPIO_PIN_0);
    ROM_GPIOPinConfigure(GPIO_PD0_M1PWM0);

    // Configure the PD1 and PD2 pins as Digital Output Pins
    ROM_GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_2 | GPIO_PIN_3);
    // Write the output value to the GPIO PortD to control the PD2 and PD3
    ROM_GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2 | GPIO_PIN_3, 0x00);

    // Calculate the Timer period of the PWM Module.
    uint32_t ui32PWMClock = ROM_SysCtlClockGet() >> 6;
    ui32Period_PWM1_0 = (ui32PWMClock / PWM_FREQUENCY) - 1;
    // Configure thE PWM1 Genrator0 to work in Count Down Mode
    ROM_PWMGenConfigure(PWM1_BASE, PWM_GEN_0, PWM_GEN_MODE_DOWN);
    // Load the calculated time period to the Generator0 of the PWM1 Module
    ROM_PWMGenPeriodSet(PWM1_BASE, PWM_GEN_0, ui32Period_PWM1_0);

    // Set the PWM duty cycle to a specified value
    ROM_PWMPulseWidthSet(PWM1_BASE, PWM_OUT_0, ui16Adjust_PWM1_0 * ui32Period_PWM1_0 / 100);
    // Enable the PWM0 pin of the PWM Module 1 as output
    ROM_PWMOutputState(PWM1_BASE, PWM_OUT_0_BIT, true);

}	


// Function for Enabling PWM1_0
void PWM1_0_enable(void){
    // Enable the PWM1 Generator0
    ROM_PWMGenEnable(PWM1_BASE, PWM_GEN_0);
}
	