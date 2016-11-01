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
#include "OneShotMod.h"

#define OSL(layer) (Akela::TapDance::FN_ONESHOT_OSL + layer)

namespace Akela {
  namespace TapDance {
    enum {
      FN_ONESHOT_OSL     = FN_ONESHOT_OSM_MAX + 1,
      FN_ONESHOT_OSL_MAX = FN_ONESHOT_MAX
    };

    namespace Component {
      class OneShotLayer : public OneShot {
      protected:
        uint8_t prev_layer = 0;

        virtual void oneShotActivate (Akela::AbstractHID *hid,
                                      Akela::KeyMap *keymap,
                                      uint16_t keycode);
        virtual void oneShotDeactivate (Akela::AbstractHID *hid,
                                        Akela::KeyMap *keymap,
                                        uint16_t keycode);
      };
    };
  };
};
