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

#include "Akela/HW/Model01.h"

M01EventHandler::M01EventHandler (AkelaAbstractHID *HID,
                                  AkelaLayeredKeyMap *keymap)
  : AkelaLayerEventHandler (HID, keymap) {
}

bool
M01EventHandler::press (uint8_t index) {
  uint16_t key = keymap->lookup (index);
  M01HID::Page page;

  if (!CHECK_USER (key, CC) && !CHECK_USER (key, SC))
    return AkelaLayerEventHandler::press (index);

  if (CHECK_USER (key, CC))
    page = M01HID::CONSUMER;
  else
    page = M01HID::SYSTEM;

  ((M01HID *)HID)->press (page, KEYCODE (key));
  return true;
}

bool
M01EventHandler::release (uint8_t index) {
  uint16_t key = keymap->lookup (index);
  M01HID::Page page;

  if (!CHECK_USER (key, CC))
    return AkelaLayerEventHandler::release (index);

  if (CHECK_USER (key, CC))
    page = M01HID::CONSUMER;
  else
    page = M01HID::SYSTEM;

  ((M01HID *)HID)->release (page, KEYCODE (key));
  return true;
}
