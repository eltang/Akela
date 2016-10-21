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

Akela::Keyboard::Keyboard (Akela::AbstractScanner *scanner,
                           Akela::KeyEventHandler *eventHandler) {
  this->scanner = scanner;
  this->keyEvent = eventHandler;
}

Akela::Keyboard::~Keyboard () {
}

void
Akela::Keyboard::setup () {
  scanner->setup ();
  keyEvent->setup ();
}

void
Akela::Keyboard::loop () {
  keyEvent->loop ();
}

void
Akela::Keyboard::press (uint8_t index) {
  keyEvent->press (index);
}

void
Akela::Keyboard::release (uint8_t index) {
  keyEvent->release (index);
}

void
Akela::Keyboard::hold (uint8_t index) {
  keyEvent->hold (index);
}
