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

#include "Akela.h"

namespace Akela {
  namespace EventHandler {

    bool
    FnMacroComponent::press (Akela::AbstractHID *HID,
                             Akela::KeyMap *keymap,
                             uint8_t,
                             uint16_t keycode) {
      if (keycode < Akela::SYSFN_FNMACRO || keycode > Akela::SYSFN_FNMACRO_MAX)
        return false;

      macroAction (HID, keymap, keycode - Akela::SYSFN_FNMACRO, true);
      return true;
    }

    bool
    FnMacroComponent::release (Akela::AbstractHID *HID,
                               Akela::KeyMap *keymap,
                               uint8_t,
                               uint16_t keycode) {
      if (keycode < Akela::SYSFN_FNMACRO || keycode > Akela::SYSFN_FNMACRO_MAX)
        return false;

      macroAction (HID, keymap, keycode - Akela::SYSFN_FNMACRO, false);
      return true;
    }

    void
    FnMacroComponent::macroAction (Akela::AbstractHID *,
                                   Akela::KeyMap *,
                                   uint8_t,
                                   bool) {
    }
  };
};
