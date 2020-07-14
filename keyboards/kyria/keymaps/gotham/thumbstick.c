#include "thumbstick.h"

void thumbstick_init(void) {
    thumbstickTimer       = 0;
    thumbstickScrollTimer = 0;
    thumbstick_state.config.mode           = THUMBSTICK_MODE_MOUSE;

#if defined THUMBSTICK_DEBUG
    rawX               = 0;
    rawY               = 0;
    distX              = 0;
    distY              = 0;
    thumbstickLogTimer = 0;
#endif
}

// Axis-level wrapper to read raw value and return signed distanced from center
int16_t thumbstick_get_component(uint8_t pin) {
    int16_t value = analogReadPin(pin); // range of [0 to 1023]
#if defined THUMBSTICK_DEBUG
    if (pin == THUMBSTICK_PIN_X) {
        rawX  = value;
        distX = value - THUMBSTICK_RANGE_CENTER;
    } else {
        rawY  = value;
        distY = value - THUMBSTICK_RANGE_CENTER;
    }
#endif
    return value - THUMBSTICK_RANGE_CENTER;
}

thumbstick_mode_t thumbstick_mode_get(void) { return thumbstick_state.config.mode; }
thumbstick_vector_t thumbstick_vector_get(void) { return thumbstick_state.vector; }
void thumbstick_mode_set(thumbstick_mode_t mode) { thumbstick_state.config.mode = mode; }
void thumbstick_vector_set(thumbstick_vector_t vector) { thumbstick_state.vector = vector; }

void thumbstick_mode_cycle_forward(void) {
    thumbstick_mode_set(addmod8(thumbstick_mode_get(), 1, _THUMBSTICK_MODE_LAST));
}
void thumbstick_mode_cycle_backward(void) {
    thumbstick_mode_set(submod8(thumbstick_mode_get(), 1, _THUMBSTICK_MODE_LAST));
}

// Get mouse speed
int16_t thumbstick_get_mouse_speed(int16_t component) {
    int16_t  speed;
    uint16_t distance = abs(component);
    if (distance > THUMBSTICK_FINE_ZONE) {
        speed = THUMBSTICK_SPEED;
    } else if (distance > THUMBSTICK_DEAD_ZONE) {
        speed = THUMBSTICK_FINE_SPEED;
    } else {
        return 0;
    }
    return (float)speed * component / THUMBSTICK_RANGE_CENTER;
}

// Fix direction within one of 8 axes (or 4 if 8-axis is disabled)
thumbstick_direction_t thumbstick_get_discretized_direction(thumbstick_vector_t vector, float axisSeparation, bool eightAxis) {
    thumbstick_direction_t direction;
    uint16_t               absX                = abs(vector.x);
    uint16_t               absY                = abs(vector.y);
    uint16_t               maxComponent        = (absX > absY) ? absX : absY;
    bool                   insideDeadZone      = (maxComponent <= THUMBSTICK_DEAD_ZONE);
    bool                   outsideDiagonalZone = ((abs(absX - absY) / (float)maxComponent) >= axisSeparation);
    if (insideDeadZone) {
        direction.up = direction.down = direction.left = direction.right = false;
    } else {
        direction.up    = (vector.y < 0);
        direction.down  = (vector.y > 0);
        direction.left  = (vector.x < 0);
        direction.right = (vector.x > 0);
        // Let only the dominant direction remain under the right conditions
        if (outsideDiagonalZone || !eightAxis) {
            if (absX > absY) {
                direction.up = direction.down = false;
            } else {
                direction.left = direction.right = false;
            }
        }
    }
    return direction;
}

void thumbstick_read_vectors(void) {
    if (timer_elapsed(thumbstickTimer) > THUMBSTICK_TIMEOUT) {
        thumbstickTimer = timer_read();
#ifndef THUMBSTICK_FLIP_X
        thumbstick_state.vector.x = thumbstick_get_component(THUMBSTICK_PIN_X);
#else
        thumbstick_state.vector.x = -thumbstick_get_component(THUMBSTICK_PIN_X);
#endif
#ifndef THUMBSTICK_FLIP_Y
        thumbstick_state.vector.y = thumbstick_get_component(THUMBSTICK_PIN_Y);
#else
        thumbstick_state.vector.y = -thumbstick_get_component(THUMBSTICK_PIN_Y);
#endif
    }
}

