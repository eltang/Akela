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
  uint8_t keycode;

  if (!IS_FNSYS (key))
    return Akela::LayerEventHandler::press (index);

  switch (key) {
  case M01::SYSFN_CONSUMER ... M01::SYSFN_CONSUMER_MAX:
    page = HID::CONSUMER;
    keycode = key - M01::SYSFN_CONSUMER;
    break;

  case M01::SYSFN_SYSTEM ... M01::SYSFN_SYSTEM_MAX:
    page = HID::SYSTEM;
    keycode = key - M01::SYSFN_SYSTEM;
    break;

  case M01::SYSFN_MOUSE_BUTTON ... M01::SYSFN_MOUSE_BUTTON_MAX:
    page = HID::MOUSE;
    keycode = key - M01::SYSFN_MOUSE_BUTTON;
    break;

  case M01::SYSFN_MOUSE_CONTROL ... M01::SYSFN_MOUSE_CONTROL_MAX:
    keycode = key - M01::SYSFN_MOUSE_CONTROL;

    if (keycode & _MOUSE_WARP) {
      ((::M01::HID::Complete *)HID)->warp
        (
         ((keycode & _MOUSE_WARP_END) ? HID::Mouse::WarpDirection::WARP_END : 0) |
         ((keycode & _MOUSE_DOWN) ? HID::Mouse::WarpDirection::WARP_DOWN : 0) |
         ((keycode & _MOUSE_RIGHT) ? HID::Mouse::WarpDirection::WARP_RIGHT : 0)
         );
    } else {
      mouseMove (keycode);
    }
    return;

  default:
    return Akela::LayerEventHandler::press (index);
  }

  ((::M01::HID::Base *)HID)->press (page, keycode);
}

void
M01::EventHandler::hold (uint8_t index) {
  uint16_t key = keymap->lookup (index);

  switch (key) {
  case SYSFN_MOUSE_CONTROL ... SYSFN_MOUSE_CONTROL_MAX:
    mouseMove (key - SYSFN_MOUSE_CONTROL);
    break;
  default:
    return Akela::LayerEventHandler::hold (index);
  }
}

void
M01::EventHandler::release (uint8_t index) {
  uint16_t key = keymap->lookup (index);
  HID::Page page;
  uint8_t keycode;

  if (!IS_FNSYS (key))
    return Akela::LayerEventHandler::press (index);

  switch (key) {
  case M01::SYSFN_CONSUMER ... M01::SYSFN_CONSUMER_MAX:
    page = HID::CONSUMER;
    keycode = key - M01::SYSFN_CONSUMER;
    break;

  case M01::SYSFN_SYSTEM ... M01::SYSFN_SYSTEM_MAX:
    page = HID::SYSTEM;
    keycode = key - M01::SYSFN_SYSTEM;
    break;

  case M01::SYSFN_MOUSE_BUTTON ... M01::SYSFN_MOUSE_BUTTON_MAX:
    page = HID::MOUSE;
    keycode = key - M01::SYSFN_MOUSE_BUTTON;
    break;

  case M01::SYSFN_MOUSE_CONTROL ... M01::SYSFN_MOUSE_CONTROL_MAX:
   return;

  default:
    return Akela::LayerEventHandler::press (index);
  }

  ((::M01::HID::Base *)HID)->release (page, keycode);
}

void
M01::EventHandler::setup () {
  Akela::LayerEventHandler::setup ();
  M01::LedControl::setup ();
}

void
M01::EventHandler::mouseMove (uint8_t key) {
  ::M01::HID::Complete *mc = (::M01::HID::Complete *) HID;

  if (key & _MOUSE_UP)
    mc->move (0, -1);
  if (key & _MOUSE_LEFT)
    mc->move (-1, 0);
  if (key & _MOUSE_DOWN)
    mc->move (0, 1);
  if (key & _MOUSE_RIGHT)
    mc->move (1, 0);
}
