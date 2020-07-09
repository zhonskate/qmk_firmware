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

uint8_t center_x, center_y, center_target_x, center_target_y;

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    center_x = OLED_DISPLAY_WIDTH/2;
    center_y = OLED_DISPLAY_HEIGHT/2;
    center_target_x = OLED_DISPLAY_WIDTH/2;
    center_target_y = OLED_DISPLAY_HEIGHT/2;
    random16_set_seed(12345);
    return OLED_ROTATION_180;
}

#define SCREEN_RATIO OLED_DISPLAY_WIDTH / OLED_DISPLAY_HEIGHT
#define SPAWN_RANGE 8
#define MAX_STARS 16
#define Z_FACTOR 1.22
#define SPAWN_DELAY 333

#define STARFIELD_FPS 18 // More than 20 and pixels get stuck in the bottom part
#define UPDATE_DELAY (uint8_t)(1000.0 / STARFIELD_FPS)

#define CENTER_JUMP_TIMEOUT 1000

uint8_t star_ang[MAX_STARS];
uint8_t star_rad[MAX_STARS];

uint8_t n_stars = 0;
uint16_t star_spawn_timer = 0;
uint16_t star_update_timer = 0;
uint16_t center_jump_timer = 0;

bool alt_frame = false;


void spawn_star(void) {
    star_ang[n_stars] = random8();
    star_rad[n_stars] = random8_max(8) + SPAWN_RANGE;
    n_stars++;
}

int16_t get_star_x(uint8_t index) {
    return center_x + (int16_t)(cos8(star_ang[index]) - 128) * star_rad[index] / 128;
}

int16_t get_star_y(uint8_t index) {
    return center_y + (int16_t)(sin8(star_ang[index]) - 128) * star_rad[index] / 128;
}

bool out_of_bounds(uint8_t index, int16_t padding) {
    int16_t val = get_star_x(index);
    if (val < -padding) return true;
    if (val >= (OLED_DISPLAY_WIDTH + padding)) return true;
    val = get_star_y(index);
    if (val < -padding) return true;
    if (val >= (OLED_DISPLAY_HEIGHT + padding)) return true;
    return false;
}

void update_star(uint8_t index) {
    star_rad[index] *= Z_FACTOR;
    if (out_of_bounds(index, 24)) {
        star_ang[index] = random8();
        star_rad[index] = random8_max(8) + SPAWN_RANGE;
    }
}

void update_center(void) {
    if (center_target_x > center_x) {
        center_x += 1;
    } else if (center_target_x < center_x) {
        center_x -= 1;
    }
    if (center_target_y > center_y) {
        center_y += 1;
    } else if (center_target_y < center_y) {
        center_y -= 1;
    }
}

void render_voyager(int16_t x, int16_t y, bool fill, bool alt_frame) {
    /*
     * Saucer section (row by row)
     */
    // Row 3
    for(uint8_t i = 0; i < 6; i++) oled_set_pixel(x + 5 + i, y + 3, fill);
    // Row 4
    for(uint8_t i = 0; i < 3; i++) {
        oled_set_pixel(x + 2 + i, y + 4, fill);
        oled_set_pixel(x + 11 + i, y + 4, fill);
    }
    if (fill) {
        for(uint8_t i = 0; i < 6; i++) oled_set_pixel(x + 5 + i, y + 4, false);
    }
    // Row 5
    for(uint8_t i = 0; i < 4; i++) oled_set_pixel(x + 6 + i, y + 5, fill);
    oled_set_pixel(x + 1, y + 5, fill);
    oled_set_pixel(x + 14, y + 5, fill);
    if (fill) {
        for(uint8_t i = 0; i < 4; i++) {
            oled_set_pixel(x + 2 + i, y + 5, false);
            oled_set_pixel(x + 10 + i, y + 5, false);
        }
    }
    // Row 6
    for(uint8_t i = 0; i < 6; i++) {
        oled_set_pixel(x + i, y + 6, fill);
        oled_set_pixel(x + 10 + i, y + 6, fill);
    }
    if (fill) {
        for(uint8_t i = 0; i < 4; i++) oled_set_pixel(x + 6 + i, y + 6, false);
    }
    // Row 7
    for(uint8_t i = 0; i < 4; i++) oled_set_pixel(x + 6 + i, y + 7, fill);
    /*
     * Warp Drives
     */
    for(uint8_t i = 0; i < 3; i++) {
        // Left Grills
        oled_set_pixel(x, y + 9 + i, fill);
        oled_set_pixel(x + 2, y + 9 + i, fill);
        oled_set_pixel(x + 4, y + 9 + i, fill);
        // Right Grills
        oled_set_pixel(x + 11, y + 9 + i, fill);
        oled_set_pixel(x + 13, y + 9 + i, fill);
        oled_set_pixel(x + 15, y + 9 + i, fill);
        // Gaps
        // Left
        oled_set_pixel(x + 1, y + 9 + i, alt_frame);
        oled_set_pixel(x + 3, y + 9 + i, alt_frame);
        // Right
        oled_set_pixel(x + 12, y + 9 + i, alt_frame);
        oled_set_pixel(x + 14, y + 9 + i, alt_frame);
        // Grill Top
        oled_set_pixel(x + 1 + i, y + 8, fill);
        oled_set_pixel(x + 12 + i, y + 8, fill);
        // Grill Bottom
        oled_set_pixel(x + 1 + i, y + 12, fill);
        oled_set_pixel(x + 12 + i, y + 12, fill);
    }
    /*
     * Connector Section
     */
    for(uint8_t i = 0; i < 2; i++) {
        oled_set_pixel(x + 7 + i, y + 8, fill);
        oled_set_pixel(x + 5 + i, y + 10, fill);
        oled_set_pixel(x + 9 + i, y + 10, fill);
    }
    oled_set_pixel(x + 6, y + 9, fill);
    oled_set_pixel(x + 9, y + 9, fill);
}

void render_starfield(void) {
    uint16_t now = timer_read();
    if ((n_stars < MAX_STARS) && (timer_elapsed(star_spawn_timer) >= SPAWN_DELAY)) {
        spawn_star();
        star_spawn_timer = now;
    }
    if ((now % CENTER_JUMP_TIMEOUT) == 0) {
        center_target_x = random8_max(OLED_DISPLAY_WIDTH);
        center_target_y = random8_max(OLED_DISPLAY_HEIGHT);
        center_jump_timer = now;
    }
    if (timer_elapsed(star_update_timer) >= UPDATE_DELAY) {
        int16_t x, y;
        for(uint8_t i = 0; i < n_stars; i++) {
            x = get_star_x(i);
            y = get_star_y(i);
            // if (!out_of_bounds(i, 0))
            { oled_set_pixel(x, y, false); }
        }
        render_voyager(center_x - 8, center_y - 8, false, false);
        update_center();
        for(uint8_t i = 0; i < n_stars; i++) {
            update_star(i);
            x = get_star_x(i);
            y = get_star_y(i);
            // if (!out_of_bounds(i, 0))
            { oled_set_pixel(x, y, true); }
        }
        render_voyager(center_x - 8, center_y - 8, true, alt_frame);
        alt_frame = !alt_frame;
        star_update_timer = now;
    }
}
#endif
