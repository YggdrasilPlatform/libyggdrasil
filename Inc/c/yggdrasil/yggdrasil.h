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

#include <c/yggdrasil/types.h>

#if defined(YGGDRASIL_PERIPHERAL_DEFS)

	#include <c/yggdrasil/peripherals/color_sensor.h>
	#include <c/yggdrasil/peripherals/humidity_sensor.h>
	#include <c/yggdrasil/peripherals/joystick.h>
	#include <c/yggdrasil/peripherals/motor_driver.h>
	#include <c/yggdrasil/peripherals/pressure_sensor.h>
	#include <c/yggdrasil/peripherals/sink_driver.h>
	#include <c/yggdrasil/peripherals/rgb_matrix.h>
	#include <c/yggdrasil/peripherals/rtc.h>
	#include <c/yggdrasil/peripherals/seven_segment.h>
	#include <c/yggdrasil/peripherals/six_axis_sensor.h>

#endif
