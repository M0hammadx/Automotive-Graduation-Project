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

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned long uint32_t;

typedef char int8_t;
typedef short int16_t;
typedef long int32_t;

typedef float fp32_t;
typedef double fp64_t;
#endif
