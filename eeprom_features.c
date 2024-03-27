#ifndef REPEAT_DELAY
    #define REPEAT_DELAY 175
#endif
#ifndef REPEAT_TERM
    #define REPEAT_TERM 10
#endif

#ifndef LAYER_LIGHT_MODE
#define LAYER_LIGHT_MODE RGBLIGHT_MODE_STATIC_LIGHT
#endif

// typedef union {
//   uint32_t raw;
//   struct {
//     bool    repeat_enabled :1;
//     bool    caps_flash_enabled :1;
//     bool    repeat_numbers :1;
//     bool    repeat_alphas :1;
//     bool    repeat_mods :1;
//     bool    caps_twinkle :1;
//     bool    repeat_alphas1 :1;
//     bool    repeat_mods1 :1;
//     uint8_t repeat_delay :8;
//     uint8_t repeat_rate :8;
//     uint8_t caps_hue :8;
//   };
// } user_config_t;
typedef union {
  uint32_t raw;
  struct {
    bool    repeat_enabled;
    bool    caps_flash_enabled;
    bool    repeat_numbers;
    bool    repeat_alphas;
    bool    repeat_mods;
    bool    caps_twinkle;
    bool    repeat_alphas1;
    bool    repeat_mods1;
    uint8_t repeat_delay;
    uint8_t repeat_rate;
    uint8_t caps_hue;
  };
} user_config_t;

user_config_t user_config;

typedef union {
  uint32_t raw;
  struct {
    uint8_t led_brightness;
    uint8_t typing_hue;
    uint8_t gaming_hue;
    uint8_t mods_hue;
  };
} user_lighting_t;

user_lighting_t user_lighting;


void keyboard_post_init_user(void) {
  eeconfig_read_user_datablock(&user_config.raw);
  eeconfig_read_user_datablock(&user_lighting.raw);
  rgblight_sethsv(user_lighting.typing_hue, 255, user_lighting.led_brightness);
}

void eeconfig_init_user(void) { //Changed from datablock
  user_config.raw = 0;
  user_config.repeat_enabled = 1;
  user_config.caps_flash_enabled = 1;
  user_config.repeat_alphas = 1;
  user_config.repeat_numbers = 0;
  user_config.repeat_mods = 0;
  user_config.repeat_alphas1 = 1;
  user_config.caps_twinkle = 0;
  user_config.repeat_mods1 = 0;
  user_config.repeat_delay = REPEAT_DELAY;
  user_config.repeat_rate = REPEAT_TERM;
  user_config.caps_hue = 36; // Gold

  user_lighting.raw = 0;
  user_lighting.led_brightness = 255;
  user_lighting.typing_hue = 191; //Magenta
  user_lighting.gaming_hue = 128; //Cyan
  user_lighting.mods_hue = 85; //Green

  eeconfig_update_user_datablock(&user_config.raw); 
  eeconfig_update_user_datablock(&user_lighting.raw);
}

