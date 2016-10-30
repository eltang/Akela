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
                             public Akela::TapDance::Component::OneShotLayer,
                             public Akela::TapDance::Component::TapDance {
public:
  TapDanceEventHandler (Akela::AbstractHID *hid, Akela::LayeredKeyMap *keymap)
    : Akela::EventHandler::Layered (hid, keymap) {};

  using Akela::TapDance::Component::OneShotMod::press;
  using Akela::TapDance::Component::OneShotLayer::press;
  using Akela::TapDance::Component::TapDance::press;
  virtual void press (uint8_t index);

  using Akela::TapDance::Component::OneShotMod::release;
  using Akela::TapDance::Component::OneShotLayer::release;
  using Akela::TapDance::Component::TapDance::release;
  virtual void release (uint8_t index);

  virtual void loop ();

protected:
  virtual void tapDanceCycle (Akela::AbstractHID *hid,
                              Akela::KeyMap *keymap,
                              uint8_t tapIndex,
                              uint8_t counter);
  virtual void tapDanceFinish (Akela::AbstractHID *hid,
                               Akela::KeyMap *keymap,
                               uint8_t tapIndex,
                               uint8_t counter);
  virtual void tapDanceRelease (Akela::AbstractHID *hid,
                                Akela::KeyMap *keymap,
                                uint8_t tapIndex,
                                uint8_t counter);

private:
  using Akela::TapDance::Component::OneShotMod::loop;
  using Akela::TapDance::Component::TapDance::loop;
};

void
TapDanceEventHandler::press (uint8_t index) {
  uint16_t keycode = keymap->lookup (index);

  if (Akela::TapDance::Component::TapDance::press (HID, keymap, index, keycode))
    return;
  if (Akela::TapDance::Component::OneShotMod::press (HID, keymap, index, keycode))
    return;
  if (Akela::TapDance::Component::OneShotLayer::press (HID, keymap, index, keycode))
    return;

  Akela::EventHandler::Layered::press (index);
};

void
TapDanceEventHandler::release (uint8_t index) {
  uint16_t keycode = keymap->lookup (index);

  if (Akela::TapDance::Component::TapDance::release (HID, keymap, index, keycode))
    return;
  if (Akela::TapDance::Component::OneShotMod::release (HID, keymap, index, keycode))
    return;
  if (Akela::TapDance::Component::OneShotLayer::release (HID, keymap, index, keycode))
    return;

  Akela::EventHandler::Layered::release (index);
}

void
TapDanceEventHandler::loop () {
  Akela::TapDance::Component::TapDance::loop (HID, keymap);
  Akela::TapDance::Component::OneShotMod::loop (HID, keymap);
  Akela::EventHandler::Layered::loop ();
}

void
TapDanceEventHandler::tapDanceCycle (Akela::AbstractHID *,
                                     Akela::KeyMap *,
                                     uint8_t,
                                     uint8_t) {
}

void
TapDanceEventHandler::tapDanceFinish (Akela::AbstractHID *hid,
                                      Akela::KeyMap *,
                                      uint8_t tapIndex,
                                      uint8_t counter) {
  switch (tapIndex) {
  case 0:
    if (counter == 1) {
      hid->press (KC_A);
    } else {
      hid->press (KC_B);
    }
    break;
  }
}

void
TapDanceEventHandler::tapDanceRelease (Akela::AbstractHID *hid,
                                       Akela::KeyMap *,
                                       uint8_t tapIndex,
                                       uint8_t counter) {
  switch (tapIndex) {
  case 0:
    if (counter == 1) {
      hid->release (KC_A);
    } else {
      hid->release (KC_B);
    }
  }
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
