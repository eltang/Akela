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

class TapDanceEventHandler : public Akela::EventHandler::Layered,
                             public Akela::TapDance::Component::OneShotMod,
                             public Akela::TapDance::Component::OneShotLayer {
public:
  TapDanceEventHandler (Akela::AbstractHID *hid, Akela::LayeredKeyMap *keymap)
    : Akela::EventHandler::Layered (hid, keymap) {};

  using Akela::TapDance::Component::OneShotMod::press;
  using Akela::TapDance::Component::OneShotLayer::press;
  virtual void press (uint8_t index);

  using Akela::TapDance::Component::OneShotMod::release;
  using Akela::TapDance::Component::OneShotLayer::release;
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
  if (Akela::TapDance::Component::OneShotLayer::press (HID, keymap, index, keycode))
    return;

  Akela::EventHandler::Layered::press (index);
};

void
TapDanceEventHandler::release (uint8_t index) {
  uint16_t keycode = keymap->lookup (index);

  if (Akela::TapDance::Component::OneShotMod::release (HID, keymap, index, keycode))
    return;
  if (Akela::TapDance::Component::OneShotLayer::release (HID, keymap, index, keycode))
    return;

  Akela::EventHandler::Layered::release (index);
}

void
TapDanceEventHandler::loop () {
  Akela::TapDance::Component::OneShotMod::loop (HID, keymap);
  Akela::EventHandler::Layered::loop ();
}

static M01::HID::Base            hid;
static M01::KeyMap               keyMap (keymap);
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
