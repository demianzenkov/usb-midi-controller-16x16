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
#include "lv_lcd_custom_mipi.h"
#include "display.h"
#include "ui.h"
#include "screens.h"
#include "task_lvgl.h"
#include "string.h"
#include "stdio.h"

#define TEST_UI 0

UI ui;

extern SPI_HandleTypeDef hspi1;
extern SPI_HandleTypeDef hspi2;
extern SPI_HandleTypeDef hspi3;
extern SPI_HandleTypeDef hspi4;

osThreadId lvglTaskHandle;
osThreadId uiTaskHandle;

// static void TaskLVGL_task(void const *arg);
// static void TaskLVGL_ui_task(void const *arg);

#if TEST_UI
osThreadId testUITaskHandle;
static void TaskLVGL_test_ui_task(void const *arg);
#endif

static const uint8_t init_cmd_list[] = {
	0xB1, 3, 0x05, 0x3C, 0x3C,
	0xB2, 3, 0x05, 0x3C, 0x3C,
	0xB3, 6, 0x05, 0x3C, 0x3C, 0x05, 0x3C, 0x3C,
	0xB4, 1, 0x03,
	0xC0, 3, 0x28, 0x08, 0x04,
	0xC1, 1, 0XC0,
	0xC2, 2, 0x0D, 0x00,
	0xC3, 2, 0x8D, 0x2A,
	0xC4, 2, 0x8D, 0xEE,
	0xC5, 1, 0x10,
	0xE0, 16, 0x04, 0x22, 0x07, 0x0A, 0x2E, 0x30, 0x25, 0x2A, 0x28, 0x26, 0x2E, 0x3A, 0x00, 0x01, 0x03, 0x13,
	0xE1, 16, 0x04, 0x16, 0x06, 0x0D, 0x2D, 0x26, 0x23, 0x27, 0x27, 0x25, 0x2D, 0x3B, 0x00, 0x01, 0x04, 0x13,
	LV_LCD_CMD_DELAY_MS, LV_LCD_CMD_EOF};

UI::UI()
{
}

