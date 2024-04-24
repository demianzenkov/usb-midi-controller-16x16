/*
 * task_encoder.h
 *
 */

#ifndef TASK_ENCODER_H_
#define TASK_ENCODER_H_

#include "main.h"

typedef struct {
    uint8_t encoder_id;
    uint8_t state_a;
    uint8_t prev_state_a;
    uint8_t state_b;
    uint8_t prev_state_b;
    uint8_t prev_state;
    uint32_t ts;
    uint32_t prev_ts;
} encoder_ev_t;

void TaskEncoder_createTask();

#endif /* TASK_ENCODER_H_ */
