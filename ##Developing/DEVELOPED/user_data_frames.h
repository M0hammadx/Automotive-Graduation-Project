/*
 * DriverIncludes.h
 *
 *  Created on: Feb 28, 2018
 *      Author: Mohab
 */

#ifndef USER_DATA_FRAMES_H_
#define USER_DATA_FRAMES_H_



//speed control frame         S(1/0)0<=>625#*

//direction control frame         D85<=75=>65#*
typedef struct IncomeFrame{
	uint8_t Frame_ID;
	uint8_t Data[7];
	
}g_IncomeFrame_t;



#endif /* USER_DATA_FRAMES_H_ */
