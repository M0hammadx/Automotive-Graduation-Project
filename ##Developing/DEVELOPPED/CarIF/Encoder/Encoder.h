#ifndef _SPEED_H_
#define _SPEED_H_

#include <stdint.h>
#include "../../DriverIncludes.h"
#include "../../CAR_PERIPHERALS_PARAMETERS.h"
/**********************defines*******************/
#define   maxDistance           43.96         //cm
#define   Max_Position          30
#define   edges                 4
#define   Timer_Period          80000000
#define   system_freq           80      // in MHz
#define   Encoder_timer_Load    80    // load /10^6

//#define CAR_SPEED_IN_METER_PER_HR

/*******************Functions_ProtoTypes**************/

/*
 *Init system clock
 *Init QEI module 0&1
 */
void Encoder_Init(void);

/*
 *calculates motors speed in RPM
 */
void Encoder_Get_Distance_Elapsed(uint16_t *Ptrdistance);
void Encoder_Get_Motors_RPM(uint8_t* RPM);
void Encoder_Init(void);

//void SysTick_Init(void);
#endif
