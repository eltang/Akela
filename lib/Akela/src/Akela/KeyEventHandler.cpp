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

Akela::KeyEventHandler::KeyEventHandler (Akela::AbstractHID *HID,
                                         Akela::KeyMap *keymap) {
  this->HID = HID;
  this->keymap = keymap;
}

Akela::KeyEventHandler::~KeyEventHandler () {
}

void
Akela::KeyEventHandler::press (uint8_t index) {
  uint16_t key = keymap->lookup (index);

  if (IS_FN (key))
    return;

  if (IS_LCTL (key))
    HID->press (KC_LCTL);
  if (IS_LSFT (key))
    HID->press (KC_LSFT);
  if (IS_LALT (key))
    HID->press (KC_LALT);
  if (IS_LGUI (key))
    HID->press (KC_LGUI);
  if (IS_RCTL (key))
    HID->press (KC_RCTL);
  if (IS_RSFT (key))
    HID->press (KC_RSFT);
  if (IS_RALT (key))
    HID->press (KC_RALT);

  HID->press (KEYCODE(key));
}

void
Akela::KeyEventHandler::release (uint8_t index) {
  uint16_t key = keymap->lookup (index);

  if (IS_FN (key))
    return;

  HID->release (KEYCODE (key));

  if (IS_LCTL (key))
    HID->release (KC_LCTL);
 if (IS_LSFT (key))
    HID->release (KC_LSFT);
  if (IS_LALT (key))
    HID->release (KC_LALT);
  if (IS_LGUI (key))
    HID->release (KC_LGUI);
  if (IS_RCTL (key))
    HID->release (KC_RCTL);
  if (IS_RSFT (key))
    HID->release (KC_RSFT);
  if (IS_RALT (key))
    HID->release (KC_RALT);
}

void
Akela::KeyEventHandler::setup () {
  HID->setup ();
}

void
Akela::KeyEventHandler::loop () {
  HID->loop ();
}
