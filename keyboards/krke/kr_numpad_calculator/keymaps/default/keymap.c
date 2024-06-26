#include QMK_KEYBOARD_H
#include "noled.c"

enum layers {
    _BL = 0,    // Base Layer
    _FL,        // Function/Media Layer
    _EX
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
     * │_FL│ / │ * │ - │
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

        TD(LOCK_TG),    KC_PSLS,    KC_PAST,    KC_PMNS,
        KC_P7,          KC_P8,      KC_P9,      KC_PPLS,
        KC_P4,          KC_P5,      KC_P6,
        KC_P1,          KC_P2,      KC_P3,      KC_PENT,
                        KC_P0,      KC_PDOT
    ),
    /*
     * ┌───┐
     * │Esc│
     * └───┘
     * ┌───┬───┬───┬───┐
     * │   │NuL│Cal│Bsp│
     * ├───┼───┼───┼───┤
     * │RGB│VUp│RGB│   │
     * ├───┼───┼───┤   │
     * │Prv│Ply│Nxt│   │
     * ├───┼───┼───┼───┤
     * │RGB│VDw│RGB│   │
     * ├───┴───┼───┤   │
     * │RGB TOG│   │   │
     * └───────┴───┴───┘
     */
    [_FL] = LAYOUT_normal(
        TO(_BL),

        TG(_EX),        KC_NO,      DB_TOGG,    QK_BOOT,
        RGB_VAI,        KC_VOLU,    RGB_MOD,    KC_NO,
        KC_MPRV,        KC_MPLY,    KC_MNXT,
        RGB_VAD,        KC_VOLD,    RGB_RMOD,   KC_NO,
                        RGB_TOG,    KC_NO
    ),
    [_EX] = LAYOUT_normal(
        TO(_BL),

        KC_NO,          KC_NO,      KC_NO,      KC_NO,
        KC_NO,          KC_NO,      KC_NO,      KC_NO,
        KC_NO,          KC_NO,      KC_NO,
        KC_NO,          KC_NO,      KC_NO,      KC_NO,
                        KC_NO,      KC_NO
    )
};

void keyboard_pre_init_user(void) {
    // debug
    debug_enable=true;

    // Display
    // Not sure what begin does.
    noledBegin();
    noledClear();

    // TESTING // FIRST ROW?
    noledWriteChars(1, (16-9), "KR_NUMPAD");
}


layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case _BL:
            noledWriteChars(0, 0, "_BL");
            break;
        case _FL:
            noledWriteChars(0, 0, "_FL");
            break;
        case _EX:
            noledWriteChars(0, 0, "_EX");
            break;
        default:
            noledWriteChars(0, 0, "Undefined");
            break;
    }
  return state;
}

// TODO
//  - Implement oled_timeout
//  - Calculator layer & code
//  - Import layer, backlight etc from keymaps/dirm
