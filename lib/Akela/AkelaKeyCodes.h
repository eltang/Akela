/*
 * Akela -- Animated Keyboard Extension Library for Arduino
 * Copyright (C) 2016  Gergely Nagy
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
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

#pragma once

enum {
  KC_NO = 0,
  KC_A = 0x04,
  KC_B,
  KC_C,
  KC_D,
  KC_E,
  KC_F,
  KC_G,
  KC_H,
  KC_I,
  KC_J,
  KC_K,
  KC_L,
  KC_M,
  KC_N,
  KC_O,
  KC_P,
  KC_Q,
  KC_R,
  KC_S,
  KC_T,
  KC_U,
  KC_V,
  KC_W,
  KC_X,
  KC_Y,
  KC_Z,

  KC_1 = 0x1E,
  KC_2,
  KC_3,
  KC_4,
  KC_5,
  KC_6,
  KC_7,
  KC_8,
  KC_9,
  KC_0,

  KC_ENT,
  KC_ESC,
  KC_BSPC,
  KC_TAB,
  KC_SPC,
  KC_MINS,
  KC_EQL,
  KC_LBRC,
  KC_RBRC,
  KC_BSLS,

  KC_QUOT = 0x034,
  KC_GRV,
  KC_COMM,
  KC_DOT,
  KC_SLSH,

  KC_F11 = 0x44,

  KC_MPLY = 0xB0, // TODO
  KC_MSTP = 0xB7,

  KC_LCTL = 0xE0,
  KC_LSFT,
  KC_LALT,
  KC_LGUI,
  KC_RCTL,
  KC_RSFT,
  KC_RALT,
  KC_RGUI
};

enum {
  MOD_LCTL = 0x01,
  MOD_LSFT = 0x02,
  MOD_LALT = 0x04,
  MOD_LGUI = 0x08,

  MOD_RCTL = 0x10,
  MOD_RSFT = 0x20,
  MOD_RALT = 0x40,

  MOD_FN   = 0x80
};

#define LCTL(kc) (kc | (MOD_LCTL << 8))
#define LSFT(kc) (kc | (MOD_LSFT << 8))
#define LALT(kc) (kc | (MOD_LALT << 8))
#define LGUI(kc) (kc | (MOD_LGUI << 8))
#define RCTL(kc) (kc | (MOD_RCTL << 8))
#define RSFT(kc) (kc | (MOD_RSFT << 8))
#define RALT(kc) (kc | (MOD_RALT << 8))
#define FN(kc)   (kc | (MOD_FN   << 8))

#define KEYCODE(kc) (kc & ~0xff00)
#define MODS(kc) (kc >> 8)
