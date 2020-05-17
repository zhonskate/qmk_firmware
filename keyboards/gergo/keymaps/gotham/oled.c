#pragma once

#include <stdio.h>

static uint32_t oled_timer_elapsed = 0;
static uint32_t oled_timer = 0;
static bool oled_enabled = false;

// #define CODE_RAIN

#ifdef CODE_RAIN
#   define RAIN_STRING_LENGTH 10
static char rain_str[RAIN_STRING_LENGTH + 1] = {' '}; // init to spaces
static const char rain_chars[] = "abcdefghikjklmnopqrstuvwxyz1234567890!@^#$(){}[]`~-_<&|>+,*./;|日ﾊﾐﾋｰｳｼﾅﾓﾆｻﾜﾂｵﾘｱﾎﾃﾏｹﾒｴｶｷﾑﾕﾗｾﾈｽﾀﾇﾍｦｲｸｺｿﾁﾄﾉﾌﾔﾖﾙﾚﾛﾝｲｸﾁﾄﾉﾌﾍﾖﾙﾚﾛﾝ";
#endif

#ifdef WPM_ENABLE
static uint8_t wpm = 0;
#endif

// 5x1 Logos

// void render_sine1_raw(void) {
//     static const char PROGMEM font_logo[5][33] = {
//         {0x10, 0x08, 0x08, 0x04, 0x04, 0x04, 0x08, 0x08, 0x10, 0x10, 0x10, 0x08, 0x08, 0x04, 0x04, 0x04,
//         0x08, 0x08, 0x10, 0x10, 0x10, 0x08, 0x08, 0x04, 0x04, 0x04, 0x08, 0x08, 0x10, 0x10, 0x10, 0x08, 0},

//         {0x10, 0x10, 0x10, 0x08, 0x08, 0x04, 0x04, 0x04, 0x08, 0x08, 0x10, 0x10, 0x10, 0x08, 0x08, 0x04,
//         0x04, 0x04, 0x08, 0x08, 0x10, 0x10, 0x10, 0x08, 0x08, 0x04, 0x04, 0x04, 0x08, 0x08, 0x10, 0x10, 0},

//         {0x08, 0x08, 0x10, 0x10, 0x10, 0x08, 0x08, 0x04, 0x04, 0x04, 0x08, 0x08, 0x10, 0x10, 0x10, 0x08,
//         0x08, 0x04, 0x04, 0x04, 0x08, 0x08, 0x10, 0x10, 0x10, 0x08, 0x08, 0x04, 0x04, 0x04, 0x08, 0x08, 0},

//         {0x04, 0x04, 0x08, 0x08, 0x10, 0x10, 0x10, 0x08, 0x08, 0x04, 0x04, 0x04, 0x08, 0x08, 0x10, 0x10,
//         0x10, 0x08, 0x08, 0x04, 0x04, 0x04, 0x08, 0x08, 0x10, 0x10, 0x10, 0x08, 0x08, 0x04, 0x04, 0x04, 0},

//         {0x08, 0x04, 0x04, 0x04, 0x08, 0x08, 0x10, 0x10, 0x10, 0x08, 0x08, 0x04, 0x04, 0x04, 0x08, 0x08,
//         0x10, 0x10, 0x10, 0x08, 0x08, 0x04, 0x04, 0x04, 0x08, 0x08, 0x10, 0x10, 0x10, 0x08, 0x08, 0x04, 0},
//     };
//     uint32_t frame = timer_read32() % 500 / 100;
//     oled_write_raw_P(font_logo[frame], 32);
// };

// void render_sine2_raw(void) {
//     static const char PROGMEM font_logo[5][33] = {
//         {0x20, 0x20, 0x20, 0x10, 0x08, 0x04, 0x04, 0x04, 0x08, 0x10, 0x20, 0x20, 0x20, 0x10, 0x08, 0x04,
//         0x04, 0x04, 0x08, 0x10, 0x20, 0x20, 0x20, 0x10, 0x08, 0x04, 0x04, 0x04, 0x08, 0x10, 0x20, 0x20, 0},

//         {0x08, 0x10, 0x20, 0x20, 0x20, 0x10, 0x08, 0x04, 0x04, 0x04, 0x08, 0x10, 0x20, 0x20, 0x20, 0x10,
//         0x08, 0x04, 0x04, 0x04, 0x08, 0x10, 0x20, 0x20, 0x20, 0x10, 0x08, 0x04, 0x04, 0x04, 0x08, 0x10, 0},

