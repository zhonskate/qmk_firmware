#ifdef OLED_ANIM_STARFIELD
#pragma once
#include "common.h"

#define MAX_STARS 16
#define Z_FACTOR 1.22
#define SPAWN_RANGE 16
#define SPAWN_DELAY 333
#define STARFIELD_FPS 18 // More than 20 and pixels get stuck in the bottom part
#define CENTER_JUMP_TIMEOUT 1000

#define UPDATE_DELAY (uint8_t)(1000.0 / STARFIELD_FPS)

void oled_init_starfield(void);

int16_t get_star_x(uint8_t index);
int16_t get_star_y(uint8_t index);

void spawn_star(void);
void update_star(uint8_t index);

#ifdef OLED_ANIM_STARFIELD_WANDER
void update_center(void);
#endif

void render_starfield(void);
#endif
