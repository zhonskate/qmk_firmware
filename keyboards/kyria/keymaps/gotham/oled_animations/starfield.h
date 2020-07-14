#ifdef OLED_ANIM_STARFIELD
#pragma once
#include "common.h"

#define MAX_STARS 24
#define ZOOM_SPEED 16
#define SPAWN_RANGE 16
#define SPAWN_DELAY 100
#define STARFIELD_FPS 16 // More than 20 and pixels get stuck in the bottom part

#define UPDATE_DELAY (uint8_t)(1000.0 / STARFIELD_FPS)

void oled_init_starfield(void);

uint8_t get_star_x(uint8_t index);
uint8_t get_star_y(uint8_t index);

void spawn_star(void);
void update_star(uint8_t index);
void erase_stars(void);

#ifdef OLED_ANIM_STARFIELD_WANDER
void set_starfield_center(void);
#endif

void render_starfield(void);
#endif
