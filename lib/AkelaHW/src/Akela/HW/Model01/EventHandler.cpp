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

    Complete::Complete (Akela::AbstractHID *HID,
                        Akela::LayeredKeyMap *keymap,
                        M01::Scanner *scanner)
      : Akela::EventHandler::Layered (HID, keymap),
        LedControl (scanner) {
    }

    void
    Complete::press (uint8_t index) {
      uint16_t key = keymap->lookup (index);

      if (!IS_FNSYS (key))
        return Akela::EventHandler::Layered::press (index);

      if (ExtraKeysComponent::press (HID, keymap, index, key))
        return;
      if (MouseComponent::press (HID, keymap, index, key))
        return;

      return Akela::EventHandler::Layered::press (index);
    }

    void
    Complete::hold (uint8_t index) {
      uint16_t key = keymap->lookup (index);

      if (MouseComponent::hold (HID, keymap, index, key))
        return;

      return Akela::EventHandler::Layered::hold (index);
    }

    void
    Complete::release (uint8_t index) {
      uint16_t key = keymap->lookup (index);

      if (!IS_FNSYS (key))
        return Akela::EventHandler::Layered::release (index);

      if (ExtraKeysComponent::release (HID, keymap, index, key))
        return;

      if (MouseComponent::release (HID, keymap, index, key))
        return;

      return Akela::EventHandler::Layered::release (index);
    }

    void
    Complete::setup () {
      Akela::EventHandler::Layered::setup ();
      LedControl::setup ();
    }
  };
};
