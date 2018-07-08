#ifndef __ULTRASONIC_H__
#define __ULTRASONIC_H__

#include "../../DriverIncludes.h"
#include "../../ECU_CONFIGURATION.h"
//#define ULTRASONIC_4TIMER

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
#define Right_Front  2
#define Right_Back  3
#define Back_Right  4
#define Back_Left  5
#define Left_Back  6
#define Left_Front  7

// Prototypes for the APIs.

void Ultrasonic_Init(void);
void Ultrasonic_Trig(uint8_t ultrasonic);
uint32_t Ultrasonic_Get_Distant(uint8_t distant);
void Ultrasonic_Get_Distant_Batch(uint8_t* distantances);
void delay_microSec(int time);
void delay_mSec(int time);

//8 Timers
//front_Left    Echo->PB0    Trig->PE0   
//front_Right   Echo->pB2    Trig->PE1
//Right_Front    Ech0->PB3    Trig->PE2
//Right_Back     Echo->pD1    Trig->PE3
//Back_Right    Echo->PD2    Trig->PA4 
//Back_Left     Echo->pD3    Trig->PA5
//Left_Back     Echo->PF2    Trigh->PB6  
//Left_Front    Echo->pF3    Trig->PB7

//4 Timers

//front  Echo->PB0   Left Trig->PE0     Right Trig->PE1
//Righ   Ech0->PB2   Front Trig->PE2    Back  Trig->PE3
//Back   Echo->PB3   Right Trig->PA4    Left  Trig->PA5
//Left   Echo->PD1   Back Trig->PB6    Front  Trig->PB7

#endif

