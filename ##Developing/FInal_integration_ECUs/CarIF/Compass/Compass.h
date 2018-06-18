

#ifndef COMPASS_H_
#define COMPASS_H_


#include "../../DriverIncludes.h"


// A6 SCL
// A7 SDA

#define PI 3.14159265358979323846

void Compass_Init(void);

void Compass_Get_Angles(double * Angle);
#endif
