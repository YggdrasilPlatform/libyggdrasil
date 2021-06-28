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
  *  @file c/yggdrasil/peripherals/humidity_sensor.cpp
  *  @ingroup yggdrasil
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief Driver to use the SHT40-AD1B-R2 humidity sensor
  */

#if defined(YGGDRASIL_PERIPHERAL_DEFS)

	#include <cpp/common/attributes.hpp>
	#include <cpp/common/types.hpp>
	#include <cpp/common/utils.hpp>

	#include <c/yggdrasil/peripherals/humidity_sensor.h>
	#include <yggdrasil.h>


	using HumiditySensor = bsp::ygg::prph::HumiditySensor;

	C_LINKAGE void yggdrasil_HumiditySensor_Init() {
		HumiditySensor::init();
	}

	C_LINKAGE float yggdrasil_HumiditySensor_GetTemperature(HumiditySensorPrecision precision) {
		return HumiditySensor::getTemperature(static_cast<HumiditySensor::Precision>(precision));
	}

	C_LINKAGE float yggdrasil_HumiditySensor_GetHumidity(HumiditySensorPrecision precision) {
		return HumiditySensor::getHumidity(static_cast<HumiditySensor::Precision>(precision));
	}

	C_LINKAGE void yggdrasil_HumiditySensor_EnableHeater(HumiditySensorHeat level) {
		HumiditySensor::enableHeater(static_cast<HumiditySensor::Heat>(level));
	}


#endif
