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
  *  @file cpp/yggdrasil/peripherals/step_motor_driver.hpp
  *  @ingroup yggdrasil
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief Driver to use the TC78H660FTG step motor driver
  */

#pragma once

#include <cpp/common/attributes.hpp>
#include <cpp/common/types.hpp>
#include <cpp/common/utils.hpp>

#include <cstdlib>
#include <cstdio>


namespace bsp::ygg::prph {

	/**
	 * @brief Step Motor driver driver TC78H660FTG
	 */
	class StepMotorDriver {
	public:
		StepMotorDriver() = delete;






		/**
		 * @brief
		 *
		 * @param
		 * @param
		 */
		static void setSteps(u16 rpm, u32 steps) {

		}

		/**
		 * @brief get the Status from the motor driver
		 *
		 * @return false when no error occurring, true when in thermal shutdown (TSD) or over current (ISD)
		 */
		static bool getError() {
			return TC78Err;
		}

	private:

		u32 m_step = 0;

		static void incrementStep() {
			m_step++;
		}

	};

}
