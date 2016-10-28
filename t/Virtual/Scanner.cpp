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

namespace Virtual {
  typedef uint8_t (*ScannerFunction) (uint16_t cycle, uint8_t state, bool *quit);

  class Scanner : public Akela::AbstractScanner {
  protected:
    uint8_t state = 0;
    ScannerFunction Scan;

  public:
    bool quit = false;
    uint16_t cycle = 0;

    Scanner (ScannerFunction f) {
      Scan = f;
    }

    virtual const void *scan () {
      state = Scan (cycle++, state, &quit);
      return (void *)&state;
    }

    virtual void setup () {}
    void reset () {
      cycle = state = 0;
      quit = false;
    }

    void set_function (ScannerFunction f) {
      Scan = f;
    }
  };
};
