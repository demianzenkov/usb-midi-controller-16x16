#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _objects_t {
    lv_obj_t *main;
    lv_obj_t *panel_general;
    lv_obj_t *panel_channel;
    lv_obj_t *label_channel;
    lv_obj_t *panel_text;
    lv_obj_t *label_name;
    lv_obj_t *bar_level;
    lv_obj_t *label_level;
    lv_obj_t *label_level_min;
    lv_obj_t *label_level_max;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_MAIN = 1,
};

void create_screen_main();
void tick_screen_main();

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/