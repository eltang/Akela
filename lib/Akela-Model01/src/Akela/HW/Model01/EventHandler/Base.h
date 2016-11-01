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

namespace M01 {
  namespace EventHandler {
    class Base : public Akela::EventHandler::Layered, public ExtraKeysComponent,
      public Akela::EventHandler::FnMacroComponent {
    public:
      Base (Akela::AbstractHID *HID, Akela::LayeredKeyMap *keymap)
        : Akela::EventHandler::Layered (HID, keymap),
          Akela::EventHandler::FnMacroComponent () {};

    protected:
      virtual void register_code (uint16_t keycode);
      virtual void unregister_code (uint16_t keycode);
      virtual void hold_code (uint16_t keycode);

    private:
      using Akela::EventHandler::Component::hold_code;

      using ExtraKeysComponent::register_code;
      using ExtraKeysComponent::unregister_code;
      using Akela::EventHandler::FnMacroComponent::register_code;
      using Akela::EventHandler::FnMacroComponent::unregister_code;
    };
  };
};
