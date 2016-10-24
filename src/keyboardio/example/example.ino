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

#include <Akela.h>
#include <AkelaHW.h>

#include "layout.h"

namespace Example {
  class EventHandler: public M01::EventHandler::Full {
  public:
    EventHandler (M01::HID::Full *hid, Akela::LayeredKeyMap *keymap,
                  M01::Scanner *scanner)
      : M01::EventHandler::Full (hid, keymap, scanner) {};

    virtual void press (uint8_t index);
    virtual void release (uint8_t index);
  private:
    using M01::EventHandler::MouseComponent::press;
    using M01::EventHandler::MouseComponent::release;
  };

  void
  EventHandler::press (uint8_t index) {
    cRGB color = {0, 0, 0};

    // When a key is pressed, highlight it for the duration
    color = {0x80, 0x80, 0x80};

    M01::EventHandler::Full::set_color (index, color);
    M01::EventHandler::Full::press (index);
  }

  void
  EventHandler::release (uint8_t index) {
    cRGB color = {0, 0, 0};

    M01::EventHandler::Full::release (index);

    M01::EventHandler::Full::set_color (index, color);
  }
};

static M01::HID::Full          hid;
static Akela::LayeredKeyMap    keyMap ((uint16_t **)keymap, 64);
static M01::Scanner            scanner;
static Example::EventHandler   eventHandler (&hid, &keyMap, &scanner);
static M01::Model01            keyboard (&scanner, &eventHandler);

void
setup () {
  keyboard.setup ();
}

void
loop () {
  keyboard.loop ();
}
