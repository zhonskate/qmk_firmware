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
