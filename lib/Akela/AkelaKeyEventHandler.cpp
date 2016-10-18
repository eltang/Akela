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

#include "Akela.h"

AkelaKeyEventHandler::AkelaKeyEventHandler (AkelaAbstractHID *HID) {
  this->HID = HID;
}

AkelaKeyEventHandler::~AkelaKeyEventHandler () {
}

bool
AkelaKeyEventHandler::press (uint8_t, uint16_t key) {
  uint8_t mods = key >> 8;

  if (mods & MOD_FN)
    return false;

  if (mods & MOD_LCTL)
    HID->press (KC_LCTL);
  if (mods & MOD_LSFT)
    HID->press (KC_LSFT);
  if (mods & MOD_LALT)
    HID->press (KC_LALT);
  if (mods & MOD_LGUI)
    HID->press (KC_LGUI);
  if (mods & MOD_RCTL)
    HID->press (KC_RCTL);
  if (mods & MOD_RSFT)
    HID->press (KC_RSFT);
  if (mods & MOD_RALT)
    HID->press (KC_RALT);

  HID->press (key & ~0xff00);

  return true;
}

bool
AkelaKeyEventHandler::release (uint8_t, uint16_t key) {
  uint8_t mods = key >> 8;

  if (mods & MOD_FN)
    return false;

  HID->release (key & ~0xff00);

  if (mods & MOD_LCTL)
    HID->release (KC_LCTL);
  if (mods & MOD_LSFT)
    HID->release (KC_LSFT);
  if (mods & MOD_LALT)
    HID->release (KC_LALT);
  if (mods & MOD_LGUI)
    HID->release (KC_LGUI);
  if (mods & MOD_RCTL)
    HID->release (KC_RCTL);
  if (mods & MOD_RSFT)
    HID->release (KC_RSFT);
  if (mods & MOD_RALT)
    HID->release (KC_RALT);

  return true;
}
