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

void
M01::EventHandler::press (uint8_t index) {
  uint16_t key = keymap->lookup (index);
  HID::Page page;

  if (!CHECK_USER (key, CC) && !CHECK_USER (key, SC) &&
      !CHECK_USER (key, MB) && !CHECK_USER (key, MC))
    return Akela::LayerEventHandler::press (index);

  if (CHECK_USER (key, CC))
    page = HID::CONSUMER;
  else if (CHECK_USER (key, SC))
    page = HID::SYSTEM;
  else if (CHECK_USER (key, MB))
    page = HID::MOUSE;
  else {
    if (key & _MOUSE_WARP) {
      uint8_t kc = KEYCODE (key);
      ((::M01::HID *)HID)->warp
        (
         ((kc & _MOUSE_WARP_END) ? MouseControl::WarpDirection::WARP_END : 0) |
         ((kc & _MOUSE_DOWN) ? MouseControl::WarpDirection::WARP_DOWN : 0) |
         ((kc & _MOUSE_RIGHT) ? MouseControl::WarpDirection::WARP_RIGHT : 0)
         );
    } else {
      mouseMove (key);
    }
    return;
  }

  ((::M01::HID *)HID)->press (page, KEYCODE (key));
}

void
M01::EventHandler::hold (uint8_t index) {
  uint16_t key = keymap->lookup (index);

  if (!CHECK_USER (key, MC))
    return;

  if (key & _MOUSE_WARP)
    return;

  mouseMove (key);
}

void
M01::EventHandler::release (uint8_t index) {
  uint16_t key = keymap->lookup (index);
  HID::Page page;

  if (!CHECK_USER (key, CC) && !CHECK_USER (key, SC) &&
      !CHECK_USER (key, MB) && !CHECK_USER (key, MC))
    return Akela::LayerEventHandler::release (index);

  if (CHECK_USER (key, CC))
    page = HID::CONSUMER;
  else if (CHECK_USER (key, SC))
    page = HID::SYSTEM;
  else if (CHECK_USER (key, MB))
    page = HID::MOUSE;
  else {
    return;
  }

  ((::M01::HID *)HID)->release (page, KEYCODE (key));
}

void
M01::EventHandler::setup () {
  Akela::LayerEventHandler::setup ();
  M01::LedControl::setup ();
}

void
M01::EventHandler::mouseMove (uint16_t key) {
  ::M01::HID *mc = (::M01::HID *) HID;

  if (key & _MOUSE_UP)
    mc->move (0, -1);
  if (key & _MOUSE_LEFT)
    mc->move (-1, 0);
  if (key & _MOUSE_DOWN)
    mc->move (0, 1);
  if (key & _MOUSE_RIGHT)
    mc->move (1, 0);
}
