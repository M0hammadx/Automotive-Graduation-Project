#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include <stdint.h>

 void set_Desired_RPM(uint16_t desired_rpm);
 uint16_t get_Desired_RPM(void);
 void set_Actual_Speed(uint16_t* act_speed);
 uint16_t get_Actual_Speed(void);




#endif
