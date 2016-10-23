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

#pragma once

namespace M01 {
  namespace SYSFN {
    enum {
      CONSUMER     = Akela::SYSFN_SAFE,
      CONSUMER_MAX = Akela::SYSFN_SAFE + 256
    };

    enum {
      SYSTEM       = CONSUMER_MAX + 1,
      SYSTEM_MAX   = CONSUMER_MAX + 257
    };

    enum {
      MOUSE_BUTTON     = SYSTEM_MAX + 1,
      MOUSE_BUTTON_MAX = SYSTEM_MAX + 9,
    };

    enum {
      MOUSE_CONTROL     = MOUSE_BUTTON_MAX + 1,
      MOUSE_CONTROL_MAX = MOUSE_BUTTON_MAX + 256
    };

    enum {
      MODEL01_SAFE = MOUSE_CONTROL_MAX + 1,
    };
  };
};
