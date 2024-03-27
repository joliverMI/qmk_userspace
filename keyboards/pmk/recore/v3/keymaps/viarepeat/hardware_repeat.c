// Copyright 2024 Javier Oliver (@joliverMI)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include QMK_KEYBOARD_H

#ifndef REPEAT_DELAY
    #define REPEAT_DELAY 150
#endif
#ifndef REPEAT_TERM
    #define REPEAT_TERM 6
#endif
#ifdef REPEAT_ALL_KEYS_ENABLED
    #define REPEAT_ALPHAS_ENABLED
    #define REPEAT_NUMBERS_ENABLED
    #define REPEAT_MODS_ENABLED
    #define REPEAT_FROW_ENABLED
#endif

#define ALPHA_REPEATS KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y,\
                      KC_A, KC_S, KC_D, KC_F, KC_G, KC_H,\
                      KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N,\
                      KC_Y, KC_U, KC_I, KC_O, KC_P,\
                      KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,\
                      KC_M, KC_COMM, KC_DOT, KC_SLSH
#define NUM_REPEATS   KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_GRV,\
                      KC_8, KC_9, KC_0, KC_EQL, KC_MINS
#define MOD_REPEATS   KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7,\
                      KC_TAB, KC_ESC, KC_CAPS, KC_LSFT, KC_LCTL, KC_LALT, KC_SPC,\
                      KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_BSPC, KC_DEL

static uint16_t key_timer = 0;
static bool key_pressed = false;
static bool key_repeating = false;
static uint8_t key_repeat = 0;
static bool key_last_send_press = false;


static uint16_t repeat_delay = REPEAT_DELAY;
static uint8_t repeat_term = REPEAT_TERM;

static uint8_t alpha_repeats[] = {ALPHA_REPEATS};
static uint8_t num_repeats[] = {NUM_REPEATS};
static uint8_t mod_repeats[] = {MOD_REPEATS};

#ifdef BOOSTED_REPEAT_ENABLED
    #ifndef BOOSTED_REPEAT_DELAY
    #define BOOSTED_REPEAT_DELAY REPEAT_DELAY
    #endif
    #ifndef BOOSTED_REPEAT_TERM
    #define BOOSTED_REPEAT_TERM REPEAT_TERM
    #endif
static uint16_t keys_to_boost[] = { BOOSTED_REPEAT_KEYS };
#ifdef BOOSTED2_REPEAT_ENABLED
    #ifndef BOOSTED2_REPEAT_DELAY
    #define BOOSTED2_REPEAT_DELAY BOOSTED_REPEAT_DELAY
    #endif
    #ifndef BOOSTED2_REPEAT_TERM
    #define BOOSTED2_REPEAT_TERM BOOSTED_REPEAT_TERM
    #endif
static uint16_t keys_to_boost2[] = { BOOSTED2_REPEAT_KEYS };
#endif
#endif

static uint16_t layers_to_check[] = { FAST_REPEAT_LAYERS };

bool check_large_layer(void){
    for (int i = 0; i < FAST_REPEAT_LAYER_COUNT; i++){
        if (IS_LAYER_ON(layers_to_check[i])){
            return true;
        }
    }
    return false;
}

bool is_repeat_key(uint8_t keycode){
    // if (user_config.repeat_numbers && user_config.repeat_alphas && user_config.repeat_mods) {
    //     return true;
    // } else {
        if (user_config.repeat_numbers) {
            for (uint8_t i=0; i < sizeof(num_repeats); i++) {
                if (keycode == num_repeats[i]) {
                    return true;
                }
            }
        }
        if (user_config.repeat_alphas) {
            for (uint8_t i=0; i < sizeof(alpha_repeats); i++) {
                if (keycode == alpha_repeats[i]) {
                    return true;
                }
            }
        }
        if (user_config.repeat_mods) {
            for (uint8_t i=0; i < sizeof(mod_repeats); i++) {
                if (keycode == mod_repeats[i]) {
                    return true;
                }
            }
        }
    // }
    return false;
}

void set_timers(uint16_t keycode){
    key_timer = timer_read();
    repeat_delay = user_config.repeat_delay;
    repeat_term = user_config.repeat_rate;
}

#ifdef BOOSTED_REPEAT_ENABLED
bool check_if_boosted_key(uint8_t keycode){
    for (int i = 0; i < BOOSTED_REPEAT_KEY_COUNT; i++){
        if (keys_to_boost[i] == keycode){
            return true;
        }
    }
    return false;
}
#ifdef BOOSTED2_REPEAT_ENABLED
bool check_if_boosted2_key(uint8_t keycode){
    for (int i = 0; i < BOOSTED2_REPEAT_KEY_COUNT; i++){
        if (keys_to_boost2[i] == keycode){
            return true;
        }
    }
    return false;
}
#endif
#endif

bool process_repeat_key(uint16_t keycode, keyrecord_t *record) {
    if (check_large_layer()){
        if (is_repeat_key(keycode)) {
            if (record->event.pressed){
                if (keycode!=key_repeat) {
                    key_repeating = false;
                }
                register_code(keycode);

                key_repeat = keycode;
                key_pressed = true;
                set_timers(keycode);
            } else {
                unregister_code(keycode);
                if (keycode==key_repeat) {
                    key_pressed = false;
                    key_repeating = false;
                    key_last_send_press = false;
                }
            }
            return false;
        }
    } else if (key_pressed) {
        key_pressed = false;
        key_repeating = false;
    }
    return true;
}

void matrix_scan_user(void) { 
    if (key_pressed) {
        if (!key_repeating && timer_elapsed(key_timer) > repeat_delay) {
            key_repeating = true;
            key_last_send_press = true;
            key_timer = timer_read();
        }
        if (key_repeating) {
            if (!key_last_send_press) {
                register_code(key_repeat);
                key_last_send_press = true;
            } else if (timer_elapsed(key_timer) > repeat_term) {
                key_timer = timer_read();
                unregister_code(key_repeat);
                key_last_send_press = false;
            }
        }
    }
}