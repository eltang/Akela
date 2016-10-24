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

Akela::LayeredKeyMap::LayeredKeyMap (uint16_t **keymap, uint8_t layerSize)
  : Akela::KeyMap ((uint16_t *)keymap) {
  LayerSize = layerSize;
}

uint16_t
Akela::LayeredKeyMap::lookup (uint8_t layer, uint8_t index) {
  return Akela::KeyMap::lookup (index + (LayerSize * layer));
}

uint16_t
Akela::LayeredKeyMap::lookup (uint8_t index) {
  return lookup (Layer, index);
}

void
Akela::LayeredKeyMap::layer_move (uint8_t index) {
  Layer = index;
}

uint8_t
Akela::LayeredKeyMap::layer () {
  return Layer;
}
