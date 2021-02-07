#pragma once

#define IGNORE_MOD_TAP_INTERRUPT

#define TAP_CODE_DELAY 5
#define TAPPING_TERM 180

#ifdef COMBO_ENABLE
#    define COMBO_COUNT 11
#    define COMBO_TERM 140
#endif

#ifdef OLED_DRIVER_ENABLE
#    define OLED_TIMEOUT 0  // Disable built-in timeout
#    define OLED_CUSTOM_TIMEOUT 10000
#endif
