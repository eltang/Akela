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

static uint16_t empty_keymap[] = {
   KC_NO    ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO
  ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO
  ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO
  ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO

                                            ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO
                                                          ,KC_NO


                                                    ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO
                                                              ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO
                                                    ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO
                                                    ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO

                                            ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO
                                                          ,KC_NO
};

static uint16_t modful_keymap[] = {
   LCTL(KC_1) ,LSFT(KC_2) ,LALT(KC_3) ,LGUI(KC_4) ,RCTL(KC_5) ,RSFT(KC_6) ,RALT(KC_7)
  ,LCTL(RCTL(LSFT(RSFT(LALT(RALT(LGUI(KC_A)))))))   ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO
  ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO
  ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO

                                            ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO
                                                          ,KC_NO


                                                    ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO
                                                              ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO
                                                    ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO
                                                    ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO

                                            ,KC_NO    ,KC_NO    ,KC_NO    ,KC_NO
                                                          ,KC_NO
};
