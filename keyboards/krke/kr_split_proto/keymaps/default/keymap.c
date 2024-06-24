#include QMK_KEYBOARD_H

// LAYERS
enum layers {
    _BL = 0,
    _FL
};

//  CUSTOM KEYCODES. KC_NONE IS PLACEHOLDER.
enum custom_keycodes {
    KC_JIGG = SAFE_RANGE,
    KC_NONE
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
    [_BL] = LAYOUT_normal(
        // LEFT
        KC_A,       KC_B,       KC_C,       KC_D,       KC_E,       KC_F,
        KC_G,       KC_H,       KC_I,       KC_J,       KC_K,       KC_L,
        KC_M,       KC_N,       KC_O,       KC_P,       KC_Q,       KC_R,
        // RIGHT
        KC_VOLD,    KC_VOLU,
        KC_MPRV,    KC_MNXT,
        KC_MPLY,    MO(_FL)
    ),
    [_FL] = LAYOUT_normal(
        // LEFT
        KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,
        KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,
        KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,
        // RIGHT
        QK_BOOT,    KC_NO,
        KC_NO,      KC_NO,
        KC_JIGG,    KC_TRNS
    )
};

// CUSTOM KEYCODES.
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // on every key event start or extend `idle_callback()` deferred execution after IDLE_TIMEOUT_MS
    static deferred_token idle_token = INVALID_DEFERRED_TOKEN;
    if (!extend_deferred_exec(idle_token, idle_timeout)) {
        idle_token = defer_exec(idle_timeout, idle_callback, NULL);
    }
    // SWITCH
    switch (keycode) {
        case KC_JIGG:
            if (record->event.pressed) {
                is_jiggling = !is_jiggling; /*flip boolean to true*/
            }
            break;
        default:
            return true;
    }
    return false;
}
