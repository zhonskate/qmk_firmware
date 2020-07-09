#include QMK_KEYBOARD_H

enum layer_names { _BASE, _LOWER, _RAISE, _ADJUST };

enum custom_keycodes { KC_SONG = SAFE_RANGE };

#define LOWER LT(_LOWER, KC_SPC)
#define RAISE LT(_RAISE, KC_BSPC)
#define ADJUST MO(_ADJUST)

#define RAI_TAB LT(_RAISE, KC_TAB)
#define RAI_BSLS LT(_RAISE, KC_BSLS)

#define SFT_A MT(MOD_LSFT, KC_A)
#define SFT_CLN MT(MOD_RSFT, KC_SCLN)

#define CTL_Z MT(MOD_LCTL, KC_Z)
#define CTL_SL MT(MOD_RCTL, KC_SLSH)

#define ALT_X MT(MOD_LALT, KC_X)
#define ALT_DOT MT(MOD_RALT, KC_DOT)

#define GUI_C MT(MOD_LGUI, KC_C)
#define GUI_COM MT(MOD_RGUI, KC_COMM)

// clang-format off
#define NIER_SONG_OF_THE_ANCIENTS \
    H__NOTE(_D6), H__NOTE(_EF6), B__NOTE(_EF6), H__NOTE(_EF6), H__NOTE(_D6), H__NOTE(_BF5), H__NOTE(_G5), BD_NOTE(_C6), H__NOTE(_D6), \
    H__NOTE(_EF6), B__NOTE(_EF6), H__NOTE(_EF6), H__NOTE(_D6), H__NOTE(_BF5), H__NOTE(_G5), BD_NOTE(_G6), H__NOTE(_G5), H__NOTE(_AF5), \
    B__NOTE(_G6), H__NOTE(_AF6), H__NOTE(_G6), H__NOTE(_F6), H__NOTE(_D6), H__NOTE(_D6), H__NOTE(_EF6), B__NOTE(_EF6), WD_NOTE(_G5), \
    WD_NOTE(_BF5), H__NOTE(_D6), H__NOTE(_EF6), B__NOTE(_EF6), H__NOTE(_EF6), H__NOTE(_D6), H__NOTE(_BF5), H__NOTE(_G5), BD_NOTE(_C6), \
    WD_NOTE(_B5), WD_NOTE(_G5), WD_NOTE(_G6), W__NOTE(_G6), H__NOTE(_AF6), W__NOTE(_G6), H__NOTE(_AF6), H__NOTE(_G6), H__NOTE(_F6), \
    H__NOTE(_D6), H__NOTE(_D6), H__NOTE(_EF6), B__NOTE(_EF6), WD_NOTE(_E6), H__NOTE(_E6), H__NOTE(_F6), H__NOTE(_G6), H__NOTE(_BF6), \
    H__NOTE(_AF6), W__NOTE(_AF6), H__NOTE(_C6), H__NOTE(_BF6), H__NOTE(_AF6), W__NOTE(_AF6), H__NOTE(_C6), H__NOTE(_AF6), BD_NOTE(_G6), \
    WD_NOTE(_B5), WD_NOTE(_G6), W__NOTE(_G6), H__NOTE(_AF6), W__NOTE(_G6), H__NOTE(_AF6), H__NOTE(_G6), H__NOTE(_F6), H__NOTE(_D6), \
    H__NOTE(_D6), H__NOTE(_EF6), B__NOTE(_EF6), WD_NOTE(_E6), H__NOTE(_E6), H__NOTE(_F6), H__NOTE(_G6), H__NOTE(_BF6), H__NOTE(_AF6), \
    W__NOTE(_AF6), H__NOTE(_C6), H__NOTE(_AF6), H__NOTE(_G6), W__NOTE(_G6), H__NOTE(_F6), H__NOTE(_D6), BD_NOTE(_EF6), WD_NOTE(_F6), \
    WD_NOTE(_G6), BD_NOTE(_C7)
// clang-format on

float nier_song[][2] = SONG(NIER_SONG_OF_THE_ANCIENTS);

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_reviung39(
    RAI_TAB,  KC_Q,     KC_W,     KC_E,     KC_R,      KC_T,               KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     RAI_BSLS,
    KC_LSFT,  SFT_A,    KC_S,     KC_D,     KC_F,      KC_G,               KC_H,     KC_J,     KC_K,     KC_L,     SFT_CLN,  KC_QUOT,
    KC_LCTL,  CTL_Z,    ALT_X,    GUI_C,    KC_V,      KC_B,               KC_N,     KC_M,     GUI_COM,  ALT_DOT,  CTL_SL,   KC_MINS,
                                                       LOWER,    KC_ENT,   RAISE
  ),

  [_LOWER] = LAYOUT_reviung39(
    KC_ESC,   KC_HASH,  KC_DLR,   KC_LCBR,  KC_RCBR,   KC_PIPE,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_PIPE,
    _______,  KC_EXLM,  KC_AT,    KC_LPRN,  KC_RPRN,   KC_GRV,             KC_MINS,  KC_PLUS,  KC_ASTR,  KC_SLSH,  KC_PERC,  KC_QUOT,
    _______,  KC_PERC,  KC_CIRC,  KC_LBRC,  KC_RBRC,   KC_TILD,            KC_AMPR,  KC_PIPE,  KC_COMM,  KC_DOT,   KC_SLSH,  KC_MINS,
                                                       _______,  KC_DEL,   _______
  ),

  [_RAISE] = LAYOUT_reviung39(
    _______,  KC_1,     KC_2,     KC_3,     KC_4,      KC_5,               KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     _______,
    _______,  XXXXXXX,  KC_MPRV,  KC_MPLY,  KC_MNXT,   KC_VOLU,            KC_PGUP,  KC_LEFT,  KC_UP,    KC_RGHT,  _______,  _______,
    _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_MUTE,   KC_VOLD,            KC_PGDN,  KC_HOME,  KC_DOWN,  KC_END,   _______,  KC_EQL,
                                                       _______,  KC_TAB,   _______
  ),

  [_ADJUST] = LAYOUT_reviung39(
    XXXXXXX,  KC_F1,    KC_F2,    KC_F3,    KC_F4,     KC_F5,              KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   XXXXXXX,
    XXXXXXX,  RGB_TOG,  RGB_HUI,  RGB_VAI,  RGB_MOD,   AU_TOG,             MU_TOG,   XXXXXXX,  XXXXXXX,  KC_F11,   KC_F12,   XXXXXXX,
    XXXXXXX,  XXXXXXX,  RGB_HUD,  RGB_VAD,  RGB_RMOD,  CK_TOGG,            MU_MOD,   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_SONG,
                                                       _______,  RESET,    _______
  ),
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) { return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST); }

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef AUDIO_ENABLE
    switch (keycode) {
        case KC_SONG:
            if (record->event.pressed) {
                PLAY_SONG(nier_song);
            }
            return false;
    }
#endif
    return true;
}
