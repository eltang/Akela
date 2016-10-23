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
    Base::press (uint8_t index) {
      uint16_t key = keymap->lookup (index);

      if (ExtraKeysComponent::press (HID, keymap, index, key))
        return;

      return Akela::EventHandler::Layered::press (index);
    }

    void
    Base::hold (uint8_t index) {
      return Akela::EventHandler::Layered::hold (index);
    }

    void
    Base::release (uint8_t index) {
      uint16_t key = keymap->lookup (index);

      if (ExtraKeysComponent::release (HID, keymap, index, key))
        return;

      return Akela::EventHandler::Layered::release (index);
    }

    // -----------

    void
    Full::press (uint8_t index) {
      uint16_t key = keymap->lookup (index);

      if (MouseComponent::press (HID, keymap, index, key))
        return;

      return Base::press (index);
    }

    void
    Full::hold (uint8_t index) {
      uint16_t key = keymap->lookup (index);

      if (MouseComponent::hold (HID, keymap, index, key))
        return;

      return Base::hold (index);
    }

    void
    Full::release (uint8_t index) {
      uint16_t key = keymap->lookup (index);

      if (MouseComponent::release (HID, keymap, index, key))
        return;

      return Base::release (index);
    }

    void
    Full::setup () {
      Base::setup ();
      LedControl::setup ();
    }
  };
};
