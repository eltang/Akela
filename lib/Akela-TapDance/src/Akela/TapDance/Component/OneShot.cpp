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

      bool
      OneShot::register_code (Akela::AbstractHID *hid,
                              Akela::KeyMap *keymap,
                              uint16_t keycode) {
        if (keycode < FN_ONESHOT || keycode > FN_ONESHOT_MAX) {
          if (oneShotState)
            oneShotShouldCancel = true;
          return false;
        }

        uint8_t oneShotIndex = keycode - FN_ONESHOT;
        oneShotTimer = 1;

        if (bitRead(oneShotState, oneShotIndex)) {
          if (bitRead(stickyState, oneShotIndex)) {
            bitWrite(oneShotState, oneShotIndex, 0);
            bitWrite(stickyState, oneShotIndex, 0);
            oneShotDeactivate (hid, keymap, keycode);
            return true;
          } else {
            bitWrite(stickyState, oneShotIndex, 1);
          }
        }
        bitWrite(oneShotState, oneShotIndex, 1);

        oneShotActivate (hid, keymap, keycode);

        return true;
      }

      bool
      OneShot::unregister_code (Akela::AbstractHID *,
                                Akela::KeyMap *,
                                uint16_t keycode) {
        if (keycode < FN_ONESHOT || keycode > FN_ONESHOT_MAX) {
          if (oneShotState)
            oneShotShouldCancel = true;
          return false;
        }

        if (oneShotTimer > oneShotTimeOut)
          oneShotShouldCancel = true;

        return true;
      }

      bool
      OneShot::isOneShotActive () {
        return !(oneShotShouldCancel || (oneShotTimer > oneShotTimeOut));
      }

      void
      OneShot::loop (Akela::AbstractHID *hid,
                     Akela::KeyMap *keymap) {
        if (oneShotTimer)
          oneShotTimer++;

        if (!isOneShotActive ()) {
          cancelOneShot (hid, keymap);
        }
      }

      void
      OneShot::cancelOneShot (Akela::AbstractHID *hid,
                              Akela::KeyMap *keymap) {
        for (uint8_t i = 0; i < 32; i++) {
          if (bitRead(oneShotState, i) && !bitRead(stickyState, i)) {
            bitWrite(oneShotState, i, 0);
            oneShotDeactivate (hid, keymap, i + FN_ONESHOT);
          }
        }
        oneShotTimer = 0;
      }

    };
  };
};
