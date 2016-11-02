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

/**
 * @mainpage Animated Keyboard Extension Library for Arduino
 *
 * Akela is a library, primarily developed for the <a
 * href="https://keyboard.io/">Keyboard.io Model01</a>, but built in a way to
 * allow reuse by any keyboard powered by an Arduino. It is a heavy work in
 * progress at this stage.
 *
 * Primary aims are:
 *
 * - Composability.
 * - Extensibility.
 * - Hardware-specific parts in separate libraries.
 */

#pragma once

#ifdef ARDUINO
# include <Arduino.h>
#else
# include <stdint.h>
#endif

#include "Akela/AbstractHID.h"
#include "Akela/AbstractScanner.h"
#include "Akela/KeyMap.h"
#include "Akela/LayeredKeyMap.h"
#include "Akela/KeyCodes.h"
#include "Akela/SysFn.h"
#include "Akela/EventHandler.h"
#include "Akela/Keyboard.h"
