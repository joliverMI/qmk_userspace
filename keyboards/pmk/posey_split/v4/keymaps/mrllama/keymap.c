// Copyright 2024 Javier Oliver (@joliverMI)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H


//System Layers
#define _QWERTY 0
#define _NAV 1
#define _SYMB 2
#define _GAME1 4
#define _GAME3 6
#define _PLAYERS 7

#define STARTING_GAMING_LAYER 4
#define ENDING_GAMING_LAYER 6
#define MAX_LAYERS 8

enum custom_keycodes {
   QWERTY = SAFE_RANGE,
   L_SYMB,
   L_NAV,
   L_GAME_1,
   L_DIABLO,
   //players
   L_PLAY,
   PL_1,
   PL_2,
   PL_3,
   PL_4,
   PL_5,
   PL_6,
   PL_7,
   PL_8
};

// System Layers
#define L_SYMB   LT(_SYMB, KC_F7)
#define L_NAV    MO(_NAV)
#define L_QWRT   TO(_QWERTY)

// Layer Switch Shortcuts
#define L_G1     TO(_GAME1)
#define L_DIA    TO(_GAME3)
#define L_PLAY   OSL(_PLAYERS)

#include "diablo_player_change.c"

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
        KC_ESC,  KC_NO,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,    L_SYMB,  KC_F8,   KC_F9,  KC_F10,  KC_F11, KC_F12, KC_PAUS, KC_DEL,
     //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼───────┤ ├────────┼────────┼────────┼────────┼────────┼────────┼────────┴───────┤
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,     KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,   KC_BACKSPACE,
     //├────────┴────────┼────────┼────────┼────────┼────────┼────────┼───────┤ ├────────┼────────┼────────┼────────┼────────┼────────┼────────┬───────┤
        KC_TAB,           KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
     //├─────────────────┼────────┼────────┼────────┼────────┼────────┼───────┤ ├────────┼────────┼────────┼────────┼────────┼────────┼────────┴───────┤
        KC_CAPS,          KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,      KC_ENT,
     //├─────────────────┼────────┼────────┼────────┼────────┼────────┼───────┤ ├────────┼────────┼────────┼────────┼────────┼────────┼────────────────┤
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,     KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,   KC_RSFT,
     //├──────────┬──────┴─┬───────┼───────┴────────┼────────┴────────┴───────┤ ├────────┴────────┴────────┼────────┼────────┼────────┼────────────────┤
        KC_LCTL,   KC_LGUI, KC_LALT,    L_NAV,           KC_SPC,                       KC_SPC,                L_NAV, KC_RGUI, KC_RALT, KC_APP,  KC_RCTL
     //└──────────┴────────┴───────┴────────────────┴─────────────────────────┘ └──────────────────────────┴────────┴────────┴────────┴───────┴────────┘
    ),
    [_NAV] = LAYOUT(
    // ┌────────┐        ┌────────┬────────┬────────┬────────┬────────┬───────┐ ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┬───────┐
        KC_TRNS, KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_VOLD, KC_VOLU, KC_MUTE, KC_MPRV, KC_MPLY, KC_MNXT,
     //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼───────┤ ├────────┼────────┼────────┼────────┼────────┼────────┼────────┴───────┤
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
     //├────────┴────────┼────────┼────────┼────────┼────────┼────────┼───────┤ ├────────┼────────┼────────┼────────┼────────┼────────┼────────┬───────┤
        KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_PSCR, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
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
        KC_ESC,  KC_NO,   KC_TRNS, KC_TRNS,  KC_TRNS,KC_TRNS,KC_TRNS,  L_QWRT ,  KC_TRNS, L_DIA,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, QK_BOOT,
     //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼───────┤ ├────────┼────────┼────────┼────────┼────────┼────────┼────────┴───────┤
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  L_G1   , KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, QK_CLEAR_EEPROM,
     //├────────┴────────┼────────┼────────┼────────┼────────┼────────┼───────┤ ├────────┼────────┼────────┼────────┼────────┼────────┼────────┬───────┤
        KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
     //├─────────────────┼────────┼────────┼────────┼────────┼────────┼───────┤ ├────────┼────────┼────────┼────────┼────────┼────────┼────────┴───────┤
        KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS,
     //├─────────────────┼────────┼────────┼────────┼────────┼────────┼───────┤ ├────────┼────────┼────────┼────────┼────────┼────────┴────────────────┤
        KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS,
     //├──────────┬──────┴─┬───────┼───────┴────────┼────────┴────────┴───────┤ ├────────┴────────┴────────┼────────┼────────┼────────┼────────────────┤
        KC_TRNS,   KC_TRNS, KC_TRNS,   KC_TRNS,                 KC_TRNS,                   KC_TRNS,         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
     //└──────────┴────────┴───────┴────────────────┴─────────────────────────┘ └──────────────────────────┴────────┴────────┴────────┴───────┴────────┘
    ),
    [_GAME1] = LAYOUT(
    // ┌────────┐        ┌────────┬────────┬────────┬────────┬────────┬───────┐ ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┬───────┐
        KC_TRNS, KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
     //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼───────┤ ├────────┼────────┼────────┼────────┼────────┼────────┼────────┴───────┤
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,
     //├────────┴────────┼────────┼────────┼────────┼────────┼────────┼───────┤ ├────────┼────────┼────────┼────────┼────────┼────────┼────────┬───────┤
        KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
     //├─────────────────┼────────┼────────┼────────┼────────┼────────┼───────┤ ├────────┼────────┼────────┼────────┼────────┼────────┼────────┴───────┤
        KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,        KC_TRNS,
     //├─────────────────┼────────┼────────┼────────┼────────┼────────┼───────┤ ├────────┼────────┼────────┼────────┼────────┼────────┴────────────────┤
        KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS,
     //├──────────┬──────┴─┬───────┼───────┴────────┼────────┴────────┴───────┤ ├────────┴────────┴────────┼────────┼────────┼────────┼────────────────┤
        KC_TRNS,   KC_TRNS, KC_TRNS,    KC_TRNS,                    KC_TRNS,                   KC_TRNS,        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS
     //└──────────┴────────┴───────┴────────────────┴─────────────────────────┘ └──────────────────────────┴────────┴────────┴────────┴───────┴────────┘
    ),
    [_GAME3] = LAYOUT(
    // ┌────────┐        ┌────────┬────────┬────────┬────────┬────────┬───────┐ ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┬───────┐
        KC_TRNS, KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
     //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼───────┤ ├────────┼────────┼────────┼────────┼────────┼────────┼────────┴───────┤
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,
     //├────────┴────────┼────────┼────────┼────────┼────────┼────────┼───────┤ ├────────┼────────┼────────┼────────┼────────┼────────┼────────┬───────┤
        KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
     //├─────────────────┼────────┼────────┼────────┼────────┼────────┼───────┤ ├────────┼────────┼────────┼────────┼────────┼────────┼────────┴───────┤
        KC_TRNS,            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,        KC_TRNS,
     //├─────────────────┼────────┼────────┼────────┼────────┼────────┼───────┤ ├────────┼────────┼────────┼────────┼────────┼────────┴────────────────┤
        KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS,
     //├──────────┬──────┴─┬───────┼───────┴────────┼────────┴────────┴───────┤ ├────────┴────────┴────────┼────────┼────────┼────────┼────────────────┤
        KC_TRNS,   L_PLAY, KC_TRNS,    KC_TRNS,          KC_TRNS,                   KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS
     //└──────────┴────────┴───────┴────────────────┴─────────────────────────┘ └──────────────────────────┴────────┴────────┴────────┴───────┴────────┘
    ),
    [_PLAYERS] = LAYOUT(
    // ┌────────┐        ┌────────┬────────┬────────┬────────┬────────┬───────┐ ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┬───────┐
        KC_TRNS, KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
     //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼───────┤ ├────────┼────────┼────────┼────────┼────────┼────────┼────────┴───────┤
        PL_8    ,PL_1    ,PL_2    ,PL_3    ,PL_4    ,PL_5    ,PL_6    ,PL_7,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,
     //├────────┴────────┼────────┼────────┼────────┼────────┼────────┼───────┤ ├────────┼────────┼────────┼────────┼────────┼────────┼────────┬───────┤
        KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
     //├─────────────────┼────────┼────────┼────────┼────────┼────────┼───────┤ ├────────┼────────┼────────┼────────┼────────┼────────┼────────┴───────┤
        KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS,
     //├─────────────────┼────────┼────────┼────────┼────────┼────────┼───────┤ ├────────┼────────┼────────┼────────┼────────┼────────┴────────────────┤
        KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS,
     //├──────────┬──────┴─┬───────┼───────┴────────┼────────┴────────┴───────┤ ├────────┴────────┴────────┼────────┼────────┼────────┼────────────────┤
        KC_TRNS,   KC_TRNS, KC_TRNS,    KC_TRNS,                 KC_TRNS,                   KC_TRNS,        KC_TRNS, KC_TRNS, KC_TRNS ,KC_TRNS,KC_TRNS
     //└──────────┴────────┴───────┴────────────────┴─────────────────────────┘ └──────────────────────────┴────────┴────────┴────────┴───────┴────────┘
    )
};

// Light adjustments
#include "color_user_layer_settings - via.c"
