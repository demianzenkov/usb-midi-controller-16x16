/*
 * task_encoder.c
 *
 */

#include "task_encoder.h"
#include "task_lvgl.h"
#include "main.h"
#include "cmsis_os.h"


#define ENC_DEBOUNCE_HIGH_FILTER    50
#define ENC_DEBOUNCE_LOW_FILTER     3000
#define ENC_DEBOUNCE_CMD_FILTER		pdMS_TO_TICKS(250)

static void TaskEncoder_task(void const *arg);

osThreadId encoderTaskHandle;
QueueHandle_t encoder_queue = 0;
encoder_ev_t encoder_ev[16] = {{0, 0, 0, 0, 0}, {1, 0, 0, 0, 0}, {2, 0, 0, 0, 0}, {3, 0, 0, 0, 0}, {4, 0, 0, 0, 0}, {5, 0, 0, 0, 0}, {6, 0, 0, 0, 0}, {7, 0, 0, 0, 0}, {8, 0, 0, 0, 0}, {9, 0, 0, 0, 0}, {10, 0, 0, 0, 0}, {11, 0, 0, 0, 0}, {12, 0, 0, 0, 0}, {13, 0, 0, 0, 0}, {14, 0, 0, 0, 0}, {15, 0, 0, 0, 0}};

int32_t encoder_values[16] = {};
int32_t encoder_delta_values[16] = {};
uint32_t ev_counter[16] = {};
uint32_t ev_last_time[16] = {};

void TaskEncoder_createTask() {
    encoder_queue = xQueueCreate(50, sizeof(encoder_ev_t));
	osThreadDef(encoderTask, TaskEncoder_task, osPriorityNormal, 0, 1024);
	encoderTaskHandle = osThreadCreate(osThread(encoderTask), NULL);
}

 void TaskEncoder_task(void const *arg) {
 	while (1) {
 		// Encoders to read without interrupts: ENC24, ENC41
		
         // Read event from interrupt: ENC11, ENC12, ENC13, ENC14, ENC21, ENC22, ENC23, ENC31, ENC32, ENC33, ENC34, ENC42, ENC43, ENC44
         encoder_ev_t ev;
         if(xQueueReceive(encoder_queue, &ev, portMAX_DELAY) == pdTRUE) {
                 if(ev.prev_state_a == 0 && ev.state_a == 1) {
                     if(ev.prev_state_b == 0 && ev.state_b == 1) {
                     	if((ev.encoder_id != 14) && (ev.encoder_id != 15)) {
                             encoder_values[ev.encoder_id]--;
                         } else {
                             encoder_values[ev.encoder_id]++;
                         }
                         TaskLVGL_showValueOnDisplay(ev.encoder_id, encoder_values[ev.encoder_id]);
                     }
                 } else if(ev.prev_state_a == 1 && ev.state_a == 0) {
                     if(ev.prev_state_b == 0 && ev.state_b == 1) {
                         if((ev.encoder_id != 14) && (ev.encoder_id != 15)) {
                             encoder_values[ev.encoder_id]++;
                         } else {
                             encoder_values[ev.encoder_id]--;
                         }
                         TaskLVGL_showValueOnDisplay(ev.encoder_id, encoder_values[ev.encoder_id]);
                     }
                 }
         }
 	}
 }
