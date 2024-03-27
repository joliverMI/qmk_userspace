// Copyright 2024 Javier Oliver (@joliverMI)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#ifndef LAYER_LIGHT_MODE
#define LAYER_LIGHT_MODE RGBLIGHT_MODE_STATIC_LIGHT
#endif

#ifndef STARTING_GAMING_LAYER
#define STARTING_GAMING_LAYER 3
#define ENDING_GAMING_LAYER 5
#define MAX_LAYERS 8
#endif

void update_led_colors(void) {
   uint8_t layer = biton32(layer_state);
   switch (layer) {
      case 0:
         rgblight_sethsv(user_lighting.typing_hue, 255, user_lighting.led_brightness);
         break;
      case 1 ... STARTING_GAMING_LAYER - 1:
         rgblight_sethsv(user_lighting.mods_hue, 255, user_lighting.led_brightness);
         break;
      case ENDING_GAMING_LAYER + 1 ... MAX_LAYERS - 1:
         rgblight_sethsv(user_lighting.mods_hue, 255, user_lighting.led_brightness);
         break;
      case STARTING_GAMING_LAYER ... ENDING_GAMING_LAYER:
         rgblight_sethsv(user_lighting.gaming_hue, 255, user_lighting.led_brightness);
         break;
   }
}

layer_state_t layer_state_set_user(layer_state_t state) {
   uint8_t layer = biton32(state);
   switch (layer) {
      case 0:
         rgblight_sethsv(user_lighting.typing_hue, 255, user_lighting.led_brightness);
         break;
      case 1 ... STARTING_GAMING_LAYER - 1:
      case ENDING_GAMING_LAYER + 1 ... MAX_LAYERS:
         rgblight_sethsv(user_lighting.mods_hue, 255, user_lighting.led_brightness);
         break;
      case STARTING_GAMING_LAYER ... ENDING_GAMING_LAYER:
         rgblight_sethsv(user_lighting.gaming_hue, 255, user_lighting.led_brightness);
         break;
   }
   // update_led_colors();
   return state;
}
