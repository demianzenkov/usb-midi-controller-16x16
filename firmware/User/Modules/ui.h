/*
 * ui.h
 *
 */

#ifndef UI_H_
#define UI_H_

#include "lvgl.h"

void ui_init();
void ui_show_string(const char *str);
void ui_set_bar_level(uint8_t value);

#endif /* UI_H_ */