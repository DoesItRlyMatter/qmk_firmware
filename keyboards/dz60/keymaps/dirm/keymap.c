#include QMK_KEYBOARD_H

// DEFINE LAYERS FOR EASE OF USE

#define BL 0 // BASE LAYER
#define FL 1 // FUNCTION LAYER

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

 /* Keymap BL: Base Layer
 * 	 1   2   3   4   5   6   7   8   9   10  11  12  13  14
 * ,-----------------------------------------------------------.
 * | ESC | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | - | = |Backs|
 * |-----------------------------------------------------------|
 * | Tab | q | w | e | r | t | y | u | i | o | p | å | ^ |enter|
 * |------------------------------------------------------     |
 * | Caps  | a | s | d | f | g | h | j | k | l | ö | ä | * |   |
 * |-----------------------------------------------------------|
 * |	Shft | z | x | c | v | b | n | m | , | . | - | > | U |Sft|
 * |-----------------------------------------------------------|
 * |CTRL| WIN | ALT| 				SPACE				  |ALT| FN | L | D | R |
 * `-----------------------------------------------------------'
 */


 [BL] = LAYOUT_DIRM(
//  1          2          3          4          5          6          7          8          9          10         11         12         13         14
			KC_ESC,    KC_1,      KC_2,      KC_3,      KC_4,      KC_5,      KC_6,      KC_7,      KC_8,      KC_9,      KC_0,      KC_MINS,   KC_EQL,    KC_BSPC,
			KC_TAB ,   KC_Q,      KC_W,      KC_E,      KC_R,      KC_T,      KC_Y,      KC_U,      KC_I,      KC_O,      KC_P,      KC_LBRC,   KC_RBRC,
			KC_CAPS,   KC_A,      KC_S,      KC_D,      KC_F,      KC_G,      KC_H,      KC_J,      KC_K,      KC_L,      KC_SCLN,   KC_QUOT,   KC_NUHS,   KC_ENT,
			KC_LSFT,   KC_Z,      KC_X,      KC_C,      KC_V,      KC_B,      KC_N,      KC_M,      KC_COMM,   KC_DOT,    KC_SLSH,   KC_NUBS,   KC_UP,     KC_RSFT
			KC_LCTL,   KC_LGUI,   KC_LALT,   KC_SPC,    KC_RALT,   MO(FL),      KC_LEFT,   KC_DOWN,   KC_RIGHT),

 /* Keymap FL: FUNCTION LAYER
 * 	 1   2   3   4   5   6   7   8   9   10  11  12  13  14
 * ,-----------------------------------------------------------.
 * |     |   |   |   |   |   |   |   |   |   |   |   |   |     |
 * |-----------------------------------------------------------|
 * |     |   |   |   |   |   |   |   |   |   |   |   |   |     |
 * |------------------------------------------------------     |
 * |       |   |   |   |   |   |   |   |   |   |   |   |   |   |
 * |-----------------------------------------------------------|
 * |	     |   |   |   |   |   |   |   |   |   |   |   |   |   |
 * |-----------------------------------------------------------|
 * |    |    |    | 				      			  |   |    |   |   |   |
 * `-----------------------------------------------------------'
 */

 [FL] = LAYOUT_DIRM(
//  1          2          3          4          5          6          7          8          9          10         11         12         13         14
		KC_ESC,    KC_F1,     KC_F2,     KC_F3,     KC_F4,     KC_F5,     KC_F6,     KC_F7,     KC_F8,     KC_F9,     KC_F10,    KC_F11,    KC_F12,    KC_DEL,
			_______ ,  _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   KC_PSCR,   _______,   _______,
			_______,   KC_MS_LEFT,KC_MS_DOWN,KC_MS_UP,  KC_MS_RIGHT,_______,  _______,   KC_LEFT,   KC_DOWN,   KC_UP,     KC_RIGHT,  _______,   _______,   _______,
			_______,   _______,   _______,   _______,   _______,   KC_MS_BTN1,KC_MS_BTN2,_______,   KC_HOME,   KC_PGDOWN, KC_PGUP,   KC_END,    _______,
			_______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______),
};
