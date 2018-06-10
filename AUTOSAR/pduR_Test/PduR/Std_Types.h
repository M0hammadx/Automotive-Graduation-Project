/** incomplete Std types header file used as a test to PDUR module */

/**
*	General types for AUTOSAR standard
*/

#ifndef STD_TYPES_H_
#define STD_TYPES_H_

#include "types.h"

#ifndef NULL
#define NULL 0
#endif

#define STD_HIGH		0x01
#define STD_LOW			0x00

#define STD_ACTIVE	0x01
#define STD_IDLE		0x00

#define STD_ON			0x01
#define STD_OFF			0x00

typedef uint8_t Std_ReturnType;

#define E_OK 				(Std_ReturnType)0
#define E_NOT_OK 		(Std_ReturnType)1



#endif //STD_TYPES_H_
