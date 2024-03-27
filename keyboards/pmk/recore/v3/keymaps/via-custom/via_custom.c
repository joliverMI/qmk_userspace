enum via_buttglow_value {
    id_buttglow_brightness   = 1,
    id_buttglow_effect       = 2,
    id_buttglow_effect_speed = 3,
    id_buttglow_color        = 4
};

void buttglow_config_set_value( uint8_t *data )
{
    // data = [ value_id, value_data ]
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch ( *value_id )
    {
        case id_buttglow_brightness:
        {
            user_config.rgb_layer_change = *value_data; // Toggles the status
            if (user_config.rgb_layer_change) { // if layer state indication is enabled,
                layer_state_set(layer_state);   // then immediately update the layer color
            }
            break;
        }
    }
}

void buttglow_config_get_value( uint8_t *data )
{
    // data = [ value_id, value_data ]
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch ( *value_id )
    {
        case id_buttglow_brightness:
        {
            *value_data = user_config.rgb_layer_change;
            break;
        }
    }
}

void buttglow_config_save(void)
{
    eeconfig_update_user(user_config.raw); // Writes the new status to EEPROM
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
                buttglow_config_set_value(value_id_and_data);
                break;
            }
            case id_custom_get_value:
            {
                buttglow_config_get_value(value_id_and_data);
                break;
            }
            case id_custom_save:
            {
                buttglow_config_save();
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