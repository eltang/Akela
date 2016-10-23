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

#include "EventHandler/SysFn.h"
#include "EventHandler/LedControl.h"
#include "EventHandler/Components/ExtraKeys.h"
#include "EventHandler/Components/Mouse.h"

namespace M01 {
  namespace EventHandler {
    class Complete : public Akela::EventHandler::Layered,
                     public LedControl,
                     public ExtraKeysComponent,
                     public MouseComponent {
    public:
      Complete (Akela::AbstractHID *HID, Akela::LayeredKeyMap *keymap,
                Scanner *scanner);

      virtual void press (uint8_t index);
      virtual void release (uint8_t index);
      virtual void hold (uint8_t index);

      virtual void setup ();
    };
  };
};
