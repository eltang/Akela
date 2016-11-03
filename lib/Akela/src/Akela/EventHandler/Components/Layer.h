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

#define ML(n) (Akela::SYSFN_LAYER_MOMENTARY + n)
#define L(n)  (Akela::SYSFN_LAYER_MOVE + n)

namespace Akela {
  namespace EventHandler {
    class LayerComponent : public Component {
    protected:
      uint8_t lastLayer = 0;
      bool isTemporary = false;
      bool shouldCancel = false;

      virtual bool register_code (Akela::AbstractHID *HID,
                                  Akela::KeyMap::Basic *keymap,
                                  uint16_t keycode);

      virtual bool unregister_code (Akela::AbstractHID *HID,
                                    Akela::KeyMap::Basic *keymap,
                                    uint16_t keycode);
      using Component::hold_code;

      virtual void loop (Akela::KeyMap::Basic *keymap);
    };
  };
};
