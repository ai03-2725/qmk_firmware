/*
Copyright 2021 ai03 Design Studio

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID    0xA103
#define PRODUCT_ID   0x0026
#define DEVICE_VER   0x0001
#define MANUFACTURER ai03 Design Studio
#define PRODUCT      AI6C-L

/* Key matrix */
#define MATRIX_ROWS 5
#define MATRIX_COLS 14

#define MATRIX_ROW_PINS { B2, B7, D5, B1, D3 }
#define MATRIX_COL_PINS { F0, F1, F4, F5, F6, F7, C7, C6, B6, B5, B4, D7, D6, D4 }
#define UNUSED_PINS

#define DIODE_DIRECTION COL2ROW

/* Debounce settings */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* Define indicator LEDs */
#define LED_CAPS_LOCK_PIN   D0
#define LED_NUM_LOCK_PIN    D1
#define LED_SCROLL_LOCK_PIN D2
#define LED_PIN_ON_STATE    0
