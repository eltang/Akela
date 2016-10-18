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

#include "Akela.h"

class DummyHID : public virtual AkelaAbstractHID {
public:
  virtual void press (uint8_t) {
  };

  virtual void release (uint8_t) {
  };

  DummyHID () : AkelaAbstractHID () {};
};

static uint16_t keymap[] = {
   KC_F11   ,KC_9     ,KC_7     ,KC_5     ,KC_3     ,KC_1     ,KC_NO
  ,KC_BSLS  ,KC_X     ,KC_W     ,KC_C     ,KC_H     ,KC_F
  ,KC_TAB   ,KC_A     ,KC_O     ,KC_E     ,KC_I     ,KC_U     ,LSFT(KC_9)
  ,KC_MPLY  ,KC_Z     ,KC_Q     ,KC_QUOT  ,KC_COMM  ,KC_DOT   ,KC_NO

                                            ,KC_NO    ,KC_BSPC  ,KC_NO    ,KC_NO
                                                          ,KC_NO


                                                    ,KC_NO    ,KC_0     ,KC_2     ,KC_4     ,KC_6     ,KC_8     ,KC_NO
                                                              ,KC_M     ,KC_G     ,KC_L     ,KC_P     ,KC_SLSH  ,KC_GRV
                                                    ,KC_NO    ,KC_D     ,KC_R     ,KC_T     ,KC_N     ,KC_S     ,KC_EQL
                                                    ,KC_NO    ,KC_B     ,KC_K     ,KC_V     ,KC_Y     ,KC_J     ,KC_MSTP

                                            ,KC_NO    ,KC_SPC   ,KC_ENT   ,KC_MINS
                                                          ,KC_NO
};

static DummyHID TestHID = DummyHID ();
static AkelaKeyEventHandler TestEH = AkelaKeyEventHandler (&TestHID);
static AkelaKeyMap TestKeyMap = AkelaKeyMap ((uint16_t *)keymap);
static AkelaKeyboard keyboard = AkelaKeyboard (&TestEH, &TestKeyMap);

void setup () {
  keyboard.setup ();
}

void loop () {
  keyboard.loop ();
}
