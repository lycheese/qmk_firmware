/* Copyright 2015-2017 Jack Humbert
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "muse.h"


enum planck_layers {
  _QWERTY,
  _RALT_OVERLAY,
  _RALT_SHIFT
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK,
  PLOVER,
  BACKLIT,
  EXT_PLV
};

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP, // Send two single taps
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

// Tap dance enums
enum {
    X_CTL,
    TD_QUOT_BKSL,
    TD_RALT_SHIFT,
};

td_state_t cur_dance(qk_tap_dance_state_t *state);

// For the x tap dance. Put it here so it can be used in any keymap
void x_finished(qk_tap_dance_state_t *state, void *user_data);
void x_reset(qk_tap_dance_state_t *state, void *user_data);

void ralt_shift_finished(qk_tap_dance_state_t *state, void *user_data);
void ralt_shift_reset(qk_tap_dance_state_t *state, void *user_data);

#define RALTP MO(_RALT_OVERLAY)
#define RALT_SH MO(_RALT_SHIFT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty for software bone layout
 * (Modifiers are rotated in software:
 *   - Alt --> Ctrl
 *   - Super --> Alt
 *   - Ctrl --> Super)
 * (Keys in parens are accessed via holding the key (tap dance))
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |   [  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Caps |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |   '  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  | Shift|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   <  | Left | Right| Ctrl | Alt  |    Space    | AltGr| Super| Down |  Up  |   \  |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_planck_grid(
    KC_TAB,  KC_Q,    KC_W,     KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,  KC_I,    KC_O,    KC_P,    KC_LBRC,
    KC_CAPS, KC_A,    KC_S,     KC_D,    KC_F,    KC_G,    KC_H,    KC_J,  KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,     KC_C,    KC_V,    KC_B,    KC_N,    KC_M,  KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
    KC_NUBS, KC_LEFT, KC_RIGHT, KC_LCTL, KC_LALT, KC_SPC,  KC_SPC,  KC_RALT, KC_LGUI, KC_DOWN, KC_UP,   KC_BSLS
),

[_RALT_OVERLAY] = LAYOUT_planck_grid(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    RALT_SH, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

[_RALT_SHIFT] = LAYOUT_planck_grid(
    _______, _______, _______, _______, _______, _______, _______, _______, S(KC_7), S(KC_8), S(KC_9), _______,
    _______, _______, _______, _______, _______, _______, _______, _______, S(KC_4), S(KC_5), S(KC_6), _______,
    _______, _______, _______, _______, _______, _______, _______, _______, S(KC_1), S(KC_2), S(KC_3), _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* [_TRANS_TEMPLATE] = LAYOUT_planck_grid( */
/*     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, */
/*     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, */
/*     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, */
/*     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ */
/* ), */

};

/* Return an integer that corresponds to what kind of tap dance should be executed.
 *
 * How to figure out tap dance state: interrupted and pressed.
 *
 * Interrupted: If the state of a dance dance is "interrupted", that means that another key has been hit
 *  under the tapping term. This is typically indicitive that you are trying to "tap" the key.
 *
 * Pressed: Whether or not the key is still being pressed. If this value is true, that means the tapping term
 *  has ended, but the key is still being pressed down. This generally means the key is being "held".
 *
 * One thing that is currenlty not possible with qmk software in regards to tap dance is to mimic the "permissive hold"
 *  feature. In general, advanced tap dances do not work well if they are used with commonly typed letters.
 *  For example "A". Tap dances are best used on non-letter keys that are not hit while typing letters.
 *
 * Good places to put an advanced tap dance:
 *  z,q,x,j,k,v,b, any function key, home/end, comma, semi-colon
 *
 * Criteria for "good placement" of a tap dance key:
 *  Not a key that is hit frequently in a sentence
 *  Not a key that is used frequently to double tap, for example 'tab' is often double tapped in a terminal, or
 *    in a web form. So 'tab' would be a poor choice for a tap dance.
 *  Letters used in common words as a double. For example 'p' in 'pepper'. If a tap dance function existed on the
 *    letter 'p', the word 'pepper' would be quite frustating to type.
 *
 * For the third point, there does exist the 'TD_DOUBLE_SINGLE_TAP', however this is not fully tested
 *
 */
td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (state->interrupted) return TD_DOUBLE_SINGLE_TAP;
        else if (state->pressed) return TD_DOUBLE_HOLD;
        else return TD_DOUBLE_TAP;
    }

    // Assumes no one is trying to type the same letter three times (at least not quickly).
    // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    // an exception here to return a 'TD_TRIPLE_SINGLE_TAP', and define that enum just like 'TD_DOUBLE_SINGLE_TAP'
    if (state->count == 3) {
        if (state->interrupted || !state->pressed) return TD_TRIPLE_TAP;
        else return TD_TRIPLE_HOLD;
    } else return TD_UNKNOWN;
}

// Create an instance of 'td_tap_t' for the 'x' tap dance.
static td_tap_t xtap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void x_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: register_code(KC_X); break;
        case TD_SINGLE_HOLD: register_code(KC_LCTRL); break;
        case TD_DOUBLE_TAP: register_code(KC_ESC); break;
        case TD_DOUBLE_HOLD: register_code(KC_LALT); break;
        // Last case is for fast typing. Assuming your key is `f`:
        // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_X); register_code(KC_X);
        default: break;
    }
}

void x_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_X); break;
        case TD_SINGLE_HOLD: unregister_code(KC_LCTRL); break;
        case TD_DOUBLE_TAP: unregister_code(KC_ESC); break;
        case TD_DOUBLE_HOLD: unregister_code(KC_LALT);
        case TD_DOUBLE_SINGLE_TAP: unregister_code(KC_X);
        default: break;
    }
    xtap_state.state = TD_NONE;
}

void ralt_shift_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: register_code(KC_RALT); break;
        case TD_SINGLE_HOLD: register_code(KC_RALT); break;
        case TD_DOUBLE_HOLD: unregister_code(KC_RALT); // Should be a layer switch but that doesn't work here
        // Last case is for fast typing. Assuming your key is `f`:
        // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_QUOT); register_code(KC_QUOT);
        default: break;
    }
}

void ralt_shift_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_RALT); break;
        case TD_SINGLE_HOLD: unregister_code(KC_RALT); break;
        case TD_DOUBLE_SINGLE_TAP: unregister_code(KC_RALT);
        default: break;
    }
    xtap_state.state = TD_NONE;
}

void quot_bksl_finished(qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: register_code(KC_QUOT); break;
        case TD_SINGLE_HOLD: register_code(KC_BSLS); break;
        // Last case is for fast typing. Assuming your key is `f`:
        // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_QUOT); register_code(KC_QUOT);
        default: break;
    }
}

void quot_bksl_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_QUOT); break;
        case TD_SINGLE_HOLD: unregister_code(KC_BSLS); break;
        case TD_DOUBLE_SINGLE_TAP: unregister_code(KC_QUOT);
        default: break;
    }
    xtap_state.state = TD_NONE;
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [X_CTL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, x_finished, x_reset),
    [TD_QUOT_BKSL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, quot_bksl_finished, quot_bksl_reset),
    [TD_RALT_SHIFT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ralt_shift_finished, ralt_shift_reset),
};
