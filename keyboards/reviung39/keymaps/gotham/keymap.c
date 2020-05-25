/* Copyright 2019 gtips
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

enum layer_names {
    _BASE,
    _LOWER,
    _RAISE,
    _ADJUST
};

#define LOWER  LT(_LOWER, KC_SPC)
#define RAISE  LT(_RAISE, KC_BSPC)
#define ADJUST MO(_ADJUST)

#define SFT_A   MT(MOD_LSFT, KC_A)
#define SFT_CLN MT(MOD_RSFT, KC_SCLN)

#define CTL_Z   MT(MOD_LCTL, KC_Z)
#define CTL_SL  MT(MOD_RCTL, KC_SLSH)

#define ALT_X   MT(MOD_LALT, KC_X)
#define ALT_DOT MT(MOD_RALT, KC_DOT)

#define GUI_C   MT(MOD_LGUI, KC_C)
#define GUI_COM MT(MOD_RGUI, KC_COMM)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_reviung39(
    KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,      KC_T,               KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_PIPE,
    KC_LSFT,  KC_A,     KC_S,     KC_D,     KC_F,      KC_G,               KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,
    KC_LCTL,  CTL_Z,    ALT_X,    GUI_C,    KC_V,      KC_B,               KC_N,     KC_M,     GUI_COM,  ALT_DOT,  CTL_SL,   KC_MINS,
                                                       LOWER,    KC_ENT,   RAISE
  ),

  [_LOWER] = LAYOUT_reviung39(
    KC_ESC,   KC_HASH,  KC_DLR,   KC_LCBR,  KC_RCBR,   KC_PIPE,            _______,  _______,  _______,  _______,  _______,  KC_PIPE,
    _______,  KC_EXLM,  KC_AT,    KC_LPRN,  KC_RPRN,   KC_GRV,             KC_PGUP,  KC_LEFT,  KC_UP,    KC_RGHT,  _______,  KC_QUOT,
    _______,  KC_PERC,  KC_CIRC,  KC_LBRC,  KC_RBRC,   KC_TILD,            KC_PGDN,  KC_HOME,  KC_DOWN,  KC_END,   _______,  KC_MINS,
                                                       _______,  KC_DEL,   _______
  ),

  [_RAISE] = LAYOUT_reviung39(
    KC_ESC,   KC_1,     KC_2,     KC_3,     KC_4,      KC_5,               KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     _______,
    _______,  _______,  KC_MPRV,  KC_MPLY,  KC_MNXT,   KC_VOLU,            KC_MINS,  KC_PLUS,  KC_ASTR,  KC_SLSH,  KC_PERC,  _______,
    _______,  _______,  _______,  _______,  KC_MUTE,   KC_VOLD,            KC_AMPR,  KC_PIPE,  KC_COMM,  KC_DOT,   KC_SLSH,  _______,
                                                       _______,  KC_TAB,   _______
  ),

  [_ADJUST] = LAYOUT_reviung39(
    _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,     KC_F5,              KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   _______,
    _______,  RGB_TOG,  RGB_HUI,  RGB_VAI,  RGB_MOD,   _______,            _______,  _______,  _______,  KC_F11,   KC_F12,   _______,
    _______,  _______,  RGB_HUD,  RGB_VAD,  RGB_RMOD,  _______,            RESET,    _______,  _______,  _______,  _______,  _______,
                                                       _______,  XXXXXXX,  _______
  ),
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