//         {0x04, 0x04, 0x08, 0x10, 0x20, 0x20, 0x20, 0x10, 0x08, 0x04, 0x04, 0x04, 0x08, 0x10, 0x20, 0x20,
//         0x20, 0x10, 0x08, 0x04, 0x04, 0x04, 0x08, 0x10, 0x20, 0x20, 0x20, 0x10, 0x08, 0x04, 0x04, 0x04, 0},

//         {0x08, 0x04, 0x04, 0x04, 0x08, 0x10, 0x20, 0x20, 0x20, 0x10, 0x08, 0x04, 0x04, 0x04, 0x08, 0x10,
//         0x20, 0x20, 0x20, 0x10, 0x08, 0x04, 0x04, 0x04, 0x08, 0x10, 0x20, 0x20, 0x20, 0x10, 0x08, 0x04, 0},

//         {0x20, 0x10, 0x08, 0x04, 0x04, 0x04, 0x08, 0x10, 0x20, 0x20, 0x20, 0x10, 0x08, 0x04, 0x04, 0x04,
//         0x08, 0x10, 0x20, 0x20, 0x20, 0x10, 0x08, 0x04, 0x04, 0x04, 0x08, 0x10, 0x20, 0x20, 0x20, 0x10, 0},
//     };
//     uint32_t frame = timer_read32() % 500 / 100;
//     oled_write_raw_P(font_logo[frame], 32);
// };

// void render_sine3_raw(void) {
//     static const char PROGMEM font_logo[4][33] = {
//         {0x18, 0x04, 0x02, 0x02, 0x02, 0x04, 0x18, 0x20, 0x40, 0x40, 0x40, 0x20, 0x18, 0x04, 0x02, 0x02,
//         0x02, 0x04, 0x18, 0x20, 0x40, 0x40, 0x40, 0x20, 0x18, 0x04, 0x02, 0x02, 0x02, 0x04, 0x18, 0x20, 0},

//         {0x40, 0x40, 0x20, 0x18, 0x04, 0x02, 0x02, 0x02, 0x04, 0x18, 0x20, 0x40, 0x40, 0x40, 0x20, 0x18,
//         0x04, 0x02, 0x02, 0x02, 0x04, 0x18, 0x20, 0x40, 0x40, 0x40, 0x20, 0x18, 0x04, 0x02, 0x02, 0x02, 0},

//         {0x18, 0x20, 0x40, 0x40, 0x40, 0x20, 0x18, 0x04, 0x02, 0x02, 0x02, 0x04, 0x18, 0x20, 0x40, 0x40,
//         0x40, 0x20, 0x18, 0x04, 0x02, 0x02, 0x02, 0x04, 0x18, 0x20, 0x40, 0x40, 0x40, 0x20, 0x18, 0x04, 0},

//         {0x02, 0x02, 0x04, 0x18, 0x20, 0x40, 0x40, 0x40, 0x20, 0x18, 0x04, 0x02, 0x02, 0x02, 0x04, 0x18,
//         0x20, 0x40, 0x40, 0x40, 0x20, 0x18, 0x04, 0x02, 0x02, 0x02, 0x04, 0x18, 0x20, 0x40, 0x40, 0x40, 0},
//     };
//     uint32_t frame = timer_read32() % 300 / 75;
//     oled_write_raw_P(font_logo[frame], 32);
// };

// void render_sine_raw(void) {
//     uint8_t wpm = get_current_wpm();
//     if (wpm < 70) {
//         render_sine1();
//     } else if (wpm < 90) {
//         render_sine2();
//     } else {
//         render_sine3();
//     }
// };

void render_sine1(void) {
    static const char PROGMEM font_logo[5][6] = {
        {0x8f, 0x90, 0x91, 0x92, 0x93, 0x00},
        {0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0x00},
        {0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0x00},
        {0x94, 0x95, 0x96, 0x97, 0x98, 0x00},
        {0xb4, 0xb5, 0xb6, 0xb7, 0xb8, 0x00},
    };
    uint32_t frame = timer_read32() % 500 / 100;
    oled_write_P(font_logo[frame], false);
};

void render_sine2(void) {
    static const char PROGMEM font_logo[5][6] = {
        {0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0x00},
        {0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0x00},
        {0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x00},
        {0xaa, 0xab, 0xac, 0xad, 0xae, 0x00},
        {0xca, 0xcb, 0xcc, 0xcd, 0xce, 0x00},
    };
    uint32_t frame = timer_read32() % 500 / 100;
    oled_write_P(font_logo[frame], false);
};

