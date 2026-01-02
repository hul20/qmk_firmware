// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
     * │Esc│ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │ Backsp│
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
     * │ Tab │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │  \  │
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
     * │ Caps │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │  Enter │
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤
     * │ Shift  │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │  Shift   │
     * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
     * │Ctrl│GUI │Alt │         Space          │ Alt│GUI │Menu│Ctrl│
     * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
     */
    [0] = LAYOUT_61_ansi(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
        KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,                    KC_RALT, KC_RGUI, KC_APP,  KC_RCTL
    ),
    
    [1] = LAYOUT_61_ansi(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
        _______, _______, KC_UP,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, QK_BOOT,
        _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______,                   _______,                   _______, _______, _______, _______
    )
};

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {  // Volume knob
        if (clockwise) {
            tap_code(KC_VOLU);  // Volume up
        } else {
            tap_code(KC_VOLD);  // Volume down
        }
    }
    return false;
}
#endif

#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;  // Vertical orientation for 32x128 display
}

// Render the OLED info panel (9 lines max)
bool oled_task_user(void) {
    // Line 1: Title
    oled_write_ln_P(PSTR("UBE61"), false);
    
    // // Line 2: Current layer
    // switch (get_highest_layer(layer_state)) {
    //     case 0:
    //         oled_write_ln_P(PSTR("L:BSE"), false);
    //         break;
    //     case 1:
    //         oled_write_ln_P(PSTR("L:FN "), false);
    //         break;
    //     default:
    //         oled_write_ln_P(PSTR("L:?? "), false);
    // }
    
    // Line 3: Caps lock status
    led_t led_state = host_keyboard_led_state();
    oled_write_ln_P(led_state.caps_lock ? PSTR("CAPS!") : PSTR("     "), false);
    
    // Line 4: Separator
    oled_write_ln_P(PSTR("-----"), false);
    
    // Line 5: WPM label
    oled_write_ln_P(PSTR("WPM  "), false);
    
    // Line 6: WPM value
    char wpm_str[16];
    snprintf(wpm_str, sizeof(wpm_str), "%u    ", get_current_wpm());
    oled_write_ln(wpm_str, false);
    
    // Line 7: Separator
    oled_write_ln_P(PSTR("-----"), false);
    
    // Line 8-9: Mods combined (show only active ones, 2 lines max)
    uint8_t mods = get_mods();
    char mod_line1[6] = "     ";
    char mod_line2[6] = "     ";
    
    if (mods & MOD_MASK_SHIFT) {
        snprintf(mod_line1, sizeof(mod_line1), "SFT  ");
    } else if (mods & MOD_MASK_CTRL) {
        snprintf(mod_line1, sizeof(mod_line1), "CTL  ");
    }
    
    if ((mods & MOD_MASK_SHIFT) && (mods & MOD_MASK_CTRL)) {
        snprintf(mod_line2, sizeof(mod_line2), "CTL  ");
    } else if (mods & MOD_MASK_ALT) {
        snprintf(mod_line2, sizeof(mod_line2), "ALT  ");
    } else if (mods & MOD_MASK_GUI) {
        snprintf(mod_line2, sizeof(mod_line2), "GUI  ");
    }
    
    oled_write_ln(mod_line1, false);  // Line 8
    oled_write_ln(mod_line2, false);  // Line 9
    
    return false;
}

// Force OLED update when LED state changes (like caps lock)
bool led_update_user(led_t led_state) {
    oled_set_cursor(0, 0);  // Reset cursor to force refresh
    return true;
}

#endif