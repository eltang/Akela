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

#include "Akela.h"

namespace Akela {
  namespace EventHandler {

    bool
    LayerComponent::register_code (Akela::AbstractHID *,
                                   Akela::KeyMap::Basic *keymap,
                                   uint16_t keycode) {
      uint8_t layer;

      switch (keycode) {
      case Akela::SYSFN_LAYER_MOVE ... Akela::SYSFN_LAYER_MOVE_MAX:
        layer = keycode - Akela::SYSFN_LAYER_MOVE;
        isTemporary = false;
        break;
      case Akela::SYSFN_LAYER_MOMENTARY ... Akela::SYSFN_LAYER_MOMENTARY_MAX:
        layer = keycode - Akela::SYSFN_LAYER_MOMENTARY;
        isTemporary = true;
        break;
      default:
        return false;
      }

      Akela::KeyMap::Layered *km = (Akela::KeyMap::Layered *)keymap;
      lastLayer = km->layer ();
      km->layer (layer);

      return true;
    }

    bool
    LayerComponent::unregister_code (Akela::AbstractHID *,
                                     Akela::KeyMap::Basic *,
                                     uint16_t keycode) {
      if (keycode != KC_TRNS) {
        return false;
      }

      if (isTemporary)
        shouldCancel = true;

      return true;
    }

    void
    LayerComponent::loop (Akela::KeyMap::Basic *keymap) {
      if (!shouldCancel)
        return;

      Akela::KeyMap::Layered *km = (Akela::KeyMap::Layered *)keymap;
      km->layer (lastLayer);

      shouldCancel = false;
    }
  };
};
