#include "ui.h"
#include "stdio.h"
#include "task_lvgl.h"

void ui_init() {
	lv_obj_t *obj;

	/* set screen background to white */
	lv_obj_t *scr = lv_screen_active();

	lv_obj_clean(scr);

	lv_obj_set_style_bg_color(scr, lv_color_white(), 0);
	lv_obj_set_style_bg_opa(scr, LV_OPA_100, 0);

	/* create label */
	obj = lv_label_create(scr);
	lv_obj_set_align(obj, LV_ALIGN_CENTER);
	lv_obj_set_height(obj, LV_SIZE_CONTENT);
	lv_obj_set_width(obj, LV_SIZE_CONTENT);
	lv_obj_set_style_text_font(obj, &lv_font_montserrat_24, 0);
	lv_obj_set_style_text_color(obj, lv_color_black(), 0);

	char string_to_print[30];
	static int cnt=0;
	cnt++;
	sprintf(string_to_print, "%i", cnt);
	lv_label_set_text(obj, string_to_print);
}

void ui_show_string(const char * str) {
    lv_obj_t *obj;

    /* set screen background to white */
    lv_obj_t *scr = lv_screen_active();

    lv_obj_clean(scr);

    lv_obj_set_style_bg_color(scr, lv_color_white(), 0);
    lv_obj_set_style_bg_opa(scr, LV_OPA_100, 0);

    /* create label */
    obj = lv_label_create(scr);
    lv_obj_set_align(obj, LV_ALIGN_CENTER);
    lv_obj_set_height(obj, LV_SIZE_CONTENT);
    lv_obj_set_width(obj, LV_SIZE_CONTENT);
    lv_obj_set_style_text_font(obj, &lv_font_montserrat_24, 0);
    lv_obj_set_style_text_color(obj, lv_color_black(), 0);

    lv_label_set_text(obj, str);
}

void ui_set_bar_level(uint8_t value) {
    lv_obj_t *obj;

    /* set screen background to white */
    lv_obj_t *scr = lv_screen_active();

    lv_obj_clean(scr);

    lv_obj_set_style_bg_color(scr, lv_color_white(), 0);
    lv_obj_set_style_bg_opa(scr, LV_OPA_100, 0);

    uint8_t max_value = 127;    // ENCODER_MAX_VALUE
    uint8_t show_value = (value * LCD_V_RES) / max_value;
    /* create rectangular box full display height showing level */
    obj = lv_obj_create(scr);
    lv_obj_set_size(obj, show_value+5, LCD_H_RES);
    lv_obj_set_pos(obj, -1, 0);
    lv_obj_set_style_bg_color(obj, lv_color_black(), 0);
    lv_obj_set_style_bg_opa(obj, LV_OPA_100, 0);

}