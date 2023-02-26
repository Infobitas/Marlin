/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
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
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */
#pragma once

#include "../inc/MarlinConfigPre.h"

typedef struct {
  uint8_t   active_speed;    // 0-255 (fullspeed); Speed with enabled stepper motors
} hotendFan_settings_t;

#ifndef HOTENDFAN_SPEED_ACTIVE
  #define HOTENDFAN_SPEED_ACTIVE 255
#endif


static constexpr hotendFan_settings_t hotendFan_defaults = {
  HOTENDFAN_SPEED_ACTIVE
};

#if ENABLED(USE_HOTEND_FAN)

class HotendFan {
  private:
    static uint8_t speed;
    static void set_fan_speed(const uint8_t s);

  public:
    #if ENABLED(HOTEND_FAN_EDITABLE)
      static hotendFan_settings_t settings;
    #else
      static const hotendFan_settings_t &settings;
    #endif
    static bool state() { return speed > 0; }
    static void init() { reset(); }
    static void reset() { TERN_(HOTEND_FAN_EDITABLE, settings = hotendFan_defaults); }
    static void setup();
    static void update();
};

extern HotendFan hotendFan;

#endif
