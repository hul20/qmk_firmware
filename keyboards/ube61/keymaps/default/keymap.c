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
        KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,                    KC_RALT, MO(1),   KC_APP,  KC_RCTL
    ),

    [1] = LAYOUT_61_ansi(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
        _______, _______, KC_UP,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, QK_BOOT,
        _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______,                   _______,                   _______, _______, _______, _______
    )
};

// Global variables for volume and OLED state
static uint32_t last_activity_time   = 0;
static uint8_t  current_volume       = 50;
static uint32_t volume_display_timer = 0;
static bool     show_volume          = false;

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { // Volume knob
        if (clockwise) {
            tap_code(KC_VOLU);
            tap_code(KC_VOLU);
            if (current_volume <= 96) {
                current_volume += 4;
            } else {
                current_volume = 100;
            }
        } else {
            tap_code(KC_VOLD);
            tap_code(KC_VOLD);
            if (current_volume >= 4) {
                current_volume -= 4;
            } else {
                current_volume = 0;
            }
        }
        show_volume          = true;
        volume_display_timer = timer_read32();
        last_activity_time   = timer_read32();
    }
    return false;
}
#endif

#ifdef OLED_ENABLE

// Idle animation bitmap - 128x32px
const unsigned char epd_bitmap_71f5Npf2WtL[] PROGMEM = {	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                            0x00, 0x00, 0x00, 0xc0, 0xf8, 0xfc, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xf8, 0xf0, 0xc0,
                                                            0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
                                                            0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                                            0xfe, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                            0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                                            0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x20, 0x00, 0x00, 0x00, 0x00,
                                                            0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xe7, 0xf9,
                                                            0xff, 0xff, 0xff, 0xfc, 0xe0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                            0x00, 0x00, 0x00, 0x7f, 0xff, 0x7f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                                            0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                            0x00, 0xf8, 0x04, 0x06, 0x06, 0x06, 0x0e, 0x0c, 0x0c, 0x19, 0x19, 0x13, 0x27, 0x4f, 0xdf, 0xbf,
                                                            0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                            0x00, 0x11, 0x0c, 0x30, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x08, 0x10, 0x00, 0x01,
                                                            0xab, 0xff, 0x3f, 0x1f, 0x0f, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                            0x00, 0x00, 0x80, 0xfc, 0xfc, 0xf9, 0xf2, 0xe2, 0xe4, 0x84, 0x04, 0x04, 0x04, 0x00, 0x02, 0x09,
                                                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                            0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x01, 0xff, 0xff, 0xff, 0xfc, 0xf0, 0x00, 0x80, 0x00, 0x00,
                                                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                            0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x9f, 0x0f, 0x9f, 0x9f, 0x3f, 0xfc, 0xf0, 0xe0, 0xc0,
                                                            0x80, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                            0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xff, 0xe7, 0x70, 0x8f, 0xcf, 0xef, 0xff,
                                                            0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                            0x00, 0x00, 0x00, 0xe3, 0xe7, 0xef, 0xef, 0xef, 0xe7, 0xf7, 0xf9, 0xfc, 0xff, 0xff, 0xff, 0xff,
                                                            0xff, 0xff, 0xff, 0xff, 0xff, 0x1f, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                            0x00, 0x00, 0x20, 0x1f, 0x7f, 0x7f, 0x7f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x3f, 0xbf,
                                                            0x9f, 0x0f, 0x07, 0x03, 0x00, 0x00, 0xfc, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                            0x00, 0x00, 0x00, 0x00, 0xe0, 0xf8, 0xfc, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x3f, 0x1f,
                                                            0x0f, 0x03, 0x00, 0x00, 0x00, 0x00, 0x27, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                            0x00, 0x00, 0x00, 0x47, 0x3f, 0x07, 0x7f, 0x7f, 0x83, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                                                        };

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    last_activity_time = timer_read32();
    return OLED_ROTATION_90; // Vertical orientation
}

