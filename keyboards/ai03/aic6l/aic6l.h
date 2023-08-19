/* SPDX-License-Identifier: GPL-2.0-or-later */

#include "quantum.h"


/* VIA-specifiable colors for RGB indicators
   Order and behavior of the 3 LEDs are as chosen by the board designer */

#ifdef VIA_ENABLE

enum via_indicator_value {
    id_indicator_caps_lock_color = 1,
    id_indicator_layer_1_color,
    id_indicator_layer_2_color
};

/* Struct to save configs */
typedef struct {
    HSV indicator_caps_lock_color;
    HSV indicator_layer_1_color;
    HSV indicator_layer_2_color;
} via_config;


/* Function declaration */
void indicator_config_set_value( uint8_t *data );
void indicator_config_get_value( uint8_t *data );
void _set_color(HSV *color, uint8_t *data);
void _get_color(HSV *color, uint8_t *data);

#endif
