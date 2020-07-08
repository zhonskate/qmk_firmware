#include "oled_utils.h"

#ifndef STARFIELD_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_180; }
#endif

void oled_task_user(void) { render_status(); }

#ifndef STARFIELD_ENABLE
// clang-format off
void render_qmk_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    };
    oled_write_P(qmk_logo, false);
}
// clang-format on
#endif

void render_layer(void) {
    oled_write_P(PSTR("\nLayer: "), false);
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("Default\n"), false);
            break;
        case _LOWER:
            oled_write_P(PSTR("Lower\n"), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("Raise\n"), false);
            break;
        case _ADJUST:
            oled_write_P(PSTR("Adjust\n"), false);
            break;
        default:
            oled_write_P(PSTR("???\n"), false);
    }
}

#ifdef ENCODER_ENABLE
void render_encoder(encoder_mode_t mode) {
    switch (mode) {
        case ENC_MODE_VOLUME:
            oled_write_P(PSTR("Volume\n"), false);
            break;
        case ENC_MODE_WORD_NAV:
            oled_write_P(PSTR("Word Nav\n"), false);
            break;
        case ENC_MODE_LEFT_RIGHT:
            oled_write_P(PSTR("Left / Right\n"), false);
            break;
        case ENC_MODE_UP_DOWN:
            oled_write_P(PSTR("Up / Down\n"), false);
            break;
        case ENC_MODE_PAGING:
            oled_write_P(PSTR("PgUp / PgDwn\n"), false);
            break;
        default:
            oled_write_P(PSTR("???\n"), false);
    }
}
#endif

#ifdef THUMBSTICK_ENABLE
void render_thumbstick(thumbstick_mode_t mode) {
    switch (mode) {
        case THUMBSTICK_MODE_MOUSE:
            oled_write_P(PSTR("Mouse"), false);
            break;
        case THUMBSTICK_MODE_ARROWS:
            oled_write_P(PSTR("Arrows"), false);
            break;
        case THUMBSTICK_MODE_SCROLL:
            oled_write_P(PSTR("Scroll"), false);
            break;
        default:
            oled_write_P(PSTR("???\n"), false);
    }
}
#endif

void render_status(void) {
    if (!is_keyboard_master()) {
        // Host Keyboard Layer Status
        render_layer();
#ifdef ENCODER_ENABLE
        // Encoder state
        oled_write_P(PSTR("L-Enc: "), false);
        render_encoder(encoder_left_mode);
        oled_write_P(PSTR("R-Enc: "), false);
        render_encoder(encoder_right_mode);
#endif
#ifdef THUMBSTICK_ENABLE
        if (!isLeftHand) {
            // Thumbstick state
            oled_write_P(PSTR("Joystick: "), false);
            render_thumbstick(thumbstick_state.config.mode);
        }
#endif
        // Host Keyboard LED Status
        led_t led_state = host_keyboard_led_state();
        oled_write_P(led_state.num_lock ? PSTR("NUMLCK ") : PSTR("       "), false);
        oled_write_P(led_state.caps_lock ? PSTR("CAPLCK ") : PSTR("       "), false);
        oled_write_P(led_state.scroll_lock ? PSTR("SCRLCK ") : PSTR("       "), false);
    } else {
        // QMK Logo and version information
#ifdef STARFIELD_ENABLE
        render_starfield();
#else
        render_qmk_logo();
#endif
        // oled_write_P(PSTR("\n      Kyria v1.0\n"), false);
    }
}

#ifdef STARFIELD_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    init_cache();
    return OLED_ROTATION_180;
}

#define CENTER_H OLED_DISPLAY_WIDTH/2
#define CENTER_V OLED_DISPLAY_HEIGHT/2
#define SCREEN_RATIO OLED_DISPLAY_WIDTH / OLED_DISPLAY_HEIGHT
#define SPAWN_RANGE 12
#define MAX_STARS 16
#define Z_FACTOR 1.1
#define SPAWN_DELAY 500
#define UPDATE_DELAY 32

#define PI2 (2 * 3.141592653589793238)

#define RAND_RESOLUTION 64
float rand_map[RAND_RESOLUTION];
float sin_map[RAND_RESOLUTION];
float cos_map[RAND_RESOLUTION];

uint8_t star_ang[MAX_STARS];
float star_rad[MAX_STARS];

uint8_t n_stars = 0;
uint16_t star_spawn_timer = 0;
uint16_t star_update_timer = 0;

void init_cache(void) {
    float part = PI2 / RAND_RESOLUTION;
    for(uint8_t i = 0; i < RAND_RESOLUTION; i++) {
        rand_map[i] = part * i;
        sin_map[i] = sin(rand_map[i]);
        cos_map[i] = cos(rand_map[i]);
    }
}

uint8_t rand_range(uint8_t range) {
    return rand() % range;
}

void spawn_star(void) {
    star_ang[n_stars] = rand_range(RAND_RESOLUTION);
    star_rad[n_stars] = rand_range(8) + SPAWN_RANGE;
    n_stars++;
}

uint8_t get_star_x(uint8_t index) {
    return (uint8_t)(round(cos_map[star_ang[index]] * star_rad[index] + CENTER_H));
}

uint8_t get_star_y(uint8_t index) {
    return (uint8_t)(round(sin_map[star_ang[index]] * star_rad[index] + CENTER_V));
}

bool out_of_bounds(uint8_t index) {
    uint8_t val = get_star_x(index);
    if (val < 0) return true;
    if (val >= OLED_DISPLAY_WIDTH) return true;
    val = get_star_y(index);
    if (val < 0) return true;
    if (val >= OLED_DISPLAY_HEIGHT) return true;
    return false;
}

void update_star(uint8_t index) {
    star_rad[index] *= Z_FACTOR;
    if (out_of_bounds(index)) {
        star_ang[index] = rand_range(RAND_RESOLUTION);
        star_rad[index] = rand_range(8) + SPAWN_RANGE;
    }
}

void render_starfield(void) {
    if ((n_stars < MAX_STARS) && (timer_elapsed(star_spawn_timer) >= SPAWN_DELAY)) {
        spawn_star();
        star_spawn_timer = timer_read();
    }
    if (timer_elapsed(star_update_timer) >= UPDATE_DELAY) {
        uint8_t x, y;
        for(uint8_t i = 0; i < n_stars; i++) {
            x = get_star_x(i);
            y = get_star_y(i);
            oled_set_pixel(x, y, false);
            update_star(i);
            x = get_star_x(i);
            y = get_star_y(i);
            oled_set_pixel(x, y, true);
        }
        star_update_timer = timer_read();
    }
}
#endif
