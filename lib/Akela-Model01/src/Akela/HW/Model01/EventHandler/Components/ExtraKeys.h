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

#define CC(n) (M01::SYSFN::CONSUMER + (n))
#define SC(n) (M01::SYSFN::SYSTEM + (n))

enum {
  CC_MUTE = CC(HID_CONSUMER_MUTE),
  CC_VUP  = CC(HID_CONSUMER_VOLUME_INCREMENT),
  CC_VDN  = CC(HID_CONSUMER_VOLUME_DECREMENT),
  CC_PLPS = CC(HID_CONSUMER_PLAY_SLASH_PAUSE),
  CC_STOP = CC(HID_CONSUMER_STOP),
  CC_PRV  = CC(HID_CONSUMER_SCAN_PREVIOUS_TRACK),
  CC_NXT  = CC(HID_CONSUMER_SCAN_NEXT_TRACK),
  CC_EJT  = CC(HID_CONSUMER_EJECT),

  SC_SLP  = SC(HID_SYSTEM_SLEEP),
};

namespace M01 {
  namespace EventHandler {
    class ExtraKeysComponent : public Akela::EventHandler::Component {
    protected:
      virtual bool press (Akela::AbstractHID *HID,
                          Akela::KeyMap *keymap,
                          uint8_t index,
                          uint16_t keycode);

      virtual bool release (Akela::AbstractHID *HID,
                            Akela::KeyMap *keymap,
                            uint8_t index,
                            uint16_t keycode);
    };
  };
};
