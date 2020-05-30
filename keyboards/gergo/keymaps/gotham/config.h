#pragma once

#ifdef MOUSEKEY_INTERVAL
#    undef MOUSEKEY_INTERVAL
#    define MOUSEKEY_INTERVAL 10
#endif

#ifdef MOUSEKEY_TIME_TO_MAX
#    undef MOUSEKEY_TIME_TO_MAX
#    define MOUSEKEY_TIME_TO_MAX 30
#endif

#define OLED_FONT_H "keyboards/gergo/keymaps/gotham/glcdfont.c"

#define IGNORE_MOD_TAP_INTERRUPT

// #define ADC_CHANNEL11               ((1 << 8) | (0x03 << MUX0))
// #define ADC_CHANNEL12               ((1 << 8) | (0x04 << MUX0))

#ifdef THUMBSTICK_ENABLE
#    define THUMBSTICK_FLIP_X
#    define THUMBSTICK_PIN_X 25
#    define THUMBSTICK_PIN_Y 26
#    define THUMBSTICK_DEBUG
#endif
