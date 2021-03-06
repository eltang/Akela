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

#pragma once

#include "Akela.h"

namespace M01 {
  namespace HID {
    class Full : public Base,
                 public MouseControl,
                 public ConsumerControl,
                 public SystemControl {
    public:
      Full ()
        : MouseControl (), ConsumerControl (), SystemControl () {};

      using Base::press;
      using MouseControl::press;
      using ConsumerControl::press;
      using SystemControl::press;
      virtual void press (Page page, uint8_t code);

      using Base::release;
      using MouseControl::release;
      using ConsumerControl::release;
      using SystemControl::release;
      virtual void release (Page page, uint8_t code);

      virtual void move (int8_t x, int8_t y);
      virtual void warp (uint8_t warp_cmd);

      virtual void setup ();
    };
  };
};
