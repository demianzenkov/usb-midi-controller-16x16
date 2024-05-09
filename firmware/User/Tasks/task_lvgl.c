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
#include "lv_lcd_generic_mipi.h"
#include "display.h"
#include "ui.h"

#define TEST_UI 0

extern SPI_HandleTypeDef hspi1;
extern SPI_HandleTypeDef hspi2;
extern SPI_HandleTypeDef hspi3;
extern SPI_HandleTypeDef hspi4;

osThreadId lvglTaskHandle;
osThreadId uiTaskHandle;
SemaphoreHandle_t lvgl_ready_sem;
SemaphoreHandle_t ui_busy_mutex;
QueueHandle_t show_string_queue;
QueueHandle_t show_value_queue;

lv_display_t *lcd_disp;
SemaphoreHandle_t ui_ready_sem;

static void TaskLVGL_task(void const *arg);
static void TaskLVGL_ui_task(void const *arg);

#if TEST_UI
osThreadId testUITaskHandle;
static void TaskLVGL_test_ui_task(void const *arg);
#endif


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

    show_string_queue = xQueueCreate(10, sizeof(show_string_queue_t));
    show_value_queue = xQueueCreate(10, sizeof(show_value_queue_t));

    ui_ready_sem = xSemaphoreCreateBinary();

	osThreadDef(lvglTask, TaskLVGL_task, osPriorityNormal, 0, 1024);
	lvglTaskHandle = osThreadCreate(osThread(lvglTask), NULL);

    osThreadDef(uiTask, TaskLVGL_ui_task, osPriorityNormal, 0, 1024);
	uiTaskHandle = osThreadCreate(osThread(uiTask), NULL);

#if TEST_UI
    osThreadDef(testUITask, TaskLVGL_test_ui_task, osPriorityNormal, 0, 1024);
    testUITaskHandle = osThreadCreate(osThread(testUITask), NULL);
#endif
}

void TaskLVGL_showValueOnDisplay(uint8_t disp, int32_t value) {
    // show_string_queue_t show_string;
    // show_string.display_id = disp;
    // sprintf(show_string.str, "%i", value);
    // xQueueSend(show_string_queue, &show_string, portMAX_DELAY);
    
    show_value_queue_t show_value;
    show_value.display_id = disp;
    show_value.value = value;
    xQueueSend(show_value_queue, &show_value, portMAX_DELAY);
}

void TaskLVGL_ui_task(void const *arg) {
    xSemaphoreTake(lvgl_ready_sem, portMAX_DELAY);

//    set_active_display(0);
    
    for(int i = 0; i < 16; i++) {
        xSemaphoreTake(ui_busy_mutex, portMAX_DELAY);
        set_active_display(i);
        ui_init();
        xSemaphoreGive(ui_busy_mutex);
        osDelay(50);
    }

    xSemaphoreGive(ui_ready_sem);
    
    show_string_queue_t show_string;
    show_value_queue_t show_value;
    for(;;) {
        if(xQueueReceive(show_string_queue, &show_string, 0) == pdTRUE) {
            xSemaphoreTake(ui_busy_mutex, portMAX_DELAY);
            set_active_display(show_string.display_id);
            ui_show_string(show_string.str);
            xSemaphoreGive(ui_busy_mutex);
            osDelay(30);
        }
        if(xQueueReceive(show_value_queue, &show_value, 0) == pdTRUE) {
            xSemaphoreTake(ui_busy_mutex, portMAX_DELAY);
            set_active_display(show_value.display_id);
            ui_set_bar_level(show_value.value);
            xSemaphoreGive(ui_busy_mutex);
            osDelay(30);
        }
    }
}


void TaskLVGL_task(void const *arg) {
	/* Initialize LVGL */
	lv_init();

    for(int i = 0; i < 16; i++) {
        set_active_display(i);
        lcd_io_init();
    }
	
	lcd_disp = lv_lcd_custom_mipi_create(LCD_H_RES, LCD_V_RES, LV_LCD_FLAG_NONE,
			lcd_send_cmd, lcd_send_color);

	for(int i = 0; i < 16; i++) {
		set_active_display(i);
		lv_lcd_init_controller(lcd_disp, LV_LCD_FLAG_NONE);
	}

	lv_lcd_set_callbacks(lcd_disp);

	for(int i = 0; i < 16; i++) {
	        set_active_display(i);
			lv_lcd_generic_mipi_send_cmd_list(lcd_disp, init_cmd_list);
	        lv_display_set_rotation(lcd_disp, LV_DISPLAY_ROTATION_270);
	        lv_st7735_set_invert(lcd_disp, 1);
	}


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
            
    xSemaphoreGive(lvgl_ready_sem);

	for (;;) {
        xSemaphoreTake(ui_busy_mutex, portMAX_DELAY);
		lv_timer_handler();
        xSemaphoreGive(ui_busy_mutex);
		osDelay(1);
	}
}

#if TEST_UI
void TaskLVGL_test_ui_task(void const *arg) {
    xSemaphoreTake(ui_ready_sem, portMAX_DELAY);
    
    for(int i = 0; i < 16; i++) {
        show_string_queue_t show_string;
        show_string.display_id = i;
        sprintf(show_string.str, "Display %d", i);
        xQueueSend(show_string_queue, &show_string, portMAX_DELAY);
    }
    
    while(1) {
        osDelay(1000);
    }
}
#endif


