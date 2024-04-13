/*
 * task_encoder.c
 *
 *  Created on: Apr 13, 2024
 *      Author: demian
 */

#include "task_encoder.h"

static void TaskEncoder_task(void const * arg);

void TaskEncoder_createTask()
{

}

void TaskEncoder_task(void const * arg)
{
	while(1){
        // Encoders to read without interrupts: ENC24, ENC41

        // Encoders to read with interrupts: ENC11, ENC12, ENC13, ENC14, ENC21, ENC22, ENC23, ENC31, ENC32, ENC33, ENC34, ENC42, ENC43, ENC44
        
	}
}
