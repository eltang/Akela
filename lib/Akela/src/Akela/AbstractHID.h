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

namespace Akela {
  class AbstractHID {
  public:
    virtual void press (uint8_t code) = 0;
    void register_code (uint8_t code) {
      press (code);
      sendReport ();
    }

    virtual void release (uint8_t code) = 0;
    void unregister_code (uint8_t code) {
      release (code);
      sendReport ();
    }

    virtual void sendReport () = 0;
    virtual bool isModifierActive (uint8_t code) = 0;

    virtual void setup () {};
    virtual void loop () {};
  };
};
