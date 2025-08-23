#include "ui.h"
#include "stdio.h"
#include "task_lvgl.h"


// void ui_init() {
// 	lv_obj_t *obj;

// 	/* set screen background to white */
// 	lv_obj_t *scr = lv_screen_active();

// 	lv_obj_clean(scr);

// 	lv_obj_set_style_bg_color(scr, lv_color_white(), 0);
// 	lv_obj_set_style_bg_opa(scr, LV_OPA_100, 0);

// 	/* create label */
// 	obj = lv_label_create(scr);
// 	lv_obj_set_align(obj, LV_ALIGN_CENTER);
// 	lv_obj_set_height(obj, LV_SIZE_CONTENT);
// 	lv_obj_set_width(obj, LV_SIZE_CONTENT);
// 	lv_obj_set_style_text_font(obj, &lv_font_montserrat_24, 0);
// 	lv_obj_set_style_text_color(obj, lv_color_black(), 0);

// 	char string_to_print[30];
// 	static int cnt=0;
// 	cnt++;
// 	sprintf(string_to_print, "%i", cnt);
// 	lv_label_set_text(obj, string_to_print);
// }

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
    uint8_t show_value = (value * LCD_V_PHYSICAL_RES) / max_value;
    /* create rectangular box full display height showing level */
    obj = lv_obj_create(scr);
    lv_obj_set_size(obj, show_value, LCD_H_PHYSICAL_RES);
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_style_bg_color(obj, lv_color_black(), 0);
    lv_obj_set_style_bg_opa(obj, LV_OPA_100, 0);

}

void ui_show_logo()
{
	LV_IMAGE_DECLARE(icon);

	lv_obj_t *scr = lv_screen_active();
	lv_obj_clean(scr);

	lv_obj_t * img1 = lv_image_create(scr);
	lv_image_set_src(img1, &icon);
	lv_obj_align(img1, LV_ALIGN_CENTER, 0, 0);
}

void ui_show_image(const uint8_t * img_buf, size_t img_size) {
//	lv_image_dsc_t img_main = {
//	    .header.w = 160,
//	    .header.h = 80,
//	    .data_size = img_size,
//	    .header.cf = LV_COLOR_FORMAT_RGB565,          /*Set the color format*/
//	    .data = img_buf,
//	};
//
//
//	lv_obj_t * img;
//    /* set screen background to white */
//    lv_obj_t *scr = lv_screen_active();
//
//    lv_obj_clean(scr);
//
//    // lv_obj_set_style_bg_color(scr, lv_color_white(), 0);
//    // lv_obj_set_style_bg_opa(scr, LV_OPA_100, 0);
//
//    /* create image */
//
//    img = lv_img_create(scr);
////    img_main.data = malloc(img_size);
////    memcpy(img_main.data, img_buf, img_size);
//    img_main.data = img_buf;
//    img_main.data_size = img_size;
//    lv_obj_set_pos(img, 0, 0);
}
