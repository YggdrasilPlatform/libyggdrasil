 /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  _____.___.                 .___                    .__.__      *
  *  \__  |   | ____   ____   __| _/___________    _____|__|  |     *
  *   /   |   |/ ___\ / ___\ / __ |\_  __ \__  \  /  ___/  |  |     *
  *   \____   / /_/  > /_/  > /_/ | |  | \// __ \_\___ \|  |  |__   *
  *   / ______\___  /\___  /\____ | |__|  (____  /____  >__|____/   *
  *   \/     /_____//_____/      \/            \/     \/            *
  *                         - Yggdrasil -                           *
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  * This software can be used by students and other personal of the *
  * Bern University of Applied Sciences under the terms of the MIT  *
  * license.                                                        *
  * For other persons this software is under the terms of the GNU   *
  * General Public License version 2.                               *
  *                                                                 *
  * Copyright &copy; 2021, Bern University of Applied Sciences.     *
  * All rights reserved.                                            *
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/**
  *  @file c/yggdrasil/peripherals/humidity_sensor.h
  *  @ingroup yggdrasil
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief Driver to use the SHT40-AD1B-R2 humidity sensor
  */

#pragma once

#include <c/yggdrasil/types.h>

/**
 * @brief Signed position data
 */
struct Position {
  i16 x;		///< X Axis
  i16 y;		///< Y Axis
};

/**
 * @brief Joystick data
 */
struct JoystickData {
  struct Position pos;		///< Position
  u16 mag;			///< Magnitude / radius from the center
  bool pressed;		///< State of the joystick button
};


C_LINKAGE struct JoystickData yggdrasil_Joystick_GetLeft();
C_LINKAGE struct JoystickData yggdrasil_Joystick_GetRight();
C_LINKAGE void yggdrasil_Joystick_SetDeadzone(u8 deadzone);
C_LINKAGE u8 yggdrasil_Joystick_GetDeadzone();

