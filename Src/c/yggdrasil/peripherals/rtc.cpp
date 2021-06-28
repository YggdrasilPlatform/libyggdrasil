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

	#include <c/yggdrasil/peripherals/rtc.h>
	#include <yggdrasil.h>


	using RealTimeClock = bsp::ygg::prph::RealTimeClock;

	C_LINKAGE bool yggdrasil_RealTimeClock_Init(void) {
		return RealTimeClock::init();
	}

	C_LINKAGE time_t yggdrasil_RealTimeClock_GetTime(void) {
		return RealTimeClock::getTime();
	}

	C_LINKAGE void yggdrasil_RealTimeClock_SetTime(time_t time) {
		return RealTimeClock::setTime(time);
	}

#endif
