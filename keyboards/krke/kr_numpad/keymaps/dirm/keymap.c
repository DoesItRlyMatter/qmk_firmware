#include QMK_KEYBOARD_H


//  CUSTOM KEYCODES. KC_NONE IS PLACEHOLDER.
enum custom_keycodes {
    RGB_RESET = SAFE_RANGE,
    KC_NONE
};

//  LAYERS
enum layers {
    _BL = 0,    // Base Layer
    _FL,        // Function/Media Layer
    _RGB, 
};

// TAP DANCE
enum {
    LOCK_TG = 0
};

// TAP DANCE ACTIONS
tap_dance_action_t tap_dance_actions[] = {
    [LOCK_TG] = ACTION_TAP_DANCE_LAYER_TOGGLE(KC_NUM, _FL)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┐   
     * │Esc│   
     * └───┘   
     * ┌───┬───┬───┬───┐
     * │TAP│ / │ * │ - │
     * ├───┼───┼───┼───┤
     * │ 7 │ 8 │ 9 │   │
     * ├───┼───┼───┤ + │
     * │ 4 │ 5 │ 6 │   │
     * ├───┼───┼───┼───┤
     * │ 1 │ 2 │ 3 │ E │
     * ├───┴───┼───┤ n │
     * │   0   │ . │ t │
     * └───────┴───┴───┘
     */
    [_BL] = LAYOUT_normal(
        KC_ESC,

        TD(LOCK_TG), KC_PSLS,  KC_PAST, KC_PMNS,
        KC_P7,       KC_P8,    KC_P9,   KC_PPLS,
        KC_P4,       KC_P5,    KC_P6,
        KC_P1,       KC_P2,    KC_P3,   KC_PENT,
                     KC_P0,    KC_PDOT
    ),
    /*
     * ┌───┐   
     * │_BL│   
     * └───┘   
     * ┌───┬───┬───┬───┐
     * │   │NuL│Cal│Bsp│
     * ├───┼───┼───┼───┤
     * │   │VUp│   │   │
     * ├───┼───┼───┤   │
     * │Prv│Ply│Nxt│   │
     * ├───┼───┼───┼───┤
     * │   │VDw│   │   │
     * ├───┴───┼───┤   │
     * │       │   │   │
     * └───────┴───┴───┘
     */
    [_FL] = LAYOUT_normal(
        TO(_BL),

        TO(_RGB),   KC_NO,     KC_CALC,  KC_BSPC,
        KC_NO,      KC_VOLU,   KC_NO,    KC_NO,
        KC_MPRV,    KC_MPLY,   KC_MNXT,
        KC_NO,      KC_VOLD,   KC_NO,    KC_NO,
                    KC_NO,     KC_NO
    ),
    /*
     * ┌───┐   
     * │_BL│   
     * └───┘   
     * ┌───┬───┬───┬───┐
     * │   │   │   │   │
     * ├───┼───┼───┼───┤
     * │   │   │   │   │
     * ├───┼───┼───┤   │
     * │   │TOG│   │   │
     * ├───┼───┼───┼───┤
     * │   │   │   │   │
     * ├───┴───┼───┤   │
     * │       │   │   │
     * └───────┴───┴───┘
     */
    [_RGB] = LAYOUT_normal(
        TO(_BL),

        KC_NO,      KC_NO,     KC_NO,    KC_NO,
        KC_NO,      RGB_VAI,   KC_NO,    KC_NO,
        RGB_RMOD,   RGB_TOG,   RGB_MOD,
        KC_NO,      RGB_VAD,   KC_NO,    KC_NO,
                    RGB_RESET, KC_NO
    )
};

// RGB LAYER SEGMENTS ('START LED', 'LIGHT X NUMBER OF LEDS', 'COLOR')
const rgblight_segment_t PROGMEM NUM_LAYER[] = RGBLIGHT_LAYER_SEGMENTS({0, 10, HSV_RED}
);
const rgblight_segment_t PROGMEM FL_LAYER[] = RGBLIGHT_LAYER_SEGMENTS({0, 10, HSV_GREEN}
);
const rgblight_segment_t PROGMEM RGB_LAYER[] = RGBLIGHT_LAYER_SEGMENTS({0, 10, HSV_CYAN}
);

// DEFINE ARRAY OF LAYERS. LATER LAYERS TAKE PRECEDENCE!
const rgblight_segment_t *const PROGMEM CUSTOM_RGB_LAYERS[] = RGBLIGHT_LAYERS_LIST(NUM_LAYER, FL_LAYER, RGB_LAYER);

// ENABLE LED LAYERS
void keyboard_post_init_user(void) {
    rgblight_layers = CUSTOM_RGB_LAYERS;
}

// NUM LOCK INDICATOR
bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(0, !led_state.num_lock);
    return true;
}

// LAYERS
layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(1, layer_state_cmp(state, _FL));
    if (layer_state_cmp(state, _RGB)){
        rgblight_blink_layer_repeat(2, 250, 3);
    }
    return state;
}

// CUSTOM KEYCODES.
// RGB_RESET = RESETS RGB TO DEFAULT.
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // SWITCH
    switch (keycode) {
        // RESET RGB TO DEFAULT
        case RGB_RESET:
            rgblight_enable();
            rgblight_sethsv(0, 255, 128);
            rgblight_mode(RGBLIGHT_MODE_RAINBOW_SWIRL + 2);
            // Do nothing else.
            return false;
        default:
            return true;
    }
}