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

static uint16_t seq_keymap[] = {
  0, 1, 2,
  3, 4, 5,
};

static uint16_t mod_keymap[] = {
  LCTL(KC_C), LSFT(LCTL(KC_S)), LALT(LSFT(LCTL(KC_I))),
  LALT(RALT(LCTL(RCTL(LSFT(RSFT(LGUI(KC_L))))))), KC_L, KC_A
};

static void
TestBasicKeyPresses () {
  Virtual::HID                hid;
  Virtual::KeyMap             keymap (seq_keymap);
  Virtual::EventHandler::Base EH (&hid, &keymap);
  Virtual::Scanner            scanner (_scan_dummy);
  Virtual::Keyboard           keyboard (&scanner, &EH);

  std::cout << __func__ << std::endl;

  keyboard.setup ();

  TESTCASE ("Pressing one key at a time", seq_keymap, _scan_one_at_a_time);

  TESTCASE ("Chording all", seq_keymap, _scan_chord_all);

  TESTCASE ("Modifiers", mod_keymap, _scan_one_at_a_time);

  TESTCASE_STEPS("Holding", seq_keymap, ,
    {
      0b00000000, // clear state
      0b00000001, // first pressed
      0b00000001, // first held
      0b00000011, // second pressed, first held
      0b00000000, // both released
    });
}
