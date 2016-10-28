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

static uint8_t
_scan_one_at_a_time (uint16_t cycle, uint8_t state, bool *quit) {
  if (cycle >= 6)
    *quit = true;

  state = 1 << cycle;
  return state;
}

static uint8_t
_scan_chord_all (uint16_t cycle, uint8_t state, bool *quit) {
  if (cycle) {
    *quit = true;
    state = 0x00;
  } else {
    state = 0xff;
  }

  return state;
}

static uint8_t
_scan_dummy (uint16_t, uint8_t, bool *quit) {
  *quit = true;
  return 0;
}

static uint8_t *_scan_spec_specs;
static uint16_t _scan_spec_size;

static uint8_t _scan_spec_inner (uint16_t cycle, uint8_t, bool *quit) {
  if (cycle >= _scan_spec_size - 1) {
    *quit = true;
  }
  return _scan_spec_specs[cycle];
}

#define _scan_spec(n) _scan_spec_gen(sizeof(n), n)

static Virtual::ScannerFunction
_scan_spec_gen (uint16_t n, uint8_t scans[]) {
  _scan_spec_size = n;
  _scan_spec_specs = scans;
  return _scan_spec_inner;
}
