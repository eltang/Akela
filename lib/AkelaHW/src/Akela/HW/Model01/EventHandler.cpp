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
      M01::HID::Page page;
      uint8_t keycode;

      if (!IS_FNSYS (key))
        return Akela::EventHandler::Layered::press (index);

      switch (key) {
      case M01::SYSFN::CONSUMER ... M01::SYSFN::CONSUMER_MAX:
        page = M01::HID::CONSUMER;
        keycode = key - M01::SYSFN::CONSUMER;
        break;

      case M01::SYSFN::SYSTEM ... M01::SYSFN::SYSTEM_MAX:
        page = M01::HID::SYSTEM;
        keycode = key - M01::SYSFN::SYSTEM;
        break;

      case M01::SYSFN::MOUSE_BUTTON ... M01::SYSFN::MOUSE_BUTTON_MAX:
        page = M01::HID::MOUSE;
        keycode = key - M01::SYSFN::MOUSE_BUTTON;
        break;

      case M01::SYSFN::MOUSE_CONTROL ... M01::SYSFN::MOUSE_CONTROL_MAX:
        keycode = key - M01::SYSFN::MOUSE_CONTROL;

        if (keycode & _MOUSE_WARP) {
          ((::M01::HID::Complete *)HID)->warp
            (
             ((keycode & _MOUSE_WARP_END) ? HID::Mouse::WarpDirection::WARP_END : 0) |
             ((keycode & _MOUSE_DOWN) ? HID::Mouse::WarpDirection::WARP_DOWN : 0) |
             ((keycode & _MOUSE_RIGHT) ? HID::Mouse::WarpDirection::WARP_RIGHT : 0)
             );
        } else {
          mouseMove (keycode);
        }
        return;

      default:
        return Akela::EventHandler::Layered::press (index);
      }

      ((::M01::HID::Base *)HID)->press (page, keycode);
    }

    void
    Complete::hold (uint8_t index) {
      uint16_t key = keymap->lookup (index);

      switch (key) {
      case M01::SYSFN::MOUSE_CONTROL ... M01::SYSFN::MOUSE_CONTROL_MAX:
        mouseMove (key - SYSFN::MOUSE_CONTROL);
        break;
      default:
        return Akela::EventHandler::Layered::hold (index);
      }
    }

    void
    Complete::release (uint8_t index) {
      uint16_t key = keymap->lookup (index);
      M01::HID::Page page;
      uint8_t keycode;

      if (!IS_FNSYS (key))
        return Akela::EventHandler::Layered::release (index);

      switch (key) {
      case M01::SYSFN::CONSUMER ... M01::SYSFN::CONSUMER_MAX:
        page = M01::HID::CONSUMER;
        keycode = key - M01::SYSFN::CONSUMER;
        break;

      case M01::SYSFN::SYSTEM ... M01::SYSFN::SYSTEM_MAX:
        page = M01::HID::SYSTEM;
        keycode = key - M01::SYSFN::SYSTEM;
        break;

      case M01::SYSFN::MOUSE_BUTTON ... M01::SYSFN::MOUSE_BUTTON_MAX:
        page = M01::HID::MOUSE;
        keycode = key - M01::SYSFN::MOUSE_BUTTON;
        break;

      case M01::SYSFN::MOUSE_CONTROL ... M01::SYSFN::MOUSE_CONTROL_MAX:
        return;

      default:
        return Akela::EventHandler::Layered::release (index);
      }

      ((::M01::HID::Base *)HID)->release (page, keycode);
    }

    void
    Complete::setup () {
      Akela::EventHandler::Layered::setup ();
      LedControl::setup ();
    }

    void
    Complete::mouseMove (uint8_t key) {
      ::M01::HID::Complete *mc = (::M01::HID::Complete *) HID;

      if (key & _MOUSE_UP)
        mc->move (0, -1);
      if (key & _MOUSE_LEFT)
        mc->move (-1, 0);
      if (key & _MOUSE_DOWN)
        mc->move (0, 1);
      if (key & _MOUSE_RIGHT)
        mc->move (1, 0);
    }
  };
};
