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

#define TD(n) (Akela::TapDance::FN_TAPDANCE + n)

namespace Akela {
  namespace TapDance {
    enum {
      FN_TAPDANCE     = FN(0x0020),
      FN_TAPDANCE_MAX = FN(0x003f),
    };

    namespace Component {

      class TapDance : public Akela::EventHandler::Component {
      public:
        virtual bool register_code (Akela::AbstractHID *hid,
                                    Akela::KeyMap::Abstract *keymap,
                                    uint16_t keycode);

        virtual bool unregister_code (Akela::AbstractHID *hid,
                                      Akela::KeyMap::Abstract *keymap,
                                      uint16_t keycode);

        virtual void loop (Akela::AbstractHID *hid,
                           Akela::KeyMap::Abstract *keymap);

      protected:
        uint16_t tapDanceTimer = 0;
        uint16_t tapDanceTimeOut = 40;
        uint32_t tapDanceState = 0;
        uint8_t lastTapDanceIndex = 0;
        uint8_t tapDanceCounter = 0;
        bool tapDanceInterrupted = false;

        virtual void tapDanceCycle (Akela::AbstractHID *hid,
                                    Akela::KeyMap::Abstract *keymap,
                                    uint8_t tapIndex,
                                    uint8_t counter) = 0;
        virtual void tapDanceFinish (Akela::AbstractHID *hid,
                                     Akela::KeyMap::Abstract *keymap,
                                     uint8_t tapIndex,
                                     uint8_t counter) = 0;
        virtual void tapDanceRelease (Akela::AbstractHID *hid,
                                      Akela::KeyMap::Abstract *keymap,
                                      uint8_t tapIndex,
                                      uint8_t counter) = 0;

      private:
        void finish (Akela::AbstractHID *hid,
                     Akela::KeyMap::Abstract *keymap,
                     uint8_t tapIndex,
                     uint8_t tapCounter);
      };
    };
  };
};
