#include QMK_KEYBOARD_H

//  CUSTOM KEYCODES. KC_NONE IS PLACEHOLDER.
enum custom_keycodes {
    RGB_RESET = SAFE_RANGE,
    KC_JIGG,
    KC_NONE
};

// KEYMAP LAYERS
enum layers {
    _BL = 0,    // Base Layer
    _FL        // Function/Media Layer
};

// TAP DANCE
enum {
    CT_CAPS = 0
};

// CAPS TAP DANCE FUNCTION
void tapdance_caps(tap_dance_state_t *state, void *user_data){
    // 1, CAPS LOCK
    if(state->count == 1){
        register_code(KC_CAPS);
    }
    // 2, CAPS WORD
    else if(state->count == 2){
        caps_word_on();
    }
}

// TAP DANCE ACTIONS
tap_dance_action_t tap_dance_actions[] = {
    [CT_CAPS] = ACTION_TAP_DANCE_FN(tapdance_caps),
};

// COMBOS
const uint16_t PROGMEM REC_MACRO1_COMBO[] = {KC_LSFT, DM_PLY1, COMBO_END};
const uint16_t PROGMEM REC_MACRO2_COMBO[] = {KC_LSFT, DM_PLY2, COMBO_END};

combo_t key_combos[] = {
    COMBO(REC_MACRO1_COMBO, DM_REC1),
    COMBO(REC_MACRO2_COMBO, DM_REC2)
};

