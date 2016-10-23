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

    Full::Full ()
      : MouseControl (), ConsumerControl (), SystemControl () {
    }

    void
    Full::press (Page page, uint8_t code) {
      Base::press (page, code);
      ConsumerControl::press (page, code);
      SystemControl::press (page, code);
      MouseControl::press (page, (Mouse::Button) code);
    }

    void
    Full::release (Page page, uint8_t code) {
      Base::release (page, code);
      ConsumerControl::release (page, code);
      SystemControl::release (page, code);
      MouseControl::release (page, (Mouse::Button) code);
    }

    void
    Full::setup () {
      Base::setup ();
      ConsumerControl::setup ();
      SystemControl::setup ();
      MouseControl::setup ();
    }

    void
    Full::move (int8_t x, int8_t y) {
      MouseControl::move (x, y);
    }

    void
    Full::warp (uint8_t warp_cmd) {
      MouseControl::warp (warp_cmd);
    }

  }
}
