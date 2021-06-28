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
  *  @file c/yggdrasil/peripherals/humidity_sensor.cpp
  *  @ingroup yggdrasil
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief Driver to use the SHT40-AD1B-R2 humidity sensor
  */

#if defined(YGGDRASIL_PERIPHERAL_DEFS)

	#include <cpp/common/attributes.hpp>
	#include <cpp/common/types.hpp>
	#include <cpp/common/utils.hpp>

	#include <c/yggdrasil/peripherals/joystick.h>
	#include <yggdrasil.h>


	using Joystick = bsp::ygg::prph::Joystick;

	C_LINKAGE ::JoystickData yggdrasil_Joystick_GetLeft() {
		::JoystickData result;

		auto joystickData = Joystick::getLeft();

		result.mag 		= joystickData.mag;
		result.pos.x 	= joystickData.pos.x;
		result.pos.y 	= joystickData.pos.y;
		result.pressed 	= joystickData.pressed;

		return result;
	}

	C_LINKAGE ::JoystickData yggdrasil_Joystick_GetRight() {
		::JoystickData result;

		auto joystickData = Joystick::getRight();

		result.mag 		= joystickData.mag;
		result.pos.x 	= joystickData.pos.x;
		result.pos.y 	= joystickData.pos.y;
		result.pressed 	= joystickData.pressed;

		return result;
	}

	C_LINKAGE void yggdrasil_Joystick_SetDeadzone(u8 deadzone) {
		Joystick::setDeadzone(deadzone);
	}

	C_LINKAGE u8 yggdrasil_Joystick_GetDeadzone() {
		return Joystick::getDeadzone();
	}


#endif
