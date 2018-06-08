/**
 * \file	types.h
 *
 * \version v0.0
 *
 * \brief	this file defines the basic fixed-length data types ,
 *				data types that defined in stdint.h are used .
 *				also it defines TRUE, False and NULL pointer .
 *
 * \date 	nov 14, 2017
 *
 * \author  ADAS
 *
 */


#ifndef TYPES_H_
#define TYPES_H_

//#ifndef FALSE
//#define FALSE		(boolean)false
//#endif
//#ifndef TRUE
//#define TRUE		(boolean)true
//#endif

#ifndef TRUE
#define TRUE	(1U)
#endif

#ifndef FALSE
#define FALSE	(0U)
#endif

#ifndef NULL
//#define NULL	((void*)0U)
#endif

/* -------------------------------------------------------------------------- */
/*                                Typedefs                                    */
/* -------------------------------------------------------------------------- */


typedef _Bool      			boolean;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned long uint32_t;

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned long uint32;

typedef char int8_t;
typedef short int16_t;
typedef long int32_t;

typedef char int8;
typedef short int16;
typedef long int32;

typedef float fp32_t;
typedef double fp64_t;
#endif
