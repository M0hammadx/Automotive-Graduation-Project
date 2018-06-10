#ifndef __ULTRASONIC_H__
#define __ULTRASONIC_H__

#define PART_TM4C123GH6PM
#define TARGET_IS_TM4C123_RA1

#include "../inc/tm4c123gh6pm.h"
#include <stdint.h>
#include <stdbool.h>
#include "../driverlib/timer.h"
#include "../driverlib/gpio.h"
#include "../inc/hw_memmap.h"
#include "../driverlib/pin_map.h"
#include "../driverlib/rom_map.h"
#include "../driverlib/interrupt.h"
#include "../driverlib/rom.h"
#include "../driverlib/sysctl.h"

#define ULTRASONIC_4TIMER

 void delay_mSec(int time);




#define Front_Left_Ultrasonic  0x01
#define Front_Right_Ultrasonic  0x02
#define Right_Front_Ultrasonic  0x04
#define Right_Back_Ultrasonic  0x08
#define Back_Right_Ultrasonic  0x10
#define Back_Left_Ultrasonic  0x20
#define Left_Back_Ultrasonic  0x40
#define Left_Front_Ultrasonic  0x80

#define Front_Left  0
#define Front_Right  1
#define Righ_Front  2
#define Right_Back  3
#define Back_Right  4
#define Back_Left  5
#define Left_Back  6
#define Left_Front  7

// Prototypes for the APIs.

void Ultrasonic_Init(void);
void Ultrasonic_Read(uint8_t ultrasonic);
uint32_t Ultrasonic_Get_Distance( uint8_t distance);
void delay_microSec(int time);


#endif

