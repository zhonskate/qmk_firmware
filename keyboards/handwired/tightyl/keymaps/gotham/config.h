/* Copyright 2020 Gautham Yerroju <gautham.yerroju@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

// // make mod taps for home row feasible
// #define PERMISSIVE_HOLD
// #define IGNORE_MOD_TAP_INTERRUPT
// #define TAPPING_TERM 200
// #define TAPPING_FORCE_HOLD

#define EE_HANDS

// Fix for Elite C rev3
#define SPLIT_USB_DETECT
// Speed up slave half startup
#define SPLIT_USB_TIMEOUT 1000

// #define ENABLE_LAYOUT_COLEMAK
#define ENABLE_LAYOUT_COLEMAK_DH
// #define ENABLE_LAYOUT_DVORAK
// #define ENABLE_LAYOUT_WORKMAN
#define ENABLE_LAYOUT_NORMAN

#ifdef OLED_DRIVER_ENABLE
#    ifdef OLED_CUSTOM_TIMEOUT
#        undef OLED_CUSTOM_TIMEOUT
#        define OLED_CUSTOM_TIMEOUT 30000
#    endif
#    define OLED_INFO_TIMEOUT 2000
#endif

#ifdef RGBLIGHT_ENABLE
#    define RGBLIGHT_EFFECT_RAINBOW_MOOD
#    define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#endif

#ifdef ENCODER_ENABLE
#    define ENCODER_DIRECTION_FLIP
#    define ENCODER_RESOLUTION 2
#endif

#ifdef THUMBSTICK_ENABLE
#    define THUMBSTICK_FLIP_X
#    define THUMBSTICK_PIN_X F0
#    define THUMBSTICK_PIN_Y F1
#endif
