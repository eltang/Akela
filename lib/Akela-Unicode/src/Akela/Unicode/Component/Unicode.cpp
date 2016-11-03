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

#include <Akela-Unicode.h>

namespace Akela {
  namespace Unicode {

    namespace Component {

      void
      Unicode::unicodeMode (Unicode::Mode mode) {
        _unicodeMode = mode;
      }

      uint8_t
      Unicode::hexToKeycode (uint8_t hex)
      {
        if (hex == 0x0) {
          return KC_0;
        } else if (hex < 0xA) {
          return KC_1 + (hex - 0x1);
        } else {
          return KC_A + (hex - 0xA);
        }
      }

      void
      Unicode::typeUnicode (Akela::AbstractHID *HID,
                            uint32_t code) {
        unicodeStart (HID);

        bool onZeroStart = true;

        for (int8_t i = 7; i >= 0; i--) {
          if (i <= 3) {
            onZeroStart = false;
          }

          uint8_t digit = ((code >> (i * 4)) & 0xF);
          if (digit == 0) {
            if (onZeroStart == false) {
              HID->press (hexToKeycode (digit));
              HID->sendReport ();
              HID->release (hexToKeycode (digit));
              HID->sendReport ();
            }
          } else {
            HID->press (hexToKeycode (digit));
            HID->sendReport ();
            HID->release (hexToKeycode (digit));
            HID->sendReport ();
            onZeroStart = false;
          }
        }

        unicodeEnd (HID);
      }

      void
      Unicode::unicodeStart (Akela::AbstractHID *HID) {
        switch (_unicodeMode) {
        case LINUX:
          HID->press (KC_LCTL);
          HID->press (KC_LSFT);
          HID->press (KC_U);
          HID->sendReport ();
          HID->release (KC_LCTL);
          HID->release (KC_LSFT);
          HID->release (KC_U);
          HID->sendReport ();
          break;
        case OSX:
          break;
        case WINDOWS:
          break;
        }
      }

      void
      Unicode::unicodeEnd (Akela::AbstractHID *HID) {
        switch (_unicodeMode) {
        case LINUX:
          HID->press (KC_SPC);
          HID->sendReport ();
          HID->release (KC_SPC);
          HID->sendReport ();
          break;
        case OSX:
          break;
        case WINDOWS:
          break;
        }
      }

    };
  };
};
