#ifndef _SPEED_H_
#define _SPEED_H_

#include <stdint.h>
#include "../../DriverIncludes.h"
/**********************defines*******************/
#define   maxDistance           43.96         //cm
#define   Max_Position          12
#define   Timer_Period          800000
#define   QEI0_INT_NUM          13
#define   QEI1_INT_NUM          38
#define   priority0             0
#define   priority1             0xE0
#define   system_freq           80      // in MHz
#define   Encoder_timer_Load    0.8     // load /10^6
#define   gear_ratio            75
#define   diameter              0.14 // in meter
#define   pi                    3.14
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
void Encoder_Get_Distance_Elapsed(double *distance);
void Encoder_Get_Motors_RPM(uint16_t* RPM);

//void SysTick_Init(void);
#endif
