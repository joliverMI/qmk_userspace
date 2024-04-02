// Copyright 2024 Javier Oliver (@joliverMI)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H


//System Layers
#define _QWERTY 0
#define _NAV 1
#define _SYMB 2
#define _GAME1 4

#define STARTING_GAMING_LAYER 4
#define ENDING_GAMING_LAYER 6
#define MAX_LAYERS 8

#define REPEAT_ENABLED

#include "via_custom.c"
#include "hardware_repeat - via.c"
#include "custom_user_scripting - via.c"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┬───┬───┬───┬───┐      ┌───┬───┬───┬───┬───┬───┬───┬───┐
     * │Esc│LED│F1 │F2 │F3 │F4 │F5 │F6 │      │L1 │F7 │F8 │F9 │F10│F11│PAS│Del│ 16
     * ├───┼───┼───┼───┼───┼───┼───┴───┤      ├───┴───┼───┼───┼───┼───┼───┴───┤
     * │ ` │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │      │7  │8  │ 9 │ 0 │ - │ = │ Backsp│ 15
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┘    ┌─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤ 
     * │ Tab │ Q │ W │ E │ R │ T │ Y │      │ Y │ U │ I │ O │ P │ [ │ ] │  \  │ 15
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐     └┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
     * │ Caps │ A │ S │ D │ F │ G │ H │      │ H │J  │ K │ L │ ; │ ' │  Enter │ 14
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┐  ┌─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤
     * │ Shift  │ Z │ X │ C │ V │ B │ N │  │ B │ N │ M │ , │ . │ / │    Shift │ 14
     * ├────┬───┴┬──┴┬──┴───┴┬──┴───┴───┤  └┬──┴───┴─┬─┴──┬┴───┴───┴┬─────────┤
     * │Ctrl│GUI │L2 │Alt    │          │   │        | L3 │ Alt│ GUI│Menu│Ctrl│ 11
     * └────┴────┴───┴───────┴──────────┘   └────────┴────┴────┴────┴────┴────┘
     */
    [_QWERTY] = LAYOUT(
    // ┌────────┐        ┌────────┬────────┬────────┬────────┬────────┬───────┐ ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┬───────┐
        KC_ESC,  KC_NO,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,    KC_F6,LT(_SYMB, KC_F7),KC_F8,KC_F9,  KC_F10,  KC_F11, KC_F12, KC_PAUS, KC_DEL,
     //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼───────┤ ├────────┼────────┼────────┼────────┼────────┼────────┼────────┴───────┤
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,     KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,   KC_BACKSPACE,
     //├────────┴────────┼────────┼────────┼────────┼────────┼────────┼───────┤ ├────────┼────────┼────────┼────────┼────────┼────────┼────────┬───────┤
        KC_TAB,           KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
     //├─────────────────┼────────┼────────┼────────┼────────┼────────┼───────┤ ├────────┼────────┼────────┼────────┼────────┼────────┼────────┴───────┤
        KC_CAPS,          KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,      KC_ENT,
     //├─────────────────┼────────┼────────┼────────┼────────┼────────┼───────┤ ├────────┼────────┼────────┼────────┼────────┼────────┼────────────────┤
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,     KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,   KC_RSFT,
     //├──────────┬──────┴─┬───────┼───────┴────────┼────────┴────────┴───────┤ ├────────┴────────┴────────┼────────┼────────┼────────┼────────────────┤
        KC_LCTL,   KC_LGUI, KC_LALT,    MO(_NAV),           KC_SPC,                       KC_SPC,           MO(_NAV), KC_RGUI, KC_RALT, KC_APP,  KC_RCTL
     //└──────────┴────────┴───────┴────────────────┴─────────────────────────┘ └──────────────────────────┴────────┴────────┴────────┴───────┴────────┘
    ),
    [_NAV] = LAYOUT(
    // ┌────────┐        ┌────────┬────────┬────────┬────────┬────────┬───────┐ ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┬───────┐
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_VOLD, KC_VOLU, KC_MUTE, KC_MPRV, KC_MPLY, KC_MNXT,
     //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼───────┤ ├────────┼────────┼────────┼────────┼────────┼────────┼────────┴───────┤
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
     //├────────┴────────┼────────┼────────┼────────┼────────┼────────┼───────┤ ├────────┼────────┼────────┼────────┼────────┼────────┼────────┬───────┤
        KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
     //├─────────────────┼────────┼────────┼────────┼────────┼────────┼───────┤ ├────────┼────────┼────────┼────────┼────────┼────────┼────────┴───────┤
        KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_ENT,
     //├─────────────────┼────────┼────────┼────────┼────────┼────────┼───────┤ ├────────┼────────┼────────┼────────┼────────┼────────┴────────────────┤
        KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_UP,
     //├──────────┬──────┴─┬───────┼───────┴────────┼────────┴────────┴───────┤ ├────────┴────────┴────────┼────────┼────────┼────────┼────────────────┤
        KC_TRNS,   KC_TRNS, KC_TRNS,  KC_TRNS,                 KC_TRNS,                   KC_TRNS,          KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_RIGHT
     //└──────────┴────────┴───────┴────────────────┴─────────────────────────┘ └──────────────────────────┴────────┴────────┴────────┴───────┴────────┘
    ),
    [_SYMB] = LAYOUT(
    // ┌────────┐        ┌────────┬────────┬────────┬────────┬────────┬───────┐ ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┬───────┐
        KC_ESC,  KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,KC_TRNS,KC_TRNS,TO(_QWERTY),KC_TRNS,TO(_GAME1),KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, QK_BOOT,
     //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼───────┤ ├────────┼────────┼────────┼────────┼────────┼────────┼────────┴───────┤
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, QK_CLEAR_EEPROM,
     //├────────┴────────┼────────┼────────┼────────┼────────┼────────┼───────┤ ├────────┼────────┼────────┼────────┼────────┼────────┼────────┬───────┤
        KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
     //├─────────────────┼────────┼────────┼────────┼────────┼────────┼───────┤ ├────────┼────────┼────────┼────────┼────────┼────────┼────────┴───────┤
        KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS,
     //├─────────────────┼────────┼────────┼────────┼────────┼────────┼───────┤ ├────────┼────────┼────────┼────────┼────────┼────────┴────────────────┤
        KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,      DT_UP,
     //├──────────┬──────┴─┬───────┼───────┴────────┼────────┴────────┴───────┤ ├────────┴────────┴────────┼────────┼────────┼────────┼────────────────┤
        KC_TRNS,   KC_TRNS, KC_TRNS,   KC_TRNS,                 KC_TRNS,                   KC_TRNS,         KC_TRNS, KC_TRNS, DT_PRNT, DT_DOWN, KC_SLEP
     //└──────────┴────────┴───────┴────────────────┴─────────────────────────┘ └──────────────────────────┴────────┴────────┴────────┴───────┴────────┘
    ),
    [_GAME1] = LAYOUT(
    // ┌────────┐        ┌────────┬────────┬────────┬────────┬────────┬───────┐ ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┬───────┐
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
     //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼───────┤ ├────────┼────────┼────────┼────────┼────────┼────────┼────────┴───────┤
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,
     //├────────┴────────┼────────┼────────┼────────┼────────┼────────┼───────┤ ├────────┼────────┼────────┼────────┼────────┼────────┼────────┬───────┤
        KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
     //├─────────────────┼────────┼────────┼────────┼────────┼────────┼───────┤ ├────────┼────────┼────────┼────────┼────────┼────────┼────────┴───────┤
        KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,        KC_TRNS,
     //├─────────────────┼────────┼────────┼────────┼────────┼────────┼───────┤ ├────────┼────────┼────────┼────────┼────────┼────────┴────────────────┤
        KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS,
     //├──────────┬──────┴─┬───────┼───────┴────────┼────────┴────────┴───────┤ ├────────┴────────┴────────┼────────┼────────┼────────┼────────────────┤
        KC_TRNS,   KC_TRNS, KC_TRNS,    KC_P,                    KC_TRNS,                   KC_TRNS,        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS
     //└──────────┴────────┴───────┴────────────────┴─────────────────────────┘ └──────────────────────────┴────────┴────────┴────────┴───────┴────────┘
    )
};

// Light adjustments
#include "color_user_layer_settings - via.c"