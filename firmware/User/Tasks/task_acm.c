/*
 * task_acm.c
 *
 */

#include "task_acm.h"
#include "task_lvgl.h"
#include "main.h"
#include "cmsis_os.h"


osThreadId ACMTaskHandle;
QueueHandle_t acm_event_queue;

static void TaskACM_task(void const *arg);

extern QueueHandle_t show_image_queue;

uint8_t pic_buffer[25604];

void TaskACM_createTask() {
    acm_event_queue = xQueueCreate(4, sizeof(acm_event_t));

	osThreadDef(ACMTask, TaskACM_task, osPriorityNormal, 0, 512);
	ACMTaskHandle = osThreadCreate(osThread(ACMTask), NULL);
}

void TaskACM_task(void const *arg) {
	acm_event_t acm_ev;
	size_t packet_cnt = 0;
	size_t img_size = 0;

	while (1) {
        if(xQueueReceive(acm_event_queue, &acm_ev, portMAX_DELAY) == pdTRUE)
        {
            memcpy(pic_buffer+img_size, acm_ev.buffer, acm_ev.len);
            img_size += acm_ev.len;
        	packet_cnt++;
            if(img_size >= sizeof(pic_buffer))
            {
                show_img_queue_t show_img;
                show_img.display_id = 0;
                show_img.img_buf = pic_buffer;
                show_img.img_size = img_size;
                xQueueSend(show_image_queue, &show_img, portMAX_DELAY);
                img_size = 0;
                packet_cnt = 0;
            }
        }
	}
}
