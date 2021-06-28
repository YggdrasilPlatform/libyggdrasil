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
  *  @file c/yggdrasil/peripherals/pressure_sensor.cpp
  *  @ingroup yggdrasil
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief Driver to use the RV-3028-C7 RTC
  */

#if defined(YGGDRASIL_PERIPHERAL_DEFS)

	#include <cpp/common/attributes.hpp>
	#include <cpp/common/types.hpp>
	#include <cpp/common/utils.hpp>

	#include <c/yggdrasil/peripherals/six_axis_sensor.h>
	#include <yggdrasil.h>


	using SixAxisSensor = bsp::ygg::prph::SixAxisSensor;

	C_LINKAGE bool yggdrasil_SixAxisSensor_Init(SixAxisSensorAccelFullScaleRange accelScale, SixAxisSensorGyroFullScaleRange gyroScale, SixAxisSensorAccelOutputDataRange accelOdr, SixAxisSensorGyroOutputDataRange gyroOdr) {
		return SixAxisSensor::init(
				static_cast<SixAxisSensor::AccelFullScaleRange>(accelScale),
				static_cast<SixAxisSensor::GyroFullScaleRange>(gyroScale),
				static_cast<SixAxisSensor::AccelOutputDataRange>(accelOdr),
				static_cast<SixAxisSensor::GyroOutputDataRange>(gyroOdr));
	}

	C_LINKAGE ::Coordinate yggdrasil_SixAxisSensor_GetRotation(void) {
		return bsp::bit_cast<::Coordinate>(SixAxisSensor::getRotation());
	}

	C_LINKAGE struct Coordinate yggdrasil_SixAxisSensor_GetAcceleration(void) {
		return bsp::bit_cast<::Coordinate>(SixAxisSensor::getAcceleration());
	}

	C_LINKAGE float yggdrasil_SixAxisSensor_GetTemperature(void) {
		return SixAxisSensor::getTemperature();
	}

	C_LINKAGE ::Orientation yggdrasil_SixAxisSensor_GetBoardOrientation(void) {
		return bsp::bit_cast<::Orientation>(SixAxisSensor::getBoardOrientation());
	}

#endif
