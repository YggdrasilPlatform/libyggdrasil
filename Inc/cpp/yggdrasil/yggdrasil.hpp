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
  *  @file cpp/yggdrasil/yggdrasil.hpp
  *  @ingroup yggdrasil
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief Top-level include file for yggdrasil
  */

#pragma once

#include <cpp/yggdrasil/types.hpp>

#if defined(YGGDRASIL_PERIPHERAL_DEFS)

	namespace bsp::ygg {

		constexpr auto NoData = std::array<u8, 0>{ };		///< Value to signal certain drivers to not send any data

	}

	#include <cpp/yggdrasil/peripherals/six_axis_sensor.hpp>
	#include <cpp/yggdrasil/peripherals/color_sensor.hpp>
	#include <cpp/yggdrasil/peripherals/humidity_sensor.hpp>
	#include <cpp/yggdrasil/peripherals/pressure_sensor.hpp>
	#include <cpp/yggdrasil/peripherals/joystick.hpp>
	#include <cpp/yggdrasil/peripherals/rtc.hpp>
	#include <cpp/yggdrasil/peripherals/seven_segment.hpp>
	#include <cpp/yggdrasil/peripherals/rgb_matrix.hpp>
	#include <cpp/yggdrasil/peripherals/motor_driver.hpp>
	#include <cpp/yggdrasil/peripherals/sink_driver.hpp>

#endif
