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
    bool    boost_1_enabled: 1;
    bool    boost_2_enabled: 1;
    bool    boost_3_enabled: 1;
    uint8_t repeat_delay :8;
    uint8_t repeat_rate :8;
  };
} user_config_t;

user_config_t user_config;

typedef union {
  uint32_t raw;
  struct {
    uint8_t led_brightness : 8;
    uint8_t typing_hue :8;
    uint8_t gaming_hue :8;
    uint8_t mods_hue :8;
  };
} user_lighting_t;

user_lighting_t user_lighting;

typedef union {
  uint32_t raw;
  struct {
    uint8_t rates : 8;
    uint8_t code_1 :8;
    uint8_t code_2 :8;
    uint8_t code_3 :8;
  };
} boost_1_t;

boost_1_t user_boost_1;

// typedef union {
//   uint32_t raw;
//   struct {
//     uint8_t rates : 8;
//     uint8_t code_1 :8;
//     uint8_t code_2 :8;
//     uint8_t code_3 :8;
//   };
// } boost_2_t;

// boost_2_t user_boost_2;

// typedef union {
//   uint32_t raw;
//   struct {
//     uint8_t rates : 8;
//     uint8_t code_1 :8;
//     uint8_t code_2 :8;
//     uint8_t code_3 :8;
//   };
// } boost_3_t;

// boost_3_t user_boost_3;

uint8_t get_delay_from_rates(uint8_t rates){
  return (rates >> 3) + 100;
}

uint8_t get_term_from_rates(uint8_t rates){
  return (rates & 0x7) + 5;
}

uint8_t get_rates_from_delay_and_term(uint8_t delay, uint8_t term){
  return ((delay-100) << 3) | ((term & 0x7) - 5);
}


void keyboard_post_init_user(void) {
  eeconfig_read_user_datablock(&user_config.raw);
  eeconfig_read_user_datablock(&user_lighting.raw);
  eeconfig_read_user_datablock(&user_boost_1.raw);
  // if (user_config.boost_2_enabled) {
  //   eeconfig_read_user_datablock(&user_boost_2.raw);
  // }
  // if (user_config.boost_3_enabled) {
  //   eeconfig_read_user_datablock(&user_boost_3.raw);
  // }
}

void eeconfig_init_user(void) { 
  user_config.raw = 0;
  user_config.repeat_enabled = true;
  user_config.caps_flash_enabled = true;
  user_config.repeat_alphas = true;
  user_config.repeat_numbers = true;
  user_config.repeat_mods = false;
  user_config.repeat_delay = REPEAT_DELAY;
  user_config.repeat_rate = REPEAT_TERM;
  user_config.boost_1_enabled = true;
  user_config.boost_2_enabled = false;
  user_config.boost_3_enabled = false;

  user_lighting.raw = 0;
  user_lighting.led_brightness = 255;
  user_lighting.typing_hue = 213; //Magenta
  user_lighting.gaming_hue = 128; //Cyan
  user_lighting.mods_hue = 85; //Green

  user_boost_1.rates = get_rates_from_delay_and_term(REPEAT_DELAY, REPEAT_TERM);
  // user_boost_2.rates = get_rates_from_delay_and_term(REPEAT_DELAY, REPEAT_TERM);
  // user_boost_3.rates = get_rates_from_delay_and_term(REPEAT_DELAY, REPEAT_TERM);

  user_boost_1.code_1 = 0x0000;
  user_boost_1.code_2 = 0x0000;
  user_boost_1.code_3 = 0x0000;
  // user_boost_2.code_1 = 0x0000;
  // user_boost_2.code_2 = 0x0000;
  // user_boost_2.code_3 = 0x0000;
  // user_boost_3.code_1 = 0x0000;
  // user_boost_3.code_2 = 0x0000;
  // user_boost_3.code_3 = 0x0000;

  eeconfig_update_user_datablock(&user_config.raw); 
  eeconfig_update_user_datablock(&user_lighting.raw);
  eeconfig_update_user_datablock(&user_boost_1.raw);
  // eeconfig_update_user_datablock(&user_boost_2.raw);
  // eeconfig_update_user_datablock(&user_boost_3.raw);

  

}