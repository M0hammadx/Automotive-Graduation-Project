/*
 * Encoder.c
 *
 *  Created on: Mar 3, 2018
 *      Author: Mohab
 */

/*	This file init 2 Encoder module 
*			
*	
*
*
*	wiring:  Qei0 module channels :::::: phA0 ==> PD6			phB0 ==> PF1
* 				 Qei1 module channels :::::: phA1 ==> PC5			phB1 ==> PC6
*/
#include "Encoder.h"


void Encoders_Init(void){
 // Enable the clock for peripherals PortC , PortD , PortF
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	while(!ROM_SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF)){}
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	while(!ROM_SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF)){}
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
	while(!ROM_SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF)){}
		
 // Enable the clock for peripherals QEI0,QEI1
  ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_QEI0);
	while(!ROM_SysCtlPeripheralReady(SYSCTL_PERIPH_QEI0)){}	
  ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_QEI1);
	while(!ROM_SysCtlPeripheralReady(SYSCTL_PERIPH_QEI1)){}	
	
	// Configure the PC5 and PC6 as PhaseA and PhaseB of QEI1	
	ROM_GPIOPinTypeQEI(GPIO_PORTC_BASE, GPIO_PIN_5 | GPIO_PIN_6);	
  ROM_GPIOPinConfigure(GPIO_PC5_PHA1);
  ROM_GPIOPinConfigure(GPIO_PC6_PHB1);
	// Configure the PD6 and PF1 as PhaseA and PhaseB of QEI0		
	ROM_GPIOPinTypeQEI(GPIO_PORTD_BASE, GPIO_PIN_6);
	ROM_GPIOPinTypeQEI(GPIO_PORTF_BASE, GPIO_PIN_1);		
  ROM_GPIOPinConfigure(GPIO_PD6_PHA0);
  ROM_GPIOPinConfigure(GPIO_PF1_PHB0);
	 // Configure the QEI0 & QEI1 to increment for both PhA and PhB for quadrature input with "QEI0_CPR & QEI1_CPR" PPR	
  ROM_QEIConfigure(QEI0_BASE, QEI_CONFIG_CAPTURE_A_B | QEI_CONFIG_QUADRATURE | QEI_CONFIG_NO_SWAP, QEI0_CPR); //QEI0_CPR Max position 
	ROM_QEIConfigure(QEI1_BASE, QEI_CONFIG_CAPTURE_A_B | QEI_CONFIG_QUADRATURE | QEI_CONFIG_NO_SWAP, QEI1_CPR); //QEI1_CPR	Max position
	
  QEIFilterConfigure(QEI0_BASE,QEI_FILTCNT_10);		//Noise filter take pulse each 10 system clock
  QEIFilterConfigure(QEI1_BASE,QEI_FILTCNT_10);		

	
	
		
	QEIFilterEnable(QEI0_BASE);
	QEIFilterEnable(QEI1_BASE);	
}


void Encoders_Enable(void){
	  ROM_QEIEnable(QEI0_BASE);
    ROM_QEIEnable(QEI1_BASE);

}
void Encoders_Disable(void){
		ROM_QEIDisable(QEI0_BASE);
   	ROM_QEIDisable(QEI1_BASE);
}
