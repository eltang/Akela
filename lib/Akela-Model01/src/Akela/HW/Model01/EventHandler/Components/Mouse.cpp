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

    bool
    MouseComponent::register_code (Akela::AbstractHID *HID,
                                   Akela::KeyMap *,
                                   uint16_t keycode) {
      switch (keycode) {
      case M01::SYSFN::MOUSE_BUTTON ... M01::SYSFN::MOUSE_BUTTON_MAX:
        ((::M01::HID::Base *)HID)->press (M01::HID::MOUSE, keycode - M01::SYSFN::MOUSE_BUTTON);
        return true;

      case M01::SYSFN::MOUSE_CONTROL ... M01::SYSFN::MOUSE_CONTROL_MAX:
        uint8_t key = keycode - M01::SYSFN::MOUSE_CONTROL;

        if (key & _MOUSE_WARP) {
          ((::M01::HID::Base *)HID)->warp
            (
             ((key & _MOUSE_WARP_END) ? HID::Mouse::WarpDirection::WARP_END : 0) |
             ((key & _MOUSE_DOWN) ? HID::Mouse::WarpDirection::WARP_DOWN : 0) |
             ((key & _MOUSE_RIGHT) ? HID::Mouse::WarpDirection::WARP_RIGHT : 0)
             );
        } else {
          move ((M01::HID::Base *)HID, key);
        }
        return true;
      }

      return false;
    }

    bool
    MouseComponent::unregister_code (Akela::AbstractHID *HID,
                                     Akela::KeyMap *,
                                     uint16_t keycode) {
      switch (keycode) {
      case M01::SYSFN::MOUSE_BUTTON ... M01::SYSFN::MOUSE_BUTTON_MAX:
        ((::M01::HID::Base *)HID)->release (M01::HID::MOUSE, keycode - M01::SYSFN::MOUSE_BUTTON);
        return true;

      case M01::SYSFN::MOUSE_CONTROL ... M01::SYSFN::MOUSE_CONTROL_MAX:
        return true;
      }

      return false;
    }

    bool
    MouseComponent::hold_code (Akela::AbstractHID *HID,
                               Akela::KeyMap *,
                               uint16_t keycode) {
      switch (keycode) {
      case M01::SYSFN::MOUSE_CONTROL ... M01::SYSFN::MOUSE_CONTROL_MAX:
        move ((M01::HID::Base *)HID, keycode - SYSFN::MOUSE_CONTROL);
        return true;
      }

      return false;
    }

    void
    MouseComponent::move (M01::HID::Base *HID, uint8_t key) {
      if (key & _MOUSE_UP)
        HID->move (0, -1);
      if (key & _MOUSE_LEFT)
        HID->move (-1, 0);
      if (key & _MOUSE_DOWN)
        HID->move (0, 1);
      if (key & _MOUSE_RIGHT)
        HID->move (1, 0);
    }

  };
};
