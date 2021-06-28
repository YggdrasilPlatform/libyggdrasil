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
  *  @brief Driver to use the LPS22HBTR pressure sensor
  */

#if defined(YGGDRASIL_PERIPHERAL_DEFS)

	#include <cpp/common/attributes.hpp>
	#include <cpp/common/types.hpp>
	#include <cpp/common/utils.hpp>

	#include <c/yggdrasil/peripherals/motor_driver.h>
	#include <yggdrasil.h>


	using PressureSensor = bsp::ygg::prph::PressureSensor;

	C_LINKAGE void yggdrasil_PressureSensor_Init(void) {
		PressureSensor::init();
	}

	C_LINKAGE float yggdrasil_PressureSensor_GetPressure(void) {
		return PressureSensor::getPressure();
	}

	C_LINKAGE float yggdrasil_PressureSensor_GetTemperature(void) {
		return PressureSensor::getTemperature();
	}


#endif
