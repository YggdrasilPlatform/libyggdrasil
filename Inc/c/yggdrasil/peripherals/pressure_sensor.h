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
  *  @file c/yggdrasil/peripherals/pressure_sensor.h
  *  @ingroup yggdrasil
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief Driver to use the LPS22HBTR pressure sensor
  */

#pragma once

#include <c/yggdrasil/types.h>

/**
 * @brief Initializes the LPS22HBTR pressure sensor
 *
 * @return True when the connected device matched the device id, false when not
 */
C_LINKAGE void yggdrasil_PressureSensor_Init(void);

/**
 * @brief Get the current air pressure
 *
 * @return Pressure in hPa
 */
C_LINKAGE float yggdrasil_PressureSensor_GetPressure(void);

/**
 * @brief Get the current sensor temperature
 *
 * @return Temperature in °C
 */
C_LINKAGE float yggdrasil_PressureSensor_GetTemperature(void);
