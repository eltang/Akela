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
  namespace Unicode {

    namespace Component {

      class Unicode {
      public:
        enum Mode {
          LINUX,
          OSX,
          WINDOWS,
        };
      protected:
        Mode _unicodeMode = LINUX;

        virtual void typeUnicode (Akela::AbstractHID *HID,
                                  uint32_t code);
        void unicodeMode (Mode mode);

        virtual void unicodeStart (Akela::AbstractHID *HID);
        virtual void unicodeEnd (Akela::AbstractHID *HID);

      private:
        uint8_t hexToKeycode (uint8_t hex);
      };

    };
  };
};
