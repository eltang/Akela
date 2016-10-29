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

#include <Akela.h>
#include <Akela-TapDance.h>

#include <iostream>
#include <iomanip>

#define KEYBOARD_COLS 3
#define KEYBOARD_ROWS 2

#define TESTCASE(name, layout, scanfunc) do {   \
    std::cout << " " << name << std::endl;      \
    scanner.set_function (scanfunc);            \
    keymap.set_keymap (layout);                 \
    while (!keyboard.quit ())                   \
      keyboard.loop ();                         \
    keyboard.reset ();                          \
  } while (0)

#define TESTCASE_STEPS(name, layout, extra_reset, steps...) do { \
    uint8_t _steps[] = steps;                                    \
    std::cout << " " << name << std::endl;                       \
    scanner.set_function (_scan_spec (_steps));                  \
    keymap.set_keymap (layout);                                  \
    while (!keyboard.quit ())                                    \
      keyboard.loop ();                                          \
    keyboard.reset ();                                           \
    extra_reset;                                                 \
  } while (0)

#include "Virtual/HID.cpp"
#include "Virtual/Scanner.cpp"
#include "Virtual/KeyMap.cpp"
#include "Virtual/EventHandler.cpp"
#include "Virtual/Keyboard.cpp"

#include "util/scanners.cpp"

#include "TestCases/BasicKeyPresses.cpp"
#include "TestCases/Layers.cpp"
#include "TestCases/FnMacros.cpp"

int
main (void) {
  TestBasicKeyPresses ();
  TestLayers ();
  TestFnMacros ();

  return 0;
}
