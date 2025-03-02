/* Copyright 2021 ai03
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
#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _NUM,
    _NAV
};

// Define some macros to keep matrix view clean
#define PREVDTP C(G(KC_LEFT))
#define NEXTDTP C(G(KC_RGHT))
#define PREVTAB C(S(KC_TAB))
#define NEXTTAB C(KC_TAB)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
        KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_LBRC, KC_RBRC, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_LPRN, KC_RPRN, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_MINS, KC_EQL,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT, 
                                   KC_LGUI, KC_LALT, MO(2),   KC_SPC,  KC_SPC,  MO(1),   KC_TAB,  KC_DEL
    ),
    [_NUM] = LAYOUT(
        _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    RESET,   RESET,   KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
        _______, KC_GRV,  KC_LBRC, KC_LCBR, KC_LPRN, KC_MINS, _______, _______, KC_EQL,  KC_RPRN, KC_RCBR, KC_RBRC, KC_BSLS, XXXXXXX,
        _______, KC_TILD, XXXXXXX, XXXXXXX, XXXXXXX, KC_UNDS, _______, _______, KC_PLUS, XXXXXXX, XXXXXXX, XXXXXXX, KC_PIPE, _______,
                                   _______, _______, _______, _______, _______, _______, _______, _______
    ),
    [_NAV] = LAYOUT(
        _______, XXXXXXX, XXXXXXX, KC_PGUP, XXXXXXX, XXXXXXX, RESET,   RESET,   XXXXXXX, XXXXXXX, KC_UP,   XXXXXXX, XXXXXXX, _______,
        _______, XXXXXXX, KC_HOME, KC_PGDN, KC_END,  PREVDTP, NEXTDTP, PREVTAB, NEXTTAB, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, _______,
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,
                                   _______, _______, _______, _______, _______, _______, _______, _______
    )
};
