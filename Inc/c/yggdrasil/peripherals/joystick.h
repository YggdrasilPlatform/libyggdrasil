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

/**
 * @brief Initialization function
 *
 * @return Success
 */
C_LINKAGE bool yggdrasil_Joystick_Init(void);

/**
 * @brief Get the joystick data for the left joystick
 *
 * @return JoyStickData struct
 * @note This function is polling
 */
C_LINKAGE struct JoystickData yggdrasil_Joystick_GetLeft();

/**
 * @brief Get the joystick data for the right joystick
 *
 * @return JoyStickData struct
 * @note This function is polling
 */
C_LINKAGE struct JoystickData yggdrasil_Joystick_GetRight();

/**
 * @brief Set both joystick's deadzone
 *
 * @param deadzone Deadzone value
 */
C_LINKAGE void yggdrasil_Joystick_SetDeadzone(u8 deadzone);

/**
 * @brief Get the current Joystick deadzone
 *
 * @return Current deadzone value
 */
C_LINKAGE u8 yggdrasil_Joystick_GetDeadzone(void);

