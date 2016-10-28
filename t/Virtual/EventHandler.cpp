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
  namespace EventHandler {
    class Base : public Akela::EventHandler::Base {
    public:
      Base (Akela::AbstractHID *hid, Akela::KeyMap *keymap)
        : Akela::EventHandler::Base (hid, keymap) {};

      virtual void hold (uint8_t index) {
        uint16_t keycode = keymap->lookup (index);

        if (IS_FN (keycode))
          return;

        ((::Virtual::HID *)HID)->hold (keycode);
      }
    };

    class Layered : public Akela::EventHandler::Layered {
    public:
      Layered (Akela::AbstractHID *hid, Akela::LayeredKeyMap *keymap)
        : Akela::EventHandler::Layered (hid, keymap) {};

      virtual void hold (uint8_t index) {
        uint16_t keycode = keymap->lookup (index);

        if (IS_FN (keycode))
          return;

        ((::Virtual::HID *)HID)->hold (keycode);
      }

      using Akela::EventHandler::Component::hold;
    };

  };
};
