/* SPDX-License-Identifier: GPL-2.0-or-later */

#include "aic6l.h"


/* VIA-specifiable colors for RGB indicators
   Order and behavior of the 3 LEDs are as chosen by the board designer */

#ifdef VIA_ENABLE

#include "eeprom.h"

/* Default configs
   Simple white medium brightness if left unconfigured */
via_config g_config = {
    .indicator_caps_lock_color = {128, 128, 128},
    .indicator_layer_1_color   = {128, 128, 128},
    .indicator_layer_2_color   = {128, 128, 128}
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
    // If the EEPROM has the magic, the data is good.
    // OK to load from EEPROM
    if (via_eeprom_is_valid()) {
        values_load();
    } else	{
        values_save();
        // DO NOT set EEPROM valid here, let caller do this
    }
}

void via_custom_value_command_kb(uint8_t *data, uint8_t length) {
  // data = [ command_id, channel_id, value_id, value_data ]
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
              // Unhandled message.
              *command_id = id_unhandled;
              break;
          }
      }
      return;
  }

  // Return the unhandled state
  *command_id = id_unhandled;

  // DO NOT call raw_hid_send(data,length) here, let caller do this
}

void via_config_set_value( uint8_t *data )
{
    // data = [ value_id, value_data ]
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch ( *value_id )
    {
        case indicator_caps_lock_color:
            _set_color( &(g_config.indicator_caps_lock_color), value_data );
            break;
        case indicator_layer_1_color:
            _set_color( &(g_config.indicator_layer_1_color), value_data );
            break;
        case indicator_layer_2_color:
            _set_color( &(g_config.indicator_layer_2_color), value_data );
            break;
    }
}

void via_config_get_value( uint8_t *data )
{
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch ( *value_id )
    {
        case indicator_caps_lock_color:
            _get_color( &(g_config.indicator_caps_lock_color), value_data );
            break;
        case indicator_layer_1_color:
            _get_color( &(g_config.indicator_layer_1_color), value_data );
            break;
        case indicator_layer_2_color:
            _get_color( &(g_config.indicator_layer_2_color), value_data );
            break;
    }
}

// Some helpers for setting/getting HSV
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

#endif /* VIA_ENABLE */
