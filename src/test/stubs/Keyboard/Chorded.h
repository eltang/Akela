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

class ChordedKeyboard : public Akela::Keyboard {
 public:
  void test () {
    press (0);
    loop ();
    release (0);
    loop ();

    press (1);
    for (int i = 2; i < 6; i++) {
      press (i);
      loop ();
      release (i);
      loop ();
    }
    release (1);
    for (int i = 2; i < 6; i++) {
      press (i);
      loop ();
      release (i);
      loop ();
    }
  }

  ChordedKeyboard (Akela::AbstractScanner *s,
                   Akela::KeyEventHandler *eh)
    : Akela::Keyboard (s, eh) {
  };
};
