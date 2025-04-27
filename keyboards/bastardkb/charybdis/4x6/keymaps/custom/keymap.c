/**
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
#    include "timer.h"
#endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

enum charybdis_keymap_layers {
    LAYER_DEF = 0,
    LAYER_NUFU,
    LAYER_SYM,
    LAYER_NAV,
    LAYER_MOUSE,
};

enum custom_keycodes {
    VS_DEF = SAFE_RANGE,
    VS_IMPL,
    VS_REF,
};

/** \brief Automatically enable sniping-mode on the pointer layer. */
#define CHARYBDIS_AUTO_SNIPING_ON_LAYER LAYER_MOUSE

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
static uint16_t auto_pointer_layer_timer = 0;

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS 1000
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD 8
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#endif     // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

#define NAV_SPC LT(LAYER_NAV, KC_SPC)

#define NUFU_TAB LT(LAYER_NUFU, KC_TAB)
#define MOUSE_Z LT(LAYER_MOUSE, KC_Z)
#define MOUSE_SLSH LT(LAYER_MOUSE, KC_SLSH)

#define SYM MO(LAYER_SYM)

#define GUI_A GUI_T(KC_A)
#define ALT_S ALT_T(KC_S)
#define ALT_L ALT_T(KC_L)
#define ALT_F4 ALT_T(KC_F4)
#define ALT_6 ALT_T(KC_6)

#define CTL_D CTL_T(KC_D)
#define CTL_K CTL_T(KC_K)
#define CTL_F5 CTL_T(KC_F5)
#define CTL_5 CTL_T(KC_5)

#define SFT_F SFT_T(KC_F)
#define SFT_J SFT_T(KC_J)
#define SFT_F6 SFT_T(KC_F6)
#define SFT_4 SFT_T(KC_4)

#define GUI_SCLN GUI_T(KC_SCLN)
#define CTL_ESC CTL_T(KC_ESC)

#ifndef POINTING_DEVICE_ENABLE
#    define DRGSCRL KC_NO
#    define DPI_MOD KC_NO
#    define S_D_MOD KC_NO
#    define SNIPING KC_NO
#endif // !POINTING_DEVICE_ENABLE

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_DEF] = LAYOUT(
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX,
       XXXXXXX,    KC_Q,    KC_W,    KC_E,    KC_R,     KC_T,       KC_Y,    KC_U,    KC_I,    KC_O,       KC_P, XXXXXXX,
       XXXXXXX,   GUI_A,   ALT_S,   CTL_D,   SFT_F,     KC_G,       KC_H,   SFT_J,   CTL_K,   ALT_L,   GUI_SCLN, XXXXXXX,
       XXXXXXX, MOUSE_Z,    KC_X,    KC_C,    KC_V,     KC_B,       KC_N,    KC_M, KC_COMM,  KC_DOT, MOUSE_SLSH, XXXXXXX,
                                  CTL_ESC, NAV_SPC, NUFU_TAB,     KC_ENT, SYM,
                                           XXXXXXX,  XXXXXXX,    XXXXXXX
  ),

  [LAYER_NUFU] = LAYOUT(
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
       XXXXXXX, XXXXXXX,   KC_F7,   KC_F8,   KC_F9,  KC_F12,    XXXXXXX,    KC_7,    KC_8,    KC_9, XXXXXXX, XXXXXXX,
       XXXXXXX, KC_LGUI,  ALT_F4,  CTL_F5,  SFT_F6,  KC_F11,    XXXXXXX,   SFT_4,   CTL_5,   ALT_6, KC_LGUI, XXXXXXX,
       XXXXXXX, XXXXXXX,   KC_F1,   KC_F2,   KC_F3,  KC_F10,    XXXXXXX,    KC_1,    KC_2,    KC_3,    KC_0, XXXXXXX,
                                  XXXXXXX, XXXXXXX, _______,    KC_BSPC,  KC_DEL,
                                           XXXXXXX, XXXXXXX,    XXXXXXX
  ),

  [LAYER_SYM] = LAYOUT(
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
       XXXXXXX, KC_TILD, KC_AMPR, KC_ASTR, KC_PLUS, XXXXXXX,    XXXXXXX, KC_LCBR, KC_RCBR,  KC_GRV, XXXXXXX, XXXXXXX,
       XXXXXXX, KC_MINS,  KC_DLR, KC_PERC, KC_CIRC, XXXXXXX,    XXXXXXX, KC_LPRN, KC_RPRN, KC_QUOT, KC_PIPE, XXXXXXX,
       XXXXXXX, KC_UNDS, KC_EXLM,   KC_AT, KC_HASH, XXXXXXX,    XXXXXXX, KC_LBRC, KC_RBRC, KC_DQUO, KC_BSLS, XXXXXXX,
                                  XXXXXXX,  KC_EQL, XXXXXXX,    XXXXXXX, _______,
                                           XXXXXXX, XXXXXXX,    XXXXXXX
  ),

  [LAYER_NAV] = LAYOUT(
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
       XXXXXXX, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX,    XXXXXXX, KC_LEFT,   KC_UP, KC_DOWN, KC_RGHT, XXXXXXX,
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, KC_HOME, KC_PGUP, KC_PGDN,  KC_END, XXXXXXX,
                                  XXXXXXX, _______, XXXXXXX,    KC_WBAK, KC_WFWD,
                                           XXXXXXX, XXXXXXX,    XXXXXXX
  ),

  [LAYER_MOUSE] = LAYOUT(
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
       XXXXXXX, QK_BOOT,  EE_CLR, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX,  EE_CLR, QK_BOOT, XXXXXXX,
       XXXXXXX, XXXXXXX,  VS_DEF, VS_IMPL,  VS_REF, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
       XXXXXXX, _______, SNIPING, DRGSCRL, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX,
                                  KC_BTN2, KC_BTN1, KC_BTN3,    KC_BTN2, KC_BTN1,
                                           XXXXXXX, XXXXXXX,    XXXXXXX
  ),
};
// clang-format on

