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

AkelaKeyboard::AkelaKeyboard (AkelaAbstractScanner *scanner,
                              AkelaKeyEventHandler *eventHandler) {
  this->scanner = scanner;
  this->keyEvent = eventHandler;
}

AkelaKeyboard::~AkelaKeyboard () {
}

void
AkelaKeyboard::setup () {
  scanner->setup ();
  keyEvent->setup ();
}

void
AkelaKeyboard::loop () {
  keyEvent->loop ();
}

bool
AkelaKeyboard::press (uint8_t index) {
  return keyEvent->press (index);
}

bool
AkelaKeyboard::release (uint8_t index) {
  return keyEvent->release (index);
}
