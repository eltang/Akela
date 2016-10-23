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

    Layered::Layered (Akela::AbstractHID *HID,
                      Akela::LayeredKeyMap *keymap)
      : Akela::EventHandler::Base (HID, keymap) {
      lastMoveIndex = 0xff;
    }

    void
    Layered::press (uint8_t index) {
      uint16_t key = keymap->lookup (index);
      uint8_t layer;

      switch (key) {
      case Akela::SYSFN_LAYER_MOVE ... Akela::SYSFN_LAYER_MOVE_MAX:
        layer = key - Akela::SYSFN_LAYER_MOVE;
        lastMoveIndex = index;
        break;
      case Akela::SYSFN_LAYER_MOMENTARY ... Akela::SYSFN_LAYER_MOMENTARY_MAX:
        layer = key - Akela::SYSFN_LAYER_MOMENTARY;
        lastMoveIndex = 0xff;
        break;
      default:
        return Akela::EventHandler::Base::press (index);
      }

      Akela::LayeredKeyMap *km = (Akela::LayeredKeyMap *)keymap;
      km->layer_move (layer);
    }

    void
    Layered::release (uint8_t index) {
      uint16_t key = keymap->lookup (index);
      uint8_t layer;

      if (lastMoveIndex == index) {
        lastMoveIndex = 0xff;
        return;
      }

      switch (key) {
      case Akela::SYSFN_LAYER_MOVE ... Akela::SYSFN_LAYER_MOVE_MAX:
        layer = key - Akela::SYSFN_LAYER_MOVE;
        break;
      case Akela::SYSFN_LAYER_MOMENTARY ... Akela::SYSFN_LAYER_MOMENTARY_MAX:
        layer = key - Akela::SYSFN_LAYER_MOMENTARY;
        break;
      default:
        return Akela::EventHandler::Base::release (index);
      }

      Akela::LayeredKeyMap *km = (Akela::LayeredKeyMap *)keymap;
      km->layer_move (layer);
    }
  };
};
