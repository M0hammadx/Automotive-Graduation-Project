

#ifndef COMPASS_H_
#define COMPASS_H_


#include "../../DriverIncludes.h"
//#include <stdarg.h>
//#include <stdint.h> // ift
//#include <stdbool.h>
//#include "inc/hw_types.h"
//#include "inc/hw_memmap.h"
//#include "driverlib/sysctl.h"
//#include "driverlib/gpio.h"
//#include "inc/hw_i2c.h"
//#include "driverlib/i2c.h"
//#include "driverlib/rom.h"
//#include "driverlib/rom_map.h"
//#include "driverlib/pin_map.h"
//#include "inc/tm4c123gh6pm.h"
//#include <math.h>

#define PI 3.14159265358979323846

void Compass_Init(void);

void Compass_Get_Angles(double * Angle);
#endif
