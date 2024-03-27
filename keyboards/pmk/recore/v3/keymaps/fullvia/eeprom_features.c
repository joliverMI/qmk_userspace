#ifndef REPEAT_DELAY
    #define REPEAT_DELAY 150
#endif
#ifndef REPEAT_TERM
    #define REPEAT_TERM 6
#endif

#ifndef LAYER_LIGHT_MODE
#define LAYER_LIGHT_MODE RGBLIGHT_MODE_STATIC_LIGHT
#endif

typedef union {
  uint32_t raw;
  struct {
    bool    repeat_enabled :1;
    bool    caps_flash_enabled :1;
    bool    repeat_numbers :1;
    bool    repeat_alphas :1;
    bool    repeat_mods :1;
    uint8_t repeat_delay :8;
    uint8_t repeat_rate :8;
  };
} user_config_t;

user_config_t user_config;


void keyboard_post_init_user(void) {
  // Call the keymap level matrix init.

  // Read the user config from EEPROM
  user_config.raw = eeconfig_read_user();
}

void eeconfig_init_user(void) {  // EEPROM is getting reset!
  user_config.raw = 0;
  user_config.repeat_enabled = false;
  user_config.caps_flash_enabled = true;
  user_config.repeat_alphas = true;
  user_config.repeat_numbers = true;
  user_config.repeat_mods = false;
  user_config.repeat_delay = REPEAT_DELAY;
  user_config.repeat_rate = REPEAT_TERM;

  eeconfig_update_user_datablock(&user_config.raw); // Write default value to EEPROM now
}