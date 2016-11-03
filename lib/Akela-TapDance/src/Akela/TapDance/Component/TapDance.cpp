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
      TapDance::finish (Akela::AbstractHID *hid,
                        Akela::KeyMap::Basic *keymap,
                        uint8_t tapIndex,
                        uint8_t tapCounter) {
        tapDanceFinish (hid, keymap, tapIndex, tapCounter);
        if (!bitRead (tapDanceState, tapIndex) ||
            (tapDanceTimer >= tapDanceTimeOut)) {
          tapDanceRelease (hid, keymap, tapIndex, tapCounter);

          lastTapDanceIndex = tapDanceCounter = tapDanceTimer = 0;
          tapDanceInterrupted = false;
          bitWrite (tapDanceState, tapIndex, 0);
        }
      }

      bool
      TapDance::register_code (Akela::AbstractHID *hid,
                               Akela::KeyMap::Basic *keymap,
                               uint16_t keycode) {
        if (keycode < FN_TAPDANCE || keycode > FN_TAPDANCE_MAX) {
          if (tapDanceCounter) {
            tapDanceInterrupted = true;
            finish (hid, keymap, lastTapDanceIndex, tapDanceCounter);
          }

          return false;
        }

        uint8_t tapDanceIndex = keycode - FN_TAPDANCE;

        if (tapDanceCounter && (tapDanceIndex != lastTapDanceIndex)) {
          tapDanceInterrupted = true;
          finish (hid, keymap, lastTapDanceIndex, tapDanceCounter);
        }

        lastTapDanceIndex = tapDanceIndex;
        tapDanceTimer = 0;
        tapDanceCounter++;
        bitWrite (tapDanceState, lastTapDanceIndex, 1);
        tapDanceCycle (hid, keymap, lastTapDanceIndex, tapDanceCounter);

        return true;
      }

      bool
      TapDance::unregister_code (Akela::AbstractHID *hid,
                                 Akela::KeyMap::Basic *keymap,
                                 uint16_t keycode) {
        if (keycode < FN_TAPDANCE || keycode > FN_TAPDANCE_MAX) {
          return false;
        }

        uint8_t tapDanceIndex = keycode - FN_TAPDANCE;

        if (tapDanceIndex != lastTapDanceIndex)
          return true;

        bitWrite (tapDanceState, tapDanceIndex, 0);

        if (tapDanceTimer >= tapDanceTimeOut || tapDanceInterrupted) {
          tapDanceRelease (hid, keymap, tapDanceIndex, tapDanceCounter);
          lastTapDanceIndex = tapDanceCounter = tapDanceTimer = 0;
          tapDanceInterrupted = false;
        }

        return true;
      }

      void
      TapDance::loop (Akela::AbstractHID *hid,
                      Akela::KeyMap::Basic *keymap) {
        if (tapDanceCounter)
          tapDanceTimer++;

        if (tapDanceTimer >= tapDanceTimeOut) {
          finish (hid, keymap, lastTapDanceIndex, tapDanceCounter);
        }
      }
    };
  };
};
