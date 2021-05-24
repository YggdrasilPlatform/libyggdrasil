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
 * @brief Heater commands for the SHT40-AD1B-R2 sensor
 * @warning Do not use heater for extended periods of time. The heater is designed for a maximal duty cycle of less than 5% when it is periodically heated
 */
enum HumiditySensorHeat {
	HumiditySensorHeat_200mWFor1s	 	= 0x39,		///< 200mW @ 3.3V for 1s
	HumiditySensorHeat_200mWFor0p1s 	= 0x32,		///< 200mW @ 3.3V for 0.1s
	HumiditySensorHeat_110mWFor1s	 	= 0x2F,		///< 110mW @ 3.3V for 1s
	HumiditySensorHeat_110mWFor0p1s 	= 0x24,		///< 110mW @ 3.3V for 0.1s
	HumiditySensorHeat_20mWFor1s	 	= 0x1E,		///< 20mW @ 3.3V for 1s
	HumiditySensorHeat_20mWFor0p1s	= 0x15,		///< 20mW @ 3.3V for 0.1s
};

/**
 * @brief Measurement precision settings for the SHT40-AD1B-R2 sensor
 */
enum HumiditySensorPrecision {
	HumiditySensorPrecision_High 	 	= 0xFD,		///< measure T & RH with High precision (High repeatability)
	HumiditySensorPrecision_Medium  	= 0xF6,		///< measure T & RH with medium precision (medium repeatability)
	HumiditySensorPrecision_Low 		= 0xE0,		///< measure T & RH with lowest precision (low repeatability)
};

C_LINKAGE void yggdrasil_HumiditySensor_Init();
C_LINKAGE float yggdrasil_HumiditySensor_GetTemperature(HumiditySensorPrecision precision);
C_LINKAGE float yggdrasil_HumiditySensor_GetHumidity(HumiditySensorPrecision precision);
C_LINKAGE void yggdrasil_HumiditySensor_EnableHeater(HumiditySensorHeat level);