#ifdef POINTING_DEVICE_ENABLE
#    ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (abs(mouse_report.x) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD || abs(mouse_report.y) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD) {
        if (auto_pointer_layer_timer == 0) {
            layer_on(LAYER_MOUSE);
#        ifdef RGB_MATRIX_ENABLE
            rgb_matrix_mode_noeeprom(RGB_MATRIX_NONE);
            rgb_matrix_sethsv_noeeprom(HSV_GREEN);
#        endif // RGB_MATRIX_ENABLE
        }
        auto_pointer_layer_timer = timer_read();
    }
    return mouse_report;
}

void matrix_scan_user(void) {
    if (auto_pointer_layer_timer != 0 && TIMER_DIFF_16(timer_read(), auto_pointer_layer_timer) >= CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS) {
        auto_pointer_layer_timer = 0;
        layer_off(LAYER_MOUSE);
#        ifdef RGB_MATRIX_ENABLE
        rgb_matrix_mode_noeeprom(RGB_MATRIX_DEFAULT_MODE);
#        endif // RGB_MATRIX_ENABLE
    }
}
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

#    ifdef CHARYBDIS_AUTO_SNIPING_ON_LAYER
layer_state_t layer_state_set_user(layer_state_t state) {
    charybdis_set_pointer_sniping_enabled(layer_state_cmp(state, CHARYBDIS_AUTO_SNIPING_ON_LAYER));
    return state;
}
#    endif // CHARYBDIS_AUTO_SNIPING_ON_LAYER
#endif     // POINTING_DEVICE_ENABLE

#ifdef RGB_MATRIX_ENABLE
// Forward-declare this helper function since it is defined in rgb_matrix.c.
void rgb_matrix_update_pwm_buffers(void);
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case VS_DEF:
                tap_code(KC_BTN1);
                wait_ms(10);
                tap_code(KC_F12);
                return false;

            case VS_IMPL:
                tap_code(KC_BTN1);
                wait_ms(10);
                tap_code16(LCTL(KC_F12));
                return false;

            case VS_REF:
                tap_code(KC_BTN1);
                wait_ms(10);
                tap_code16(LCTL(KC_K));
                wait_ms(10);
                tap_code(KC_R);
                return false;
        }
    }
    return true;
}
