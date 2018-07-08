#include "Ultrasonic_requests_rte.h"

#ifdef ECU1_SENSORYNODE
extern Semaphore_Handle rte_Binary_Semaphore_Ultrasonic_Requests_handle;
extern Semaphore_Handle rte_Mutex_Ultrasonic_Requests_handle;
static uint8_t rte_ultrasonic_request_byte = 0;

 uint8_t rte_ultrasonic_request_byte_debug[10];
void Rte_Ultrasonic_requests_iwrite(uint8_t u) //Com call
{

    rte_ultrasonic_request_byte |= u;
    //post
//    rte_ultrasonic_request_byte_debug[i] = rte_ultrasonic_request_byte;
//    if (i == 9)
//        i = 0;
//    i++;
    Semaphore_post(rte_Binary_Semaphore_Ultrasonic_Requests_handle);

}

void Rte_Ultrasonic_requests_iread(uint8_t* data) //SWC call //blocking call
{
    //pend
    Semaphore_pend(rte_Binary_Semaphore_Ultrasonic_Requests_handle,
                   BIOS_WAIT_FOREVER);
//    Hwi_disableInterrupt(55);
    *data = rte_ultrasonic_request_byte;
    rte_ultrasonic_request_byte = 0;
//    Hwi_enableInterrupt(55);

}
#endif

#ifdef ECU2_ALGORITHMICNODE //updated
extern Semaphore_Handle rte_Binary_Semaphore_Ultrasonic_Requests_handle;
extern Semaphore_Handle rte_Mutex_Ultrasonic_Requests_handle;
static uint8_t rte_ultrasonic_request_byte = 0;
void Rte_Ultrasonic_requests_iwrite(uint8_t u) //SWC call
{
    Semaphore_pend(rte_Mutex_Ultrasonic_Requests_handle, BIOS_WAIT_FOREVER);

    rte_ultrasonic_request_byte |= u;
    Semaphore_post(rte_Mutex_Ultrasonic_Requests_handle);
    //post
    Semaphore_post(rte_Binary_Semaphore_Ultrasonic_Requests_handle);

}

uint8_t Rte_Ultrasonic_requests_iread(uint8_t* data) //COM call //not blocking
{
    //pend
    uint8_t SemaVlaue;
    SemaVlaue = Semaphore_pend(rte_Binary_Semaphore_Ultrasonic_Requests_handle,
            BIOS_NO_WAIT);

    if (SemaVlaue == 0)
    {

    }
    else
    {
        Semaphore_pend(rte_Mutex_Ultrasonic_Requests_handle, BIOS_WAIT_FOREVER);
        *data = rte_ultrasonic_request_byte;
        rte_ultrasonic_request_byte = 0;
        Semaphore_post(rte_Mutex_Ultrasonic_Requests_handle);

    }
    return SemaVlaue;

}
#endif

//#ifdef ECU3_ACTUATORNODE
//void Rte_Ultrasonic_requests_iwrite(uint8_t u)
//{
//
//    rte_ultrasonic_request_byte |= u;
//    //post
//    sema = 1;
//
//}
//
//uint8_t Rte_Ultrasonic_requests_iread(uint8_t* data)
//{
//    //pend
//    if (sema == 0)
//    return 1;
//    Hwi_disableInterrupt(55);
//    *data = rte_ultrasonic_request_byte;
//    rte_ultrasonic_request_byte = 0;
//    sema = 0;
//    Hwi_enableInterrupt(55);
//
//    return 0;
//
//}
//#endif

