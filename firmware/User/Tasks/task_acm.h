/*
 * task_acm.h
 *
 */

#ifndef TASK_ACM_H_
#define TASK_ACM_H_

#include "main.h"
#include "usbd_cdc_acm_if.h"
#include "cmsis_os.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef struct {
    uint8_t buffer[64];
    size_t len;
} acm_event_t;

// void TaskACM_createTask();

class ACM {
public:
	void createTask();
private:
	static void task(void const *arg);
	void parseInputBuffer(char * buffer);

public:
	QueueHandle_t acm_event_queue;
private:
	osThreadId ACMTaskHandle;
};

extern ACM acm;

#ifdef __cplusplus
}
#endif


#endif /* TASK_MIDI_H_ */
