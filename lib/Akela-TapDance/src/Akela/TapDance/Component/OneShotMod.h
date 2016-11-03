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

#pragma once

#include <Akela.h>

#include "OneShot.h"

#define _OSM_HELPER(kc) KC_ ## kc

#define OSM(kc) (Akela::TapDance::FN_ONESHOT_OSM + _OSM_HELPER(kc) - KC_LCTL)

namespace Akela {
  namespace TapDance {
    enum {
      FN_ONESHOT_OSM     = FN_ONESHOT,
      FN_ONESHOT_OSM_MAX = FN_ONESHOT + 8
    };

    namespace Component {
      class OneShotMod : public OneShot {
      protected:
        virtual void oneShotActivate (Akela::AbstractHID *hid,
                                      Akela::KeyMap::Basic *keymap,
                                      uint16_t keycode);
        virtual void oneShotDeactivate (Akela::AbstractHID *hid,
                                        Akela::KeyMap::Basic *keymap,
                                        uint16_t keycode);

        bool isOneShotModifierActive (uint8_t keycode);
      };
    };
  };
};
