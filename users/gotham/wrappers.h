/* Copyright 2020 Gautham Yerroju <gautham.yerroju@gmail.com>
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

/*
Since our quirky block definitions are basically a list of comma separated
arguments, we need a wrapper in order for these definitions to be
expanded before being used as arguments to the LAYOUT_xxx macro.
*/
// clang-format off
#define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)

/*
Blocks for each of the four major keyboard layouts
Organized so we can quickly adapt and modify all of them
at once, rather than for each keyboard, one at a time.
And this allows for much cleaner blocks in the keymaps.
For instance Tap/Hold for Control on all of the layouts
*/

/*
 * Keyboard Layouts
*/

#define _________________QWERTY_L1_________________ KC_Q,    KC_W,    KC_E,    KC_R,    KC_T
#define _________________QWERTY_L2_________________ KC_A,    KC_S,    KC_D,    KC_F,    KC_G
#define _________________QWERTY_L3_________________ KC_Z,    KC_X,    KC_C,    KC_V,    KC_B

#define _________________QWERTY_R1_________________ KC_Y,    KC_U,    KC_I,    KC_O,    KC_P
#define _________________QWERTY_R2_________________ KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN
#define _________________QWERTY_R3_________________ KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLASH


#define _________________COLEMAK_L1________________ KC_Q,    KC_W,    KC_F,    KC_P,    KC_G
#define _________________COLEMAK_L2________________ KC_A,    KC_R,    KC_S,    KC_T,    KC_D
#define _________________COLEMAK_L3________________ KC_Z,    KC_X,    KC_C,    KC_V,    KC_B

#define _________________COLEMAK_R1________________ KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN
#define _________________COLEMAK_R2________________ KC_H,    KC_N,    KC_E,    KC_I,    KC_O
#define _________________COLEMAK_R3________________ KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLASH


#define ______________COLEMAK_MOD_DH_L1____________ KC_Q,    KC_W,    KC_F,    KC_P,    KC_B
#define ______________COLEMAK_MOD_DH_L2____________ KC_A,    KC_R,    KC_S,    KC_T,    KC_G
#define ______________COLEMAK_MOD_DH_L3____________ KC_Z,    KC_X,    KC_C,    KC_D,    KC_V

#define ______________COLEMAK_MOD_DH_R1____________ KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN
#define ______________COLEMAK_MOD_DH_R2____________ KC_K,    KC_N,    KC_E,    KC_I,    KC_O
#define ______________COLEMAK_MOD_DH_R3____________ KC_M,    KC_H,    KC_COMM, KC_DOT,  KC_SLASH


#define _____________COLEMAK_MOD_DHM_L1____________ KC_Q,    KC_W,    KC_F,    KC_P,    KC_B
#define _____________COLEMAK_MOD_DHM_L2____________ KC_A,    KC_R,    KC_S,    KC_T,    KC_G
#define _____________COLEMAK_MOD_DHM_L3____________ KC_Z,    KC_X,    KC_C,    KC_D,    KC_V

#define _____________COLEMAK_MOD_DHM_R1____________ KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN
#define _____________COLEMAK_MOD_DHM_R2____________ KC_M,    KC_N,    KC_E,    KC_I,    KC_O
#define _____________COLEMAK_MOD_DHM_R3____________ KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLASH


#define _________________DVORAK_L1_________________ KC_QUOT, KC_COMM, KC_DOT, KC_P,     KC_Y
#define _________________DVORAK_L2_________________ KC_A,    KC_O,    KC_E,   KC_U,     KC_I
#define _________________DVORAK_L3_________________ KC_SCLN, KC_Q,    KC_J,   KC_K,     KC_X

#define _________________DVORAK_R1_________________ KC_F,    KC_G,    KC_C,    KC_R,    KC_L
#define _________________DVORAK_R2_________________ KC_D,    KC_H,    KC_T,    KC_N,    KC_S
#define _________________DVORAK_R3_________________ KC_B,    KC_M,    KC_W,    KC_V,    KC_Z


#define _________________WORKMAN_L1________________ KC_Q,    KC_D,    KC_R,   KC_W,     KC_B
#define _________________WORKMAN_L2________________ KC_A,    KC_S,    KC_H,   KC_T,     KC_G
#define _________________WORKMAN_L3________________ KC_Z,    KC_X,    KC_M,   KC_C,     KC_V

#define _________________WORKMAN_R1________________ KC_J,    KC_F,    KC_U,    KC_P,    KC_SCLN
#define _________________WORKMAN_R2________________ KC_Y,    KC_N,    KC_E,    KC_O,    KC_I
#define _________________WORKMAN_R3________________ KC_K,    KC_L,    KC_COMM, KC_DOT,  KC_SLASH


#define _________________NORMAN_L1_________________ KC_Q,    KC_W,    KC_D,    KC_F,    KC_K
#define _________________NORMAN_L2_________________ KC_A,    KC_S,    KC_E,    KC_T,    KC_G
#define _________________NORMAN_L3_________________ KC_Z,    KC_X,    KC_C,    KC_V,    KC_B

#define _________________NORMAN_R1_________________ KC_J,    KC_U,    KC_R,    KC_L,    KC_SCLN
#define _________________NORMAN_R2_________________ KC_Y,    KC_N,    KC_I,    KC_O,    KC_H
#define _________________NORMAN_R3_________________ KC_P,    KC_M,    KC_COMM, KC_DOT,  KC_SLASH

/*
 * Layout Components
*/

