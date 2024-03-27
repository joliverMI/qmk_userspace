typedef union {
  uint32_t raw;
  struct {
    bool     rgb_layer_change :1;
  };
} user_config_t;

user_config_t user_config;

#ifndef LAYER_LIGHT_MODE
#define LAYER_LIGHT_MODE RGBLIGHT_MODE_STATIC_LIGHT
#endif

void keyboard_post_init_user(void) {
  // Call the keymap level matrix init.

  // Read the user config from EEPROM
  user_config.raw = eeconfig_read_user();

  // Set default layer, if enabled
  if (user_config.rgb_layer_change) {
    rgblight_enable_noeeprom();
    rgblight_sethsv_noeeprom(C_QWERTY);
    rgblight_mode_noeeprom(LAYER_LIGHT_MODE);
  }
}

void eeconfig_init_user(void) {  // EEPROM is getting reset!
  user_config.raw = 0;
  user_config.rgb_layer_change = true; // We want this enabled by default
  eeconfig_update_user(user_config.raw); // Write default value to EEPROM now

  // use the non noeeprom versions, to write these values to EEPROM too
  rgblight_enable();
  rgblight_sethsv(C_QWERTY);
  rgblight_mode(LAYER_LIGHT_MODE); 
}