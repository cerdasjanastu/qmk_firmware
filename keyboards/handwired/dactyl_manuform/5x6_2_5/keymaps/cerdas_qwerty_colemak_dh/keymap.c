#include QMK_KEYBOARD_H

// Layers
#define _QWERTY         0
#define _SYMBOLS_QWERTY 1
#define _NUMS_QWERTY    2
#define _COLEMAK_DH     3
#define _SYMBOLS_DH     4
#define _NUMS_DH        5

// Aliases
#define SYMQW   MO(_SYMBOLS_QWERTY)         // Hold: switch to QWERTY symbols layer
#define NUMQW   LT(_NUMS_QWERTY, KC_BSPC)   // Tap: Backspace | Hold: QWERTY numbers layer
#define SYMDH   MO(_SYMBOLS_DH)             // Hold: switch to Colemak symbols layer
#define NUMDH   LT(_NUMS_DH, KC_BSPC)       // Tap: Backspace | Hold: Colemak numbers layer
#define SPCALT  LALT_T(KC_SPC)              // Tap: Space | Hold: Left Alt

enum custom_keycodes {
    LY_TOG = SAFE_RANGE,
};

// toggles the default layer between QWERTY and Colemak-DH, and saves
// the choice to EEPROM so it persists after reset or unplug.
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case LY_TOG:
                if (get_highest_layer(default_layer_state) == _QWERTY) {
                    default_layer_set(1UL << _COLEMAK_DH);
                    eeconfig_update_default_layer(1UL << _COLEMAK_DH);
                } else {
                    default_layer_set(1UL << _QWERTY);
                    eeconfig_update_default_layer(1UL << _QWERTY);
                }
                return false;
        }
    }
    return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_5x6_2_5(
        KC_GRV  ,KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                        KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_MINS,
        KC_TAB  ,KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,                        KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_BSLS,
        KC_ESC  ,KC_A   , KC_S   , KC_D   , KC_F   , KC_G   ,                        KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT,
        KC_LSFT ,KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   ,                        KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT,
        KC_LCTL ,KC_LALT, KC_UP  , KC_DOWN, SYMDH  , SPCALT , KC_LGUI,      KC_ENT , KC_SPC , NUMQW  , KC_LEFT, KC_RGHT, KC_RALT, KC_RCTL,
                                                     KC_LCTL, KC_LSFT,      KC_RSFT, KC_RCTL
    ),

    [_SYMBOLS_QWERTY] = LAYOUT_5x6_2_5(
        KC_NO  , KC_MUTE, KC_VOLD, KC_VOLU, KC_BRID, KC_BRIU,                        KC_STOP, KC_MPRV, KC_MNXT, KC_PSCR, KC_NO  , LY_TOG ,
        KC_NO  , KC_TILD, KC_LBRC, KC_LCBR, KC_LPRN, KC_HASH,                        KC_EQL , KC_RPRN, KC_RCBR, KC_RBRC, KC_PLUS, KC_NO  ,
        KC_NO  , KC_GRV , KC_AT  , KC_DLR , KC_QUOT, KC_AMPR,                        KC_PERC, KC_DQUO, KC_UNDS, KC_EXLM, KC_MINS, KC_QUOT,
        KC_NO  , KC_NO  , KC_LT  , KC_CIRC, KC_PIPE, KC_ASTR,                        KC_BSLS, KC_QUES, KC_ASTR, KC_GT  , KC_NO  , KC_NO  ,
        KC_NO  , KC_PGUP, KC_PGDN, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,      KC_DEL , KC_TRNS, KC_TRNS, KC_HOME, KC_END , KC_NO  , KC_NO  ,
                                                     KC_TRNS, KC_TRNS,      KC_RSFT, KC_RCTL
    ),

    [_NUMS_QWERTY] = LAYOUT_5x6_2_5(
        KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  ,                        KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 ,
        KC_NO  , KC_NO  , KC_HOME, KC_UP  , KC_END , KC_NO  ,                        KC_EQL , KC_7   , KC_8   , KC_9   , KC_PLUS, KC_NO  ,
        KC_NO  , KC_COMM, KC_LEFT, KC_DOWN, KC_RGHT, KC_NO  ,                        KC_0   , KC_4   , KC_5   , KC_6   , KC_MINS, KC_NO  ,
        KC_NO  , KC_NO  , KC_PGUP, KC_NO  , KC_PGDN, KC_NO  ,                        KC_DOT , KC_1   , KC_2   , KC_3   , KC_SLSH, KC_NO  ,
        KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_TRNS, KC_SPC , KC_BSPC,      KC_NO  , KC_NO  , KC_TRNS, KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
                                                     KC_LCTL, KC_LSFT,      KC_RCTL, KC_RSFT
    ),

    [_COLEMAK_DH] = LAYOUT_5x6_2_5(
        KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                        KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_MINS,
        KC_TAB , KC_Q   , KC_W   , KC_F   , KC_P   , KC_B   ,                        KC_J   , KC_L   , KC_U   , KC_Y   , KC_SCLN, KC_BSLS,
        KC_ESC , KC_A   , KC_R   , KC_S   , KC_T   , KC_G   ,                        KC_M   , KC_N   , KC_E   , KC_I   , KC_O   , KC_QUOT,
        KC_LSFT, KC_X   , KC_C   , KC_D   , KC_V   , KC_Z   ,                        KC_K   , KC_H   , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT,
        KC_LCTL, KC_LALT, KC_UP  , KC_DOWN, SYMDH  , SPCALT , KC_LGUI,      KC_ENT , KC_SPC , NUMDH  , KC_LEFT, KC_RGHT, KC_RALT, KC_RCTL,
                                                     KC_LCTL, KC_LSFT,      KC_RSFT, KC_RCTL
    ),

    [_SYMBOLS_DH] = LAYOUT_5x6_2_5(
        KC_NO  , KC_MUTE, KC_VOLD, KC_VOLU, KC_BRID, KC_BRIU,                        KC_STOP, KC_MPRV, KC_MNXT, KC_PSCR, KC_NO  , LY_TOG ,
        KC_NO  , KC_TILD, KC_LBRC, KC_LCBR, KC_LPRN, KC_HASH,                        KC_EQL , KC_RPRN, KC_RCBR, KC_RBRC, KC_PLUS, KC_NO  ,
        KC_NO  , KC_GRV , KC_AT  , KC_DLR , KC_QUOT, KC_AMPR,                        KC_PERC, KC_DQUO, KC_UNDS, KC_EXLM, KC_MINS, KC_QUOT,
        KC_NO  , KC_NO  , KC_LT  , KC_CIRC, KC_PIPE, KC_ASTR,                        KC_BSLS, KC_SCLN, KC_ASTR, KC_GT  , KC_NO  , KC_NO  ,
        KC_NO  , KC_PGUP, KC_PGDN, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,      KC_DEL , KC_TRNS, KC_TRNS, KC_HOME, KC_END , KC_NO  , KC_NO  ,
                                                     KC_TRNS, KC_COLN,      KC_RSFT, KC_RCTL
    ),

    [_NUMS_DH] = LAYOUT_5x6_2_5(
        KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  ,                        KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 ,
        KC_NO  , KC_NO  , KC_HOME, KC_UP  , KC_END , KC_NO  ,                        KC_EQL , KC_7   , KC_8   , KC_9   , KC_PLUS, KC_NO  ,
        KC_NO  , KC_COMM, KC_LEFT, KC_DOWN, KC_RGHT, KC_NO  ,                        KC_0   , KC_4   , KC_5   , KC_6   , KC_MINS, KC_NO  ,
        KC_NO  , KC_NO  , KC_PGUP, KC_NO  , KC_PGDN, KC_NO  ,                        KC_DOT , KC_1   , KC_2   , KC_3   , KC_SLSH, KC_NO  ,
        KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_TRNS, KC_SPC , KC_BSPC,      KC_NO  , KC_NO  , KC_TRNS, KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
                                                     KC_LCTL, KC_LSFT,      KC_RCTL, KC_RSFT
    ),
};
