/*
 * task_acm.c
 *
 */

#include "task_acm.h"
#include "task_lvgl.h"
#include "main.h"
#include "cmsis_os.h"
#include "usbd_cdc_acm_if.h"
#include "task_encoder.h"


osThreadId ACMTaskHandle;
QueueHandle_t acm_event_queue;

static void TaskACM_task(void const *arg);
void TaskACM_parseInputBuffer(char * buffer);

extern QueueHandle_t show_image_queue;

// uint8_t pic_buffer[25604];

void TaskACM_createTask() {
    acm_event_queue = xQueueCreate(4, sizeof(acm_event_t));

	osThreadDef(ACMTask, TaskACM_task, osPriorityNormal, 0, 512);
	ACMTaskHandle = osThreadCreate(osThread(ACMTask), NULL);
}

void TaskACM_task(void const *arg) {
	acm_event_t acm_ev = {};
	size_t packet_cnt = 0;
	size_t img_size = 0;

	char command_string_buffer[128] = {0};
	size_t command_string_len = 0;
	while (1) {
        if(xQueueReceive(acm_event_queue, &acm_ev, portMAX_DELAY) == pdTRUE)
        {
			// Check if the buffer contains "\n" to indicate end of command
			// If it doen't - accumulate the buffer
			if(acm_ev.buffer[acm_ev.len - 1] != '\n')
			{
				// Accumulate the buffer
				if(command_string_len + acm_ev.len < sizeof(command_string_buffer) - 1)
				{
					memcpy(command_string_buffer + command_string_len, acm_ev.buffer, acm_ev.len);
					command_string_len += acm_ev.len;
					command_string_buffer[command_string_len] = '\0'; // Null-terminate the string
					continue; // Wait for more data
				}
			} else {
				// If the buffer ends with "\n", copy it to command_string_buffer
				if(command_string_len + acm_ev.len < sizeof(command_string_buffer) - 1)
				{
					memcpy(command_string_buffer + command_string_len, acm_ev.buffer, acm_ev.len);
					command_string_len += acm_ev.len;
					command_string_buffer[command_string_len] = '\0'; // Null-terminate the string
					TaskACM_parseInputBuffer(command_string_buffer);
				}
				command_string_len = 0; // Reset command string length
			}
					// copy buffer to command_string_buffer

			// TaskACM_parseInputBuffer(&acm_ev);
			
            // memcpy(pic_buffer+img_size, acm_ev.buffer, acm_ev.len);
            // img_size += acm_ev.len;
        	// packet_cnt++;
            // if(img_size >= sizeof(pic_buffer))
            // {
            //     show_img_queue_t show_img;
            //     show_img.display_id = 0;
            //     show_img.img_buf = pic_buffer;
            //     show_img.img_size = img_size;
            //     xQueueSend(show_image_queue, &show_img, portMAX_DELAY);
            //     img_size = 0;
            //     packet_cnt = 0;
            // }

        }
	}
}

void TaskACM_parseInputBuffer(char * buffer) {
	// Check string for commands
	// "/set/name/x/y" - where x - display id, y - string value
	if(buffer[0] == '/') {
		char * cmd = (char *)buffer;
		if(strncmp(cmd, "/set/name/", 10) == 0) {
			cmd += 10; // skip "/set/name/"
			uint8_t disp_id = atoi(cmd);
			cmd = strchr(cmd, '/');
			if(cmd != NULL) {
				cmd++; // skip '/'
				TaskLVGL_showStringOnDisplay(disp_id, cmd);
				CDC_Transmit(0, (uint8_t *)"OK\n\r", 4);
			}
			else {
				CDC_Transmit(0, (uint8_t *)"FAIL\n\r", 6);
			}
		}
		else if(strncmp(cmd, "/set/value/", 11) == 0) {
			cmd += 11; // skip "/set/value/"
			uint8_t disp_id = atoi(cmd);
			cmd = strchr(cmd, '/');
			if(cmd != NULL) {
				cmd++; // skip '/'
				int32_t value = atoi(cmd);
				if((value < 0) || (value > 127)) {
					CDC_Transmit(0, (uint8_t *)"FAIL\n\r", 6);
					return;
				}
				TaskLVGL_showValueOnDisplay(disp_id, value);
				encoder_values[disp_id] = value;
				CDC_Transmit(0, (uint8_t *)"OK\n\r", 4);
				return;
			}
			else {
				CDC_Transmit(0, (uint8_t *)"FAIL\n\r", 6);
			}
		}
		else {
			CDC_Transmit(0, (uint8_t *)"FAIL\n\r", 6);
		}
	}
}
