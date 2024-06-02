#include QMK_KEYBOARD_H

enum layers {
    _BL = 0,    // Base Layer
    _FL,        // Function/Media Layer
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

        MO(_FL), KC_PSLS, KC_PAST, KC_PMNS,
        KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
        KC_P4,   KC_P5,   KC_P6,
        KC_P1,   KC_P2,   KC_P3,   KC_PENT,
                 KC_P0,   KC_PDOT
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
        KC_TRNS,

        KC_NO,   KC_NUM,  KC_CALC,  KC_BSPC,
        RGB_VAI, KC_VOLU, RGB_MOD,  KC_NO,
        KC_MPRV, KC_MPLY, KC_MNXT,
        RGB_VAD, KC_VOLD, RGB_RMOD, KC_NO,
                 RGB_TOG, KC_NO
    )
};