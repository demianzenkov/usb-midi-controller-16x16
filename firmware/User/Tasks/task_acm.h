/*
 * task_acm.h
 *
 */

#ifndef TASK_ACM_H_
#define TASK_ACM_H_

#include "main.h"
#include "usbd_cdc_acm_if.h"

typedef struct {
    uint8_t buffer[APP_RX_DATA_SIZE];
    size_t len;
} acm_event_t;

void TaskACM_createTask();


#endif /* TASK_MIDI_H_ */
