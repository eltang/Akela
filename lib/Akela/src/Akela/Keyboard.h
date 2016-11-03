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

#pragma once

#include "Akela.h"

namespace Akela {
  class Keyboard {
  protected:
    Akela::EventHandler::Base *keyEvent;
    Akela::AbstractScanner *scanner;

    virtual void press (uint8_t index);
    virtual void release (uint8_t index);
    virtual void hold (uint8_t index);
  public:
    Keyboard (Akela::AbstractScanner *scanner,
              Akela::EventHandler::Base *eventHandler);

    void setup ();
    void loop ();
  };
};
