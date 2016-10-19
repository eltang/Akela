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

#define MOD_FN_USER 0x4000

class PrinterFnHandler : public AkelaKeyEventHandler {
 public:
  PrinterFnHandler (AkelaAbstractHID *HID) : AkelaKeyEventHandler (HID) {};

  virtual bool press (uint8_t index, uint16_t key) {
    bool k;

    if (!IS_FN (key))
      return AkelaKeyEventHandler::press (index, key);

    k = !!(key & MOD_FN_USER);
    std::cout << __PRETTY_FUNCTION__ << "(" << (int)index
              << std::hex << key << ") = " << (bool)k << std::endl;

    return false;
  };

  virtual bool release (uint8_t index, uint16_t key) {
    bool k;

    if (!IS_FN (key))
      return AkelaKeyEventHandler::release (index, key);

    k = !!(key & MOD_FN_USER);
    std::cout << __PRETTY_FUNCTION__ << "(" << (int)index
              << std::hex << key << ") = " << (bool)k << std::endl;

    return false;
  };
};
