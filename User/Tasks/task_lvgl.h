/*
 * task_lvgl.h
 *
 *  Created on: Apr 13, 2024
 *      Author: demian
 */

#ifndef TASK_LVGL_H_
#define TASK_LVGL_H_

#include "display.h"

#define LCD_H_RES       132
#define LCD_V_RES       162
#define BUS_SPI1_POLL_TIMEOUT 0x1000U

void TaskLVGL_createTask();

typedef struct{
    uint8_t display_id;
    char str[32];
} show_string_queue_t;

#endif /* TASK_LVGL_H_ */
