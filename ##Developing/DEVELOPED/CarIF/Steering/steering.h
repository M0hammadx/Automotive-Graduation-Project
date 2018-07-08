#ifndef STEERING_H_
#define STEERING_H_

#include "../DriverIncludes.h"

#define VEL_INT_FREQ    10000               // Macro to store the Interrupt frequency of QEI1
#define QEI0_PPR        (3*4)              // Macro to store the PPR of the QEI1
#define	REVERSE          (-1)
#define	FORWARD           (1)
#define MAX_POS          (10500)
#define MAX_ANGLE        (48)

void steering_init(unsigned long initial_position);
unsigned long steering_AngleGet(void);
uint8_t steering_AngleSet(unsigned long posision);

//void steering_speed(uint16_t duty);

//long steering_DirectionGet(void);
//unsigned long steering_VelocityGet(void);

//void Motor_Backward(void);
//void Motor_Forward(void);
#endif /* STEERING_ENCODER_H_ */