void render_sine3(void) {
    static const char PROGMEM font_logo[4][6] = {
        {0x80, 0x81, 0x82, 0x83, 0x84, 0x00},
        {0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0x00},
        {0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0x00},
        {0x85, 0x86, 0x87, 0x88, 0x89, 0x00},
    };
    uint32_t frame = timer_read32() % 300 / 75;
    oled_write_P(font_logo[frame], false);
};

void render_sine(void) {
#ifdef WPM_ENABLE
    wpm = get_current_wpm();
    if (wpm < 70) {
        render_sine1();
    } else if (wpm < 90) {
        render_sine2();
    } else {
        render_sine3();
    }
#else
    if (oled_timer_elapsed < 2000) {
        render_sine3();
    } else if (oled_timer_elapsed < 5000) {
        render_sine2();
    } else {
        render_sine1();
    }
#endif
};

#ifdef WPM_ENABLE
void render_wpm(void) {
    char wpm_str[5] = "";
    snprintf(wpm_str, sizeof(wpm_str), "WPM:\n%5u", wpm);
    oled_write_ln(wpm_str, false);
};
#endif

#ifdef CODE_RAIN
void render_code_rain(void) {
    oled_write(rain_str, false);
    for(uint8_t i = (RAIN_STRING_LENGTH - 1); i > 0; i--) {
        rain_str[i] = rain_str[i - 1];
    }
    for(uint8_t i = 0; i < 1; ++i) {
        rain_str[i] = rain_chars[rand() % 123];
    }
}
#endif

// 5x2 Mod and feature indicator clusters

void render_mod_status(void) {
    // 2x1 Ctrl, Alt, Shift, GUI, Mouse
    static const char PROGMEM font_ctrl[3] = {0x99, 0x9a, 0};
    static const char PROGMEM font_alt[3] = {0xb9, 0xba, 0};
    static const char PROGMEM font_shift[3] = {0xbb, 0xbc, 0};
    static const char PROGMEM font_gui[3] = {0x9b, 0x9c, 0};
#ifdef NO_ACTION_ONESHOT
    uint8_t modifiers = get_mods();
#else
    uint8_t modifiers = get_mods() | get_oneshot_mods();
#endif
    oled_write_P((modifiers & MOD_MASK_CTRL) ? font_ctrl : PSTR("  "), false);
    oled_write_P(PSTR(" "), false);
    oled_write_P((modifiers & MOD_MASK_SHIFT) ? font_shift : PSTR("  "), false);
    oled_write_P((modifiers & MOD_MASK_ALT) ? font_alt : PSTR("  "), false);
    oled_write_P(PSTR(" "), false);
    oled_write_P((modifiers & MOD_MASK_GUI) ? font_gui : PSTR("  "), false);
}

// 5x2 Layer indicator

void render_layer(void) {
    static const char PROGMEM font_layer[4][6] = {
        {0xd4, 0xd5, 0xd6, 0xd7, 0xd8, 0},
        {0xd9, 0xda, 0xdb, 0xdc, 0xdd, 0},
        {0xdf, 0x9d, 0x9e, 0x9f, 0xdf, 0},
        {0xdf, 0xbd, 0xbe, 0xbf, 0xdf, 0},
    };
    if (layer_state_is(MOUS)) {
        oled_write_P(font_layer[2], false);
        oled_write_P(font_layer[3], false);
    } else if (layer_state_is(NUMB)) {
        oled_write("\n", false);
        oled_write_P(font_layer[1], false);
    } else if (layer_state_is(SYMB)) {
        oled_write("\n", false);
        oled_write_P(font_layer[0], false);
    } else {
        oled_write("\n\n", false);
    }
};

void render_status_main(void) {
    oled_write("\n", false);
    render_layer();
    oled_write("\n\n\n\n\n", false);
    render_sine();
    oled_write("\n\n\n\n", false);
    render_mod_status();
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_90;
}

void toggle_oled_mode(void) {
    oled_enabled = !oled_enabled;
}

void oled_task_user(void) {
    if (oled_enabled) {
        oled_timer_elapsed = timer_elapsed32(oled_timer);
        if (oled_timer_elapsed > 10000) {
            oled_off();
        } else {
            render_status_main();
        }
    } else {
        oled_off();
    }
}
// todo oled write raw byte
