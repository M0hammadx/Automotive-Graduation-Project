


#include "Ultrasonic_requests_rte.h"

static uint8_t rte_ultrasonic_request_byte=0;

void Rte_Ultrasonic_requests_iwrite(uint8_t u){

    rte_ultrasonic_request_byte|=u;
    //post
}


uint8_t Rte_Ultrasonic_requests_iread(){
//pend
   return rte_ultrasonic_request_byte;

}

