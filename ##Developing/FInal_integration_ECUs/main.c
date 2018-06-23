/**
 * main.c
 */
/*
 * Authors : ~ Mohab Adel - Mohamed Hatem - Noha elmenbawy - Nada elshawy - Mahmoud elghzaly
 *            Sahar Elnagar - Hager Eldaadaa - Mohamed  elsherbini (Embedded Software Engineer)
 *
 *          ~ Shrook wafa - Omar ghoneim - Omar Al-Ezaby  (Algorithm Engineer)
 *          ~ Mahmoud elghazaly (Electronics Engineer)
 *          ~ Ahmed Elshafaey (project documentation)
 *          ~ Abdelrahman Hossam - Mostafa fawzy (Mechanical design)
 *          ~ Old team members : Selwan mohamed - Amr Ali (Embedded software)
 * Date : 12-6-2018
 *
 */
/*This is the last integration code. This code can be configured to run on each ECU(1-3)
 * The Car component component and the wiring map is defined in each component header file(ultrasonic.h)  (xxxx.h),
 * you also must check the communication bus (CAN) and  the wiring first
 *
 *
 *
 *
 */

/* Steps to configure the code in order to run correctly on each ECU
 * 1) go to Ecu configuration mode and uncomment the Name of the required ECU (ECU_CONFIGURATION.h)
 * 2) make sure the you include the tiva-ware driver library (driverlib.lib)
 * 3) Add "PART_TM4C123GH6PM" and "TARGET_IS_BLIZZARD_Rxx" to your compiler predefined symbols
 * 4)
 */
//#define debug
#include "ECU.h"

#ifdef debug
#include "UART.h"
#endif

int main(void)
{

    ECU_Init(); //all hardware communication

#ifdef debug
    Output_Init_Debug();
#endif
    ECU2_Begin_SWC1();
    return 0;
}



void Delay100ms(unsigned long time){
  unsigned long i;
  while(time > 0){
    i = 1333333;  // this number means 100ms
    while(i > 0){
      i = i - 1;
    }
    time = time - 1; // decrements every 100 ms
  }
}
