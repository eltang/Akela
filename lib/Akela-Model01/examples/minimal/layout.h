/* -*- mode: c++ -*-
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

#define KC_NIY KC_NO

static const uint16_t keymap[] PROGMEM =
  KEYMAP (
  // left hand

   KC_NIY     ,KC_1       ,KC_2       ,KC_3       ,KC_4       ,KC_5       ,KC_NO
  ,KC_GRV     ,KC_Q       ,KC_W       ,KC_E       ,KC_R       ,KC_T       ,KC_TAB
  ,KC_PGUP    ,KC_A       ,KC_S       ,KC_D       ,KC_F       ,KC_G
  ,KC_PGDN    ,KC_Z       ,KC_X       ,KC_C       ,KC_V       ,KC_B       ,KC_ESC

                   ,KC_LCTL    ,KC_BSPC    ,KC_LGUI    ,KC_LSFT
                               ,KC_NO

   // right hand

   ,KC_NO      ,KC_6       ,KC_7       ,KC_8       ,KC_9       ,KC_0       ,KC_NO
   ,KC_ENT     ,KC_Y       ,KC_U       ,KC_I       ,KC_O       ,KC_P       ,KC_EQL
               ,KC_H       ,KC_J       ,KC_K       ,KC_L       ,KC_SCLN    ,KC_QUOT
   ,KC_NO      ,KC_N       ,KC_M       ,KC_COMM    ,KC_DOT     ,KC_SLSH    ,KC_MINS

                   ,KC_RSFT    ,KC_RALT    ,KC_SPC     ,KC_RCTL
                               ,KC_NO
);
