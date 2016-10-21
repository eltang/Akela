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

/*
 * Portions of this file were adapted from KeyboardioFirmware[0], which is
 * Copyright (C) 2013-2016 Keyboardio, inc, and under the GNU General Public
 * License, version 2 or later.
 *
 * [0]: https://github.com/keyboardio/KeyboardioFirmware
 */

#include "Akela/HW/Model01.h"

M01::MouseControl::MouseControl () {
}

void
M01::MouseControl::setup () {
  Mouse.begin ();
  AbsoluteMouse.begin ();
}

void
M01::MouseControl::press (M01::MouseControl::Button button) {
  Mouse.press (button);
  end_warping ();
}

void
M01::MouseControl::release (M01::MouseControl::Button button) {
  Mouse.release (button);
}

void
M01::MouseControl::move (int8_t x, int8_t y) {
  if (x != 0 || y != 0) {
    mouseActiveForCycles++;

    double accel = (double) acceleration (mouseActiveForCycles);
    float moveX = 0;
    float moveY = 0;

    if (x > 0) {
      moveX = (x * accel) + carriedOverX;
      carriedOverX = moveX - floor (moveX);
    } else if (x < 0) {
      moveX = (x * accel) - carriedOverX;
      carriedOverX = ceil (moveX) - moveX;
    }

    if (y > 0) {
      moveY = (y * accel) + carriedOverY;
      carriedOverY = moveY - floor (moveY);
    } else if (y < 0) {
      moveY = (y * accel) - carriedOverY;
      carriedOverY = ceil (moveY) - moveY;
    }
    end_warping ();

    Mouse.move (moveX, moveY, 0);
  } else {
    mouseActiveForCycles = 0;
  }
}

void
M01::MouseControl::warp (uint8_t warp_cmd) {
  if (is_warping == false) {
    begin_warping ();
  }

  if (warp_cmd & WARP_END) {
    end_warping ();
    return;
  }

  next_width = next_width / 2;
  next_height = next_height / 2;

  if (warp_cmd & WARP_UP) {
  } else if (warp_cmd & WARP_DOWN) {
    section_top  = section_top + next_height;
  }

  if (warp_cmd & WARP_LEFT) {
  } else if (warp_cmd & WARP_RIGHT) {
    section_left  = section_left + next_width;
  }

  warp_jump (section_left, section_top, next_height, next_width);
}

// ------------

// apparently, the mac discards 15% of the value space for mouse movement.
// need to test this on other platforms

#define MAX_WARP_WIDTH 32767
#define MAX_WARP_HEIGHT 32767

#define WARP_ABS_TOP 0
#define WARP_ABS_LEFT 0

// Mouse acceleration

// we want the whole s curve, not just the bit
// that's usually above the x and y axes;
#define ATAN_LIMIT 1.57079633
#define ACCELERATION_FLOOR 0.25
#define ACCELERATION_MULTIPLIER 5
#define  ACCELERATION_RUNWAY 5
// Climb speed is how fast we get to max speed
// 1 is "instant"
// 0.05 is just right
// 0.001 is insanely slow

#define ACCELERATION_CLIMB_SPEED  0.05

void
M01::MouseControl::warp_jump (long left, long top, long height, long width) {
  long x_center = left + width / 2;
  long y_center = top + height / 2;
  AbsoluteMouse.moveTo (x_center, y_center);
}

void
M01::MouseControl::begin_warping () {
  section_left = WARP_ABS_LEFT;
  section_top = WARP_ABS_TOP;
  next_width = MAX_WARP_WIDTH;
  next_height = MAX_WARP_HEIGHT;
  is_warping = true;
}

void
M01::MouseControl::end_warping () {
  is_warping= false;
}

double
M01::MouseControl::acceleration (double cycles) {
  double accel = (atan ((cycles * ACCELERATION_CLIMB_SPEED) - ACCELERATION_RUNWAY) + ATAN_LIMIT) *
    ACCELERATION_MULTIPLIER;
  if (accel < ACCELERATION_FLOOR) {
    accel = ACCELERATION_FLOOR;
  }
  return accel;
}
