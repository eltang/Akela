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
#include <Akela-Unicode.h>

#include "layout.h"

namespace Unicode {
    class EventHandler : public Akela::EventHandler::Base,
                         public Akela::EventHandler::FnMacroComponent,
                         public Akela::Unicode::Component::Unicode {
    public:
      EventHandler (Akela::AbstractHID *hid, Akela::KeyMap::Abstract *keymap)
        : Akela::EventHandler::Base (hid, keymap) {};

      virtual void register_code (uint16_t keycode) {
        if (Akela::EventHandler::FnMacroComponent::register_code (HID, keymap, keycode))
          return;

        Akela::EventHandler::Base::register_code (keycode);
      }

      virtual void unregister_code (uint16_t keycode) {
        if (Akela::EventHandler::FnMacroComponent::unregister_code (HID, keymap, keycode))
          return;

        Akela::EventHandler::Base::unregister_code (keycode);
      }

      virtual void macroAction (Akela::AbstractHID *HID,
                                Akela::KeyMap::Abstract *,
                                uint8_t index,
                                bool pressed) {
        if (!pressed)
          return;

        if (index != 0)
          return;

        typeUnicode (HID, 0x2615);
      }

    private:
      using Akela::EventHandler::FnMacroComponent::register_code;
      using Akela::EventHandler::FnMacroComponent::unregister_code;
    };
};

static M01::HID::Base            hid;
static Akela::KeyMap::Basic      keyMap ((uint16_t *)keymap);
static M01::Scanner              scanner;
static Unicode::EventHandler     eventHandler (&hid, &keyMap);
static M01::Model01              keyboard (&scanner, &eventHandler);

void
setup () {
  keyboard.setup ();
}

void
loop () {
  keyboard.loop ();
}
