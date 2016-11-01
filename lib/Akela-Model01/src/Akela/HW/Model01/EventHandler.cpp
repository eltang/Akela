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

static const uint8_t _KeyToMatrixMap[] PROGMEM = {
  0,  1,  2,  3,  4,  5,  6,
  16, 17, 18, 19, 20, 21, 99,
  32, 33, 34, 35, 36, 37, 38,
  48, 49, 50, 51, 52, 53, 22,
  07, 23, 39, 55, 99, 99, 99,
  54, 99, 99, 99, 99, 99, 99,

  9, 10, 11, 12, 13, 14, 15,
  26, 27, 28, 29, 30, 31, 99,
  41, 42, 43, 44, 45, 46, 47,
  57, 58, 59, 60, 61, 62, 63,
  56, 40, 24,  8, 99, 99, 99,
  25, 99, 99, 99, 99, 99, 99,
};

namespace M01 {
  namespace EventHandler {

    void
    Base::register_code (uint16_t keycode) {
      if (Akela::EventHandler::FnMacroComponent::register_code (HID, keymap, keycode))
        return;
      if (ExtraKeysComponent::register_code (HID, keymap, keycode))
        return;

      return Akela::EventHandler::Layered::register_code (keycode);
    }

    void
    Base::unregister_code (uint16_t keycode) {
      if (Akela::EventHandler::FnMacroComponent::unregister_code (HID, keymap, keycode))
        return;
      if (ExtraKeysComponent::unregister_code (HID, keymap, keycode))
        return;

      return Akela::EventHandler::Layered::unregister_code (keycode);
    }

    void
    Base::hold_code (uint16_t keycode) {
      return Akela::EventHandler::Layered::hold_code (keycode);
    }

    uint8_t
    Base::keyToMatrix (Hand hand, uint8_t row, uint8_t col) {
      uint8_t keyIndex;

      keyIndex = row * 7 + col;
      if (hand == RIGHT)
        keyIndex += 6 * 8;

      return pgm_read_byte (_KeyToMatrixMap + keyIndex);
    }

    // -----------

    void
    Full::register_code (uint16_t keycode) {
      if (MouseComponent::register_code (HID, keymap, keycode))
        return;

      return Base::register_code (keycode);
    }

    void
    Full::hold_code (uint16_t keycode) {
      if (MouseComponent::hold_code (HID, keymap, keycode))
        return;

      return Base::hold_code (keycode);
    }

    void
    Full::unregister_code (uint16_t keycode) {
      if (MouseComponent::unregister_code (HID, keymap, keycode))
        return;

      return Base::unregister_code (keycode);
    }

    void
    Full::setup () {
      Base::setup ();
      LedControl::setup ();
    }

    void
    Full::setColor (Base::Hand hand, uint8_t row, uint8_t col, cRGB crgb) {
      uint8_t mapPos = keyToMatrix (hand, row, col);
      if (mapPos == 99)
        return;

      LedControl::setColor (mapPos, crgb);
    }

  };
};
