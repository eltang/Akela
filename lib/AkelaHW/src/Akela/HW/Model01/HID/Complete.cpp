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

#include "Akela/HW/Model01.h"

namespace M01 {
  namespace HID {

    Complete::Complete ()
      : MouseControl (), ConsumerControl (), SystemControl () {
    }

    void
    Complete::press (Page page, uint8_t code) {
      switch (page) {
      case KEYBOARD:
        Base::press (page, code);
        break;
      case CONSUMER:
        ConsumerControl::press (page, code);
        break;
      case SYSTEM:
        SystemControl::press (page, code);
        break;
      case MOUSE:
        MouseControl::press (page, (Mouse::Button) code);
        break;
      }
    }

    void
    Complete::release (Page page, uint8_t code) {
      switch (page) {
      case KEYBOARD:
        Base::release (page, code);
        break;
      case CONSUMER:
        ConsumerControl::release (page, code);
        break;
      case SYSTEM:
        SystemControl::release (page, code);
        break;
      case MOUSE:
        MouseControl::release (page, (Mouse::Button) code);
        break;
      }
    }

    void
    Complete::setup () {
      Base::setup ();
      ConsumerControl::setup ();
      SystemControl::setup ();
      MouseControl::setup ();
    }

    void
    Complete::move (int8_t x, int8_t y) {
      MouseControl::move (x, y);
    }

    void
    Complete::warp (uint8_t warp_cmd) {
      MouseControl::warp (warp_cmd);
    }

  }
}
