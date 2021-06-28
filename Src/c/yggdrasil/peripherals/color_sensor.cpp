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
  *  @file c/yggdrasil/peripherals/color_sensor.cpp
  *  @ingroup yggdrasil
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief Driver to use the TCS3472 color sensor
  */

#if defined(YGGDRASIL_PERIPHERAL_DEFS)

	#include <cpp/common/attributes.hpp>
	#include <cpp/common/types.hpp>
	#include <cpp/common/utils.hpp>

	#include <c/yggdrasil/peripherals/color_sensor.h>

	#include <yggdrasil.h>


	using ColorSensor = bsp::ygg::prph::ColorSensor;

	C_LINKAGE bool yggdrasil_ColorSensor_Init(void) {
		return ColorSensor::init();
	}

	C_LINKAGE void yggdrasil_ColorSensor_SetIntegrationTime(ColorSensorIntegrationTime integrationTime) {
		ColorSensor::setIntergrationTime(static_cast<ColorSensor::IntegrationTime>(integrationTime));
	}

	C_LINKAGE void yggdrasil_ColorSensor_SetGain(ColorSensorGain gain) {
		return ColorSensor::setGain(static_cast<ColorSensor::Gain>(gain));
	}

	C_LINKAGE void yggdrasil_ColorSensor_Enable(void) {
		ColorSensor::enable();
	}

	C_LINKAGE void yggdrasil_ColorSensor_Disable(void) {
		ColorSensor::disable();
	}

	C_LINKAGE u16 yggdrasil_ColorSensor_StartConversion(void) {
		return ColorSensor::startConversion();
	}

	C_LINKAGE bool yggdrasil_ColorSensor_IsDone(void) {
		return ColorSensor::isDone();
	}

	C_LINKAGE RGBA8 yggdrasil_ColorSensor_GetColor8(bool restartConversion) {
		RGBA8 ret;
		auto color = ColorSensor::getColor8(restartConversion);

		ret.rgba = color.rgba;

		return ret;
	}

	C_LINKAGE RGBA16 yggdrasil_ColorSensor_GetColor16(bool restartConversion) {
		RGBA16 ret;
		auto color = ColorSensor::getColor16(restartConversion);

		ret.rgba = color.rgba;

		return ret;
	}

#endif
