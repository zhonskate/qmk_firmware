#pragma once

// Reduce firmware size
#define NO_ACTION_MACRO
#define NO_ACTION_ONESHOT

#define TAPPING_TERM 180
#define IGNORE_MOD_TAP_INTERRUPT

#ifdef AUDIO_ENABLE
#    define B6_AUDIO
#    define AUDIO_CLICKY
#endif

#define RGB_DI_PIN D3
#ifdef RGB_DI_PIN
#    define RGBLED_NUM 11
#    define RGBLIGHT_HUE_STEP 16
#    define RGBLIGHT_SAT_STEP 16
#    define RGBLIGHT_VAL_STEP 16
#    define RGBLIGHT_LIMIT_VAL 255
#    define RGBLIGHT_SLEEP
#    define RGBLIGHT_EFFECT_BREATHING
#    define RGBLIGHT_EFFECT_RAINBOW_MOOD
#    define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#    define RGBLIGHT_EFFECT_KNIGHT
#endif
