#pragma once

enum via_repeat_value {
    id_repeat_enabled       = 1,
    id_caps_flash_enabled   = 2,
    id_repeat_numbers       = 3,
    id_repeat_alphas        = 4,
    id_repeat_mods          = 5,
    id_repeat_delay         = 6,
    id_repeat_rate          = 7,
    id_led_brightness       = 8,
    id_typing_color         = 9,
    id_gaming_color         = 10,
    id_mods_color           = 11
};

void basic_config_set_value( uint8_t *data )
{
    // data = [ value_id, value_data ]
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch ( *value_id )
    {
        case id_repeat_enabled:
        {
            user_config.repeat_enabled = *value_data;
            break;
        }
        case id_caps_flash_enabled:
        {
            user_config.caps_flash_enabled = *value_data;
            break;
        }
        case id_repeat_numbers:
        {
            user_config.repeat_numbers = *value_data;
            break;
        }
        case id_repeat_alphas:
        {
            user_config.repeat_alphas = *value_data;
            break;
        }
        case id_repeat_mods:
        {
            user_config.repeat_mods = *value_data;
            break;
        }
        case id_repeat_delay:
        {
            user_config.repeat_delay = *value_data;
            break;
        }
        case id_repeat_rate:
        {
            user_config.repeat_rate = *value_data;
            break;
        }
        case id_led_brightness:
        {
            user_lighting.led_brightness = *value_data;
            break;
        }
        case id_typing_color:
        {
            user_lighting.typing_hue = value_data[0];
            break;
        }
        case id_mods_color:
        {
            user_lighting.mods_hue = value_data[0];
            break;
        }
        case id_gaming_color:
        {
            user_lighting.gaming_hue = value_data[0];
            break;
        }
    }
}

void basic_config_get_value( uint8_t *data )
{
    // data = [ value_id, value_data ]
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch ( *value_id )
    {
        case id_repeat_enabled:
        {
            *value_data = user_config.repeat_enabled;
            break;
        }
        case id_caps_flash_enabled:
        {
            *value_data = user_config.caps_flash_enabled;
            break;
        }
        case id_repeat_numbers:
        {
            *value_data = user_config.repeat_numbers;
            break;
        }
        case id_repeat_alphas:
        {
            *value_data = user_config.repeat_alphas;
            break;
        }
        case id_repeat_mods:
        {
            *value_data = user_config.repeat_mods;
            break;
        }
        case id_repeat_delay:
        {
            *value_data = user_config.repeat_delay;
            break;
        }
        case id_repeat_rate:
        {
            *value_data = user_config.repeat_rate;
            break;
        }
        case id_led_brightness:
        {
            *value_data = user_lighting.led_brightness;
            break;
        }
        case id_typing_color:
        {
            value_data[0] = user_lighting.typing_hue;
            value_data[1] = 255;
            break;
        }
        case id_mods_color:
        {
            value_data[0] = user_lighting.mods_hue;
            value_data[1] = 255;
            break;
        }
        case id_gaming_color:
        {
            value_data[0] = user_lighting.gaming_hue;
            value_data[1] = 255;
            break;
        }
}

void basic_config_save(void)
{
    eeconfig_update_user_datablock(&user_config.raw);
    eeconfig_update_user_datablock(&user_lighting.raw);
}

void via_custom_value_command_kb(uint8_t *data, uint8_t length) {
    // data = [ command_id, channel_id, value_id, value_data ]
    uint8_t *command_id        = &(data[0]);
    uint8_t *channel_id        = &(data[1]);
    uint8_t *value_id_and_data = &(data[2]);

    if (*channel_id == id_custom_channel) {
        switch ( *command_id )
        {
            case id_custom_set_value:
            {
                basic_config_set_value(value_id_and_data);
                break;
            }
            case id_custom_get_value:
            {
                basic_config_get_value(value_id_and_data);
                break;
            }
            case id_custom_save:
            {
                basic_config_save();
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