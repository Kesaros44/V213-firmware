#include "quantum.h"
#include "split_util.h"

void matrix_init_kb(void) {
    // 캡스락 LED는 왼쪽 보드에만 물리적으로 존재함.
    // 오른쪽 보드는 같은 핀(D6)을 엔코더 pin_b로 사용하므로,
    // 오른쪽에서 OUTPUT으로 설정하면 회전 감지가 깨짐 -> 왼쪽에서만 초기화.
    if (is_keyboard_left()) {
        gpio_set_pin_output(LED_CAPS_LOCK_PIN);
    }
    matrix_init_user();
}

bool led_update_kb(led_t led_state) {
    if (is_keyboard_left()) {
        gpio_write_pin(LED_CAPS_LOCK_PIN, !led_state.caps_lock);
    }
    return true;
}

void eeconfig_init_kb(void) {
#ifdef BACKLIGHT_ENABLE
    backlight_enable();
    backlight_level(3);
#endif

    eeconfig_update_kb(0);
    eeconfig_init_user();
}


// encoder_update_kb는 keymap.c의 encoder_update_user에서 처리