#define ___________________BLANK___________________ _______, _______, _______, _______, _______
#define ___________________KC_NO___________________ KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO
#define ________________NUMBER_LEFT________________ KC_1,    KC_2,    KC_3,    KC_4,    KC_5
#define ________________NUMBER_RIGHT_______________ KC_6,    KC_7,    KC_8,    KC_9,    KC_0
#define __________________FN_LEFT__________________ KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5
#define __________________FN_RIGHT_________________ KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10

#define __________________NUMPAD_1_________________ KC_NO,   KC_1,    KC_2,    KC_3,    KC_NO
#define __________________NUMPAD_2_________________ KC_0,    KC_4,    KC_5,    KC_6,    KC_0
#define __________________NUMPAD_3_________________ KC_NO,   KC_7,    KC_8,    KC_9,    KC_NO
#define __________________FN_PAD_1_________________ KC_F10,  KC_F1,   KC_F2,   KC_F3,   KC_NO
#define __________________FN_PAD_2_________________ KC_F11,  KC_F4,   KC_F5,   KC_F6,   KC_NO
#define __________________FN_PAD_3_________________ KC_F12,  KC_F7,   KC_F8,   KC_F9,   KC_NO

#define ________________VIM_ARROWS_________________ KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, _______

#define ___________________NAV1____________________ KC_PGUP, KC_LEFT, KC_UP,   KC_RIGHT, _______
#define ___________________NAV2____________________ KC_PGDN, KC_HOME, KC_DOWN, KC_END,   _______

#define __________________MOUSE1___________________ KC_NO,   KC_BTN4, KC_BTN3, KC_BTN5, KC_NO
#define __________________MOUSE2___________________ KC_WH_U, KC_MS_L, KC_MS_U, KC_MS_R, KC_WH_U
#define __________________MOUSE3___________________ KC_WH_D, KC_BTN1, KC_MS_D, KC_BTN2, KC_WH_D

/*
 * Game Mode Components
*/

#define __________________GAME_L1__________________ KC_T,    KC_Q,    KC_W,    KC_E,    KC_R
#define __________________GAME_L2__________________ KC_G,    KC_A,    KC_S,    KC_D,    KC_F
#define __________________GAME_L3__________________ KC_B,    KC_Z,    KC_X,    KC_C,    KC_V

#define __________________GAME_R1__________________ _________________QWERTY_R1_________________
#define __________________GAME_R2__________________ _________________QWERTY_R2_________________
#define __________________GAME_R3__________________ _________________QWERTY_R3_________________

#define _________________GAMENUM_L1________________ __________________NUMPAD_1_________________
#define _________________GAMENUM_L2________________ KC_0,    KC_4,    KC_5,    KC_6,    TG_GAME
#define _________________GAMENUM_L3________________ __________________NUMPAD_3_________________

#define _________________GAMENUM_R1________________ __________________FN_PAD_1_________________
#define _________________GAMENUM_R2________________ __________________FN_PAD_2_________________
#define _________________GAMENUM_R3________________ __________________FN_PAD_3_________________

#define _________________GAMENAV_1_________________ _______, _______, KC_UP,   _______, _______
#define _________________GAMENAV_2_________________ _______, KC_LEFT, KC_DOWN, KC_RIGHT,_______

/*
 * Layers
*/

#define _________________LOWER_L1__________________ KC_HASH, KC_DLR,  KC_LCBR, KC_RCBR, KC_BSLS
#define _________________LOWER_L2__________________ KC_EXLM, KC_AT,   KC_LPRN, KC_RPRN, KC_GRV
#define _________________LOWER_L3__________________ KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD

#define _________________LOWER_R1__________________ KC_EXLM, KC_AMPR, KC_EQL,  KC_PIPE, KC_BSLS
#define _________________LOWER_R2__________________ KC_PLUS, KC_MINS, KC_ASTR, KC_PERC, KC_QUOT
#define _________________LOWER_R3__________________ KC_GRV,  KC_UNDS, KC_COMM, KC_DOT,  KC_SLSH


#define _________________RAISE_L1__________________ ________________NUMBER_LEFT________________
#define _________________RAISE_L2__________________ _______, _______, KC_VOLD, KC_VOLU, KC_MUTE
#define _________________RAISE_L3__________________ KC_PSCR, KC_SLCK, KC_BRK,  KC_INS,  _______

#define _________________RAISE_R1__________________ ________________NUMBER_RIGHT_______________
#define _________________RAISE_R2__________________ ___________________NAV1____________________
#define _________________RAISE_R3__________________ ___________________NAV2____________________


#define _________________ADJUST_L1_________________ __________________FN_LEFT__________________
#define _________________ADJUST_L2_________________ RGB_TOG, RGB_SAI, RGB_VAI, RGB_HUI, RGB_MOD
#define _________________ADJUST_L3_________________ MU_TOG,  RGB_SAD, RGB_VAD, RGB_HUD, CG_TOGG

#define _________________ADJUST_R1_________________ __________________FN_RIGHT_________________
#define _________________ADJUST_R2_________________ RESET,     KC_MAKE, VRSN,    KC_F11,  KC_F12
#define _________________ADJUST_R3_________________ KC_LAYOUT, CMB_TOG, _______, _______, _______


#define _________________MOUSE_L1__________________ ___________________KC_NO___________________
#define _________________MOUSE_L2__________________ KC_NO,   KC_NO,   KC_NO,   KC_NO,   TG_GAME
#define _________________MOUSE_L3__________________ ___________________KC_NO___________________

#define _________________MOUSE_R1__________________ __________________MOUSE1___________________
#define _________________MOUSE_R2__________________ __________________MOUSE2___________________
#define _________________MOUSE_R3__________________ __________________MOUSE3___________________
// clang-format on
