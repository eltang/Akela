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

#include <Akela-TapDance.h>

namespace Akela {
  namespace TapDance {
    namespace Component {

      void
      OneShotLayer::oneShotActivate (Akela::AbstractHID *,
                                     Akela::KeyMap *keymap,
                                     uint8_t keycode) {
        Akela::LayeredKeyMap *km = (Akela::LayeredKeyMap *)keymap;
        uint8_t layer = keycode - FN_ONESHOT_OSL;
        prev_layer = km->layer ();

        km->layer (layer);
      }

      void
      OneShotLayer::oneShotDeactivate (Akela::AbstractHID *,
                                       Akela::KeyMap *keymap,
                                       uint8_t) {
        Akela::LayeredKeyMap *km = (Akela::LayeredKeyMap *)keymap;
        km->layer (prev_layer);
        prev_layer = 0;
      }
    };
  };
};
