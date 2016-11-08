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

#define MC(n) (M01::SYSFN::MOUSE_CONTROL + (n))
#define MB(n) (M01::SYSFN::MOUSE_BUTTON + (n))

#define _MOUSE_UP            B0000001
#define _MOUSE_DOWN          B0000010
#define _MOUSE_LEFT          B0000100
#define _MOUSE_RIGHT         B0001000
#define _MOUSE_CENTER        B0010000
#define _MOUSE_WARP          B0100000
#define _MOUSE_WARP_END      B1000000

enum {
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
  namespace EventHandler {
    class MouseComponent : public Akela::EventHandler::Component {
    private:
      void move (M01::HID::Base *HID, uint8_t key);

    protected:
      virtual bool register_code (Akela::AbstractHID *HID,
                                  Akela::KeyMap::Abstract *keymap,
                                  uint16_t keycode);

      virtual bool unregister_code (Akela::AbstractHID *HID,
                                    Akela::KeyMap::Abstract *keymap,
                            uint16_t keycode);

      virtual bool hold_code (Akela::AbstractHID *HID,
                              Akela::KeyMap::Abstract *keymap,
                              uint16_t keycode);
    };
  };
};
