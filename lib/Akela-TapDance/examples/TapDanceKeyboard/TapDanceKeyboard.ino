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

protected:
  virtual void register_code (uint16_t keycode);
  virtual void unregister_code (uint16_t keycode);

  virtual void loop ();

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
  using Akela::EventHandler::LayerComponent::loop;
  using Akela::EventHandler::LayerComponent::register_code;
  using Akela::EventHandler::LayerComponent::unregister_code;
  using Akela::TapDance::Component::OneShotMod::loop;
  using Akela::TapDance::Component::TapDance::loop;
};

void
TapDanceEventHandler::register_code (uint16_t keycode) {
  if (Akela::TapDance::Component::TapDance::register_code (HID, keymap, keycode))
    return;
  if (Akela::TapDance::Component::OneShotMod::register_code (HID, keymap, keycode))
    return;
  if (Akela::TapDance::Component::OneShotLayer::register_code (HID, keymap, keycode))
    return;

  Akela::EventHandler::Layered::register_code (keycode);
};

void
TapDanceEventHandler::unregister_code (uint16_t keycode) {
  if (Akela::TapDance::Component::TapDance::unregister_code (HID, keymap, keycode))
    return;
  if (Akela::TapDance::Component::OneShotMod::unregister_code (HID, keymap, keycode))
    return;
  if (Akela::TapDance::Component::OneShotLayer::unregister_code (HID, keymap, keycode))
    return;

  Akela::EventHandler::Layered::unregister_code (keycode);
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
