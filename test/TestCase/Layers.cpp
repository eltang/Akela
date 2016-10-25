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

int
TestLayers () {
  PrinterHID hid = PrinterHID ();
  LayerPrinterKeyMap keymap = LayerPrinterKeyMap ((uint16_t **)layered_keymap, 64);
  Akela::EventHandler::Base EH =
    Akela::EventHandler::Base (&hid, &keymap);
  NoOpScanner scanner = NoOpScanner ();
  PressReleaseLayeredKeyboard keyboard = PressReleaseLayeredKeyboard (&scanner, &EH, &keymap);

  std::cout << __func__ << std::endl;

  keyboard.setup ();
  keyboard.test ();

  return 0;
}

int
TestLayerKeys () {
  PrinterHID hid = PrinterHID ();
  LayerPrinterKeyMap keymap = LayerPrinterKeyMap ((uint16_t **)layer_key_keymap, 64);
  Akela::EventHandler::Layered EH =
    Akela::EventHandler::Layered (&hid, &keymap);
  NoOpScanner scanner = NoOpScanner ();
  ChordedKeyboard keyboard = ChordedKeyboard (&scanner, &EH);

  std::cout << __func__ << std::endl;

  keyboard.setup ();
  keyboard.test ();

  return 0;
}
