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

namespace Akela {
  namespace TapDance {
    enum {
      FN_ONESHOT     = FN(0x0000),
      FN_ONESHOT_MAX = FN(0x001f),
    };

    namespace Component {

      class OneShot : public Akela::EventHandler::Component {
      public:
        virtual bool press (Akela::AbstractHID *hid,
                            Akela::KeyMap *keymap,
                            uint8_t index,
                            uint16_t keycode);

        virtual bool release (Akela::AbstractHID *hid,
                              Akela::KeyMap *keymap,
                              uint8_t index,
                              uint16_t keycode);

        virtual void loop (Akela::AbstractHID *hid,
                           Akela::KeyMap *keymap);

        virtual void cancelOneShot (Akela::AbstractHID *hid,
                                    Akela::KeyMap *keymap);

      protected:
        uint16_t Timer = 0;
        uint16_t TimeOut = 40;
        uint32_t oneShotState = 0;
        uint32_t stickyState = 0;
        bool oneShotShouldCancel = false;

        virtual void activate (Akela::AbstractHID *hid,
                               Akela::KeyMap *keymap,
                               uint8_t keycode) = 0;
        virtual void deactivate (Akela::AbstractHID *hid,
                                 Akela::KeyMap *keymap,
                                 uint8_t keycode) = 0;
      };

    };
  };
};
