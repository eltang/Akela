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

namespace Virtual {
  class KeyMap : public Akela::KeyMap {
  public:
    KeyMap (uint16_t *keymap) : Akela::KeyMap (keymap) {};

    virtual uint16_t lookup (uint8_t index) {
      uint16_t k = Akela::KeyMap::lookup (index);

      std::cout << "\t" << __PRETTY_FUNCTION__ << "(" << (int)0 << ", "
                << (int)index << ") = " << std::hex << (int)k << std::endl;
      return k;
    }

    void set_keymap (uint16_t *keymap) {
      this->keymap = keymap;
    }
  };

  class LayeredKeyMap : public Akela::LayeredKeyMap {
  public:
    LayeredKeyMap (uint16_t **keymap, uint8_t layoutSize)
      : Akela::LayeredKeyMap (keymap, layoutSize) {};

    virtual uint16_t lookup (uint8_t index) {
      uint16_t k = Akela::LayeredKeyMap::lookup (index);

      std::cout << "\t" << __PRETTY_FUNCTION__ << "(" << (int)Layer << ", "
                << (int)index << ") = " << std::hex << (int)k << std::endl;
      return k;
    }

    void set_keymap (uint16_t *keymap) {
      this->keymap = keymap;
    }

    virtual void layer (uint8_t l) {
      std::cout << "\t" << __PRETTY_FUNCTION__ << "(" << (int)l << ")" << std::endl;
      Akela::LayeredKeyMap::layer (l);
    }

    using Akela::LayeredKeyMap::lookup;
    using Akela::LayeredKeyMap::layer;
  };

};
