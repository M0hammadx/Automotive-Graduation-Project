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
 * Channel0-1 Dir pin ===> PA3 ==>Motor1
 * Channel0-2 Dir pin ===> PA4 ==>Motor1
 *
 * Channel1-1 Dir pin ===> PA6 ==>Motor2
 * Channel1-2 Dir pin ===> PA7 ==>Motor2
 * #Note: This file must use Driverlib and inc files to perform its operation
 *        Using ROM driver also
 */

//************************* Includes *******************************//
#include "Motor_DIO.h"
static char InitFlag = 0;
void Motor_DIO_Init(void)
{
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA); //enable clocks on port c
    while (!ROM_SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA))
        ; //wait until clock stable
    ROM_GPIOPinTypeGPIOOutput(
            GPIO_PORTA_BASE, GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_6 | GPIO_PIN_7); //set digital output
    ROM_GPIOPadConfigSet(GPIO_PORTA_BASE,
    GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_6 | GPIO_PIN_7,
                         GPIO_STRENGTH_8MA,
                         GPIO_PIN_TYPE_STD);
    ROM_GPIOPinWrite(GPIO_PORTA_BASE,
    GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_6 | GPIO_PIN_7,
                     0x00);

//disable alternative functions
//high current output   GPIOPadConfigSet();
    InitFlag = 1;
}
void Motor_DIO_Forward(void)
{
    if (InitFlag == 0)
    {
        //generate error flag
    }
    else
    {
        ROM_GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3, GPIO_PIN_3);
        ROM_GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_4, 0x00);
        ROM_GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_6, GPIO_PIN_6);
        ROM_GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_7, 0x00);

    }
}

void Motor_DIO_Backward(void)
{

    if (InitFlag == 0)
    {
        //generate error flag
    }
    else
    {

        ROM_GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3, 0x00);
        ROM_GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_4, GPIO_PIN_4);
        ROM_GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_6, 0x00);
        ROM_GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_7, GPIO_PIN_7);
    }
}

