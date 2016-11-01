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

    void
    Layered::register_code (uint16_t keycode) {
      if (LayerComponent::register_code (HID, keymap, keycode))
        return;
      Akela::EventHandler::Base::register_code (keycode);
    }

    void
    Layered::unregister_code (uint16_t keycode) {
      if (LayerComponent::unregister_code (HID, keymap, keycode))
        return;
      Akela::EventHandler::Base::unregister_code (keycode);
    }

    void
    Layered::hold_code (uint16_t keycode) {
      Akela::EventHandler::Base::hold_code (keycode);
    }
  };
};
