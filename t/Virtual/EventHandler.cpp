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

namespace Virtual {
  namespace EventHandler {
    class Base : public Akela::EventHandler::Base {
    public:
      Base (Akela::AbstractHID *hid, Akela::KeyMap *keymap)
        : Akela::EventHandler::Base (hid, keymap) {};

      virtual void hold_code (uint16_t keycode) {
        if (IS_FN (keycode))
          return;

        ((::Virtual::HID *)HID)->hold (keycode);
      }
    };

    class Macros : public Akela::EventHandler::Base,
                   public Akela::EventHandler::FnMacroComponent {
    public:
      Macros (Akela::AbstractHID *hid, Akela::KeyMap *keymap)
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

      virtual void macroAction (Akela::AbstractHID *,
                                Akela::KeyMap *,
                                uint8_t index,
                                bool pressed) {
        std::cout << "  " << __PRETTY_FUNCTION__ << "(macroIndex=" << std::hex << (int) index
                  << ", pressed=" << (bool) pressed << ")" << std::endl;
      }

    private:
      using Akela::EventHandler::FnMacroComponent::register_code;
      using Akela::EventHandler::FnMacroComponent::unregister_code;
    };

    class Layered : public Akela::EventHandler::Layered {
    public:
      Layered (Akela::AbstractHID *hid, Akela::LayeredKeyMap *keymap)
        : Akela::EventHandler::Layered (hid, keymap) {};

      virtual void hold_code (uint16_t keycode) {
        if (IS_FN (keycode))
          return;

        ((::Virtual::HID *)HID)->hold (keycode);
      }

      using Akela::EventHandler::Component::hold_code;
    };

  };
};
