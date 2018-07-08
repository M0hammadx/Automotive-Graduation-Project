#include "Ultrasonic_data_rte.h"


extern Semaphore_Handle rte_Binary_Semaphore_Ultrasonic_Data_handle;
extern Semaphore_Handle rte_Mutex_Ultrasonic_Data_handle;
#ifdef ECU1_SENSORYNODE
static uint8_t rte_Ultrasonic_Reading[8];
void Rte_Ultrasonic_data_iwrite(uint8_t* data) //SWC call
{
    Semaphore_pend(rte_Mutex_Ultrasonic_Data_handle, BIOS_WAIT_FOREVER);
//    System_printf("SWC takes U_M_D\n");
//    System_flush();
    for (int i = 0; i < 8; i++)
    {
        rte_Ultrasonic_Reading[i] = data[i];

    }
    //post
    Semaphore_post(rte_Mutex_Ultrasonic_Data_handle);
//    System_printf("SWC release U_M_D\n");
//    System_flush();
    Semaphore_post(rte_Binary_Semaphore_Ultrasonic_Data_handle);
//    System_printf("SWC release U_M_D\n");
//    System_flush();

}

uint8_t Rte_Ultrasonic_data_iread(uint8_t* data) //Com Call //BIOS_NO_WAIT /check fun ouput
{
    //pend
    uint8_t semaVlaue;
    semaVlaue = Semaphore_pend(rte_Binary_Semaphore_Ultrasonic_Data_handle,
    BIOS_NO_WAIT);
    if (semaVlaue == 0)
    {

    }
    else
    {
        Semaphore_pend(rte_Mutex_Ultrasonic_Data_handle, BIOS_WAIT_FOREVER);
        for (int i = 0; i < 8; i++)
        {

            data[i] = rte_Ultrasonic_Reading[i];
        }
        Semaphore_post(rte_Mutex_Ultrasonic_Data_handle);
    }
    return semaVlaue;

}
#endif

#ifdef ECU2_ALGORITHMICNODE
static uint8_t rte_Ultrasonic_Reading[8];
void Rte_Ultrasonic_data_iwrite(uint8_t* data) //Com_Rx_indication Call
{
    for (int i = 0; i < 8; i++)
    {
        rte_Ultrasonic_Reading[i] = data[i];

    }
    Semaphore_post(rte_Binary_Semaphore_Ultrasonic_Data_handle);

}

uint8_t Rte_Ultrasonic_data_iread(uint8_t* data) //SWC call
{
    //pend no wait semas
    uint8_t SemaValue=0;
    SemaValue= Semaphore_pend(rte_Binary_Semaphore_Ultrasonic_Data_handle,
            200);

    if(SemaValue == 0){

    }
    else{
    Hwi_disableInterrupt(55);
    for (int i = 0; i < 8; i++)
    {
        data[i] = rte_Ultrasonic_Reading[i];

    }
    Hwi_enableInterrupt(55);
    }
    return SemaValue;

}
#endif

//#ifdef ECU3_ACTUATORNODE
//void Rte_Ultrasonic_data_iwrite(uint8_t* data)
//{
//    for(int i =0; i<8; i++)
//    {
//        rte_Ultrasonic_Reading[i] = data[i];
//
//    }
////post no wait sema
//
//}
//
//uint8_t Rte_Ultrasonic_data_iread(uint8_t* data)
//{
//    //pend no wait semas
//
//    for(int i =0; i<=7; i++)
//    {
//        data[i]= rte_Ultrasonic_Reading[i];
//
//    }
//
//}
//#endif
