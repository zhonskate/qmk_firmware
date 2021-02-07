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

#define _________________QWERTY_L1_________________        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T
#define _________________QWERTY_L2_________________        KC_A,    KC_S,    KC_D,    KC_F,    KC_G
#define _________________QWERTY_L3_________________        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B

#define _________________QWERTY_R1_________________        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P
#define _________________QWERTY_R2_________________        KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN
#define _________________QWERTY_R3_________________        KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLASH


#define _________________GAMEPAD_L1________________        KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R
#define _________________GAMEPAD_L2________________        KC_LSFT, KC_A,    KC_S,    KC_D,    KC_F
#define _________________GAMEPAD_L3________________        KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_V


#define _________________COLEMAK_L1________________       KC_Q,    KC_W,    KC_F,    KC_P,    KC_G
#define _________________COLEMAK_L2________________       KC_A,    KC_R,    KC_S,    KC_T,    KC_D
#define _________________COLEMAK_L3________________       KC_Z,    KC_X,    KC_C,    KC_V,    KC_B

#define _________________COLEMAK_R1________________       KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN
#define _________________COLEMAK_R2________________       KC_H,    KC_N,    KC_E,    KC_I,    KC_O
#define _________________COLEMAK_R3________________       KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLASH


#define ______________COLEMAK_MOD_DH_L1____________       KC_Q,    KC_W,    KC_F,    KC_P,    KC_B
#define ______________COLEMAK_MOD_DH_L2____________       KC_A,    KC_R,    KC_S,    KC_T,    KC_G
#define ______________COLEMAK_MOD_DH_L3____________       KC_Z,    KC_X,    KC_C,    KC_D,    KC_V

#define ______________COLEMAK_MOD_DH_R1____________       KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN
#define ______________COLEMAK_MOD_DH_R2____________       KC_M,    KC_N,    KC_E,    KC_I,    KC_O
#define ______________COLEMAK_MOD_DH_R3____________       KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLASH


#define _________________DVORAK_L1_________________       KC_QUOT, KC_COMM, KC_DOT, KC_P,     KC_Y
#define _________________DVORAK_L2_________________       KC_A,    KC_O,    KC_E,   KC_U,     KC_I
#define _________________DVORAK_L3_________________       KC_SCLN, KC_Q,    KC_J,   KC_K,     KC_X

#define _________________DVORAK_R1_________________       KC_F,    KC_G,    KC_C,    KC_R,    KC_L
#define _________________DVORAK_R2_________________       KC_D,    KC_H,    KC_T,    KC_N,    KC_S
#define _________________DVORAK_R3_________________       KC_B,    KC_M,    KC_W,    KC_V,    KC_Z


#define _________________WORKMAN_L1________________       KC_Q,    KC_D,    KC_R,   KC_W,     KC_B
#define _________________WORKMAN_L2________________       KC_A,    KC_S,    KC_H,   KC_T,     KC_G
#define _________________WORKMAN_L3________________       KC_Z,    KC_X,    KC_M,   KC_C,     KC_V

#define _________________WORKMAN_R1________________       KC_J,    KC_F,    KC_U,    KC_P,    KC_SCLN
#define _________________WORKMAN_R2________________       KC_Y,    KC_N,    KC_E,    KC_O,    KC_I
#define _________________WORKMAN_R3________________       KC_K,    KC_L,    KC_COMM, KC_DOT,  KC_SLASH


#define _________________NORMAN_L1_________________       KC_Q,    KC_W,    KC_D,    KC_F,    KC_K
#define _________________NORMAN_L2_________________       KC_A,    KC_S,    KC_E,    KC_T,    KC_G
#define _________________NORMAN_L3_________________       KC_Z,    KC_X,    KC_C,    KC_V,    KC_B

#define _________________NORMAN_R1_________________       KC_J,    KC_U,    KC_R,    KC_L,    KC_SCLN
#define _________________NORMAN_R2_________________       KC_Y,    KC_N,    KC_I,    KC_O,    KC_U
#define _________________NORMAN_R3_________________       KC_P,    KC_M,    KC_COMM, KC_DOT,  KC_SLASH

/*
 * Layout Components
*/

#define ___________________BLANK___________________       _______, _______, _______, _______, _______
#define ________________NUMBER_LEFT________________       KC_1,    KC_2,    KC_3,    KC_4,    KC_5
#define ________________NUMBER_RIGHT_______________       KC_6,    KC_7,    KC_8,    KC_9,    KC_0
#define _________________FUNC_LEFT_________________       KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5
#define _________________FUNC_RIGHT________________       KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10

#define ________________VIM_ARROWS_________________       KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, _______

#define __________________NAV_L1___________________       _______, KC_PGUP, KC_LEFT, KC_UP,   KC_RIGHT
#define __________________NAV_L2___________________       _______, KC_PGDN, KC_HOME, KC_DOWN, KC_END
#define __________________NAV_R1___________________       KC_PGUP, KC_LEFT, KC_UP,   KC_RIGHT, _______
#define __________________NAV_R2___________________       KC_PGDN, KC_HOME, KC_DOWN, KC_END,   _______

/*
 * Layers
*/

#define _________________LOWER_L1__________________       KC_HASH, KC_DLR,  KC_LCBR, KC_RCBR, KC_PIPE
#define _________________LOWER_L2__________________       KC_EXLM, KC_AT,   KC_LPRN, KC_RPRN, KC_GRV
#define _________________LOWER_L3__________________       KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD

#define _________________LOWER_R1__________________       ___________________BLANK___________________
#define _________________LOWER_R2__________________       __________________NAV_R1___________________
#define _________________LOWER_R3__________________       __________________NAV_R2___________________


#define _________________RAISE_L1__________________       ________________NUMBER_LEFT________________
#define _________________RAISE_L2__________________       _______, KC_MPRV, KC_MPLY, KC_MNXT, KC_VOLU
#define _________________RAISE_L3__________________       _______, _______, _______, KC_MUTE, KC_VOLD

#define _________________RAISE_R1__________________       ________________NUMBER_RIGHT_______________
#define _________________RAISE_R2__________________       KC_MINS, KC_PLUS, KC_ASTR, KC_SLSH, KC_PERC
#define _________________RAISE_R3__________________       KC_AMPR, KC_PIPE, KC_COMM, KC_DOT,  KC_SLSH


#define _________________ADJUST_L1_________________       _________________FUNC_LEFT_________________
#define _________________ADJUST_L2_________________       RGB_TOG, RGB_SAI, RGB_VAI, RGB_HUI, RGB_MOD
#define _________________ADJUST_L3_________________       MU_TOG,  RGB_SAD, RGB_VAD, RGB_HUD, RGB_RMOD

#define _________________ADJUST_R1_________________       _________________FUNC_RIGHT________________
#define _________________ADJUST_R2_________________       RESET,   KC_MAKE, VRSN,    KC_F11,  KC_F12
#define _________________ADJUST_R3_________________       QWERTY,  COLEMAK, WORKMAN, NORMAN,  DVORAK

// clang-format on
