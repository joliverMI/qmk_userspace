// Copyright 2024 Javier Oliver (@joliverMI)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
   #ifdef DIABLO_PLAYERS_CHANGE_ENABLED
   if (!process_diablo_player_change(keycode, record)) {
      return false;
   }
   #endif
   #ifdef QUICK_GAME_TYPE_ENABLED
   if (!process_quick_game_type(keycode, record)) {
      return false;
   }
   #endif

   if (user_config.repeat_enabled && !process_repeat_key(keycode, record)) {
      return false;
   }

   #ifdef MOD_SPOOF_ENABLED
   if (!process_mod_spoof(keycode, record)) {
      return false;
   }
   #endif
   return true;
};

void caps_activated_script(void) {
   rgblight_mode(RGBLIGHT_MODE_TWINKLE);
}

bool led_update_user(led_t led_state) {
   static uint8_t caps_state = 0;
   if (user_config.caps_flash_enabled && caps_state != led_state.caps_lock) {
      led_state.caps_lock ? caps_activated_script() : rgblight_mode(LAYER_LIGHT_MODE);
      caps_state = led_state.caps_lock;
   }
   return true;
}