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

/*
 * Portions of this file were adapted from KeyboardioFirmware[0], which is
 * Copyright (C) 2013-2016 Keyboardio, inc, and under the GNU General Public
 * License, version 2 or later.
 *
 * [0]: https://github.com/keyboardio/KeyboardioFirmware
 */

#pragma once

#include "Akela.h"

namespace M01 {
  class MouseControl {
  public:
    enum Button {
      MB_LEFT  = 0x01,
      MB_MID   = 0x02,
      MB_RIGHT = 0x04
    };
    enum WarpDirection {
      WARP_END   = 0x01,
      WARP_UP    = 0x02,
      WARP_DOWN  = 0x04,
      WARP_LEFT  = 0x08,
      WARP_RIGHT = 0x10
    };

    MouseControl ();

    void setup ();

    void press (Button button);
    void release (Button button);

    void move (int8_t x, int8_t y);
    void warp (uint8_t warp_cmd);

  private:
    double mouseActiveForCycles = 0;
    float carriedOverX = 0;
    float carriedOverY = 0;

    uint16_t next_width = 0;
    uint16_t next_height = 0;
    uint16_t section_top = 0;
    uint16_t section_left = 0;
    boolean is_warping = false;

    double acceleration (double cycles);
    void begin_warping ();
    void end_warping ();
    void warp_jump (long left, long top, long height, long width);
  };
};
