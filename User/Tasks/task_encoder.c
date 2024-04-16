/*
 * task_encoder.c
 *
 */

#include "task_encoder.h"
#include "main.h"
#include "cmsis_os.h"

static void TaskEncoder_task(void const *arg);

osThreadId encoderTaskHandle;


void TaskEncoder_createTask() {
	osThreadDef(encoderTask, TaskEncoder_task, osPriorityNormal, 0, 128);
	encoderTaskHandle = osThreadCreate(osThread(encoderTask), NULL);

}

void TaskEncoder_task(void const *arg) {
	while (1) {
		// Encoders to read without interrupts: ENC24, ENC41
		osDelay(1);
		// Encoders to read with interrupts: ENC11, ENC12, ENC13, ENC14, ENC21, ENC22, ENC23, ENC31, ENC32, ENC33, ENC34, ENC42, ENC43, ENC44

	}
}
