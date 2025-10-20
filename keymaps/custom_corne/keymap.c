#include QMK_KEYBOARD_H

#define VOL_UP   KC_KB_VOLUME_UP
#define VOL_DOWN KC_KB_VOLUME_DOWN

#define HP_SPC MT(MOD_LCTL|MOD_LALT, KC_SPC)
#define HP_TAB MT(MOD_LCTL|MOD_LALT|MOD_LSFT, KC_TAB)
// #define HP_QUOTE MT(MOD_LALT|MOD_LSFT, KC_QUOT)

#define TD_CLN TD(TD_SCLN_COLN)
#define TD_SLSH TD(TD_SLSH_QUESTMARK)
#define TD_COMM TD(TD_COMM_LT)
#define TD_DOT TD(TD_DOT_GT)
#define TD_QUOTE TD(TD_SQUOTE_DQUOTES)

enum layers { _DEFAULT, _LOWER, _RAISE, _ADJUST };
enum custom_keycodes { TD_SCLN_COLN, TD_SLSH_QUESTMARK, TD_COMM_LT, TD_DOT_GT, TD_SQUOTE_DQUOTES };

tap_dance_action_t tap_dance_actions[] = {
    [TD_SCLN_COLN] = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, KC_COLN),
    [TD_SLSH_QUESTMARK] = ACTION_TAP_DANCE_DOUBLE(KC_SLSH, KC_QUES),
    [TD_COMM_LT] = ACTION_TAP_DANCE_DOUBLE(KC_COMM, KC_LT),
    [TD_DOT_GT] = ACTION_TAP_DANCE_DOUBLE(KC_DOT, KC_GT),
    [TD_SQUOTE_DQUOTES] = ACTION_TAP_DANCE_DOUBLE(KC_QUOTE, KC_DQT),
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_DEFAULT] = LAYOUT_split_3x6_3(
  //,------------------------------------------------------                    ,------------------------------------------------------
      KC_ESC,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      HP_TAB,   KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L,    TD_CLN,  TD_QUOTE,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,                       KC_N,    KC_M,    TD_COMM, TD_DOT,  TD_SLSH, KC_RGUI,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                   KC_LCTL,   MO(_LOWER),  HP_SPC,     KC_ENT,   MO(_RAISE), KC_RALT
                               //|----------------------------------| |---------------------------------|
  ),

    [_LOWER] = LAYOUT_split_3x6_3(
  //,------------------------------------------------------                    ,------------------------------------------------------
      KC_ESC,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_DEL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      HP_TAB,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_CAPS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, KC_PGUP, KC_PGDN,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LCTL, _______, HP_SPC,     KC_ENT,   MO(_RAISE), KC_RALT
                                      //`--------------------------'  `--------------------------'
  ),

    [_RAISE] = LAYOUT_split_3x6_3(
  //,------------------------------------------------------                    ,------------------------------------------------------
      KC_ESC, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_TAB, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS,  KC_GRV,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, VOL_UP, VOL_DOWN,                     KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_TILD,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LCTL,   MO(_ADJUST),  KC_SPC,     KC_ENT, _______, KC_RALT
                                      //`--------------------------'  `--------------------------'
  ),

    [_ADJUST] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                        KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,   KC_F12,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      UG_TOGG, UG_HUEU, UG_SATU, UG_VALU, XXXXXXX, XXXXXXX,                     XXXXXXX , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      UG_NEXT, UG_HUED, UG_SATD, UG_VALD, XXXXXXX, XXXXXXX,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LCTL, _______,  KC_SPC,     KC_ENT, _______, KC_RALT
                                      //`--------------------------'  `--------------------------'
  )
};
