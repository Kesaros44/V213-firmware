#include QMK_KEYBOARD_H
#include "krsplit.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _WBASE 0
#define _MBASE 1
#define _WMFN1 2
#define _WMFN2 3  // Future Blank Keymap Layer

//enum encoder_names {
  //RIGHT_HALF_ENC = 0,
//};


// 한영키 코드 = KC_HAEN(VIA Keycode기준), KC_LNG1 (QMK Keycode기준) / 윈도우상 101키 레이아웃으로 설정 시 KC_RALT가 한영키로 동작함.

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_WBASE] = LAYOUT(
        KC_DEL,  KC_BSPC, KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                                      KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, KC_SCRL, KC_PAUS, 
        KC_NUM,  KC_PSLS, KC_PAST, KC_PMNS, KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,            KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_INS,  KC_HOME, KC_PGUP, 
        KC_P7,   KC_P8,   KC_P9,   KC_PPLS, KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,  KC_END,  KC_PGDN, 
        KC_P4,   KC_P5,   KC_P6,   KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                              KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,  
        KC_P1,   KC_P2,   KC_P3,   KC_PENT, KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                     KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,  
        KC_P0,   KC_PDOT, KC_LCTL, KC_LGUI, KC_LALT, KC_SPC,                                                       KC_SPC,  KC_RALT, MO(2),   KC_APP,  KC_RWIN, KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT  
    ),

    [_MBASE] = LAYOUT(
        KC_DEL,  KC_BSPC, KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                                      KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, KC_SCRL, KC_PAUS, 
        KC_NUM,  KC_PSLS, KC_PAST, KC_PMNS, KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,            KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_INS,  KC_HOME, KC_PGUP, 
        KC_P7,   KC_P8,   KC_P9,   KC_PPLS, KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,  KC_END,  KC_PGDN, 
        KC_P4,   KC_P5,   KC_P6,   KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                              KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,  
        KC_P1,   KC_P2,   KC_P3,   KC_PENT, KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                     KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,  
        KC_P0,   KC_PDOT, KC_LCTL, KC_LOPT, KC_LCMD, KC_SPC,                                                       KC_SPC,  KC_APP,  MO(2),   KC_RCMD, KC_ROPT, KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT  
    ),

    [_WMFN1] = LAYOUT(
        _______, _______, QK_RBT,  _______, _______, _______, _______, _______,                                    _______, _______, _______, _______, _______, _______, _______, _______, _______, QK_RBT, 
        _______, _______, _______, _______, KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC,         KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_UNDS, KC_PLUS, _______, BL_TOGG, BL_DOWN, BL_UP, 
        KC_HOME, KC_UP,   KC_PGUP, _______, _______, _______, _______, _______, _______, _______,                  _______, _______, _______, _______, _______, KC_LCBR, KC_RCBR, _______, _______, _______, _______, 
        KC_LEFT, _______, KC_RGHT, _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, KC_COLN, KC_DQUO, _______, 
        KC_END,  KC_DOWN, KC_PGDN, _______, _______, _______, _______, _______, _______, _______,                  _______, _______, _______, KC_LT,   KC_GT,   KC_QUES, _______, _______, 
        KC_INS,  KC_DEL,  _______, _______, _______, _______,                                                      _______,   TG(1), _______, _______, _______, _______, _______, _______, _______  
    ),

    [_WMFN2] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______,                                    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
        _______, _______, _______, _______, _______, _______, _______, _______, _______,                           _______, _______, _______, _______, _______, _______, _______, 
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                  _______, _______, _______, _______, _______, _______, _______, _______, 
        _______, _______, _______, _______, _______, _______,                                                      _______, _______, _______, _______, _______, _______, _______, _______, _______  
    )
};
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (get_highest_layer(layer_state) == _MBASE) {
        // Mac: Consumer keycodes for reliable media key handling
        if (clockwise) {
            register_code(KC_AUDIO_VOL_UP);
            unregister_code(KC_AUDIO_VOL_UP);
        } else {
            register_code(KC_AUDIO_VOL_DOWN);
            unregister_code(KC_AUDIO_VOL_DOWN);
        }
    } else {
        // Windows
        if (clockwise) {
            register_code(KC_VOLU);
            unregister_code(KC_VOLU);
        } else {
            register_code(KC_VOLD);
            unregister_code(KC_VOLD);
        }
    }
    return true;
}