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
  namespace EventHandler {
    class LedControl {
    protected:
      Scanner *scanner;

      void enable_high_power ();
      void boot_animation ();

      const uint8_t map [64] = {
        3,4,11,12,19,20,26,27,     36,37,43,44,51,52,59,60,
        2,5,10,13,18,21,31,28,     35,32,42,45,50,53,58,61,
        1,6, 9,14,17,22,25,29,     34,38,41,46,49,54,57,62,
        0,7, 8,15,16,23,24,30,     33,39,40,47,48,55,56,63,
      };


    public:
      LedControl (Scanner *scanner);

      virtual void setup ();

      void set_color_at_led (uint8_t i, cRGB crgb);
      void set_color (cRGB crgb);
      void set_color (uint8_t row, uint8_t col, cRGB crgb);
      void set_color (uint8_t i, cRGB crgb);
      void sync ();
    };
  };
};
