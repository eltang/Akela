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

static void
TestLayers () {
  Virtual::HID                   hid;
  Virtual::LayeredKeyMap         keymap ((uint16_t **)layered_keymap, KEYBOARD_ROWS * KEYBOARD_COLS);
  Virtual::EventHandler::Layered EH (&hid, &keymap);
  Virtual::Scanner               scanner (_scan_dummy);
  Virtual::Keyboard              keyboard (&scanner, &EH);

  std::cout << __func__ << std::endl;

  keyboard.setup ();

  TESTCASE("Pressing one key at a time", (uint16_t *)layered_keymap,
           _scan_one_at_a_time);

  TESTCASE_STEPS("Tapping the momentary layer key", (uint16_t *)ml_keymap, keymap.layer (0),
    {
      0b00000000, // clear state
      0b00000001, // first (ML) pressed
      0b00000000, // first (ML) released
      0b00000010, // second pressed
      0b00000000, // second released
    });

  TESTCASE_STEPS("Holding the momentary layer key", (uint16_t *)ml_keymap, keymap.layer (0),
    {
      0b00000000, // clear state
      0b00000001, // first (ML) pressed
      0b00000011, // second pressed, first held
      0b00000001, // second released
      0b00000000, // first released
      0b00000001, // first pressed
      0b00000011, // second pressed, first held
      0b00000000, // both released
    });
}