void                   thumbstick_calculate_state(void) {
    switch (thumbstick_state.config.mode) {
        case THUMBSTICK_MODE_MOUSE:
            thumbstick_state.report.x = thumbstick_get_mouse_speed(thumbstick_state.vector.x);
            thumbstick_state.report.y = thumbstick_get_mouse_speed(thumbstick_state.vector.y);
            break;
        case THUMBSTICK_MODE_ARROWS:
            thumbstick_state.direction = thumbstick_get_discretized_direction(thumbstick_state.vector, THUMBSTICK_AXIS_SEPARATION, THUMBSTICK_EIGHT_AXIS);
            break;
        case THUMBSTICK_MODE_SCROLL:
            if (timer_elapsed(thumbstickScrollTimer) > THUMBSTICK_SCROLL_TIMEOUT) {
                thumbstick_direction_t scrollDirection;
                thumbstickScrollTimer     = timer_read();
                scrollDirection           = thumbstick_get_discretized_direction(thumbstick_state.vector, THUMBSTICK_AXIS_SEPARATION, false);
                thumbstick_state.report.v = (scrollDirection.up || scrollDirection.down) ? (scrollDirection.up ? THUMBSTICK_SCROLL_SPEED : -THUMBSTICK_SCROLL_SPEED) : 0;
                thumbstick_state.report.h = (scrollDirection.left || scrollDirection.right) ? (scrollDirection.left ? -THUMBSTICK_SCROLL_SPEED : THUMBSTICK_SCROLL_SPEED) : 0;
            } else {
                thumbstick_state.report.v = thumbstick_state.report.h = 0;
            }
            break;
        default:
            break;
    }
}

void thumbstick_process_state(report_mouse_t* report) {
    switch (thumbstick_state.config.mode) {
        case THUMBSTICK_MODE_MOUSE:
            report->x = thumbstick_state.report.x;
            report->y = thumbstick_state.report.y;
#ifdef THUMBSTICK_DEBUG
            if (timer_elapsed(thumbstickLogTimer) > 100) {
                thumbstickLogTimer = timer_read();
                uprintf("Raw (%d, %d); Dist (%d, %d); Vec (%d, %d);\n", rawX, rawY, distX, distY, thumbstick_state.vector.x, thumbstick_state.vector.y);
            }
#endif
            break;
        case THUMBSTICK_MODE_ARROWS:
            update_keycode_status(KC_UP, thumbstick_state.lastDirection.up, thumbstick_state.direction.up);
            update_keycode_status(KC_DOWN, thumbstick_state.lastDirection.down, thumbstick_state.direction.down);
            update_keycode_status(KC_LEFT, thumbstick_state.lastDirection.left, thumbstick_state.direction.left);
            update_keycode_status(KC_RIGHT, thumbstick_state.lastDirection.right, thumbstick_state.direction.right);
            thumbstick_state.lastDirection = thumbstick_state.direction;
#ifdef THUMBSTICK_DEBUG
            if (timer_elapsed(thumbstickLogTimer) > 100) {
                thumbstickLogTimer = timer_read();
                uprintf("Up %d; Down %d; Left: %d; Right %d; Vec (%d, %d);\n", direction.up, direction.down, direction.left, direction.right, thumbstick_state.vector.x, thumbstick_state.vector.y);
            }
#endif
            break;
        case THUMBSTICK_MODE_SCROLL:
            report->v = thumbstick_state.report.v;
            report->h = thumbstick_state.report.h;
#ifdef THUMBSTICK_DEBUG
            if (timer_elapsed(thumbstickLogTimer) > 100) {
                thumbstickLogTimer = timer_read();
                uprintf("Scroll (%d, %d)\n", report.h, report.v);
            }
#endif
            break;
        default:
            break;
    }
}

void update_keycode_status(uint16_t keycode, bool last, bool current) {
    if (last != current) {
        if (current) {
            register_code16(keycode);
        } else {
            unregister_code16(keycode);
        }
    }
}

void pointing_device_init(void) { thumbstick_init(); }

void pointing_device_task(void) {
    report_mouse_t report = pointing_device_get_report();

    // Only read pins on the right half where the thunmbstick is attached, and set state
    if (!isLeftHand) {
        thumbstick_read_vectors();
    }
    // Calculate and process thumbstick state (if master half doesn't have the thumbstick, the custom transport will bring the vectors over)
    thumbstick_calculate_state();
    thumbstick_process_state(&report);

    pointing_device_set_report(report);
    pointing_device_send();
}
