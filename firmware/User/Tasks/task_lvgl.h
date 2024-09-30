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
void TaskLVGL_showValueOnDisplay(uint8_t disp, int32_t value);

typedef struct{
    uint8_t display_id;
    char str[32];
} show_string_queue_t;

typedef struct{
    uint8_t display_id;
    uint8_t value;
} show_value_queue_t;

typedef struct{
    uint8_t display_id;
    uint8_t * img_buf;
    size_t img_size;
} show_img_queue_t;

#endif /* TASK_LVGL_H_ */
