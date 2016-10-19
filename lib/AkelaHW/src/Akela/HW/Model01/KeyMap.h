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

#define KEYMAP(                                     \
  k00, k01, k02, k03, k04, k05, k06,                \
  k10, k11, k12, k13, k14, k15,                     \
  k20, k21, k22, k23, k24, k25, k26,                \
  k30, k31, k32, k33, k34, k35, k36,                \
  k40, k41, k42, k43,                               \
  k50,                                              \
                                                    \
  k60, k61, k62, k63, k64, k65, k66,                \
  k70, k71, k72, k73, k74, k75,                     \
  k80, k81, k82, k83, k84, k85, k86,                \
  k90, k91, k92, k93, k94, k95, k96,                \
  ka0, ka1, ka2, ka3,                               \
  kb0)                                              \
                                                    \
  {                                                                     \
    k00, k01, k02, k03, k04, k05, k06,  k40, ka3,  k60, k61, k62, k63, k64, k65, k66, \
    k10, k11, k12, k13, k14, k15, k26,  k41, ka2,  kb0, k70, k71, k72, k73, k74, k75, \
    k20, k21, k22, k23, k24, k25, k36,  k42, ka1,  k80, k81, k82, k83, k84, k85, k86, \
    k30, k31, k32, k33, k34, k35, k50,  k43, ka0,  k90, k91, k92, k93, k94, k95, k96, \
  }
