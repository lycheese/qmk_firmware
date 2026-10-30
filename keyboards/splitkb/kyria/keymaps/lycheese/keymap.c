/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
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

enum layers {
    _QWERTY = 0,
    _GAME,
    _NUM,
    _SYM,
    _FUN,
    _NAV,
    _MEDIA,
    _SYMR,
    _HB,    // gaming hotbar layer (held from _GAME)
    _MENU   // gaming menu layer (one-shot from _HB)
};

// Latching modifiers for the hotbar layer: tap once while _HB is held and the
// modifier stays active until _HB is released (see process_record_user and
// layer_state_set_user below).
enum custom_keycodes {
    LATCH_CTL = SAFE_RANGE,
    LATCH_ALT,
    LATCH_CA
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Bone layer
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |   J  |   D  |   U  |   A  |   X  |                              |   P  |   H  |   L  |   M  |   W  |  ẞ     |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |   C  |   T  |   I  |   E  |   O  |                              |   B  |   N  |   R  |   S  |   G  |  Q     |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |   F  |   V  |   Ü  |   Ä  |   Ö  | GAME |QWERTY|  |COLEMK|      |   Y  |   Z  |   ,  |   .  |   K  |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      | ESC  | SPC  | TAB  |      |  |      | RET  | BSPC | DEL  |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_QWERTY] = LAYOUT(
      XXXXXXX,          KC_J,           KC_D,           KC_U,            KC_A,           KC_X,                                                                                               KC_P,    KC_H,         KC_L,         KC_M,         KC_W,            RALT(KC_S),
      XXXXXXX,          LGUI_T(KC_C),   LALT_T(KC_T),   LCTL_T(KC_I),    LSFT_T(KC_E),   KC_O,                                                                                               KC_B,    RSFT_T(KC_N), RCTL_T(KC_R), LALT_T(KC_S), RGUI_T(KC_G),    KC_Q,
      XXXXXXX,          KC_F,           KC_V,           RALT(KC_U),      RALT(KC_A),     RALT(KC_O),       TG(_GAME),     KC_SCRL,                                KC_LSFT, XXXXXXX,          KC_Y,    KC_Z,         KC_COMM,      KC_DOT,       KC_K,            XXXXXXX,
                                                        XXXXXXX, LT(_MEDIA, KC_ESC), LT(_NAV, KC_SPC), LT(_SYMR, KC_TAB), XXXXXXX,                                XXXXXXX, LT(_SYM, KC_ENT), LT(_NUM, KC_BSPC),     LT(_FUN, KC_DEL),       XXXXXXX
    ),

