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

#include <Wire.h>

#include "Akela/HW/Model01.h"

KeyboardioScanner M01::Scanner::leftHand(0);
KeyboardioScanner M01::Scanner::rightHand(3);

void
M01::Scanner::enable_power () {
  pinMode (13, OUTPUT);
  digitalWrite (13, HIGH);
}

void
M01::Scanner::setup () {
  enable_power ();

  matrixState.left.all = 0;
  matrixState.right.all = 0;

  Wire.begin ();
  TWBR=12; // This is 400mhz, which is the fastest we can drive the ATTiny
}

const void *
M01::Scanner::scan () {
  matrixState.left = leftHand.getKeyData ();
  matrixState.right = rightHand.getKeyData ();

  return &matrixState;
}
