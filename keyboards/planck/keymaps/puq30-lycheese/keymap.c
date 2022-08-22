#include QMK_KEYBOARD_H

enum planck_layers {
  _PUQ,
  _NAV,
  _NUM,
  _SYMR,
  _SYML,
  _MEDIA,
  _FUN,
};

//#define LSFT LT(KC_RSFT, KC_A) // Switches to the shift layer for the right side on hold.
//#define RSFT LT(KC_LSFT, KC_T)

#define HRM_H LGUI_T(KC_H)
#define HRM_I LALT_T(KC_I)
#define HRM_E LCTL_T(KC_E)
#define HRM_A LSFT_T(KC_A)
#define HRM_T LSFT_T(KC_T)
#define HRM_R LCTL_T(KC_R)
#define HRM_N LALT_T(KC_N)
#define HRM_S LGUI_T(KC_S)

#define ESC LT(_MEDIA, KC_ESC)
#define SPC LT(_NAV,   KC_SPC)
#define TAB LT(_SYMR,  KC_TAB)
#define RET LT(_SYML,  KC_ENT)
#define BSP LT(_NUM,   KC_BSPC)
#define DEL LT(_FUN,   KC_DEL)

enum macro_keycodes {
  DIA = SAFE_RANGE, // Diacritics key, NO-OP by default
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* PUQ30
 *
 * DIA is the diacritics key which is a no-op unless one of the special keys
 * (a,o,u,s) is pressed before. Pressing is after a will tap backspace and
 * insert an umlaut a and so on. For s it will insert sz (scharfes s).
 *
 * ,-----------------------------------------------------------------------------------.
 * | P    |   U  | DIA  |   ,  |   Q  |   _  |   _  |   G  |   C  |   L  |   M  |    F |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | H    |   I  |   E  |   A  |   O  |   _  |   _  |   D  |   T  |   R  |   N  |    S |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | K    |   Y  |   .  |   '  |   X  |   _  |   _  |   J  |   V  |   W  |   B  |    Z |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | _    |   _  |  ESC |  SPC |  TAB |   _  |   _  |  RET |  BSP |  DEL |   _  |    _ |
 * `-----------------------------------------------------------------------------------'
 */
[_PUQ] = LAYOUT_planck_grid(
    KC_P,    KC_U,    DIA,     KC_COMM, KC_Q,    KC_NO,    KC_NO,    KC_G,    KC_C,    KC_L,    KC_M,    KC_F,
    HRM_H,   HRM_I,   HRM_E,   HRM_A,   KC_O,    KC_NO,    KC_NO,    KC_D,    HRM_T,   HRM_R,   HRM_N,   HRM_S,
    KC_K,    KC_Y,    KC_DOT,  KC_QUOT, KC_X,    KC_NO,    KC_NO,    KC_J,    KC_V,    KC_W,    KC_B,    KC_Z,
    KC_NO,   KC_NO,   ESC,     SPC,     TAB,     KC_NO,    KC_NO,    RET,     BSP,     DEL,     KC_NO,   KC_NO
),

[_NAV] = LAYOUT_planck_grid(
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_NO,   KC_NO,    KC_NO,    KC_NO,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,    KC_NO,   KC_HOME, KC_PGDN, KC_PGUP, KC_END,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,    KC_ENT,  KC_BSPC, KC_DEL,  KC_NO,   KC_NO

),

[_NUM] = LAYOUT_planck_grid(
    KC_NO,   KC_7,    KC_8,    KC_9,    KC_NO,   KC_NO,    KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    KC_NO,   KC_4,    KC_5,    KC_6,    KC_NO,   KC_NO,    KC_NO,    KC_NO,   KC_LSFT, KC_RCTL, KC_LALT, KC_LGUI,
    KC_NO,   KC_1,    KC_2,    KC_3,    KC_NO,   KC_NO,    KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    KC_NO,   KC_NO,   KC_NO,   KC_0,    KC_NO,   KC_NO,    KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO
),

[_SYMR] = LAYOUT_planck_grid(
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,    KC_EXLM, KC_LT,   KC_GT,   KC_EQL,  KC_AMPR,
    KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_NO,   KC_NO,    KC_NO,    KC_QUES, KC_LPRN, KC_RPRN, KC_MINS, KC_COLN,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,    KC_PLUS, KC_PERC, KC_DQUO, KC_QUOT, KC_SCLN,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,    KC_ENT,  KC_BSPC, KC_DEL,  KC_NO,   KC_NO
),

[_SYML] = LAYOUT_planck_grid(
    KC_AT,   KC_UNDS, KC_LBRC, KC_RBRC, KC_CIRC, KC_NO,    KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    KC_BSLS, KC_SLSH, KC_LCBR, KC_RCBR, KC_ASTR, KC_NO,    KC_NO,    KC_NO,   KC_LSFT, KC_RCTL, KC_LALT, KC_LGUI,
    KC_HASH, KC_DLR,  KC_PIPE, KC_TILD, KC_GRV,  KC_NO,    KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    KC_NO,   KC_NO,   KC_NO,   KC_0,    KC_NO,   KC_NO,    KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO
),

[_MEDIA] = LAYOUT_planck_grid(
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_NO,   KC_NO,    KC_NO,    KC_NO,   KC_NO,   KC_VOLD, KC_VOLU, KC_NO,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,    KC_NO,   KC_MUTE, KC_NO,   KC_NO,   KC_NO
),

[_FUN] = LAYOUT_planck_grid(
    KC_F12,  KC_F7,   KC_F8,   KC_F9,   KC_PSCR,  KC_NO,    KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    KC_F11,  KC_F4,   KC_F5,   KC_F6,   KC_SLCK,  KC_NO,    KC_NO,    KC_NO,   KC_LSFT, KC_RCTL, KC_LALT, KC_LGUI,
    KC_F10,  KC_F1,   KC_F2,   KC_F3,   KC_PAUS,  KC_NO,    KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    KC_NO,   KC_NO,   KC_NO,   KC_0,    KC_NO,    KC_NO,    KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO
),


/* Vorlage
 *
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */

/*
[_VORL] = LAYOUT_planck_grid(
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO

),
*/
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  static uint8_t dia_key = 0;
  //char dia_str[3]; // DEBUG

  switch (keycode) {
    case HRM_A:
      if (record->event.pressed) {
        if ((get_mods() & MOD_BIT(KC_LSFT)) == MOD_BIT(KC_LSFT)) {
          dia_key = 11;
        } else {
          dia_key = 1;
        }
      }
      return true;
    case KC_O:
      if (record->event.pressed) {
        if ((get_mods() & MOD_BIT(KC_LSFT)) == MOD_BIT(KC_LSFT)) {
          dia_key = 22;
        } else {
          dia_key = 2;
        }
      }
      return true;
    case KC_U:
      if (record->event.pressed) {
        if ((get_mods() & MOD_BIT(KC_LSFT)) == MOD_BIT(KC_LSFT)) {
          dia_key = 33;
        } else {
          dia_key = 3;
        }
      }
      return true;
    case HRM_S:
      if (record->event.pressed) {
        dia_key = 4;
      }
      return true;
    case DIA:
      if (record->event.pressed) {
        //sprintf(dia_str, "%d", dia_key); // DEBUG

        switch (dia_key) {
          case 1:
            SEND_STRING(SS_TAP(X_BSPC)
                        SS_RALT("a"));
            break;
          case 11:
            SEND_STRING(SS_TAP(X_BSPC)
                        SS_DOWN(X_LSFT)
                        SS_RALT("a")
                        SS_UP(X_LSFT));
            break;
          case 2:
            SEND_STRING(SS_TAP(X_BSPC)
                        SS_RALT("o"));
            break;
          case 22:
            SEND_STRING(SS_TAP(X_BSPC)
                        SS_DOWN(X_LSFT)
                        SS_RALT("o")
                        SS_UP(X_LSFT));
            break;
          case 3:
            SEND_STRING(SS_TAP(X_BSPC)
                        SS_RALT("u"));
            break;
          case 33:
            SEND_STRING(SS_TAP(X_BSPC)
                        SS_DOWN(X_LSFT)
                        SS_RALT("u")
                        SS_UP(X_LSFT));
            break;
          case 4:
            SEND_STRING(SS_TAP(X_BSPC)
                        SS_RALT("s"));
            break;
        }
        //send_string(dia_str); // For debugging purposes
        dia_key = 0;
      }
      return false;
    default:
      if (record->event.pressed) {
        dia_key = 0;
      }
      return true;
  }
}

const uint16_t PROGMEM test_combo1[] = {HRM_A, HRM_E, COMBO_END};
const uint16_t PROGMEM test_combo2[] = {HRM_A, HRM_I, COMBO_END};
const uint16_t PROGMEM test_combo3[] = {HRM_E, HRM_I, COMBO_END};
const uint16_t PROGMEM test_combo4[] = {HRM_R, HRM_N, COMBO_END};
const uint16_t PROGMEM test_combo5[] = {HRM_T, HRM_N, COMBO_END};
const uint16_t PROGMEM test_combo6[] = {HRM_T, HRM_R, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  COMBO(test_combo1, OSM(MOD_LSFT)),
  COMBO(test_combo2, OSM(MOD_LCTL)),
  COMBO(test_combo3, OSM(MOD_LALT)),
  COMBO(test_combo4, OSM(MOD_LALT)),
  COMBO(test_combo5, OSM(MOD_LCTL)),
  COMBO(test_combo6, OSM(MOD_LSFT)),
};
