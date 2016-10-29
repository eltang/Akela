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

      void OneShotMod::oneShotActivate (Akela::AbstractHID *hid,
                                        Akela::KeyMap *,
                                        uint8_t keycode) {
        hid->press (keycode - FN_ONESHOT_OSM + KC_LCTL);
        hid->sendReport ();
      }

      void OneShotMod::oneShotDeactivate (Akela::AbstractHID *hid,
                                          Akela::KeyMap *,
                                          uint8_t keycode) {
        hid->release (keycode - FN_ONESHOT_OSM + KC_LCTL);
        hid->sendReport ();
      }

      bool
      OneShotMod::isOneShotModifierActive (uint8_t keycode) {
        uint8_t n = keycode - KC_LCTL;
        bool active = !!(oneShotState & (1 << n));

        return active && isOneShotActive ();
      }
    };
  };
};
