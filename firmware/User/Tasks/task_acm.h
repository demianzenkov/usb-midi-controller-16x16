/*
 * task_acm.h
 *
 */

#ifndef TASK_ACM_H_
#define TASK_ACM_H_

#include "main.h"
#include "usbd_cdc_acm_if.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef struct {
    uint8_t buffer[APP_RX_DATA_SIZE];
    size_t len;
} acm_event_t;

void TaskACM_createTask();


#ifdef __cplusplus
}
#endif


#endif /* TASK_MIDI_H_ */
