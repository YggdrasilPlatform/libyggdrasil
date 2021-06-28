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
  *  @file c/yggdrasil/peripherals/sink_driver.cpp
  *  @ingroup yggdrasil
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief Driver to use the sink driver
  */

#if defined(YGGDRASIL_PERIPHERAL_DEFS)

	#include <cpp/common/attributes.hpp>
	#include <cpp/common/types.hpp>
	#include <cpp/common/utils.hpp>

	#include <c/yggdrasil/peripherals/sink_driver.h>
	#include <yggdrasil.h>


	using SinkDriver = bsp::ygg::prph::SinkDriver;

	C_LINKAGE void yggdrasil_SinkDriver_Init(void) {
		SinkDriver::init();
	}

	C_LINKAGE void yggdrasil_SinkDriver_Servo_Set(SinkDriverChannel channel, float percent) {
		SinkDriver::Servo::set(static_cast<SinkDriver::Channel>(channel), percent);
	}

	C_LINKAGE void yggdrasil_SinkDriver_Servo_SetDeltaHighTime(SinkDriverChannel channel, u16 delta) {
		SinkDriver::Servo::setDeltaHighTime(static_cast<SinkDriver::Channel>(channel), delta);
	}


	C_LINKAGE void yggdrasil_SinkDriver_PWM_SetDuty(SinkDriverChannel channel, float dutyCycle) {
		SinkDriver::PWM::setDuty(static_cast<SinkDriver::Channel>(channel), dutyCycle);
	}

	C_LINKAGE bool yggdrasil_SinkDriver_PWM_SetFrequency(u32 frequency, u16 resolution) {
		return SinkDriver::PWM::setFrequency(frequency, resolution);
	}

	C_LINKAGE u32 yggdrasil_SinkDriver_PWM_GetFrequency(enum SinkDriverChannel channel) {
		return SinkDriver::PWM::getFrequency(static_cast<SinkDriver::Channel>(channel));
	}


	C_LINKAGE void yggdrasil_SinkDriver_Out_Set(SinkDriverChannel channel, bool state) {
		SinkDriver::Out::set(static_cast<SinkDriver::Channel>(channel), state);
	}


#endif
