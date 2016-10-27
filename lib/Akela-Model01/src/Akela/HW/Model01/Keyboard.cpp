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

#include <avr/wdt.h>

#include "Akela/HW/Model01.h"

M01::Model01::Model01 (Akela::AbstractScanner *scanner,
                       Akela::EventHandler::Base *eh)
  : Akela::Keyboard (scanner, eh) {
  prevState.left.all = prevState.right.all = 0;
  currState.left.all = currState.right.all = 0;
}

void
M01::Model01::setup ()
{
  wdt_disable ();
  Akela::Keyboard::setup ();
}

void
M01::Model01::handleKey (byte side, byte row, byte col) {
  keydata_t p, c;
  uint8_t keynum = (row * 8) + col;

  if (side == 1) {
    p = prevState.right;
    c = currState.right;
  } else {
    p = prevState.left;
    c = currState.left;
  }

  bool pp = bitRead(p.all, keynum);
  bool cp = bitRead(c.all, keynum);

  if (pp == cp && cp)
    return hold (keynum + (32 * side));

  if (cp)
    return press (keynum + (32 * side));

  return release (keynum + (32 * side));
}

void
M01::Model01::loop ()
{
  prevState = currState;
  currState = *((M01::Scanner::MatrixState *)scanner->scan ());

  for (uint8_t row = 0; row < 4; row++) {
    for (uint8_t col = 0; col < 8; col++) {
      handleKey (0, row, col);
      handleKey (1, row, col);
    }
  }

  Akela::Keyboard::loop ();
}
