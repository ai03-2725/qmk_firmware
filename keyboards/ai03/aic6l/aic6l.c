/* SPDX-License-Identifier: GPL-2.0-or-later */

#include "aic6l.h"


/* VIA-specifiable colors for RGB indicators
   Order and behavior of the 3 LEDs are as chosen by the board designer */

#ifdef RGB_MATRIX_ENABLE
#ifdef VIA_ENABLE

#include "eeprom.h"

/* Default configs
   Simple white medium brightness if left unconfigured */
via_config g_config = {
    .caps_indicator_enabled = 0,
    .caps_indicator_color = {0, 0, 128},
    .layers_indicator_enabled = 0
};

void values_load(void)
{
    eeprom_read_block( &g_config, ((void*)VIA_EEPROM_CUSTOM_CONFIG_ADDR), sizeof(g_config) );
}

void values_save(void)
{
    eeprom_update_block( &g_config, ((void*)VIA_EEPROM_CUSTOM_CONFIG_ADDR), sizeof(g_config) );
}

void via_init_kb(void)
{
    /* If the EEPROM has the magic, the data is good.
       OK to load from EEPROM */
    if (via_eeprom_is_valid()) {
        values_load();
    } else	{
        values_save();
        /* DO NOT set EEPROM valid here, let caller do this */
    }
}

void _set_color( HSV *color, uint8_t *data )
{
    color->h = data[0];
    color->s = data[1];
}

void _get_color( HSV *color, uint8_t *data )
{
    data[0] = color->h;
    data[1] = color->s;
}

void via_config_set_value( uint8_t *data )
{
    /* data = [ value_id, value_data ] */
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch ( *value_id )
    {
        case id_caps_indicator_enabled:
            g_config.caps_indicator_enabled = *value_data;
            break;
        case id_caps_indicator_brightness:
            g_config.caps_indicator_color.v = *value_data;
            break;
        case id_caps_indicator_color:
            _set_color( &(g_config.caps_indicator_color), value_data );
            break;
        case id_layers_indicator_enabled:
            g_config.layers_indicator_enabled = *value_data;
            break;
    }
}

void via_config_get_value( uint8_t *data )
{
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch ( *value_id )
    {
        case id_caps_indicator_enabled:
            *value_data = g_config.caps_indicator_enabled;
            break;
        case id_caps_indicator_brightness:
            *value_data = g_config.caps_indicator_color.v;
            break;
        case id_caps_indicator_color:
            _get_color( &(g_config.caps_indicator_color), value_data );
            break;
        case id_layers_indicator_enabled:
            *value_data = g_config.layers_indicator_enabled;
            break;
    }
}

void via_custom_value_command_kb(uint8_t *data, uint8_t length) {
  /* data = [ command_id, channel_id, value_id, value_data ] */
  uint8_t *command_id        = &(data[0]);
  uint8_t *channel_id        = &(data[1]);
  uint8_t *value_id_and_data = &(data[2]);

  if ( *channel_id == id_custom_channel ) {
      switch ( *command_id )
      {
          case id_custom_set_value:
          {
              via_config_set_value(value_id_and_data);
              break;
          }
          case id_custom_get_value:
          {
              via_config_get_value(value_id_and_data);
              break;
          }
          case id_custom_save:
          {
              values_save();
              break;
          }
          default:
          {
              /* Unhandled message */
              *command_id = id_unhandled;
              break;
          }
      }
      return;
  }

  /* Return the unhandled state */
  *command_id = id_unhandled;

  /* DO NOT call raw_hid_send(data,length) here, let caller do this */
}


// INDICATOR CALLBACK ------------------------------------------------------------------------------
/* LED index to physical position
 *
 * LED0 | LED1 | LED2
 * -----+------+-----
 * Caps |  OFF | OFF  | Layer 0 active
 * Caps |  OFF | ON   | Layer 1 active
 * Caps |  ON  | OFF  | Layer 2 active
 * Caps |  ON  | ON   | Layer 3 active
 */
bool rgb_matrix_indicators_kb(void) {
    if (g_config.caps_indicator_enabled) {
        /* Get VIA indicator state */
        RGB rgb_caps_indicator_color = hsv_to_rgb( (HSV){ .h = g_config.caps_indicator_color.h,
                                                          .s = g_config.caps_indicator_color.s,
                                                          .v = g_config.caps_indicator_color.v } );
        if (host_keyboard_led_state().caps_lock)
            rgb_matrix_set_color(CAPS_INDICATOR_INDEX, rgb_caps_indicator_color.r, rgb_caps_indicator_color.g, rgb_caps_indicator_color.b);
        else
            rgb_matrix_set_color(CAPS_INDICATOR_INDEX, 0, 0, 0);
    } else {
        rgb_matrix_set_color(CAPS_INDICATOR_INDEX, 0, 0, 0);
    }

    if (g_config.layers_indicator_enabled) {
        if (IS_LAYER_ON(3)) {
            if (true) {
                // Trick if statement to execute the check and exit early if layer 3 is active
            }
        } else if (IS_LAYER_ON(2)) {
            rgb_matrix_set_color(LAYERS_INDICATOR_INDEX_RIGHT, 0, 0, 0);
        } else if (IS_LAYER_ON(1)) {
            rgb_matrix_set_color(LAYERS_INDICATOR_INDEX_LEFT, 0, 0, 0);
        } else if (IS_LAYER_ON(0)) {
            rgb_matrix_set_color(LAYERS_INDICATOR_INDEX_LEFT, 0, 0, 0);
            rgb_matrix_set_color(LAYERS_INDICATOR_INDEX_RIGHT, 0, 0, 0);
        }
    } else {
        rgb_matrix_set_color(LAYERS_INDICATOR_INDEX_LEFT, 0, 0, 0);
        rgb_matrix_set_color(LAYERS_INDICATOR_INDEX_RIGHT, 0, 0, 0);
    }
    return true;
}

#endif /* VIA_ENABLE */
#endif /* RGB_MATRIX_ENABLE */
