/*
 * task_buttons.c
 *
 */

#include "task_buttons.h"
#include "main.h"
#include "cmsis_os.h"


static void TaskButtons_task(void const *arg);

osThreadId buttonsTaskHandle;

extern ADC_HandleTypeDef hadc1;

void TaskButtons_createTask() {
	osThreadDef(buttonsTask, TaskButtons_task, osPriorityNormal, 0, 1024);
	buttonsTaskHandle = osThreadCreate(osThread(buttonsTask), NULL);
}

void TaskButtons_task(void const *arg) {
 	while (1) {
        osDelay(100);
    }
 }