// JIGGLER STUFF
__attribute__((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) { return true; }

__attribute__((weak))
bool process_record_secrets(uint16_t keycode, keyrecord_t *record) { return true; }

// BOOL FOR JIGGLER
bool is_jiggling = false;

// TIMERS FOR JIGGLER
uint32_t idle_timeout = 30000; // (after 30s)
uint32_t mouse_interval = 10000; // (every 10s)

// JIGGLER
static uint32_t idle_callback(uint32_t trigger_time, void* cb_arg) {
    // now idle
    if (is_jiggling){
        SEND_STRING(SS_TAP(X_F15));
        // SEND_STRING("TEST");
        return mouse_interval;
    }
    return false;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* _BL KEYMAP                                                              | USE AU_TOGG OR KC_PAUS DEPENDING ON IF ENCODER INSTALLED.
     * ┌───┐   ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┐
     * │Esc│   │F1 │F2 │F3 │F4 │ │F5 │F6 │F7 │F8 │ │F9 │F10│F11│F12│ │PSc│Scr│Mute│
     * └───┘   └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┘
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐ ┌───┬───┬───┐
     * │ ` │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │ Backsp│ │Ins│Hom│PgU│
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤ ├───┼───┼───┤
     * │ Tab │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │  \  │ │Del│End│PgD│
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤ └───┴───┴───┘
     * │ Caps │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │  Enter │
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤     ┌───┐
     * │ Shift  │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │    Shift │     │ ↑ │
     * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤ ┌───┼───┼───┐
     * │Ctrl│GUI │Alt │                        │ Alt│ GUI│ _FL│Ctrl│ │ ← │ ↓ │ → │
     * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘ └───┴───┴───┘
     */
    [_BL] = LAYOUT_tkl_ansi(
        KC_ESC,               KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,     KC_PSCR, KC_SCRL, KC_MUTE,

        KC_GRV,      KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,    KC_INS,  KC_HOME, KC_PGUP,
        KC_TAB,      KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,    KC_DEL,  KC_END,  KC_PGDN,
        TD(CT_CAPS), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
        KC_LSFT,              KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,             KC_UP,
        KC_LCTL,     KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, KC_RGUI, MO(_FL), KC_RCTL,    KC_LEFT, KC_DOWN, KC_RGHT
    ),
    /* _FL KEYMAP
     * ┌───┐   ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┐
     * │   │   │   │   │   │   │ │   │   │   │   │ │   │   │   │   │ │   │   │M_TOG│
     * └───┘   └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┘
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐ ┌───┬───┬───┐
     * │   │   │   │   │   │   │   │   │   │   │   │   │   │       │ │   │   │   │
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤ ├───┼───┼───┤
     * │     │   │   │   │RST│   │   │   │   │   │   │   │   │     │ │   │RGB│RST_RGB
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤ └───┴───┴───┘
     * │      │   │   │   |FLSH│  │   │   │   │   │   │   │        │
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤     ┌───┐
     * │        │   │   │   │   │   │   │   │   │   │   │          │     │RGB│
     * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤ ┌───┼───┼───┐
     * │    │    │    │                        │    │    │    │    │ │RGB│RGB│RGB│
     * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘ └───┴───┴───┘
     */
    [_FL] = LAYOUT_tkl_ansi(
        KC_NO,            KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,      KC_NO,   KC_NO,   KC_MPLY,

        KC_NO,   DM_PLY1, DM_PLY2,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,      KC_NO,   KC_NO,   KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   QK_BOOT, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,      KC_NO,   RGB_TOG, RGB_RESET,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,            KC_NO,
        KC_LSFT,          KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,            KC_RSFT,               RGB_VAI,
        KC_LCTL, KC_NO,   KC_NO,                              KC_JIGG,                            KC_NO,   KC_NO,   KC_NO,   KC_RCTL,      RGB_RMOD,RGB_VAD, RGB_MOD
    )
};

// ENCODER FUNCTIONALITY.
// _BL = VOLUME UP/DOWN, _FL = NEXT/PRV TRACK.
#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_BL] = {ENCODER_CCW_CW(KC_VOLU, KC_VOLD)},
    [_FL] = {ENCODER_CCW_CW(KC_MNXT, KC_MPRV)},
};
#endif

// DEFINE DOLCE ACCENT COLORS FOR INDICATORS
// #define DOLCE_N9 8, 214, 189

// RGB LAYER SEGMENTS ('START LED', 'LIGHT X NUMBER OF LEDS', 'COLOR')
const rgblight_segment_t PROGMEM CAPS_LAYER[] = RGBLIGHT_LAYER_SEGMENTS({0, 24, HSV_RED}
);
// EXAMPLE OF MULTIPLE RGB SEGMENTS
// const rgblight_segment_t PROGMEM CAPS_LAYER[] = RGBLIGHT_LAYER_SEGMENTS({0, 2, HSV_RED},
//                                                                         {8, 6, HSV_RED},
//                                                                         {20, 5, HSV_RED}
// );
const rgblight_segment_t PROGMEM SCROLL_LAYER[] = RGBLIGHT_LAYER_SEGMENTS({0, 24, HSV_BLUE}
);
const rgblight_segment_t PROGMEM ALL_LOCKS_LAYER[] = RGBLIGHT_LAYER_SEGMENTS({5, 12, HSV_RED},
                                                                             {0, 5, HSV_BLUE},
                                                                             {17, 7, HSV_BLUE}
);
const rgblight_segment_t PROGMEM JIGG_LAYER[] = RGBLIGHT_LAYER_SEGMENTS({0, 24, HSV_ORANGE}
);
const rgblight_segment_t PROGMEM FL_LAYER[] = RGBLIGHT_LAYER_SEGMENTS({0, 24, HSV_GREEN}
);

// DEFINE ARRAY OF LAYERS. LATER LAYERS TAKE PRECEDENCE!
const rgblight_segment_t *const PROGMEM CUSTOM_RGB_LAYERS[] = RGBLIGHT_LAYERS_LIST(JIGG_LAYER, CAPS_LAYER, SCROLL_LAYER, ALL_LOCKS_LAYER, FL_LAYER);

// ENABLE LED LAYERS
void keyboard_post_init_user(void) {
    rgblight_layers = CUSTOM_RGB_LAYERS;
}

// CAPS & SCROLL LOCK INDICATOR
bool led_update_user(led_t led_state) {
    // CHECK IF BOTH LOCKS ARE ON.
    if(led_state.caps_lock == true && led_state.scroll_lock == true){
        // ACTIVATE ALL_LOCKS_LAYER, DISABLE CAPS AND SCROLL LOCK LAYERS
        rgblight_set_layer_state(1, false);
        rgblight_set_layer_state(2, false);
        rgblight_set_layer_state(3, true);
    }
    else{
        // ACTIVATE CAPS AND SCROLL LOCK LAYERS, DISABLE ALL_LOCKS_LAYER
        rgblight_set_layer_state(1, led_state.caps_lock);
        rgblight_set_layer_state(2, led_state.scroll_lock);
        rgblight_set_layer_state(3, false);
    }
    return true;
}
// LAYERS
layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(4, layer_state_cmp(state, _FL));
    return state;
}

// CUSTOM KEYCODES.
// RGB_RESET = RESETS RGB TO DEFAULT.
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // on every key event start or extend `idle_callback()` deferred execution after IDLE_TIMEOUT_MS
    static deferred_token idle_token = INVALID_DEFERRED_TOKEN;
    if (!extend_deferred_exec(idle_token, idle_timeout)) {
        idle_token = defer_exec(idle_timeout, idle_callback, NULL);
    }
    // SWITCH
    switch (keycode) {
        // RESET RGB TO DEFAULT
        case RGB_RESET:
            rgblight_enable();
            rgblight_sethsv(0, 255, 128);
            rgblight_mode(RGBLIGHT_MODE_RAINBOW_SWIRL + 2);
            // Do nothing else.
            return false;
        case KC_JIGG:
            if (record->event.pressed) {
                is_jiggling = !is_jiggling; /*flip boolean to true*/
                rgblight_set_layer_state(0, is_jiggling);
            }
            break;
        default:
            return true;
    }
    return false;
}

// // BACKLIGHT COLOR BASED ON LAYER.
// // _FL = ON, REST = OFF.
// layer_state_t layer_state_set_user(layer_state_t state) {
//     switch (get_highest_layer(state)) {
//         case _BL:
//             // CODE
//             rgblight_disable();
//             break;
//         case _FL:
//             // CODE
//             rgblight_enable();
//             break;
//         default:
//             // CODE
//             rgblight_disable();
//             break;
//     }
//     return state;
// }
