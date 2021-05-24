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
  *  @file yggdrasil/peripherals/pressure_sensor.cpp
  *  @ingroup yggdrasil
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief Driver to use the LPS22HBTR pressure sensor
  */

#if defined(YGGDRASIL_PERIPHERAL_DEFS)

	#include <cpp/common/attributes.hpp>
	#include <cpp/common/types.hpp>
	#include <cpp/common/utils.hpp>

	#include <c/yggdrasil/peripherals/push_pull_driver.h>
	#include <yggdrasil.h>


	using PushPullDriver = bsp::ygg::prph::PushPullDriver;

	C_LINKAGE void yggdrasil_PushPullDriver_Servo_Set(PushPullDriverChannel channel, float percent) {
		PushPullDriver::Servo::set(static_cast<PushPullDriver::Channel>(channel), percent);
	}

	C_LINKAGE void yggdrasil_PushPullDriver_Servo_SetDeltaHighTime(PushPullDriverChannel channel, u16 delta) {
		PushPullDriver::Servo::setDeltaHighTime(static_cast<PushPullDriver::Channel>(channel), delta);
	}


	C_LINKAGE void yggdrasil_PushPullDriver_PWM_SetDuty(PushPullDriverChannel channel, float dutyCycle) {
		PushPullDriver::PWM::setDuty(static_cast<PushPullDriver::Channel>(channel), dutyCycle);
	}

	C_LINKAGE bool yggdrasil_PushPullDriver_PWM_SetFrequency(u32 frequency, u16 resolution) {
		return PushPullDriver::PWM::setFrequency(frequency, resolution);
	}

	C_LINKAGE u32 yggdrasil_PushPullDriver_PWM_GetFrequency() {
		return PushPullDriver::PWM::getFrequency();
	}


	C_LINKAGE void yggdrasil_PushPullDriver_Out_Set(PushPullDriverChannel channel, bool state) {
		PushPullDriver::Out::set(static_cast<PushPullDriver::Channel>(channel), state);
	}


#endif
