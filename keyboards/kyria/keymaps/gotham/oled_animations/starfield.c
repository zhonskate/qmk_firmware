#ifdef OLED_ANIM_STARFIELD
#include "starfield.h"

uint8_t n_stars = 0;
uint8_t star_ang[MAX_STARS];
uint8_t star_rad[MAX_STARS];
uint16_t star_spawn_timer = 0;
uint16_t star_update_timer = 0;

uint16_t center_x = OLED_DISPLAY_WIDTH/2;
uint16_t center_y = OLED_DISPLAY_HEIGHT/2;
#ifdef OLED_ANIM_STARFIELD_WANDER
uint16_t center_jump_timer = 0;
uint16_t center_target_x = OLED_DISPLAY_WIDTH/2;
uint16_t center_target_y = OLED_DISPLAY_HEIGHT/2;
#endif

#ifdef OLED_ANIM_STARFIELD_SHIP
bool alt_frame = false;
#endif

void oled_init_starfield(void) {
    random16_set_seed(12345);
}

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

void update_star(uint8_t index) {
    star_rad[index] *= Z_FACTOR;
    if (rect_out_of_bounds(get_star_x(index), get_star_y(index), 1, 1, 24)) {
        star_ang[index] = random8();
        star_rad[index] = random8_max(8) + SPAWN_RANGE;
    }
}

#ifdef OLED_ANIM_STARFIELD_WANDER
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
#endif

#ifdef OLED_ANIM_STARFIELD_SHIP
void render_voyager(int16_t x, int16_t y, bool fill, bool alt_frame) {
    /*
     * Saucer section (row by row)
     */
    // Row 3
    for(uint8_t i = 0; i < 6; i++) oled_write_pixel(x + 5 + i, y + 3, fill);
    // Row 4
    for(uint8_t i = 0; i < 3; i++) {
        oled_write_pixel(x + 2 + i, y + 4, fill);
        oled_write_pixel(x + 11 + i, y + 4, fill);
    }
    if (fill) {
        for(uint8_t i = 0; i < 6; i++) oled_write_pixel(x + 5 + i, y + 4, false);
    }
    // Row 5
    for(uint8_t i = 0; i < 4; i++) oled_write_pixel(x + 6 + i, y + 5, fill);
    oled_write_pixel(x + 1, y + 5, fill);
    oled_write_pixel(x + 14, y + 5, fill);
    if (fill) {
        for(uint8_t i = 0; i < 4; i++) {
            oled_write_pixel(x + 2 + i, y + 5, false);
            oled_write_pixel(x + 10 + i, y + 5, false);
        }
    }
    // Row 6
    for(uint8_t i = 0; i < 6; i++) {
        oled_write_pixel(x + i, y + 6, fill);
        oled_write_pixel(x + 10 + i, y + 6, fill);
    }
    if (fill) {
        for(uint8_t i = 0; i < 4; i++) oled_write_pixel(x + 6 + i, y + 6, false);
    }
    // Row 7
    for(uint8_t i = 0; i < 4; i++) oled_write_pixel(x + 6 + i, y + 7, fill);
    /*
     * Warp Drives
     */
    for(uint8_t i = 0; i < 3; i++) {
        // Left Grills
        oled_write_pixel(x, y + 9 + i, fill);
        oled_write_pixel(x + 2, y + 9 + i, fill);
        oled_write_pixel(x + 4, y + 9 + i, fill);
        // Right Grills
        oled_write_pixel(x + 11, y + 9 + i, fill);
        oled_write_pixel(x + 13, y + 9 + i, fill);
        oled_write_pixel(x + 15, y + 9 + i, fill);
        // Gaps
        // Left
        oled_write_pixel(x + 1, y + 9 + i, alt_frame);
        oled_write_pixel(x + 3, y + 9 + i, alt_frame);
        // Right
        oled_write_pixel(x + 12, y + 9 + i, alt_frame);
        oled_write_pixel(x + 14, y + 9 + i, alt_frame);
        // Grill Top
        oled_write_pixel(x + 1 + i, y + 8, fill);
        oled_write_pixel(x + 12 + i, y + 8, fill);
        // Grill Bottom
        oled_write_pixel(x + 1 + i, y + 12, fill);
        oled_write_pixel(x + 12 + i, y + 12, fill);
    }
    /*
     * Connector Section
     */
    for(uint8_t i = 0; i < 2; i++) {
        oled_write_pixel(x + 7 + i, y + 8, fill);
        oled_write_pixel(x + 5 + i, y + 10, fill);
        oled_write_pixel(x + 9 + i, y + 10, fill);
    }
    oled_write_pixel(x + 6, y + 9, fill);
    oled_write_pixel(x + 9, y + 9, fill);
}
#endif

void render_starfield(void) {
    uint16_t now = timer_read();
    if ((n_stars < MAX_STARS) && (timer_elapsed(star_spawn_timer) >= SPAWN_DELAY)) {
        spawn_star();
        star_spawn_timer = now;
    }
#ifdef OLED_ANIM_STARFIELD_WANDER
    if ((now % CENTER_JUMP_TIMEOUT) == 0) {
        center_target_x = random8_max(OLED_DISPLAY_WIDTH);
        center_target_y = random8_max(OLED_DISPLAY_HEIGHT);
        center_jump_timer = now;
    }
#endif
    if (timer_elapsed(star_update_timer) >= UPDATE_DELAY) {
        int16_t x, y;
        for(uint8_t i = 0; i < n_stars; i++) {
            x = get_star_x(i);
            y = get_star_y(i);
            { oled_write_pixel(x, y, false); }
        }
#ifdef OLED_ANIM_STARFIELD_SHIP
        render_voyager(center_x - 8, center_y - 8, false, false);
#endif
#ifdef OLED_ANIM_STARFIELD_WANDER
        update_center();
#endif
        for(uint8_t i = 0; i < n_stars; i++) {
            update_star(i);
            x = get_star_x(i);
            y = get_star_y(i);
            { oled_write_pixel(x, y, true); }
        }
#ifdef OLED_ANIM_STARFIELD_SHIP
        render_voyager(center_x - 8, center_y - 8, true, alt_frame);
        alt_frame = !alt_frame;
#endif
        star_update_timer = now;
    }
}
#endif
