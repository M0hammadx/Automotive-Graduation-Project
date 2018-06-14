/*
 * Servo.c
 *
 *  Created on: Mar 3, 2018
 *      Author: Mohab
 */

/*



	Wiring 	Servo_PWM ==> D0
*/
#include "Servo.h"


#define SERVO_PWM_FREQUENCY 55

static volatile uint32_t ui32Load;
static volatile uint32_t ui32PWMClock;
static volatile uint8_t ui8Adjust=75;
void Servo_Init(void){

SysCtlPWMClockSet(SYSCTL_PWMDIV_64);
ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
ROM_GPIOPinTypePWM(GPIO_PORTD_BASE, GPIO_PIN_0);
ROM_GPIOPinConfigure(GPIO_PD0_M1PWM0);
ui32PWMClock = ROM_SysCtlClockGet() / 64;
ui32Load = (ui32PWMClock / SERVO_PWM_FREQUENCY) - 1;
ROM_PWMGenConfigure(PWM1_BASE, PWM_GEN_0, PWM_GEN_MODE_DOWN|PWM_GEN_MODE_DBG_RUN);
ROM_PWMGenPeriodSet(PWM1_BASE, PWM_GEN_0, ui32Load);
ROM_PWMPulseWidthSet(PWM1_BASE, PWM_OUT_0, ui8Adjust * ui32Load / 1000);
ROM_PWMOutputState(PWM1_BASE, PWM_OUT_0_BIT, true);
ROM_PWMGenEnable(PWM1_BASE, PWM_GEN_0);
}

/*Parameter passed from 0 <=> 180 mapping this value to 45 <=> 84
//Servo_HeadDirectionAngle =75

u8AngleAdjust : unsigned number from 0 <=> 180
*/
void Servo_Go(uint8_t u8AngleAdjust){
	
	//uint8_t u8AngleAdjustActual = (uint8_t)(u8AngleAdjust/3 ) + 45;
	if(u8AngleAdjust>84)u8AngleAdjust=84;
	if(u8AngleAdjust<45)u8AngleAdjust=45;
	ROM_PWMPulseWidthSet(PWM1_BASE, PWM_OUT_0, u8AngleAdjust * ui32Load / 1000);
	
}

