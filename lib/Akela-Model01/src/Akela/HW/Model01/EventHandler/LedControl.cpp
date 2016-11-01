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

#include "Akela/HW/Model01.h"

#include <avr/pgmspace.h>

static const uint8_t _LedControlMap[64] PROGMEM = {
  3,4,11,12,19,20,26,27,     36,37,43,44,51,52,59,60,
  2,5,10,13,18,21,31,28,     35,32,42,45,50,53,58,61,
  1,6, 9,14,17,22,25,29,     34,38,41,46,49,54,57,62,
  0,7, 8,15,16,23,24,30,     33,39,40,47,48,55,56,63,
};

static const uint8_t _KeyIndexMap[] PROGMEM = {
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

    LedControl::LedControl (Scanner *scanner) {
      this->scanner = scanner;
    }

    void
    LedControl::setup () {
      enable_high_power ();
      boot_animation ();
    }

    void
    LedControl::enable_high_power () {
      pinMode(7, OUTPUT);
      digitalWrite(7, LOW);
    }

    void
    LedControl::set_color_at_led (uint8_t i, cRGB crgb) {
      if (i < 32) {
        scanner->leftHand.ledData.leds[i] = crgb;
      } else if (i < 64) {
        scanner->rightHand.ledData.leds[i - 32] = crgb;
      }
    }

    void
    LedControl::set_color (cRGB color) {
      for (uint8_t i = 0; i < sizeof (_LedControlMap); i++) {
        set_color (i, color);
      }
    }

    void
    LedControl::set_color (Hand hand, uint8_t row, uint8_t col, cRGB crgb) {
      uint8_t keyIndex;

      keyIndex = row * 7 + col;
      if (hand == RIGHT)
        keyIndex += 6 * 8;

      uint8_t mapPos = pgm_read_byte (_KeyIndexMap + keyIndex);
      if (mapPos == 99)
        return;

      uint8_t pos = pgm_read_byte_near (_LedControlMap + mapPos);
      set_color (pos, crgb);
    }

    void
    LedControl::set_color (uint8_t i, cRGB crgb) {
      uint8_t pos = pgm_read_byte_near (_LedControlMap + i);

      set_color_at_led (pos, crgb);
    }

    void
    LedControl::boot_animation () {
      // keyboardio 0.9
      static uint8_t idxs[] = {49, 13, 42, 23, 53, 6, 18, 14, 50, 53,
                               34, 59, 55, 52};

      set_color ({0, 0, 0});

      for (uint8_t i = 0; i < sizeof (idxs); i++) {
        set_color_at_led (i, {255, 0, 0});
        sync ();
        delay (250);
        set_color_at_led (i, {0, 0, 0});
        sync ();
        delay (10);
      }
    }

    void
    LedControl::sync() {
      scanner->leftHand.sendLEDData();
      scanner->rightHand.sendLEDData();

      scanner->leftHand.sendLEDData();
      scanner->rightHand.sendLEDData();

      scanner->leftHand.sendLEDData();
      scanner->rightHand.sendLEDData();

      scanner->leftHand.sendLEDData();
      scanner->rightHand.sendLEDData();
    }
  };
};
