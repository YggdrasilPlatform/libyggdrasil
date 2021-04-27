/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  _____.___.                 .___                    .__.__      *
  *  \__  |   | ____   ____   __| _/___________    _____|__|  |     *
  *   /   |   |/ ___\ / ___\ / __ |\_  __ \__  \  /  ___/  |  |     *
  *   \____   / /_/  > /_/  > /_/ | |  | \// __ \_\___ \|  |  |__   *
  *   / ______\___  /\___  /\____ | |__|  (____  /____  >__|____/   *
  *   \/     /_____//_____/      \/            \/     \/            *
  *                          - Peripherals -                        *
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  @file yggdrasil/peripherals/push_pull_driver.hpp   	        *
  *  @ingroup Peripherals                                           *
  *  @author Fabian Weber, Nikolaij Saegesser						*
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  @brief API to use the 4 push pull driver						*
  *  			                                                    *
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  * This software can be used by students and other personal of the *
  * Bern University of Applied Sciences under the terms of the MIT  *
  * license.                                                        *
  * For other persons this software is under the terms of the GNU   *
  * General Public License version 2.                               *
  *                                                                 *
  * Copyright &copy; 2021, Bern University of Applied Sciences.     *
  * All rights reserved.                                            *
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/

#pragma once

#include <common/attributes.hpp>
#include <common/types.hpp>
#include <common/utils.hpp>

#include "../../Core/Inc/main.h"

#define _USE_MATH_DEFINES
#include <cmath>


namespace bsp::ygg::prph {




	class PushPullDriver {
	public:
		PushPullDriver() = delete;

		/**
		 * @brief
		 */
		enum class Mode {
			GPIO = 1,
			PWM = 2,
			Servo = 3,
		};

		/**
		 * @brief
		 */
		enum class Channel {
			A = 0,
			B = 1,
			C = 2,
			D = 3,
		};

		class Servo{
		public:
			Servo() = delete;

			static bool setDegree(Channel channel, float degrees) {
				if(s_mode[static_cast<u8>(channel)] != Mode::Servo) {
					return false;
				}
				if(degrees > (s_maxRotation / 2)) return false;
				if(degrees < (-s_maxRotation / 2)) return false;


				return true;
			}

			static bool setRadian(Channel channel, float radian) {
				if(s_mode[static_cast<u8>(channel)] != Mode::Servo) {
					return false;
				}
				if(radian > (degToRad(s_maxRotation) / 2)) return false;
				if(radian < (-degToRad(s_maxRotation) / 2)) return false;

				return true;
			}

			static void setMaxRotationDegree(float degrees){s_maxRotation = degrees;}

			static void setMaxRotationRadian(float radian){s_maxRotation = radToDeg(radian);}

		private:
			static inline float s_maxRotation = 180;

			constexpr float radToDeg(float radian) { return radian * 180 / M_PI; }
			constexpr float degToRad(float degrees) { return degrees * M_PI / 180; }
		};

		class PWM{
		public:
			PWM() = delete;
			static void pwmSetDuty(Channel channel, u16 dutyCycle) {
				if(s_mode[static_cast<u8>(channel)] != Mode::PWM){

				}

				return true;
			}

		};

		class Out{
		public:
			Out() = delete;

			static bool set(Channel channel, bool state) {
				if(s_mode[static_cast<u8>(channel)] != Mode::GPIO) {
					return false;
				}


				switch(channel) {
					case Channel::A: DriverA = state; break;
					case Channel::B: DriverB = state; break;
					case Channel::C: DriverC = state; break;
					case Channel::D: DriverC = state; break;
				}
			}

		};

	private:
		static inline u8 s_mode[] = {0,0,0,0};

	};

}
