#include QMK_KEYBOARD_H
#include "timer.h"
#include "quantum.h"

static uint16_t rgb_idle_timer = 0;
static bool rgb_is_on = true;

enum layer_names
{
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_split_3x6_3(
        KC_ESC, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC,
        KC_LCTL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_TAB,
        KC_LGUI, MO(1), KC_SPC, KC_ENT, MO(2), KC_RALT),

    [_LOWER] = LAYOUT_split_3x6_3(
        KC_TAB, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC,
        KC_LCTL, KC_NO, KC_NO, KC_NO, KC_MPRV, KC_MNXT, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_NO, KC_DEL,
        KC_LSFT, KC_NO, KC_MUTE, KC_VOLD, KC_VOLU, KC_MPLY, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_PSCR,
        KC_LGUI, KC_TRNS, KC_SPC, KC_ENT, MO(3), KC_RALT),

    [_RAISE] = LAYOUT_split_3x6_3(
        KC_TAB, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
        KC_LCTL, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_MINS, KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS, KC_GRV,
        KC_LSFT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_TILD,
        KC_LGUI, MO(3), KC_SPC, KC_ENT, KC_TRNS, KC_RALT),

    [_ADJUST] = LAYOUT_split_3x6_3(
        QK_BOOT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        RM_TOGG, RM_HUEU, RM_SATU, RM_VALU, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        RM_NEXT, RM_HUED, RM_SATD, RM_VALD, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_LGUI, KC_TRNS, KC_SPC, KC_ENT, KC_TRNS, KC_RALT)};

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
    if (record->event.pressed)
    {
        rgb_idle_timer = timer_read();

        if (!rgb_is_on)
        {
            rgb_is_on = true;
            rgb_matrix_set_suspend_state(false);
        }
    }
    return true;
}

void matrix_scan_user(void)
{
    uint16_t idle_timeout = 60000;

    if (rgb_is_on && (timer_elapsed(rgb_idle_timer) > idle_timeout))
    {
        rgb_is_on = false;
        rgb_matrix_set_suspend_state(true);
    }
}