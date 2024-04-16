/*
 * task_lvgl.c
 *
 *  Created on: Apr 13, 2024
 *      Author: demian
 */

#include "task_lvgl.h"
#include "cmsis_os.h"
#include "main.h"
#include "lvgl.h"
#include "src/drivers/display/st7735/lv_st7735.h"

#include "display.h"
#include "ui.h"



extern SPI_HandleTypeDef hspi1;
extern SPI_HandleTypeDef hspi2;
extern SPI_HandleTypeDef hspi3;
extern SPI_HandleTypeDef hspi4;

osThreadId lvglTaskHandle;
osThreadId uiTaskHandle;
SemaphoreHandle_t lvgl_ready_sem;
SemaphoreHandle_t ui_busy_mutex;

lv_display_t *lcd_disp;

static void TaskLVGL_task(void const *arg);
static void TaskLVGL_ui_task(void const *arg);
static lv_display_t * TaskLVGL_createDisplay(uint32_t hor_res, uint32_t ver_res, lv_lcd_flag_t flags,
                                          lv_lcd_send_cmd_cb_t send_cmd_cb, lv_lcd_send_color_cb_t send_color_cb);

static const uint8_t init_cmd_list[] = {
    0xB1,       3,  0x05, 0x3C, 0x3C,
    0xB2,       3,  0x05, 0x3C, 0x3C,
    0xB3,       6,  0x05, 0x3C, 0x3C, 0x05, 0x3C, 0x3C,
    0xB4,       1,  0x03,
    0xC0,       3,  0x28, 0x08, 0x04,
    0xC1,       1,  0XC0,
    0xC2,       2,  0x0D, 0x00,
    0xC3,       2,  0x8D, 0x2A,
    0xC4,       2,  0x8D, 0xEE,
    0xC5,       1,  0x10,
    0xE0,       16, 0x04, 0x22, 0x07, 0x0A, 0x2E, 0x30, 0x25, 0x2A, 0x28, 0x26, 0x2E, 0x3A, 0x00, 0x01, 0x03, 0x13,
    0xE1,       16, 0x04, 0x16, 0x06, 0x0D, 0x2D, 0x26, 0x23, 0x27, 0x27, 0x25, 0x2D, 0x3B, 0x00, 0x01, 0x04, 0x13,
    LV_LCD_CMD_DELAY_MS, LV_LCD_CMD_EOF
};


void TaskLVGL_createTask() {
    lvgl_ready_sem = xSemaphoreCreateBinary();
    ui_busy_mutex = xSemaphoreCreateMutex();
    xSemaphoreGive(ui_busy_mutex);

	osThreadDef(lvglTask, TaskLVGL_task, osPriorityNormal, 0, 1024);
	lvglTaskHandle = osThreadCreate(osThread(lvglTask), NULL);

    osThreadDef(uiTask, TaskLVGL_ui_task, osPriorityNormal, 0, 1024);
	uiTaskHandle = osThreadCreate(osThread(uiTask), NULL);
}

void TaskLVGL_ui_task(void const *arg) {
    xSemaphoreTake(lvgl_ready_sem, portMAX_DELAY);

//    set_active_display(0);
    for(int i = 0; i < 16; i++) {
        xSemaphoreTake(ui_busy_mutex, portMAX_DELAY);
        set_active_display(i);
        ui_init();
        xSemaphoreGive(ui_busy_mutex);
        osDelay(5);
    }

//    xSemaphoreTake(ui_busy_mutex, portMAX_DELAY);
//    ui_init(lcd_disp);
//    xSemaphoreGive(ui_busy_mutex);

    for(;;) {
        osDelay(1000);
    }
}


void TaskLVGL_task(void const *arg) {
	/* Initialize LVGL */
	lv_init();

//	set_active_display(4);
//	lcd_io_init();

    for(int i = 0; i < 16; i++) {
        set_active_display(i);
        lcd_io_init();
//        osDelay(100);
    }
//    set_active_display(0);
    
	// /* Initialize LCD I/O */
	// if (lcd_io_init() != 0)
	// 	return;

	/* Create the LVGL display object and the LCD display driver */
	lcd_disp = lv_lcd_custom_mipi_create(LCD_H_RES, LCD_V_RES, LV_LCD_FLAG_NONE,
			lcd_send_cmd, lcd_send_color);

	for(int i = 0; i < 16; i++) {
		set_active_display(i);
		lv_lcd_init_controller(lcd_disp, LV_LCD_FLAG_NONE);
//		osDelay(100);
	}

	lv_lcd_set_callbacks(lcd_disp);

//	lcd_disp = TaskLVGL_createDisplay(LCD_H_RES, LCD_V_RES, LV_LCD_FLAG_NONE, lcd_send_cmd, lcd_send_color);
//	lv_lcd_generic_mipi_send_cmd_list(lcd_disp, init_cmd_list);

	for(int i = 0; i < 16; i++) {
	        set_active_display(i);
			lv_lcd_generic_mipi_send_cmd_list(lcd_disp, init_cmd_list);
	        lv_display_set_rotation(lcd_disp, LV_DISPLAY_ROTATION_270);
	        lv_st7735_set_invert(lcd_disp, 1);
//	        osDelay(100);
	}
//	set_active_display(0);


	/* Allocate draw buffers on the heap. In this example we use two partial buffers of 1/10th size of the screen */
	lv_color_t *buf1 = NULL;
	lv_color_t *buf2 = NULL;

	uint32_t buf_size = LCD_H_RES * LCD_V_RES / 10
			* lv_color_format_get_size(lv_display_get_color_format(lcd_disp));

	buf1 = lv_malloc(buf_size);
	if (buf1 == NULL) {
		LV_LOG_ERROR("display draw buffer malloc failed");
		return;
	}

	buf2 = lv_malloc(buf_size);
	if (buf2 == NULL) {
		LV_LOG_ERROR("display buffer malloc failed");
		lv_free(buf1);
		return;
	}
	lv_display_set_buffers(lcd_disp, buf1, buf2, buf_size,
			LV_DISPLAY_RENDER_MODE_PARTIAL);

    // for(int i = 0; i < 16; i++) {
    //     set_active_display(i);
    //     ui_init(lcd_disp);
    // }

    // set_active_display(0);
    // ui_init(lcd_disp);
	
    xSemaphoreGive(lvgl_ready_sem);

	for (;;) {
        xSemaphoreTake(ui_busy_mutex, portMAX_DELAY);
		lv_timer_handler();
        xSemaphoreGive(ui_busy_mutex);
		osDelay(10);
	}
}


