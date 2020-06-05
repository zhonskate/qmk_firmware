#include QMK_KEYBOARD_H

// Define a custom keycode for switching encoder direction
enum custom_keycodes {
    ENC_MODE = SAFE_RANGE
};

// Flag to indicate encoder direction
bool encoder_vertical = false;

// Keymap
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
        [0] = LAYOUT(
            KC_C,       ENC_MODE,   LALT(KC_WH_U),
            LCTL(KC_X), KC_SPC,     LALT(KC_WH_D),
            LCTL(KC_V), KC_ENT,     LT(1,KC_D)
        ),
        [1] = LAYOUT(
            BL_TOGG,    KC_TRNS,    BL_BRTG,
            BL_INC,     BL_DEC,     BL_STEP,
            BL_ON,      BL_OFF,     KC_TRNS
        )
};

// Define what encoder does depending on direction flag.
void encoder_update_user(uint8_t index, bool clockwise) {
    if (clockwise) {
        if (encoder_vertical) {
            tap_code(KC_DOWN);
        } else {
            tap_code(KC_RIGHT);
        }
    } else {
        if (encoder_vertical) {
            tap_code(KC_UP);
        } else {
            tap_code(KC_LEFT);
        }
    }
}

// When custom keycode ENC_MODE is clicked, switch encoder direction
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case ENC_MODE:
      if (record->event.pressed) {
          encoder_vertical = true;
      }
      return false; // Skip all further processing of this key
    default:
      return true; // Process all other keycodes normally
  }
}
