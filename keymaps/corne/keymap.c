#include QMK_KEYBOARD_H

#define ACTION_TD_TH(tap, hold) { .fn = {NULL, td_th_finished, td_th_reset}, .user_data = (void *)&((td_tap_hold_t){tap, hold}) }
#define HYPER_SPC MT(MOD_LCTL|MOD_LALT, KC_SPC)
#define HYPER_TAB MT(MOD_LCTL|MOD_LALT|MOD_LSFT, KC_TAB)

enum layers { _DEFAULT, _LOWER, _RAISE, _ADJUST };
enum custom_keycodes { TD_SCLN_COLN };

typedef struct {
  uint16_t tap;
  uint16_t hold;
  uint16_t held;
} td_tap_hold_t;

static void td_th_finished(tap_dance_state_t *state, void *user_data) {
  td_tap_hold_t *tap_hold = (td_tap_hold_t *)user_data;
  if(state->pressed) {
    if(state->count == 1
#ifndef PERMISSIVE_HOLD
       && !state->interrupted
#endif
    ) {
      register_code16(tap_hold->hold);
      tap_hold->held = tap_hold->hold;
    } else {
      register_code16(tap_hold->tap);
      tap_hold->held = tap_hold->tap;
    }
  }
}

static void td_th_reset(tap_dance_state_t *state, void *user_data) {
  td_tap_hold_t *tap_hold = (td_tap_hold_t *)user_data;

  if(tap_hold->held) {
    unregister_code16(tap_hold->held);
    tap_hold->held = 0;
  }
}

tap_dance_action_t tap_dance_actions[] = { [TD_SCLN_COLN] = ACTION_TD_TH(KC_COLN, KC_SCLN) };
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  tap_dance_action_t *action;

  switch(keycode) {
    case TD(TD_SCLN_COLN):
      action = &tap_dance_actions[QK_TAP_DANCE_GET_INDEX(keycode)];
      if(!record->event.pressed && action->state.count && !action->state.finished) {
        td_tap_hold_t *tap_hold = (td_tap_hold_t *)action->user_data;
        tap_code16(tap_hold->tap);
      }
  }
  return true;
}



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_DEFAULT] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_ESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,    KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      HYPER_TAB,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L,   KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M,    KC_COMM, KC_DOT, KC_SLSH, KC_RGUI,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                   KC_LCTL,   MO(_LOWER),  HYPER_SPC,     KC_ENT,   MO(_RAISE), KC_RALT
                               //|----------------------------------| |---------------------------------|
  ),

    [_LOWER] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_ESC,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  KC_DEL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      HYPER_TAB,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                          KC_6,    KC_7,    KC_8,    KC_9,     KC_0,  KC_CAPS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, KC_UNDO, KC_CUT, KC_COPY, KC_PASTE, XXXXXXX,                      KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, KC_PGUP,  KC_PGDN,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LCTL, _______, HYPER_SPC,     KC_ENT,   MO(_RAISE), KC_RALT
                                      //`--------------------------'  `--------------------------'
  ),

    [_RAISE] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_ESC, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_TAB, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS,  KC_GRV,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_TILD,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LCTL,   MO(_ADJUST),  KC_SPC,     KC_ENT, _______, KC_RALT
                                      //`--------------------------'  `--------------------------'
  ),

    [_ADJUST] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                        KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,   KC_F12,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX,                      RGB_MODE_REVERSE, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX,                      RGB_MODE_FORWARD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LCTL, _______,  KC_SPC,     KC_ENT, _______, KC_RALT
                                      //`--------------------------'  `--------------------------'
  )
};
