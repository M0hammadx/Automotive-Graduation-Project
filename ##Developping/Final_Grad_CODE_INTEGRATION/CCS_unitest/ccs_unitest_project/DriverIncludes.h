/*
 * DriverIncludes.h
 *
 *  Created on: Feb 28, 2018
 *      Author: Mohab
 */

#ifndef DRIVERINCLUDES_H_
#define DRIVERINCLUDES_H_

#define TARGET_IS_BLIZZARD_RB1
#define PART_TM4C123GH6PM

#include <stdint.h>                         // Library of Standard Integer Types
#include <stdbool.h>                        // Library of Standard Boolean Types
#include <stdlib.h>                         // Standard Library
#include <string.h>                         // Library for String functions
#include <inttypes.h>                       // Library for conversions to Integer types
#include "inc/tm4c123gh6pm.h"               // Definitions for interrupt and register assignments on Tiva C
#include "inc/hw_memmap.h"                  // Macros defining the memory map of the Tiva C Series device
#include "inc/hw_types.h"                   // Defines common types and macros
#include "driverlib/sysctl.h"               // Defines and macros for System Control API of DriverLib
#include "driverlib/interrupt.h"            // Defines and macros for NVIC Controller API of DriverLib
#include "driverlib/gpio.h"                 // Defines and macros for GPIO API of DriverLib
#include "driverlib/qei.h"                  // Prototypes for the Quadrature Encoder Driver
#include "driverlib/pwm.h"                  // API function prototypes for PWM ports
#include "driverlib/uart.h"                 // Defines and Macros for the UART
#include "driverlib/fpu.h"                  // Prototypes for floating point manipulation routine
#include "driverlib/pin_map.h"              // Mapping of peripherals to pins for all parts
#include "driverlib/rom.h"                  // Defines and macros for ROM API of driverLib



#endif /* DRIVERINCLUDES_H_ */
