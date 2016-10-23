/*
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

#include "Akela/HW/Model01.h"

namespace M01 {
  namespace EventHandler {

    bool
    ExtraKeysComponent::press (Akela::AbstractHID *HID,
                               Akela::KeyMap *,
                               uint8_t,
                               uint16_t keycode) {
      M01::HID::Page page;
      uint8_t key;

      switch (keycode) {
      case M01::SYSFN::CONSUMER ... M01::SYSFN::CONSUMER_MAX:
        page = M01::HID::CONSUMER;
        key = keycode - M01::SYSFN::CONSUMER;
        break;

      case M01::SYSFN::SYSTEM ... M01::SYSFN::SYSTEM_MAX:
        page = M01::HID::SYSTEM;
        key = keycode - M01::SYSFN::SYSTEM;
        break;

      default:
        return false;
      }

      ((::M01::HID::Base *)HID)->press (page, key);
      return true;
    }

    bool
    ExtraKeysComponent::release (Akela::AbstractHID *HID,
                                 Akela::KeyMap *,
                                 uint8_t,
                                 uint16_t keycode) {
      M01::HID::Page page;
      uint8_t key;

      switch (keycode) {
      case M01::SYSFN::CONSUMER ... M01::SYSFN::CONSUMER_MAX:
        page = M01::HID::CONSUMER;
        key = keycode - M01::SYSFN::CONSUMER;
        break;

      case M01::SYSFN::SYSTEM ... M01::SYSFN::SYSTEM_MAX:
        page = M01::HID::SYSTEM;
        key = keycode - M01::SYSFN::SYSTEM;
        break;

      default:
        return false;
      }

      ((::M01::HID::Base *)HID)->release (page, key);
      return true;
    }
  };
};
