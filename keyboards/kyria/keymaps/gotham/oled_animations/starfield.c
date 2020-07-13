#ifdef OLED_ANIM_STARFIELD
#include "starfield.h"

uint8_t n_stars = 0;
uint8_t star_ang[MAX_STARS];
uint8_t star_rad[MAX_STARS];
uint16_t star_spawn_timer = 0;
uint16_t star_update_timer = 0;

uint16_t center_x = OLED_DISPLAY_WIDTH/2;
uint16_t center_y = OLED_DISPLAY_HEIGHT/2;

void oled_init_starfield(void) {
    random16_set_seed(timer_read());
    set_starfield_center();
}

void spawn_star(void) {
    star_ang[n_stars] = random8();
    star_rad[n_stars] = random8_max(16) + SPAWN_RANGE;
    n_stars++;
}

uint8_t get_star_x(uint8_t index) {
    return center_x + (cos8(star_ang[index]) - 128) * star_rad[index] / 128;
}

uint8_t get_star_y(uint8_t index) {
    return center_y + (sin8(star_ang[index]) - 128) * star_rad[index] / 128;
}

void update_star(uint8_t index) {
    if (index % 5 == 2) {
        star_rad[index] += map8(cubicwave8(star_rad[index]), 1, ZOOM_SPEED);
    } else {
        star_rad[index] += 1;
    }
    if (rect_out_of_bounds(get_star_x(index), get_star_y(index), 1, 1, 24)) {
        star_ang[index] = random8_max(250) + 5;
        star_rad[index] = random8_max(16) + SPAWN_RANGE;
    }
}

void update_stars(void) {
    for(uint8_t i = 0; i < n_stars; i++) {
        update_star(i);
    }
}

void set_starfield_center(void) {
    center_x = random8_max(OLED_DISPLAY_WIDTH);
    center_y = random8_max(OLED_DISPLAY_HEIGHT);
}

void draw_stars(void) {
    uint8_t x, y;
    for(uint8_t i = 0; i < n_stars; i++) {
        x = get_star_x(i);
        y = get_star_y(i);
        if (!point_out_of_bounds(x, y, 0))
        { oled_write_pixel(x, y, true); }
    }
}

void erase_stars(void) {
    uint8_t x, y;
    for(uint8_t i = 0; i < n_stars; i++) {
        x = get_star_x(i);
        y = get_star_y(i);
        if (!point_out_of_bounds(x, y, 0))
        { oled_write_pixel(x, y, false); }
    }
}

void render_starfield(void) {
    uint16_t now = timer_read();
    if ((n_stars < MAX_STARS) && (timer_elapsed(star_spawn_timer) >= SPAWN_DELAY)) {
        spawn_star();
        star_spawn_timer = now;
    }
    if (timer_elapsed(star_update_timer) >= UPDATE_DELAY) {
        erase_stars();
        update_stars();
        draw_stars();
        star_update_timer = now;
    }
}
#endif
