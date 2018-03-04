/*
 * Motor_DIO.c
 *
 *  Created on: Feb 28, 2018
 *      Author: Mohab
 */
/* This File Init and control Dir pins on Motor driver circuit for 2 channels
 * channel 1 & 2
 * drive 0 or 1 will change the direction of the motor
 * Wiring
 * Channel0 Dir pin ===> PA3 ==>Motor1
 * Channel1 Dir pin ===> PA4 ==>Motor2
 * #Note: This file must use Driverlib and inc files to perform its operation
 *        Using ROM driver also
 */



//************************* Includes *******************************//

#include "Motor_DIO.h"
static char InitFlag=0;
void Motor_DIO_Init(void){
   ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA); //enable clocks on port c
   while(!ROM_SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA)){}; //wait until clock stable
   ROM_GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_3 | GPIO_PIN_4); //set digital output
	 ROM_GPIOPadConfigSet(GPIO_PORTA_BASE, GPIO_PIN_3 | GPIO_PIN_4 ,GPIO_STRENGTH_8MA,GPIO_PIN_TYPE_STD);
   ROM_GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_3 | GPIO_PIN_4, 0x00);

//disable alternative functions
//high current output   GPIOPadConfigSet();
   InitFlag=1;
}
void Motor_DIO_Set(void){
    if(InitFlag==0){
       //generate error flag
    }
    else{
			ROM_GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_3 | GPIO_PIN_4, GPIO_PIN_3 | GPIO_PIN_4);
    }
}

void Motor_DIO_Clear(void){

    if(InitFlag==0){
           //generate error flag
        }
    else{
      ROM_GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_3 | GPIO_PIN_4, 0x00);
    }
}

