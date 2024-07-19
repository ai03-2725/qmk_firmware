/* SPDX-License-Identifier: GPL-2.0-or-later */

#pragma once


/* Board-specific RGBLED configuration */

/* Disable RGB keycodes - should only be controlled programatically as indicators */
#define RGBLIGHT_DISABLE_KEYCODES

#define RGB_MATRIX_LED_COUNT 3
#define RGB_MATRIX_DEFAULT_VAL 60
#define RGB_MATRIX_KEYPRESSES
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_MATRIX_SLEEP

#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_SOLID_COLOR

#define ENABLE_RGB_MATRIX_BREATHING
#define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON

#define CAPS_INDICATOR_INDEX 0
#define LAYERS_INDICATOR_INDEX_LEFT 1
#define LAYERS_INDICATOR_INDEX_RIGHT 2
