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

namespace M01 {
  enum {
    SYSFN_CONSUMER     = Akela::SYSFN_SAFE,
    SYSFN_CONSUMER_MAX = Akela::SYSFN_SAFE + 256
  };

  enum {
    SYSFN_SYSTEM       = SYSFN_CONSUMER_MAX + 1,
    SYSFN_SYSTEM_MAX   = SYSFN_CONSUMER_MAX + 257
  };

  enum {
    SYSFN_MOUSE_BUTTON     = SYSFN_SYSTEM_MAX + 1,
    SYSFN_MOUSE_BUTTON_MAX = SYSFN_SYSTEM_MAX + 9,
  };

  enum {
    SYSFN_MOUSE_CONTROL     = SYSFN_MOUSE_BUTTON_MAX + 1,
    SYSFN_MOUSE_CONTROL_MAX = SYSFN_MOUSE_BUTTON_MAX + 256
  };

  enum {
    SYSFN_MODEL01      = Akela::SYSFN_SAFE,
    SYSFN_MODEL01_SAFE = SYSFN_MOUSE_CONTROL_MAX + 1,
  };
};

#define CC(n) (M01::SYSFN_CONSUMER + (n))
#define SC(n) (M01::SYSFN_SYSTEM + (n))
#define MC(n) (M01::SYSFN_MOUSE_CONTROL + (n))
#define MB(n) (M01::SYSFN_MOUSE_BUTTON + (n))

#define _MOUSE_UP            B0000001
#define _MOUSE_DOWN          B0000010
#define _MOUSE_LEFT          B0000100
#define _MOUSE_RIGHT         B0001000
#define _MOUSE_CENTER        B0010000
#define _MOUSE_WARP          B0100000
#define _MOUSE_WARP_END      B1000000

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

  MB_LFT  = MB(M01::HID::Mouse::Button::MB_LEFT),
  MB_RGT  = MB(M01::HID::Mouse::Button::MB_RIGHT),
  MB_MID  = MB(M01::HID::Mouse::Button::MB_MID),

  MM_UPL  = MC(_MOUSE_UP | _MOUSE_LEFT),
  MM_UP   = MC(_MOUSE_UP),
  MM_UPR  = MC(_MOUSE_UP | _MOUSE_RIGHT),
  MM_L    = MC(_MOUSE_LEFT),
  MM_R    = MC(_MOUSE_RIGHT),
  MM_DNL  = MC(_MOUSE_DOWN | _MOUSE_LEFT),
  MM_DN   = MC(_MOUSE_DOWN),
  MM_DNR  = MC(_MOUSE_DOWN | _MOUSE_RIGHT),

  MW_NW   = MC(_MOUSE_WARP | _MOUSE_UP | _MOUSE_LEFT),
  MW_NE   = MC(_MOUSE_WARP | _MOUSE_UP | _MOUSE_RIGHT),
  MW_SW   = MC(_MOUSE_WARP | _MOUSE_DOWN | _MOUSE_LEFT),
  MW_SE   = MC(_MOUSE_WARP | _MOUSE_DOWN | _MOUSE_RIGHT),
  MW_END  = MC(_MOUSE_WARP | _MOUSE_WARP_END)
};

namespace M01 {
  class EventHandler : public Akela::LayerEventHandler, public LedControl {
  private:
    virtual void mouseMove (uint8_t key);
  public:
    EventHandler (Akela::AbstractHID *HID, Akela::LayeredKeyMap *keymap,
                  Scanner *scanner);

    virtual void press (uint8_t index);
    virtual void release (uint8_t index);
    virtual void hold (uint8_t index);

    virtual void setup ();
  };
};