/*
 * Gaming layer (Voyager simulation: only 2 thumb keys on the left)
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * | t      | Esc  |  q   |  w   |  e   |  r   |                              |   y  |  u   |  i   |  o   |  p   |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * | g      |LShift|  a   |  s   |  d   |  f   |                              |   h  |  j   |  k   |  l   |      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | b      | Tab  |  z   |  x   |  c   |  v   | GAME |      |  |      |      |   n  |  m   |  ,   |  .   |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |  HB  | SPC  |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_GAME] = LAYOUT(
      KC_T,    KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,                                        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    _______,
      KC_G,    KC_LSFT, KC_A,    KC_S,    KC_D,    KC_F,                                        KC_H,    KC_J,    KC_K,    KC_L,    _______, _______,
      KC_B,    KC_TAB,  KC_Z,    KC_X,    KC_C,    KC_V,    _______, _______, _______, _______, KC_N,    KC_M,    KC_COMM, KC_DOT,  _______, _______,
                                 XXXXXXX, XXXXXXX, XXXXXXX, MO(_HB), KC_SPC,  _______, _______, _______, _______, _______
    ),
/*
 * Number layer
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  '     |  [   |  7   |  8   |  9   |  ]   |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |  /     |  ;   |  4   |  5   |  6   |  =   |                              |      | LSFT | LCTL | LALT | LGUI |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |  `   |  1   |  2   |  3   |  \   |      |      |  |      |      |      |      |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |  .   |  0   |  -   |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_NUM] = LAYOUT(
      KC_QUOT, KC_LBRC, KC_7,    KC_8,    KC_9,    KC_RBRC,                                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      KC_SLSH, KC_SCLN, KC_4,    KC_5,    KC_6,    KC_EQL,                                      XXXXXXX, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, XXXXXXX,
      XXXXXXX, KC_GRV,  KC_1,    KC_2,    KC_3,    KC_BSLS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                 XXXXXXX, KC_DOT,  KC_0,    KC_MINS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    ),

/*
 * Symbol layer
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  "     |  {   |  &   |  *   |  (   |  }   |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |  ?     |  :   |  $   |  %   |  ^   |  +   |                              |      | LSFT | LCTL | LALT | LGUI |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |  ~   |  !   |  @   |  #   |  |   |      |      |  |      |      |      |      |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |  (   |  )   |  _   |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_SYM] = LAYOUT(
      XXXXXXX, XXXXXXX, KC_UNDS, KC_LBRC, KC_RBRC, KC_CIRC,                                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      XXXXXXX, KC_BSLS, KC_SLSH, KC_LCBR, KC_RCBR, KC_ASTR,                                     XXXXXXX, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, XXXXXXX,
      XXXXXXX, KC_HASH, KC_DLR,  KC_PIPE, KC_TILD, KC_GRV,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                 XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    ),

/*
 * Function layer
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |  F12 |  F7  |  F8  |  F9  |      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  F11 |  F4  |  F5  |  F6  |      |                              |      | LSFT | LCTL | LALT | LGUI |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |  F10 |  F1  |  F2  |  F3  |      |      |      |  |      |      |      |      |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      | MENU | SPC  | TAB  |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_FUN] = LAYOUT(
      XXXXXXX, KC_F12,  KC_F7,   KC_F8,   KC_F9,   KC_PSCR,                                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      XXXXXXX, KC_F11,  KC_F4,   KC_F5,   KC_F6,   KC_SCRL,                                     XXXXXXX, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, XXXXXXX,
      XXXXXXX, KC_F10,  KC_F1,   KC_F2,   KC_F3,   KC_PAUS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                 XXXXXXX, KC_APP,  KC_SPC,  KC_TAB,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    ),

/*
 * Navigation layer
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_NAV] = LAYOUT(
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      XXXXXXX, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX,                                     KC_CAPS, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX,
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_INS,  KC_HOME, KC_PGDN, KC_PGUP, KC_END,  XXXXXXX,
                                 XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_ENT,  KC_BSPC, KC_DEL,  XXXXXXX
    ),

/*
 * Media layer
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_MEDIA] = LAYOUT(
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      XXXXXXX, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX,                                     XXXXXXX, XXXXXXX, KC_VOLD, KC_VOLU, XXXXXXX, XXXXXXX,
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                 XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MUTE, XXXXXXX
    ),


/*
 * Media layer
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_SYMR] = LAYOUT(
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                     KC_EXLM, KC_LT,   KC_GT,   KC_EQL,  KC_AMPR, XXXXXXX,
      XXXXXXX, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX,                                     KC_QUES, KC_LPRN, KC_RPRN, KC_MINS, KC_COLN, KC_AT,
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PLUS, KC_PERC, KC_DQUO, KC_QUOT, KC_SCLN, XXXXXXX,
                                 XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    ),

/*
 * Hotbar layer (held via HB on the gaming layer)
 *
 * Alt*, Ctrl* and C+A* latch: tap once and the modifier stays active for all
 * following hotbar presses until HB is released. Tapping another latch key
 * switches to it, tapping the same one again returns to the plain bar.
 * MENU is a one-shot menu layer.
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * | MENU   | Alt* |  7   |  8   |  9   |  -   |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * | C+A*   |LShift|  4   |  5   |  6   |  0   |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        | Ctrl*|  1   |  2   |  3   |  =   |      |      |  |      |      |      |      |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      | (HB) | SPC  |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_HB] = LAYOUT(
      OSL(_MENU), LATCH_ALT, KC_7, KC_8,    KC_9,    KC_MINS,                                     _______, _______, _______, _______, _______, _______,
      LATCH_CA,   KC_LSFT,   KC_4, KC_5,    KC_6,    KC_0,                                        _______, _______, _______, _______, _______, _______,
      XXXXXXX,    LATCH_CTL, KC_1, KC_2,    KC_3,    KC_EQL,  XXXXXXX, XXXXXXX, _______, _______, _______, _______, _______, _______, _______, _______,
                                   XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, _______, _______, _______, _______, _______
    ),

/*
 * Menu layer (one-shot from the hotbar layer)
 *
 * Each left-hand key sends the right-hand key of the same finger, so game
 * menus bound to right-hand keys are reachable without leaving the mouse.
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * | Esc    |  p   |  o   |  i   |  u   |  y   |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  ;   |  l   |  k   |  j   |  h   |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |  /   |  .   |  ,   |  m   |  n   |      |      |  |      |      |      |      |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      | SPC  |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_MENU] = LAYOUT(
      KC_ESC,  KC_P,    KC_O,    KC_I,    KC_U,    KC_Y,                                        _______, _______, _______, _______, _______, _______,
      XXXXXXX, KC_SCLN, KC_L,    KC_K,    KC_J,    KC_H,                                        _______, _______, _______, _______, _______, _______,
      XXXXXXX, KC_SLSH, KC_DOT,  KC_COMM, KC_M,    KC_N,    XXXXXXX, XXXXXXX, _______, _______, _______, _______, _______, _______, _______, _______,
                                 XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, _______, _______, _______, _______, _______
    ),

// /*
//  * Layer template
//  *
//  * ,-------------------------------------------.                              ,-------------------------------------------.
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
//  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        `----------------------------------'  `----------------------------------'
//  */
//     [_LAYERINDEX] = LAYOUT(
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
//     ),
};

// Modifiers currently latched on the hotbar layer (8-bit mod mask).
static uint8_t latched_mods = 0;

static void clear_latch(void) {
    if (latched_mods) {
        unregister_mods(latched_mods);
        latched_mods = 0;
    }
}

// Latch `mods`; latching the same mods again clears the latch.
static void toggle_latch(uint8_t mods) {
    bool same = (latched_mods == mods);
    clear_latch();
    if (!same) {
        latched_mods = mods;
        register_mods(latched_mods);
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) {
        return true;
    }
    switch (keycode) {
        case LATCH_CTL:
            toggle_latch(MOD_BIT(KC_LCTL));
            return false;
        case LATCH_ALT:
            toggle_latch(MOD_BIT(KC_LALT));
            return false;
        case LATCH_CA:
            toggle_latch(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LALT));
            return false;
    }
    return true;
}

// Releasing HB (leaving the hotbar layer) releases any latched modifier.
layer_state_t layer_state_set_user(layer_state_t state) {
    if (!layer_state_cmp(state, _HB)) {
        clear_latch();
    }
    return state;
}

