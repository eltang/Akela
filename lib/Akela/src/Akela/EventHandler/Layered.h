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

#include "Components/Layer.h"

namespace Akela {
  namespace EventHandler {
    class Layered : public Akela::EventHandler::Base,
                    public LayerComponent {
    public:
      Layered (Akela::AbstractHID *HID, Akela::KeyMap::Layered *keymap)
        : Akela::EventHandler::Base (HID, keymap) {};

    protected:
      virtual void register_code (uint16_t keycode);
      virtual void unregister_code (uint16_t keycode);
      virtual void hold_code (uint16_t keycode);

      virtual void loop ();
      using LayerComponent::loop;

      using LayerComponent::hold_code;
      using LayerComponent::register_code;
      using LayerComponent::unregister_code;
    };
  };
};
