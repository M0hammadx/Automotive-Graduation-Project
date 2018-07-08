#ifndef STD_TYPES_H_
#define STD_TYPES_H_

#include "types.h"
#include "compile.h"

#ifndef NULL
#define NULL 0
#endif

#define STD_HIGH          0x01        /* Physical state 5V or 3.3V */ 
#define STD_LOW           0x00        /* Physical state 0V */
#define STD_ACTIVE        0x01        /* Logical state active */
#define STD_IDLE          0x00        /* Logical state idle */
//#define E_OK              0x00
//#define E_NOT_OK          0x01
#define STD_ON            0x01
#define STD_OFF           0x00



typedef enum Std_ReturnType_t{
    E_OK=0,
    E_NOT_OK
}Std_ReturnType;

typedef struct 
{ 
        uint16 vendorID; 
        uint16 moduleID; 
        uint8 sw_major_version; 
        uint8 sw_minor_version; 
        uint8 sw_patch_version; 
} Std_VersionInfoType; 
 

#endif