void UI::createTask()
{
	lvgl_ready_sem = xSemaphoreCreateBinary();
	ui_busy_mutex = xSemaphoreCreateMutex();
	xSemaphoreGive(ui_busy_mutex);

	show_level_queue = xQueueCreate(16, sizeof(show_level_t));
	show_name_queue = xQueueCreate(16, sizeof(show_string_t));
	show_value_queue = xQueueCreate(16, sizeof(show_string_t));
	show_channel_queue = xQueueCreate(16, sizeof(show_string_t));
	show_color_queue = xQueueCreate(16, sizeof(show_color_t));
	// show_image_queue = xQueueCreate(16, sizeof(show_img_t));

	ui_ready_sem = xSemaphoreCreateBinary();

	osThreadDef(lvglTask, taskLVGL, osPriorityNormal, 0, 1024);
	lvglTaskHandle = osThreadCreate(osThread(lvglTask), this);

	osThreadDef(uiTask, taskUI, osPriorityNormal, 0, 1024);
	uiTaskHandle = osThreadCreate(osThread(uiTask), this);

#if TEST_UI
	osThreadDef(testUITask, TaskLVGL_test_ui_task, osPriorityNormal, 0, 1024);
	testUITaskHandle = osThreadCreate(osThread(testUITask), NULL);
#endif
}

	
void UI::taskUI(void const *arg)
{
	UI *p_this = (UI *)arg;

	xSemaphoreTake(p_this->lvgl_ready_sem, portMAX_DELAY);

	//    set_active_display(0);

	for (int i = 0; i < 16; i++)
	{
		xSemaphoreTake(p_this->ui_busy_mutex, portMAX_DELAY);
		set_active_display(i);
		// ui_show_logo();
		ui_init();
		loadScreen(SCREEN_ID_MAIN);
		xSemaphoreGive(p_this->ui_busy_mutex);
		osDelay(30);
	}

	xSemaphoreGive(p_this->ui_ready_sem);

	show_string_t show_name;
	show_string_t show_value;
	show_level_t show_level;
	show_string_t show_channel;
	show_color_t show_color;
	// show_img_t show_img;
	
	for (;;)
	{
		if(xQueueReceive(p_this->show_name_queue, &show_name, 1) == pdTRUE) {
			xSemaphoreTake(p_this->ui_busy_mutex, portMAX_DELAY);
			set_active_display(show_name.display_id);
			lv_obj_t *obj = objects.label_name;
			lv_label_set_text(obj, show_name.str);
			xSemaphoreGive(p_this->ui_busy_mutex);
			osDelay(30);
		}

		if(xQueueReceive(p_this->show_value_queue, &show_value, 1) == pdTRUE) {
			xSemaphoreTake(p_this->ui_busy_mutex, portMAX_DELAY);
			set_active_display(show_value.display_id);
			lv_label_set_text(objects.label_level, show_value.str);
			xSemaphoreGive(p_this->ui_busy_mutex);
			osDelay(30);
		}
		if(xQueueReceive(p_this->show_channel_queue, &show_channel, 1) == pdTRUE) {
			xSemaphoreTake(p_this->ui_busy_mutex, portMAX_DELAY);
			set_active_display(show_channel.display_id);
			lv_obj_t *obj = objects.label_channel;
			lv_label_set_text(obj, show_channel.str);
			xSemaphoreGive(p_this->ui_busy_mutex);
			osDelay(30);
		}
		if(xQueueReceive(p_this->show_level_queue, &show_level, 1) == pdTRUE) {
			xSemaphoreTake(p_this->ui_busy_mutex, portMAX_DELAY);
			set_active_display(show_level.display_id);
			lv_bar_set_value(objects.bar_level, show_level.level, LV_ANIM_OFF);
			lv_obj_invalidate(objects.bar_level);
			xSemaphoreGive(p_this->ui_busy_mutex);
			osDelay(30);
		}
		
		if(xQueueReceive(p_this->show_color_queue, &show_color, 1) == pdTRUE) {
			xSemaphoreTake(p_this->ui_busy_mutex, portMAX_DELAY);
			set_active_display(show_color.display_id);
			lv_obj_t *obj = NULL;
			switch (show_color.element)
			{
			case COLOR_ELEMENT_BACKGROUND: {
				obj = objects.panel_general;
				lv_obj_set_style_bg_color(obj, show_color.color, LV_PART_MAIN | LV_STATE_DEFAULT);
				lv_obj_invalidate(obj);
				obj = objects.panel_channel;
				lv_obj_set_style_bg_color(obj, show_color.color, LV_PART_MAIN | LV_STATE_DEFAULT);
				lv_obj_invalidate(obj);
				obj = objects.panel_text;
				lv_obj_set_style_bg_color(obj, show_color.color, LV_PART_MAIN | LV_STATE_DEFAULT);
				lv_obj_invalidate(obj);
				break;
			}
			case COLOR_ELEMENT_BORDER: {
				obj = objects.panel_general;
				lv_obj_set_style_border_color(obj, show_color.color, LV_PART_MAIN | LV_STATE_DEFAULT);
				lv_obj_invalidate(obj);
				obj = objects.panel_channel;
				lv_obj_set_style_border_color(obj, show_color.color, LV_PART_MAIN | LV_STATE_DEFAULT);
				lv_obj_invalidate(obj);
				obj = objects.panel_text;
				lv_obj_set_style_border_color(obj, show_color.color, LV_PART_MAIN | LV_STATE_DEFAULT);
				lv_obj_invalidate(obj);
				
				break;
			}
			case COLOR_ELEMENT_TEXT: {
				lv_obj_set_style_text_color(objects.label_name, show_color.color, LV_PART_MAIN | LV_STATE_DEFAULT);
				lv_obj_invalidate(objects.label_name);	
				lv_obj_set_style_text_color(objects.label_channel, show_color.color, LV_PART_MAIN | LV_STATE_DEFAULT);
				lv_obj_invalidate(objects.label_channel);
				lv_obj_set_style_text_color(objects.label_level, show_color.color, LV_PART_MAIN | LV_STATE_DEFAULT);
				lv_obj_invalidate(objects.label_level);
				break;
			}
			case COLOR_ELEMENT_BAR: {
				obj = objects.bar_level;
				lv_obj_set_style_bg_color(obj, show_color.color, LV_PART_INDICATOR | LV_STATE_DEFAULT);
				lv_obj_set_style_bg_opa(obj, LV_OPA_COVER, LV_PART_INDICATOR | LV_STATE_DEFAULT);
				lv_obj_invalidate(obj);
				break;
			}
			default: {
				break;
			}
			}
			
			xSemaphoreGive(p_this->ui_busy_mutex);
			osDelay(30);
		}
		

		// if(xQueueReceive(show_image_queue, &show_img, 1) == pdTRUE) {
		// 	xSemaphoreTake(ui_busy_mutex, portMAX_DELAY);
		// 	set_active_display(show_img.display_id);
		// 	ui_show_image(show_img.img_buf, show_img.img_size);
		// 	xSemaphoreGive(ui_busy_mutex);
		// }
	}
}

