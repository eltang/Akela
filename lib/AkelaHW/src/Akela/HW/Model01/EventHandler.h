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

#include "Akela.h"

#define MOD_FN_USER_CC 0x2000
#define MOD_FN_USER_SC 0x1000

#define CC(n) FN(n | MOD_FN_USER | MOD_FN_USER_CC)
#define SC(n) FN(n | MOD_FN_USER | MOD_FN_USER_SC)

#define CHECK_USER(kc,u) (CHECK_FN (kc, USER) && (kc & MOD_FN_USER_ ## u))

enum {
  CC_MUTE = CC(HID_CONSUMER_MUTE),
  CC_VUP  = CC(HID_CONSUMER_VOLUME_INCREMENT),
  CC_VDN  = CC(HID_CONSUMER_VOLUME_DECREMENT),
  CC_PLPS = CC(HID_CONSUMER_PLAY_SLASH_PAUSE),
  CC_STOP = CC(HID_CONSUMER_STOP),
  CC_PRV  = CC(HID_CONSUMER_SCAN_PREVIOUS_TRACK),
  CC_NXT  = CC(HID_CONSUMER_SCAN_NEXT_TRACK),
  CC_EJT  = CC(HID_CONSUMER_EJECT),

  SC_SLP  = SC(HID_SYSTEM_SLEEP)
};

class M01EventHandler : public AkelaLayerEventHandler {
 public:
  M01EventHandler (AkelaAbstractHID *HID, AkelaLayeredKeyMap *keymap);

  virtual bool press (uint8_t index);
  virtual bool release (uint8_t index);
};
