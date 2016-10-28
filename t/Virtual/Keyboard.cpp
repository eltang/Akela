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

#include <bitset>

namespace Virtual {
  class Keyboard : public Akela::Keyboard {
  protected:
    uint8_t prevState = 0, currState = 0;

    void handleKey (uint8_t row, uint8_t col) {
      uint8_t keynum = (row * KEYBOARD_COLS) + col;

      bool pp = !!(prevState & (1 << keynum));
      bool cp = !!(currState & (1 << keynum));

      if (pp == cp && cp)
        return hold (keynum);

      if (cp)
        return press (keynum);

      if (pp)
        return release (keynum);
    }

  public:
    Keyboard (Akela::AbstractScanner *scanner, Akela::EventHandler::Base *eh)
      : Akela::Keyboard (scanner, eh) {
    };

    virtual void loop () {
      prevState = currState;
      currState = *((uint8_t *)scanner->scan ());

      std::cout << "    " << __PRETTY_FUNCTION__ << "(" << (int)((Virtual::Scanner *)scanner)->cycle << ")"
                << " = " << std::bitset<8>(currState) << std::endl;

      for (uint8_t row = 0; row < KEYBOARD_ROWS; row++) {
        for (uint8_t col = 0; col < KEYBOARD_COLS; col++) {
          handleKey (row, col);
        }
      }

      Akela::Keyboard::loop ();
    }

    bool quit () {
      return ((Virtual::Scanner *)scanner)->quit;
    }

    void reset () {
      ((Virtual::Scanner *)scanner)->reset ();
      currState = prevState = 0;
    }
  };
};
