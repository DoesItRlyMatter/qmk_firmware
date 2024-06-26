#include QMK_KEYBOARD_H
#include "print.h"
#include "bongo.c"
#include <stdio.h>

#define CUSTOM_OLED_TIMEOUT 300000 // (after 5 minutes)

// Variable for WPM Counter
char wpm[5];

// LAYERS
enum layers {
    _BL = 0,
    _FL,
    _EX
};

//  CUSTOM KEYCODES. KC_NONE IS PLACEHOLDER.
enum custom_keycodes {
    KC_JIGG = SAFE_RANGE,
    KC_OLP,
    KC_OLM,
    KC_NONE
};

enum oled_layers {
    OL_LOGO = 0,
    OL_INFO,
    OL_ANIM,
    NUM_OF_PAGES // DO NOT REMOVE, USED FOR COUNTING ENUMS.
};

// OLED LAYER. START AT DEFINED, WOULD TYPICALLY BE 0.
uint16_t current_oled_layer = 1;

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
        KC_VOLD,    KC_VOLU,
        KC_MPRV,    KC_MNXT,
        KC_MPLY,    MO(_FL)
    ),
    [_FL] = LAYOUT_normal(
        TO(_EX),    QK_BOOT,
        KC_OLM,     KC_OLP,
        KC_JIGG,    KC_TRNS
    ),
    [_EX] = LAYOUT_normal(
        TO(_BL),    KC_1,
        KC_A,       KC_B,
        KC_SPC,     KC_BSPC
    )
};

// OLED
#ifdef OLED_ENABLE

bool oled_task_user(void) {
    // Check if oled is on and there has been activity.
    if (last_input_activity_elapsed() > CUSTOM_OLED_TIMEOUT){
        // Turn off if oled on.
        if (is_oled_on()){
            oled_off();
        }
    }
    // if oled is off and theres activity
    else {
        // turn oled on
        if(!is_oled_on()){
            oled_on();
        }
        // QMK Logo
        static const char PROGMEM qmk_logo[] = {
            0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
            0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
            0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
        };

        oled_clear();
        // Oled pages
        switch(current_oled_layer){
            case OL_LOGO:
                // Write logo & kb information
                oled_write_P(PSTR("\n"), false);
                oled_write_ln_P(qmk_logo, false);
                oled_write_P(PSTR(" KRKE\n"), false);
                oled_write_P(PSTR(" KR-Split-Proto\n"), false);
                oled_write_P(PSTR(" Version: 0.0.1 OLED\n"), false);
                break;
            case OL_INFO:
                // Layer & Indicators
                oled_write_P(PSTR("\nLayer: "), false);
                switch (get_highest_layer(layer_state)) {
                    case _BL:
                        oled_write_P(PSTR(" Base\n"), false);
                        break;
                    case _FL:
                        oled_write_P(PSTR(" Func\n"), false);
                        break;
                    case _EX:
                        oled_write_P(PSTR(" Test\n"), false);
                        break;
                    default:
                        oled_write_P(PSTR("Undefined\n"), false);
                        break;
                }
                // Jiggler
                oled_write_P(PSTR("\nJiggle: "), false);
                if(is_jiggling){
                    oled_write_P(PSTR("Active  \n\n\n"), false);
                }
                else{
                    oled_write_P(PSTR("Inactive\n\n\n"), false);
                }

                // Host Keyboard LED Status
                led_t led_state = host_keyboard_led_state();
                oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
                oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
                oled_write_P(led_state.scroll_lock ? PSTR("SCR \n") : PSTR("    \n"), false);
                // IMPORTANT BREAK!
                break;
            case OL_ANIM:
                // Call anime animation.
                render_bongo();
                // Display WPM
                oled_write_P(PSTR("\n WPM: "), false);
                // WPM to string
                sprintf(wpm, "%i", get_current_wpm());
                oled_write(wpm, false);
                break;
            default:
                oled_write_P(PSTR("Undefined"), false);
        }
        oled_render_dirty(true);
    }
    return false;
}
#endif

// debug
void keyboard_post_init_user(void) {
    // Customise these values to desired behaviour
    // debug_enable=false;
    // debug_matrix=true;
    // debug_keyboard=true;
    // debug_mouse=true;
}

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
        case KC_OLP:
            if (record->event.pressed) {
                if (current_oled_layer < NUM_OF_PAGES-1){
                    current_oled_layer = current_oled_layer + 1;
                }
                else {
                    current_oled_layer = 0; // Goto first page.
                }
            }
            break;
        case KC_OLM:
            if (record->event.pressed) {
                if (current_oled_layer > 0) {
                    current_oled_layer = current_oled_layer - 1;
                }
                else {
                    current_oled_layer = NUM_OF_PAGES-1; // Goto last page
                }
            }
            break;
        default:
            return true;
    }
    return false;
}
