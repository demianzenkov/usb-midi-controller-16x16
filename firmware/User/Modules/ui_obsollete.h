/*
 * ui.h
 *
 */

#ifndef UI_H_
#define UI_H_

#include "lvgl.h"

// void ui_init();
void ui_show_string(const char * str);
void ui_set_bar_level(uint8_t value);
void ui_show_image(const uint8_t * img_buf, size_t img_size);
void ui_show_logo();

#endif /* UI_H_ */
