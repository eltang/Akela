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

M01::LedControl::LedControl (Scanner *scanner) {
  this->scanner = scanner;
}

void
M01::LedControl::setup () {
  enable_high_power ();
  boot_animation ();
}

void
M01::LedControl::enable_high_power () {
  pinMode(7, OUTPUT);
  digitalWrite(7, LOW);
}

void
M01::LedControl::set_color(uint8_t i, cRGB crgb) {
  if(i<32) {
    scanner->leftHand.ledData.leds[i] = crgb;
  } else if (i<64) {
    scanner->rightHand.ledData.leds[i - 32] = crgb;
  }}


void
M01::LedControl::set_color (cRGB color) {
  for (uint8_t i = 0; i < LED_COUNT; i++) {
    set_color (i, color);
  }
}

void
M01::LedControl::boot_animation () {
  static uint8_t idxs[] = {};

  set_color ({0, 0, 0});

  for (uint8_t i = 0; i < sizeof (idxs); i++) {
    set_color (i, {255, 0, 0});
    sync ();
    delay (250);
    set_color (i, {0, 0, 0});
    sync ();
    delay (10);
  }
}

void
M01::LedControl::sync() {
  scanner->leftHand.sendLEDData();
  scanner->rightHand.sendLEDData();

  scanner->leftHand.sendLEDData();
  scanner->rightHand.sendLEDData();

  scanner->leftHand.sendLEDData();
  scanner->rightHand.sendLEDData();

  scanner->leftHand.sendLEDData();
  scanner->rightHand.sendLEDData();
}