// Render the OLED info panel (9 lines max)
bool oled_task_user(void) {
    static bool was_idle = false;

    // Hide volume indicator after 2 seconds
    if (show_volume && timer_elapsed32(volume_display_timer) > 2000) {
        show_volume = false;
        oled_clear();
    }

    // Show volume bar when adjusting
    if (show_volume) {
        // Clear screen for each update to allow volume to decrease visually
        oled_clear();

        // Show percentage at top
        oled_set_cursor(0, 0);
        char vol_str[6];
        snprintf(vol_str, sizeof(vol_str), "%3u%%", current_volume);
        oled_write_ln(vol_str, false);

        // Draw volume bar using pixel rectangles
        // After 90° rotation: display is 32px wide x 128px tall
        const uint8_t bar_width = 24;
        const uint8_t bar_height = 100;
        const uint8_t bar_x = (32 - bar_width) / 2; // Center horizontally
        const uint8_t bar_y = 20; // Start position from top

        // Draw outer border
        for (uint8_t x = bar_x; x < bar_x + bar_width; x++) {
            oled_write_pixel(x, bar_y, true);
            oled_write_pixel(x, bar_y + bar_height - 1, true);
        }
        for (uint8_t y = bar_y; y < bar_y + bar_height; y++) {
            oled_write_pixel(bar_x, y, true);
            oled_write_pixel(bar_x + bar_width - 1, y, true);
        }

        // Fill bar based on volume (fill from bottom to top)
        uint8_t fill_height = (current_volume * (bar_height - 4)) / 100; // -4 for border spacing
        for (uint8_t y = 0; y < fill_height; y++) {
            for (uint8_t x = bar_x + 2; x < bar_x + bar_width - 2; x++) {
                oled_write_pixel(x, bar_y + bar_height - 3 - y, true);
            }
        }

        return false;
    }

    // Check idle time (10 seconds = 10000ms)
    if (timer_elapsed32(last_activity_time) > 10000) {
        if (!was_idle) {
            oled_clear();
            was_idle = true;
        }
        oled_write_raw_P((const char *)epd_bitmap_71f5Npf2WtL, 512);
        return false;
    }

    // Clear when returning from idle
    if (was_idle) {
        oled_clear();
        was_idle = false;
    }

    // Normal display - vertical layout (8 lines max)
    oled_write_ln_P(PSTR("UBE61"), false);

    led_t led_state = host_keyboard_led_state();
    oled_write_ln_P(led_state.caps_lock ? PSTR("CAPS!") : PSTR("     "), false);

    oled_write_ln_P(PSTR("WPM  "), false);
    char wpm_str[16];
    snprintf(wpm_str, sizeof(wpm_str), "%u    ", get_current_wpm());
    oled_write_ln(wpm_str, false);

    uint8_t mods         = get_mods();
    char    mod_line1[6] = "     ";
    char    mod_line2[6] = "     ";
    char    mod_line3[6] = "     ";

    if (mods & MOD_MASK_SHIFT) {
        snprintf(mod_line1, sizeof(mod_line1), "SFT  ");
    }
    if (mods & MOD_MASK_CTRL) {
        snprintf(mod_line2, sizeof(mod_line2), "CTL  ");
    }
    if (mods & MOD_MASK_ALT || mods & MOD_MASK_GUI) {
        snprintf(mod_line3, sizeof(mod_line3), (mods & MOD_MASK_ALT) ? "ALT  " : "GUI  ");
    }

    oled_write_ln(mod_line1, false);
    oled_write_ln(mod_line2, false);
    oled_write_ln(mod_line3, false);

    return false;
}

// Force OLED update when LED state changes (like caps lock)
bool led_update_user(led_t led_state) {
    oled_set_cursor(0, 0); // Reset cursor to force refresh
    return true;
}

// Reset idle timer on any key press
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        last_activity_time = timer_read32();
    }
    return true;
}

#endif
