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

#define KEYMAP(                                               \
               r0c0, r0c1, r0c2, r0c3, r0c4, r0c5, r0c6,      \
               r1c0, r1c1, r1c2, r1c3, r1c4, r1c5, r1c6,      \
               r2c0, r2c1, r2c2, r2c3, r2c4, r2c5, /* r1c6 */ \
               r3c0, r3c1, r3c2, r3c3, r3c4, r3c5, r2c6,      \
               r0c7, r1c7, r2c7, r3c7,                        \
               r3c6,                                          \
                                                              \
               r0c9, r0ca, r0cb, r0cc, r0cd, r0ce, r0cf,      \
               r1c9, r1ca, r1cb, r1cc, r1cd, r1ce, r1cf,      \
                     r2ca, r2cb, r2cc, r2cd, r2ce, r2cf,      \
               r2c9, r3ca, r3cb, r3cc, r3cd, r3ce, r3cf,      \
               r3c8, r2c8, r1c8, r0c8,                        \
               r3c9)                                          \
  {                                                           \
    r0c0, r0c1, r0c2, r0c3, r0c4, r0c5, r0c6, r0c7, r0c8, r0c9, r0ca, r0cb, r0cc, r0cd, r0ce, r0cf, \
    r1c0, r1c1, r1c2, r1c3, r1c4, r1c5, r1c6, r1c7, r1c8, r1c9, r1ca, r1cb, r1cc, r1cd, r1ce, r1cf, \
    r2c0, r2c1, r2c2, r2c3, r2c4, r2c5, r2c6, r2c7, r2c8, r2c9, r2ca, r2cb, r2cc, r2cd, r2ce, r2cf, \
    r3c0, r3c1, r3c2, r3c3, r3c4, r3c5, r3c6, r3c7, r3c8, r3c9, r3ca, r3cb, r3cc, r3cd, r3ce, r3cf, \
  }
