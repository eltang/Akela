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
#include <Akela-Model01.h>
#include <Akela-TapDance.h>

#include "layout.h"

class TapDanceEventHandler : public Akela::EventHandler::Base,
                             public Akela::TapDance::Component::OneShotMod {
public:
  TapDanceEventHandler (Akela::AbstractHID *hid, Akela::KeyMap *keymap)
    : Akela::EventHandler::Base (hid, keymap) {};

  using Akela::TapDance::Component::OneShotMod::press;
  virtual void press (uint8_t index);

  using Akela::TapDance::Component::OneShotMod::release;
  virtual void release (uint8_t index);

  virtual void loop ();

private:
  using Akela::TapDance::Component::OneShotMod::loop;
};

void
TapDanceEventHandler::press (uint8_t index) {
  uint16_t keycode = keymap->lookup (index);

  if (Akela::TapDance::Component::OneShotMod::press (HID, keymap, index, keycode))
    return;

  Akela::EventHandler::Base::press (index);
};

void
TapDanceEventHandler::release (uint8_t index) {
  uint16_t keycode = keymap->lookup (index);

  if (Akela::TapDance::Component::OneShotMod::release (HID, keymap, index, keycode))
    return;

  Akela::EventHandler::Base::release (index);
}

void
TapDanceEventHandler::loop () {
  Akela::TapDance::Component::OneShotMod::loop (HID, keymap);
  Akela::EventHandler::Base::loop ();
}

static M01::HID::Base            hid;
static Akela::KeyMap             keyMap ((uint16_t *)keymap);
static M01::Scanner              scanner;
static TapDanceEventHandler      eventHandler (&hid, &keyMap);
static M01::Model01              keyboard (&scanner, &eventHandler);

void
setup () {
  keyboard.setup ();
}

void
loop () {
  keyboard.loop ();
}
