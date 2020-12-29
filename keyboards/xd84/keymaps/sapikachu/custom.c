#include QMK_KEYBOARD_H

// 5 -> ~1 second
#define BACKLIGHT_LENGTH 1500

static uint8_t _backlight_counter_1;
static uint16_t _backlight_counter_2;

static void set_level(uint8_t level) {
    backlight_level_noeeprom(level);
    _backlight_counter_1 = 255;
    _backlight_counter_2 = BACKLIGHT_LENGTH;
}

void keyboard_post_init_user(void) {
    set_level(255);
}

void housekeeping_task_user(void) {
    if (!_backlight_counter_1) {
        return;
    }
    if (--_backlight_counter_1) {
        return;
    }
    if (!--_backlight_counter_2) {
        uint8_t level = get_backlight_level();
        if (level > 1) {
            _backlight_counter_1 = 32;
            _backlight_counter_2 = 1;
        }
        backlight_level_noeeprom(level - 1);
        return;
    }
    _backlight_counter_1 = 255;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    set_level(255);
    return true;
}
