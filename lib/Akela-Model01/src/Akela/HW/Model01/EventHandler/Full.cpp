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

#include "Akela/HW/Model01.h"

namespace M01 {
  namespace EventHandler {

    void
    Full::register_code (uint16_t keycode) {
      if (MouseComponent::register_code (HID, keymap, keycode))
        return;

      return Base::register_code (keycode);
    }

    void
    Full::hold_code (uint16_t keycode) {
      if (MouseComponent::hold_code (HID, keymap, keycode))
        return;

      return Base::hold_code (keycode);
    }

    void
    Full::unregister_code (uint16_t keycode) {
      if (MouseComponent::unregister_code (HID, keymap, keycode))
        return;

      return Base::unregister_code (keycode);
    }

    void
    Full::setup () {
      Base::setup ();
      LedControl::setup ();
    }

    void
    Full::setColor (Base::Hand hand, uint8_t row, uint8_t col, cRGB crgb) {
      uint8_t mapPos = keyToMatrix (hand, row, col);
      if (mapPos == 99)
        return;

      LedControl::setColor (mapPos, crgb);
    }

  };
};
