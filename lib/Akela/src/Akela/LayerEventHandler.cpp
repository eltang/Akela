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

Akela::LayerEventHandler::LayerEventHandler (Akela::AbstractHID *HID,
                                             Akela::LayeredKeyMap *keymap)
  : Akela::KeyEventHandler (HID, keymap) {
  lastMoveIndex = 0xff;
}

void
Akela::LayerEventHandler::press (uint8_t index) {
  uint16_t key = keymap->lookup (index);

  if (!CHECK_FN (key, LAYER))
    return Akela::KeyEventHandler::press (index);

  Akela::LayeredKeyMap *km = (Akela::LayeredKeyMap *)keymap;
  bool move = !!(key & 0x0010);
  uint8_t layer = key & ~0xfffc;

  if (move)
    lastMoveIndex = index;
  else
    lastMoveIndex = 0xff;

  km->layer_move (layer);
}

void
Akela::LayerEventHandler::release (uint8_t index) {
  uint16_t key = keymap->lookup (index);

  if (lastMoveIndex == index) {
    lastMoveIndex = 0xff;
    return;
  }

  if (!CHECK_FN (key, LAYER))
    return Akela::KeyEventHandler::release (index);

  Akela::LayeredKeyMap *km = (Akela::LayeredKeyMap *)keymap;
  uint8_t layer = key & ~0xfffc;
  km->layer_move (layer);
}
