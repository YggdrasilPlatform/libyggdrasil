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
  *  @file yggdrasil/peripherals/motor_driver.cpp
  *  @ingroup yggdrasil
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief Driver to use the TC78H660FTG DC motor driver
  */

#if defined(YGGDRASIL_PERIPHERAL_DEFS)

	#include <cpp/common/attributes.hpp>
	#include <cpp/common/types.hpp>
	#include <cpp/common/utils.hpp>

	#include <c/yggdrasil/peripherals/motor_driver.h>
	#include <yggdrasil.h>


	using MotorDriver = bsp::ygg::prph::MotorDriver;

	C_LINKAGE void yggdrasil_MotorDriver_Init() {
		MotorDriver::init();
	}

	C_LINKAGE void yggdrasil_MotorDriver_Standby(bool stby) {
		MotorDriver::standby(stby);
	}

	C_LINKAGE void yggdrasil_MotorDriver_SetSpeed(MotorDriverChannel channel, float speed) {
		MotorDriver::setSpeed(static_cast<MotorDriver::Channel>(channel), speed);
	}

	C_LINKAGE bool yggdrasil_MotorDriver_GetError() {
		return MotorDriver::getError();
	}


#endif
