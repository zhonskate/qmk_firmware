#include QMK_KEYBOARD_H

#ifdef PROTOCOL_LUFA
#    include "lufa.h"
#    include "split_util.h"
#endif
#ifdef SSD1306OLED
#    include "ssd1306.h"
#endif

enum layers {
    _QWERTY = 0,
    _LOWER,
    _RAISE
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Base Layer: QWERTY */

 [_QWERTY] = LAYOUT( \
  KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV, \
  KC_ESC,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS, \
  KC_LSFT,  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, MT(MOD_RSFT, KC_QUOT), \
  KC_LCTL,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,    KC_EQL,  KC_EQL,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, MT(MOD_RCTL, KC_MINS), \
      KC_LGUI, KC_LALT, LT(_LOWER, KC_SPC), LT(_RAISE, KC_TAB),  LT(_RAISE, KC_ENT),   LT(_LOWER, KC_BSPC),   KC_DEL, KC_EQL \
),
/* Lower Layer: Symbols, Navigation */
[_LOWER] = LAYOUT( \
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, KC_TILD,\
  _______, KC_HASH, KC_DLR,  KC_LCBR, KC_RCBR, KC_PIPE,                   _______, _______, _______, _______, _______, KC_PIPE, \
  _______, KC_EXLM, KC_AT,   KC_LPRN, KC_RPRN, XXXXXXX,                   KC_PGUP, KC_LEFT, KC_UP,   KC_RGHT, _______, KC_QUOT, \
  _______, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, XXXXXXX, _______, _______, KC_PGDN, KC_HOME, KC_DOWN, KC_END,  _______, KC_MINS, \
                             _______, _______, _______, _______, _______, _______, _______, _______\
),
/* Raise Layer: Number keys, media, more symbols */

[_RAISE] = LAYOUT( \
  KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                       KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11, \
  _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______, \
  _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, KC_VOLU,                     KC_MINS, KC_PLUS, KC_ASTR, KC_SLSH, KC_PERC, _______, \
  _______, _______, _______, _______, KC_MUTE, KC_VOLD,  _______, _______,  KC_AMPR, KC_PIPE, KC_COMM, KC_DOT,  KC_SLSH, _______, \
                             _______, _______, _______,  _______, _______,  _______, _______, _______ \
),
};
// clang-format on
