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
  *  @file yggdrasil/peripherals/motor_driver.hpp
  *  @ingroup yggdrasil
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief Driver to use the TC78H660FTG DC motor driver
  */

#pragma once

#include <common/attributes.hpp>
#include <common/types.hpp>
#include <common/utils.hpp>

#include <cstdlib>
#include <cstdio>


namespace bsp::ygg::prph {

	/**
	 * @brief Dual DC Motor driver driver TC78H660FTG
	 */
	class MotorDriver {
	public:
		MotorDriver() = delete;

		/**
		 * @brief Channels
		 */
		enum class Channel : u8 {
			A = 0,		///< Channel A
			B = 1,		///< Channel B
		};

		/**
		 * @brief init function for the motor as a dual channel dc driver
		 * @note this function does start the needed pwm generators
		 */
		static void init() {
			TC78Mode = true;	// Set the mode as dual DC motor driver
			core::delay(1);
			TC78Stby = true;	// Enables the motor driver

			bsp::TimerBCHB.startPwm();
			bsp::TimerBCHC.startPwm();
		}

		/**
		 * @brief set the motor driver to standby
		 *
		 * @param stby True for standby, false for active
		 */
		static void standby(bool stby) {
			if(stby) {
				TC78Stby = false;				// Set the driver to standby

				bsp::TimerBCHB.stopPwm();
				bsp::TimerBCHC.stopPwm();
			}
			else {
				TC78Stby = true;				// Enables the motor driver

				bsp::TimerBCHB.startPwm();
				bsp::TimerBCHC.startPwm();
			}
		}


		/**
		 * @brief Controls the speed and rotation of each channel
		 *
		 * @param ch Channel to set speed
		 * @param speed Speed from -100% o 100% where - does change the rotation direction
		 */
		static void setSpeed(Channel ch, float speed) {
			bool rotation = speed > 0;			// Get the rotation for the selected channel
			speed = std::abs(speed);			// Get the absolute duty for the selected channel

			switch(ch){
			case Channel::A:
				PhaseA = rotation;				// Set the rotation fpr channel A
				TimerBCHB.setDutyCycle(speed);	// Set the pwm for channel A
				break;
			case Channel::B:
				PhaseB = rotation;				// Set the rotation fpr channel B
				TimerBCHC.setDutyCycle(speed);	// Set the pwm for channel B
				break;

			}
		}

		/**
		 * @brief get the Status from the motor driver
		 *
		 * @return false when no error occurring, true when in thermal shutdown (TSD) or over current (ISD)
		 */
		static bool hasError() {
			return TC78Err;
		}

	};

}
