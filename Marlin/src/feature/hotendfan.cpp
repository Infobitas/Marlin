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

#include "../inc/MarlinConfig.h"

#if ENABLED(USE_HOTEND_FAN)

#include "hotendfan.h"
#include "../module/stepper.h"

HotendFan hotendFan;
uint8_t HotendFan::speed;

#if ENABLED(HOTEND_FAN_EDITABLE)
  hotendFan_settings_t HotendFan::settings; // {0}
#else
   const hotendFan_settings_t &HotendFan::settings = hotendFan_defaults;
#endif

void HotendFan::setup() {
  //SET_OUTPUT(HOTEND_FAN_PIN);
  init();
}

void HotendFan::set_fan_speed(const uint8_t s) {
  speed = s < (HOTENDFAN_SPEED_MIN) ? 0 : s; // Fan OFF below minimum
}

void HotendFan::update() {
  
  static millis_t nextMotorCheck = 0; // Last time the state was checked
  const millis_t ms = millis();  
  
  if (ELAPSED(ms, nextMotorCheck)) {
    nextMotorCheck = ms + 2500UL; // Not a time critical function, so only check every 2.5s  

    // Fan Settings. Set fan > 0:
    set_fan_speed(
       settings.active_speed
    );

    speed = CALC_FAN_SPEED(speed);

    if (PWM_PIN(HOTEND_FAN_PIN))
        hal.set_pwm_duty(pin_t(HOTEND_FAN_PIN), speed);
    else
        WRITE(HOTEND_FAN_PIN, speed > 0);

  }
}

#endif // USE_HOTEND_FAN
