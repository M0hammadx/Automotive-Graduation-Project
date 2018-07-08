/*
 * Request_task_rte.c
 *
 *  Created on: ??ş/??ş/????
 *      Author: Sahar Elnagar
 */
#include"Request_task_rte.h"

static g_RequiredTask Car_task ;
static uint8_t sema=0;
void Rte_Request_task_iwrite(g_RequiredTask task){

    Car_task =task;
    sema=1;
   //post
}

uint8_t Rte_Request_task_iread(g_RequiredTask* task){
    //pend

    if(sema==0) return 1;
       *task =Car_task;
       sema=0;

   return 0;

}
