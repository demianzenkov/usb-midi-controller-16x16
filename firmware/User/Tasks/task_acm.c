/*
 * task_acm.c
 *
 */

#include "task_acm.h"
#include "main.h"
#include "cmsis_os.h"


osThreadId ACMTaskHandle;
QueueHandle_t acm_event_queue;

static void TaskACM_task(void const *arg);

void TaskACM_createTask() {
    acm_event_queue = xQueueCreate(4, sizeof(acm_event_t));

	osThreadDef(ACMTask, TaskACM_task, osPriorityNormal, 0, 512);
	ACMTaskHandle = osThreadCreate(osThread(ACMTask), NULL);
}

void TaskACM_task(void const *arg) {
	acm_event_t acm_ev;
	while (1) {
        if(xQueueReceive(acm_event_queue, &acm_ev, portMAX_DELAY) == pdTRUE) {
            // CDC_Transmit(0, uint8_t* Buf, uint16_t Len);
            osDelay(10);
        }
	}
}
