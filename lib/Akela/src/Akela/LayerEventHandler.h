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

#define MOD_FN_LAYER 0x2000
#define MOD_FN_LAYER_MOMENTARY 0x0000
#define MOD_FN_LAYER_MOVE 0x0010

#define ML(n) FN(n | MOD_FN_LAYER | MOD_FN_LAYER_MOMENTARY)
#define L(n)  FN(n | MOD_FN_LAYER | MOD_FN_LAYER_MOVE)

namespace Akela {
  class LayerEventHandler : public Akela::KeyEventHandler {
  protected:
    uint8_t lastMoveIndex;
  public:
    LayerEventHandler (Akela::AbstractHID *HID, Akela::LayeredKeyMap *keymap);

    virtual void press (uint8_t index);
    virtual void release (uint8_t index);
  };
};
