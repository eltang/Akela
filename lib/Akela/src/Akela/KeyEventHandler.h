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

#pragma once

#include "Akela.h"

class AkelaKeyEventHandler {
 protected:
  AkelaAbstractHID *HID;
  AkelaKeyMap *keymap;

 public:
  AkelaKeyEventHandler (AkelaAbstractHID *HID, AkelaKeyMap *keymap);

  virtual bool press (uint8_t index);
  virtual bool release (uint8_t index);

  virtual void setup ();
  virtual void loop ();
};