void UI::taskLVGL(void const *arg)
{
	UI *p_this = (UI *)arg;
	/* Initialize LVGL */
	lv_init();

	for (int i = 0; i < 16; i++)
	{
		set_active_display(i);
		lcd_io_init();
	}

	p_this->lcd_disp = lv_lcd_custom_mipi_create(LCD_H_RES, LCD_V_RES, LV_LCD_FLAG_BGR,
												 lcd_send_cmd, lcd_send_color);

	/* Don't explicitly set color format, let LVGL use its default */
	/* lv_display_set_color_format(lcd_disp, LV_COLOR_FORMAT_RGB565); */

	for (int i = 0; i < 16; i++)
	{
		set_active_display(i);
		lv_lcd_custom_init_controller(p_this->lcd_disp, LV_LCD_FLAG_BGR);
	}

	lv_lcd_custom_mipi_set_callbacks(p_this->lcd_disp);

	for (int i = 0; i < 16; i++)
	{
		set_active_display(i);
		lv_lcd_generic_mipi_send_cmd_list(p_this->lcd_disp, init_cmd_list);
		lv_display_set_rotation(p_this->lcd_disp, LV_DISPLAY_ROTATION_270);
		lv_display_set_resolution(p_this->lcd_disp, LCD_H_PHYSICAL_RES, LCD_V_PHYSICAL_RES);
		// lv_display_set_physical_resolution(lcd_disp, LCD_H_PHYSICAL_RES, LCD_V_PHYSICAL_RES+2);
		lv_st7735_set_invert(p_this->lcd_disp, 1);
		lv_display_set_offset(p_this->lcd_disp, 1, (LCD_H_RES - LCD_H_PHYSICAL_RES) / 2);
	}

	/* Allocate draw buffers on the heap. In this example we use two partial buffers of 1/10th size of the screen */
	lv_color_t *buf1 = NULL;
	lv_color_t *buf2 = NULL;

	uint32_t buf_size = LCD_V_PHYSICAL_RES * LCD_DRAW_BUFF_HEIGHT * lv_color_format_get_size(lv_display_get_color_format(p_this->lcd_disp));

	buf1 = (lv_color_t *)lv_malloc(buf_size);
	if (buf1 == NULL)
	{
		LV_LOG_ERROR("display draw buffer malloc failed");
		return;
	}

	buf2 = NULL;
	// buf2 = (lv_color_t *)lv_malloc(buf_size);
	// if (buf2 == NULL) {
	// 	LV_LOG_ERROR("display buffer malloc failed");
	// 	lv_free(buf1);
	// 	return;
	// }
	lv_display_set_buffers(p_this->lcd_disp, buf1, buf2, buf_size,
						   LV_DISPLAY_RENDER_MODE_PARTIAL);

	xSemaphoreGive(p_this->lvgl_ready_sem);

	for (;;)
	{
		xSemaphoreTake(p_this->ui_busy_mutex, portMAX_DELAY);
		lv_timer_handler();
		xSemaphoreGive(p_this->ui_busy_mutex);
		osDelay(1);
	}
}


void UI::showBarLevel(uint8_t disp, uint8_t level)
{
	if(level > 127) {
		return;
	}
	show_level_t show_level = {};
	show_level.display_id = disp;
	show_level.level = level;
	xQueueSend(show_level_queue, &show_level, portMAX_DELAY);
}

void UI::showValue(uint8_t disp, const char *str)
{
	if (strlen(str) > MAX_NAME_LENGTH - 1)
	{
		return;
	}
	show_string_t show_value = {};
	show_value.display_id = disp;
	strncpy(show_value.str, str, sizeof(show_value.str));
	xQueueSend(show_value_queue, &show_value, portMAX_DELAY);
}

void UI::showName(uint8_t disp, const char *str)
{
	if (strlen(str) > MAX_NAME_LENGTH - 1)
	{
		return;
	}
	show_string_t show_name = {};
	show_name.display_id = disp;
	strncpy(show_name.str, str, sizeof(show_name.str));
	xQueueSend(show_name_queue, &show_name, portMAX_DELAY);
}

void UI::showChannel(uint8_t disp, const char *str)
{
	if (strlen(str) > MAX_NAME_LENGTH - 1)
	{
		return;
	}
	show_string_t show_name = {};
	show_name.display_id = disp;
	strncpy(show_name.str, str, sizeof(show_name.str));
	xQueueSend(show_channel_queue, &show_name, portMAX_DELAY);
}

void UI::showColor(uint8_t disp, color_element_e element, lv_color_t color)
{
	show_color_t show_color = {};
	show_color.display_id = disp;
	show_color.element = element;
	show_color.color = color;
	xQueueSend(show_color_queue, &show_color, portMAX_DELAY);
}

#if TEST_UI
void TaskLVGL_test_ui_task(void const *arg)
{
	xSemaphoreTake(ui_ready_sem, portMAX_DELAY);

	for (int i = 0; i < 16; i++)
	{
		show_string_t show_name;
		show_name.display_id = i;
		sprintf(show_name.str, "Display %d", i);
		xQueueSend(show_name_queue, &show_name, portMAX_DELAY);
	}

	while (1)
	{
		osDelay(1000);
	}
}
#endif
