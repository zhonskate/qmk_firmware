#include QMK_KEYBOARD_H

#define _QWERTY 0
#define _LOWER 3
#define _RAISE 4
#define _ADJUST 16

#define ESC_RAISE LT(_RAISE, KC_ESC)
#define BSLS_RAISE LT(_RAISE, KC_BSLS)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer: QWERTY
*/
    [_QWERTY] = LAYOUT( \
      ESC_RAISE,    KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_LPRN,            KC_RPRN,    KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,       BSLS_RAISE, \
      KC_LSFT,      KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_LBRC,            KC_RBRC,    KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,    MT(MOD_LSFT, KC_QUOT), \
      KC_LCTL,      KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   MO(_ADJUST),    MO(_ADJUST),     KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,    MT(MOD_RCTL, KC_MINS), \
            KC_LALT,    LT(_LOWER, KC_SPC), LT(_RAISE, KC_TAB), KC_LGUI,    KC_EQL, LT(_RAISE, KC_ENT), LT(_LOWER, KC_BSPC),    KC_DEL \
    ), \
/*
 * Lower Layer: Symbols, Navigation
 */
    [_LOWER] = LAYOUT( \
      _______, KC_HASH, KC_DLR,  KC_LCBR, KC_RCBR, KC_PIPE, _______,            _______, _______, _______, _______, _______, _______, KC_PIPE, \
      _______, KC_EXLM, KC_AT,   KC_LPRN, KC_RPRN, KC_GRV,  _______,            _______, KC_PGUP, KC_LEFT, KC_UP,   KC_RGHT, _______, KC_QUOT, \
      _______, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD, _______,            _______, KC_PGDN, KC_HOME, KC_DOWN, KC_END,  _______, KC_MINS, \
                                 _______, _______, KC_SCLN, KC_EQL,             KC_EQL,  KC_SCLN, _______, _______ \
    ), \
/*
 * Raise Layer: Number keys, media, more symbols
 */
    [_RAISE] = LAYOUT( \
      _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    _______,            _______, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______, \
      _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, KC_VOLU, _______,            _______, XXXXXXX, KC_PLUS, KC_ASTR, KC_SLSH, KC_PERC, _______, \
      _______, _______, _______, _______, KC_MUTE, KC_VOLD, _______,            _______, XXXXXXX, KC_PIPE, KC_COMM, KC_DOT,  KC_SLSH, _______, \
                                 _______, _______, _______, _______,            _______, _______, _______, _______ \
    ), \
/*
 * Adjust Layer: Function keys, RGB
 */
    [_ADJUST] = LAYOUT( \
      _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______,            _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______, \
      _______, _______, _______, _______, _______, _______, _______,            _______, _______, _______, _______, KC_F11,  KC_F12,  _______, \
      _______, _______, _______, _______, _______, _______, _______,            _______, _______, _______, _______, _______, _______, _______, \
                                 _______, _______, _______, _______,            _______, _______, _______, _______ \
    ) \
};
// clang-format on


layer_state_t layer_state_set_user(layer_state_t state) { return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST); }
