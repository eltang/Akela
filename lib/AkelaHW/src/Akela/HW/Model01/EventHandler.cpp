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

M01::EventHandler::EventHandler (Akela::AbstractHID *HID,
                                 Akela::LayeredKeyMap *keymap,
                                 M01::Scanner *scanner)
  : Akela::LayerEventHandler (HID, keymap), M01::LedControl (scanner) {
}

bool
M01::EventHandler::press (uint8_t index) {
  uint16_t key = keymap->lookup (index);
  HID::Page page;

  if (!CHECK_USER (key, CC) && !CHECK_USER (key, SC))
    return Akela::LayerEventHandler::press (index);

  if (CHECK_USER (key, CC))
    page = HID::CONSUMER;
  else
    page = HID::SYSTEM;

  ((::M01::HID *)HID)->press (page, KEYCODE (key));
  return true;
}

bool
M01::EventHandler::release (uint8_t index) {
  uint16_t key = keymap->lookup (index);
  HID::Page page;

  if (!CHECK_USER (key, CC) && !CHECK_USER (key, SC))
    return Akela::LayerEventHandler::release (index);

  if (CHECK_USER (key, CC))
    page = HID::CONSUMER;
  else
    page = HID::SYSTEM;

  ((::M01::HID *)HID)->release (page, KEYCODE (key));
  return true;
}

void
M01::EventHandler::setup () {
  Akela::LayerEventHandler::setup ();
  M01::LedControl::setup ();
}
