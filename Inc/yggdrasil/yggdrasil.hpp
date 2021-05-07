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
  *  @file yggdrasil/yggdrasil.hpp
  *  @ingroup yggdrasil
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief Top-level include file for yggdrasil
  */

#pragma once

#include <yggdrasil/types.hpp>

#if defined(YGGDRASIL_PERIPHERAL_DEFS)

	namespace bsp::ygg {

		constexpr static inline auto NoData = std::array<u8, 0>{ };

	}

	#include <yggdrasil/peripherals/six_axis_sensor.hpp>
	#include <yggdrasil/peripherals/color_sensor.hpp>
	#include <yggdrasil/peripherals/humidity_sensor.hpp>
	#include <yggdrasil/peripherals/pressure_sensor.hpp>
	#include <yggdrasil/peripherals/joystick.hpp>
	#include <yggdrasil/peripherals/rtc.hpp>
	#include <yggdrasil/peripherals/seven_segment.hpp>
	#include <yggdrasil/peripherals/rgb_matrix.hpp>
	#include <yggdrasil/peripherals/motor_driver.hpp>
	#include <yggdrasil/peripherals/push_pull_driver.hpp>

#endif
