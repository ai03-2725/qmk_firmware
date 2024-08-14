/* SPDX-License-Identifier: GPL-2.0-or-later */

#include "quantum.h"


/* VIA-specifiable colors for RGB indicators
   Order and behavior of the 3 LEDs are as chosen by the board designer */

#ifdef VIA_ENABLE

enum via_indicator_value {
    id_caps_indicator_enabled = 1,
    id_caps_indicator_brightness,
    id_caps_indicator_color,
    id_layers_indicator_enabled
};

/* Struct to save configs */
typedef struct {
    bool caps_indicator_enabled:1;   // |
    bool layers_indicator_enabled:1; // 1 byte
    HSV caps_indicator_color;        // 3 bytes
} via_config; // Total 4 bytes


/* Function declaration */
void indicator_config_set_value( uint8_t *data );
void indicator_config_get_value( uint8_t *data );
void _set_color(HSV *color, uint8_t *data);
void _get_color(HSV *color, uint8_t *data);

#endif /* VIA_ENABLE */
