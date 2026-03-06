#include QMK_KEYBOARD_H
#include "rgblight.h"

static uint16_t rgb_reset_timer = 0;
static bool rgb_override_active = false;
static bool rgb_saved_once = false;

// Saved RGB state
static uint8_t saved_mode = 0;
static uint16_t saved_hue = 0;
static uint8_t saved_sat = 0;
static uint8_t saved_val = 0;

// ------------------ Custom keycodes ------------------
enum custom_keycodes {
    KC_CYCLE = SAFE_RANGE,   // cycle through layers
};

// ------------------ Keymaps ------------------
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_ortho_3x3(
        KC_CYCLE, KC_B, KC_1,
        KC_D,     KC_E, KC_F,
        KC_G,     KC_H, KC_C
    ),

    [1] = LAYOUT_ortho_3x3(
        KC_CYCLE, KC_2, KC_2,
        KC_4,     KC_5, KC_6,
        KC_7,     KC_8, KC_3
    ),

    [2] = LAYOUT_ortho_3x3(
        KC_CYCLE, KC_AT,   KC_3,
        KC_DLR,   KC_PERC, KC_CIRC,
        KC_AMPR,  KC_ASTR, KC_HASH
    ),

    [3] = LAYOUT_ortho_3x3(
        KC_CYCLE, KC_MUTE, KC_4,
        KC_MPRV,  KC_MNXT, KC_VOLD,
        KC_HOME,  KC_END,  KC_VOLU
    )
};

// ------------------ RGB Override ------------------
void trigger_layer_rgb(uint16_t hue, uint8_t sat, uint8_t val) {
    if (!rgb_saved_once) {
        saved_mode = rgblight_get_mode();
        HSV hsv = rgblight_get_hsv();
        saved_hue = hsv.h;
        saved_sat = hsv.s;
        saved_val = hsv.v;
        rgb_saved_once = true;
    }

    rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
    rgblight_sethsv_noeeprom(hue, sat, val);

    rgb_reset_timer = timer_read();
    rgb_override_active = true;
}

void matrix_scan_user(void) {
    if (rgb_override_active && timer_elapsed(rgb_reset_timer) > 5000) {
        // Restore saved effect
        rgblight_mode(saved_mode);
        rgblight_sethsv_noeeprom(saved_hue, saved_sat, saved_val);
        rgb_override_active = false;
    }
}

// ------------------ Layer RGB Colors ------------------
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case 1: trigger_layer_rgb(0,   0,   255); break;   // White
        case 2: trigger_layer_rgb(0,   255, 255); break;   // Red
        case 3: trigger_layer_rgb(85,  255, 255); break;   // Green
        default: trigger_layer_rgb(170, 255, 255); break;  // Blue
    }
    return state;
}

// ------------------ Post Init ------------------
void keyboard_post_init_user(void) {
    // Set default mode at boot
    rgblight_mode(RGBLIGHT_MODE_RAINBOW_SWIRL);

    // Save this as "baseline" so restore works
    saved_mode = rgblight_get_mode();
    HSV hsv = rgblight_get_hsv();
    saved_hue = hsv.h;
    saved_sat = hsv.s;
    saved_val = hsv.v;
    rgb_saved_once = true;
}

// ------------------ Process Record ------------------
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_CYCLE:
            if (record->event.pressed) {
                uint8_t current = get_highest_layer(layer_state);
                uint8_t next = (current + 1) % 4;
                layer_move(next);
            }
            return false;
    }
    return true;
}

// ------------------ Encoder Mapping ------------------
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [1] = { ENCODER_CCW_CW(KC_LEFT, KC_RGHT) },
    [2] = { ENCODER_CCW_CW(KC_DOWN, KC_UP)   },
    [3] = { ENCODER_CCW_CW(KC_MPRV, KC_MNXT) }
};
#endif
