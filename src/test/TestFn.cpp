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

#include "Akela.h"

#include "TestCommon.h"

#include "PrinterKeymap.h"
#include "PrinterHID.h"
#include "TestKeymaps.h"
#include "PressReleaseKb.h"
#include "PrinterFnHandler.h"

// -------------------------------------------------------------------------------------

int
TestFn () {
  PrinterHID hid = PrinterHID ();
  AkelaKeyEventHandler EH = AkelaKeyEventHandler (&hid);
  PrinterKeyMap keymap = PrinterKeyMap ((uint16_t *)fn_keymap);
  PressReleaseKeyboard keyboard = PressReleaseKeyboard (&EH, &keymap);

  std::cout << __func__ << std::endl;

  keyboard.setup ();
  keyboard.test ();

  return 0;
}

int
TestFnHandler () {
  PrinterHID hid = PrinterHID ();
  PrinterFnHandler EH = PrinterFnHandler (&hid);
  PrinterKeyMap keymap = PrinterKeyMap ((uint16_t *)fn_keymap);
  PressReleaseKeyboard keyboard = PressReleaseKeyboard (&EH, &keymap);

  std::cout << __func__ << std::endl;

  keyboard.setup ();
  keyboard.test ();

  return 0;
}
