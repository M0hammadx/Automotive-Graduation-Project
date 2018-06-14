/*
 * Motor_PWM.c
 *
 *  Created on: Feb 28, 2018
 *      Author: Mohab
 */
 
 /*
 
 
 
 Wiring :   Motor1_PWM ==> PB6  , Motor2_PWM ==> PB7
 */

#include "Motor_PWM.h"
#define PWM_FREQUENCY_TEST  400
volatile uint32_t ui32Load;
volatile uint32_t ui32PWMClock;
volatile uint16_t ui16Adjust;

static uint8_t Init_Flag=0;

void Motor_PWM_Init(void){
	ROM_SysCtlPWMClockSet(SYSCTL_PWMDIV_64);
	
	ui16Adjust=78;
	ui32PWMClock = ROM_SysCtlClockGet() / 64;
	ui32Load = (ui32PWMClock / PWM_FREQUENCY_TEST) - 1; //load =1000  //easy to map this value Motor frequency 5Khz
	
  ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);
	while(!ROM_SysCtlPeripheralReady(SYSCTL_PERIPH_PWM0)){}; //wait until clock stable
  ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
	while(!ROM_SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB)){}; //wait until clock stable
  
	ROM_GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_6|GPIO_PIN_7);
		
	ROM_GPIOPinConfigure(GPIO_PB6_M0PWM0);
	ROM_GPIOPinConfigure(GPIO_PB7_M0PWM1);
		
	ROM_GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_6 | GPIO_PIN_7);
  ROM_GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_6 | GPIO_PIN_7, 0x00);
		
	ROM_PWMGenConfigure(PWM0_BASE, PWM_GEN_0 , PWM_GEN_MODE_DOWN); // Configure thE PWM0 Genrator0 to work in Count Down Mode
	ROM_PWMGenConfigure(PWM0_BASE, PWM_GEN_1 , PWM_GEN_MODE_DOWN); // Configure thE PWM0 Genrator1 to work in Count Down Mode
		
	ROM_PWMGenPeriodSet(PWM0_BASE, PWM_GEN_0 , ui32Load); // Load the calculated time period to the Generator0 of the PWM0 Module
	ROM_PWMGenPeriodSet(PWM0_BASE, PWM_GEN_1 , ui32Load); // Load the calculated time period to the Generator1 of the PWM0 Module
		
	ROM_PWMPulseWidthSet(PWM0_BASE, PWM_GEN_0, ui16Adjust * ui32Load / 100);// Set the PWM duty cycle to a specified value
	ROM_PWMPulseWidthSet(PWM0_BASE, PWM_GEN_1, ui16Adjust * ui32Load / 100);
		
	ROM_PWMOutputState(PWM0_BASE, PWM_OUT_6_BIT|PWM_OUT_7_BIT, true); // Enable the PWM0 pin of the PWM Module 1 as output
	
	
}

void Motor_PWM_Start(void){
	if(Init_Flag==1){
		//return a type of error
	}
	else{
		ROM_PWMGenEnable(PWM0_BASE, PWM_GEN_0);
		ROM_PWMGenEnable(PWM0_BASE, PWM_GEN_1);
	}
}

void Motor_PWM_Stop(void){
	if(Init_Flag==1){
		//return a type of error
	}
	else{
		ROM_PWMGenDisable(PWM0_BASE, PWM_GEN_0);
		ROM_PWMGenDisable(PWM0_BASE, PWM_GEN_1);
	}
}

void Motor_PWM_Speed_Control(uint16_t ui16AdjustMotor1 ,uint16_t ui16AdjustMotor2){
	
	if(Init_Flag==1){
		//return a type of error
	}
	else{
		ROM_PWMPulseWidthSet(PWM0_BASE, PWM_GEN_0, ui16AdjustMotor1 * ui32Load / 100);// Set the PWM duty cycle to a specified value
	  ROM_PWMPulseWidthSet(PWM0_BASE, PWM_GEN_1, ui16AdjustMotor2 * ui32Load / 100);
		//Motor_PWM_Start();
		ROM_PWMGenEnable(PWM0_BASE, PWM_GEN_0);
		ROM_PWMGenEnable(PWM0_BASE, PWM_GEN_1);
	}
}



void Motor_PWM_break(void){
		ROM_PWMPulseWidthSet(PWM0_BASE, PWM_GEN_0, 0);// Set the PWM duty cycle to a specified value
	  ROM_PWMPulseWidthSet(PWM0_BASE, PWM_GEN_1, 0);
}
