/* SPDX-License-Identifier: GPL-2.0-or-later */

#pragma once

#include "config_common.h"


/* Board-specific RGBLED configuration */

/* Disable RGB keycodes - should only be controlled programatically as indicators */
#define RGBLIGHT_DISABLE_KEYCODES

/* By default disable RGBs - their state should be set programatically */
#define RGBLIGHT_DEFAULT_HUE 0
#define RGBLIGHT_DEFAULT_SAT 0
#define RGBLIGHT_DEFAULT_VAL 0
