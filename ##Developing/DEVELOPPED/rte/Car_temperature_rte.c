/*
 * Car_temperature_rte.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Sahar Elnagar
 */
#include "Car_temperature_rte.h"
extern Semaphore_Handle  rte_Binary_Semaphore_Car_temperature_Data_handle ;
static uint8_t rte_Car_temperature=0 ;
#ifdef ECU1_SENSORYNODE
void Rte_Car_temperature_iwrite(uint8_t data){ //SWC
    rte_Car_temperature=data;
    Semaphore_post(rte_Binary_Semaphore_Car_temperature_Data_handle); //post
}

uint8_t Rte_Car_temperature_iread(uint8_t* data){ //Com main
    uint8_t SemaValue=0;
    SemaValue= Semaphore_pend(rte_Binary_Semaphore_Car_temperature_Data_handle,
               BIOS_NO_WAIT);
    if(SemaValue ==0)
      {
      }
      else
      {
          *data = rte_Car_temperature;
      }
      return SemaValue;

}


#endif



#ifdef ECU2_ALGORITHMICNODE


void Rte_Car_temperature_iwrite(uint8_t data){ //SWC
    rte_Car_temperature=data;
    Semaphore_post(rte_Binary_Semaphore_Car_temperature_Data_handle); //post
}

uint8_t Rte_Car_temperature_iread(uint8_t* data){ //Com main
    uint8_t SemaValue=0;
    SemaValue= Semaphore_pend(rte_Binary_Semaphore_Car_temperature_Data_handle,
               BIOS_NO_WAIT);
    if(SemaValue ==0)
      {
      }
      else
      {
          *data = rte_Car_temperature;
      }
      return SemaValue;

}




#endif





#ifdef ECU3_ACTUATORNODE
void Rte_Car_temperature_iwrite(uint8_t data){ //SWC
    rte_Car_temperature=data;
    Semaphore_post(rte_Binary_Semaphore_Car_temperature_Data_handle); //post
}

uint8_t Rte_Car_temperature_iread(uint8_t* data){ //Com main
    uint8_t SemaValue=0;
    SemaValue= Semaphore_pend(rte_Binary_Semaphore_Car_temperature_Data_handle,
               BIOS_NO_WAIT); //pend
    if(SemaValue ==0)
      {
      }
      else
      {
          *data = rte_Car_temperature;
      }
      return SemaValue;

}


#endif

