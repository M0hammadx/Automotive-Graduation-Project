/*
 * Desired_Car_speed.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Sahar Elnagar
 */
#include "rte/Desired_Car_speed_direction_rte.h"

#ifdef ECU2_ALGORITHMICNODE
extern Semaphore_Handle rte_Binary_Semaphore_Desired_Car_speed_handle;
extern Semaphore_Handle rte_Binary_Semaphore_Desired_Car_Direction_handle;

static uint16_t Desired_Car_speed=0;
static uint8_t Desired_Car_Direction =0;

void Rte_Desired_Car_speed_groupSignal_iwrite(uint16_t data)//swc call
{
    Desired_Car_speed=data;
    Semaphore_post(rte_Binary_Semaphore_Desired_Car_speed_handle);
}

uint8_t Rte_Desired_Car_speed_groupSignal_iread(uint16_t* data) //com main
{
    uint8_t SemaValue= Semaphore_pend(rte_Binary_Semaphore_Desired_Car_speed_handle,BIOS_NO_WAIT);
    if(SemaValue==0)
    {

    }
    else
    {
        *data= Desired_Car_speed;
    }
    return SemaValue;

}
void Rte_Desired_Car_Direction_signalGroup_iwrite(uint8_t data) //swc call
{
    Desired_Car_Direction = data;
    Semaphore_post(rte_Binary_Semaphore_Desired_Car_Direction_handle);
}
uint8_t Rte_Desired_Car_Direction_signalGroup_iread(uint8_t* data) //com main
{
    uint8_t SemaValue= Semaphore_pend(rte_Binary_Semaphore_Desired_Car_Direction_handle,BIOS_NO_WAIT);
    if(SemaValue==0)
    {

    }
    else
    {
        *data= Desired_Car_Direction;
    }
    return SemaValue;

}

#endif

//#ifdef ECU2_ALGORITHMICNODE
//extern Semaphore_Handle rte_Binary_Semaphore_Desired_Car_speed_Requests_handle;
//extern Semaphore_Handle rte_Mutex_Desired_Car_speed_Requests_handle;
//static uint16_t Desired_Car_speed=0;
//void Rte_Desired_Car_speed_iwrite(uint16_t data){
//    Semaphore_pend( rte_Mutex_Desired_Car_speed_Requests_handle,BIOS_WAIT_FOREVER);
//    Desired_Car_speed=data;
//    Semaphore_post( rte_Mutex_Desired_Car_speed_Requests_handle);
//    Semaphore_post(rte_Binary_Semaphore_Desired_Car_speed_Requests_handle);
//}
//
//uint8_t Rte_Desired_Car_speed_iread(uint16_t* data){
//   uint8_t SemaValue= Semaphore_pend(rte_Binary_Semaphore_Desired_Car_speed_Requests_handle,BIOS_NO_WAIT);
//   if(SemaValue==0){
//
//   }
//   else{
//       Semaphore_pend( rte_Mutex_Desired_Car_speed_Requests_handle,BIOS_WAIT_FOREVER);
//         *data= Desired_Car_speed;
//         Semaphore_post( rte_Mutex_Desired_Car_speed_Requests_handle);
//   }
//  return SemaValue;
//
//}
//
//
//#endif

#ifdef ECU3_ACTUATORNODE
extern Semaphore_Handle rte_Binary_Semaphore_Desired_Car_speed_handle;
extern Semaphore_Handle rte_Binary_Semaphore_Desired_Car_Direction_handle;
static uint8_t Desired_Car_Direction = 0;
static uint16_t Desired_Car_speed = 0;

void Rte_Desired_Car_speed_iwrite(uint16_t data) //com rx_indication call
{ //com RX_Indication call

    Desired_Car_speed = data;
    Semaphore_post(rte_Binary_Semaphore_Desired_Car_speed_handle);
}

void Rte_Desired_Car_speed_iread(uint16_t* data) //swc call
{ //swc
    Semaphore_pend(rte_Binary_Semaphore_Desired_Car_speed_handle,
    BIOS_WAIT_FOREVER);
    Hwi_disableInterrupt(55);
    *data = Desired_Car_speed;
    Hwi_enableInterrupt(55);

}

void Rte_Desired_Car_Direction_iwrite(uint8_t data)//com rx indication call
{
    Desired_Car_Direction = data;
    Semaphore_post(rte_Binary_Semaphore_Desired_Car_Direction_handle);
}
void Rte_Desired_Car_Direction_iread(uint8_t* data)//swc call
{
    Semaphore_pend(rte_Binary_Semaphore_Desired_Car_Direction_handle,
                                           BIOS_WAIT_FOREVER);
    Hwi_disableInterrupt(55);
    *data = Desired_Car_Direction;
    Hwi_enableInterrupt(55);

}

#endif

//#ifdef ECU3_ACTUATORNODE
//extern Semaphore_Handle rte_Binary_Semaphore_Desired_Car_speed_Requests_handle;
//extern Semaphore_Handle rte_Mutex_Desired_Car_speed_Requests_handle;
//static uint16_t Desired_Car_speed=0;
//void Rte_Desired_Car_speed_iwrite(uint16_t data){ //com RX_Indication call
//
//       Desired_Car_speed=data;
//       Semaphore_post(rte_Binary_Semaphore_Desired_Car_speed_Requests_handle);
//}
//
//void Rte_Desired_Car_speed_iread(uint16_t* data){ //swc
//    Semaphore_pend( rte_Mutex_Desired_Car_speed_Requests_handle,BIOS_WAIT_FOREVER);
//    Hwi_disableInterrupt(55);
//    *data=Desired_Car_speed;
//    Hwi_enableInterrupt(55);
//
//}
//
//
//#endif
