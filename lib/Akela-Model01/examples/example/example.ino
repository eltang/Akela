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

#include <Akela.h>
#include <Akela-Model01.h>

#include "layout.h"

namespace Example {
  class EventHandler: public M01::EventHandler::Full {
  public:
    EventHandler (M01::HID::Full *hid, Akela::LayeredKeyMap *keymap,
                  M01::Scanner *scanner)
      : M01::EventHandler::Full (hid, keymap, scanner) {};

    virtual void press (uint8_t index);
    virtual void release (uint8_t index);
    virtual void loop ();
  private:
    using M01::EventHandler::MouseComponent::press;
    using M01::EventHandler::MouseComponent::release;
  };

  void
  EventHandler::loop () {
    M01::EventHandler::Full::loop ();
    M01::EventHandler::Full::sync ();
  }

  void
  EventHandler::press (uint8_t index) {
    cRGB color = {0, 0, 0};
    uint16_t keycode = keymap->lookup (index);

    // When a key is pressed, highlight it for the duration
    color = {0x80, 0x80, 0x80};

    // When a modifier is pressed, highlight the modifier, but only if the
    // modifier is pressed directly!
    if (!IS_FN (keycode)) {
      switch (KEYCODE (keycode)) {
      case KC_LCTL:
      case KC_LSFT:
      case KC_LALT:
      case KC_LGUI:
      case KC_RCTL:
      case KC_RSFT:
      case KC_RALT:
        color = {0x00, 0x55, 0x80};
        break;
      }
    }

    M01::EventHandler::Full::set_color (index, color);

    // If any layer is active...
    Akela::LayeredKeyMap *km = (Akela::LayeredKeyMap *)keymap;

    if (km->layer () != 0) {
      for (uint8_t i = 0; i < 64; i++) {
        uint16_t base_kc = km->lookup (0, i);
        uint16_t curr_kc = km->lookup (i);

        // If the key did not change, not touching the color
        if (base_kc == curr_kc)
          continue;

        cRGB color = {0, 0, 0};
        switch (curr_kc) {
        case M01::SYSFN::CONSUMER ... M01::SYSFN::SYSTEM_MAX:
          // ExtraKeys are green
          color = {0, 0xff, 0};
          break;

        case M01::SYSFN::MOUSE_BUTTON ... M01::SYSFN::MOUSE_BUTTON_MAX:
          // Mouse buttons are yellow
          color = {0xff, 0xff, 0};
          break;

        case M01::SYSFN::MOUSE_CONTROL ... M01::SYSFN::MOUSE_CONTROL_MAX:
          // Mouse controls are white
          color = {0xff, 0xff, 0xff};
          break;

        case Akela::SYSFN_LAYER_MOMENTARY ... Akela::SYSFN_LAYER_MOVE_MAX:
          // Layer switchers are red
          color = {0xff, 0, 0};
          break;
        }

        if (!IS_FN(curr_kc)) {
          switch (KEYCODE (curr_kc)) {
          case KC_KP1 ... KC_KP0:
            // Keypad numbers are light green
            color = {0, 0xff, 0x55};
            break;
          case KC_KPSLSH ... KC_KPENT:
          case KC_KPDOT:
            // non-number keypad stuff are cyan
            color = {0, 0xff, 0xff};
            break;
          }
        }

        M01::EventHandler::Full::set_color (i, color);
      }
    }

    M01::EventHandler::Full::press (index);
  }

  void
  EventHandler::release (uint8_t index) {
    cRGB color = {0, 0, 0};

    M01::EventHandler::Full::release (index);

    M01::EventHandler::Full::set_color (index, color);
  }
};

static M01::HID::Full          hid;
static Akela::LayeredKeyMap    keyMap ((uint16_t **)keymap, 64);
static M01::Scanner            scanner;
static Example::EventHandler   eventHandler (&hid, &keyMap, &scanner);
static M01::Model01            keyboard (&scanner, &eventHandler);

void
setup () {
  keyboard.setup ();
}

void
loop () {
  keyboard.loop ();
}
