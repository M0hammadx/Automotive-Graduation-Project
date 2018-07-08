/*
 * Request_task_rte.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: Sahar Elnagar
 */

#ifndef RTE_REQUEST_TASK_RTE_H_
#define RTE_REQUEST_TASK_RTE_H_

#include "user_data_types.h"


void Rte_Request_task_iwrite(g_RequiredTask task);
uint8_t Rte_Request_task_iread(g_RequiredTask* task);
#endif /* RTE_REQUEST_TASK_RTE_H_ */
