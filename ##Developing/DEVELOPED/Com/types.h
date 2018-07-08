


#ifndef TYPES_H_
#define TYPES_H_

/** \brief Defines TRUE status value */
#ifndef TRUE
#define TRUE     (1U)
#endif

/** \brief Defines FALSE status value */
#ifndef FALSE
#define FALSE    (0U)
#endif

#ifndef false
#define false    (0U)
#endif

/** \brief Defines NULL pointer value */
#ifndef NULL
#define NULL ((void*) 0U)
#endif


typedef _Bool               boolean;

//typedef unsigned char uint8_t;
//typedef unsigned short uint16_t;
//typedef unsigned long uint32_t;

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned long uint32;

//typedef char int8_t;
//typedef short int16_t;
//typedef long int32_t;

typedef char int8;
typedef short int16;
typedef long int32;

typedef float fp32_t;
typedef double fp64_t;

typedef float fp32;
typedef double fp64;


#endif 

