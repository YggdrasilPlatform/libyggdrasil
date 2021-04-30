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
			uninitialised = 0,
			GPIO = 1,
			PWM = 2,
			Servo = 3,
		};

		/**
		 * @brief
		 */
		enum class Channel {
			_chA = 0,
			_chB = 1,
			_chC = 2,
			_chD = 3,
		};

		class Servo{
		public:
			Servo() = delete;

			static void init(Channel channel, float delta_ms = 600){
				checkMode(channel);
				s_Delta_ms[static_cast<u8>(channel)] = delta_ms;
			}

			static void set(Channel channel, float percent) {
				checkMode(channel);

				if(percent > 100) percent = 100;
				else if(percent < -100) percent = -100;

				float dutyCycle = ((Midposition_ms + ((s_Delta_ms[static_cast<u8>(channel)] / 100.0F) * percent)) / Tpwm_ms) * 100.0F;

				switch(channel){
				case Channel::_chA:
					bsp::TimerDCHA.setDutyCycle(dutyCycle);
					break;
				case Channel::_chB:
					bsp::TimerDCHB.setDutyCycle(dutyCycle);
					break;
				case Channel::_chC:
					bsp::TimerDCHC.setDutyCycle(dutyCycle);
					break;
				case Channel::_chD:
					bsp::TimerDCHD.setDutyCycle(dutyCycle);
					break;
				}


			}

			static void setDeltaHighTime(Channel channel, float delta_ms) {
				s_Delta_ms[static_cast<u8>(channel)] = delta_ms;
			}


		private:
			static inline std::array s_Delta_ms = {600, 600, 600, 600};
			constexpr static inline u16 Midposition_ms	= 1500;
			constexpr static inline u16 Tpwm_ms	= 20000;

			static float radToDeg(float radian) { return radian * 180 / M_PI; }
			static float degToRad(float degrees) { return degrees * M_PI / 180; }

			static void checkMode(Channel channel){
				if(s_mode[static_cast<u8>(channel)] != Mode::Servo) {
					if(bsp::TimerD::getPwmFrequency() != 50){
						bsp::TimerD::setPwmFrequency(50,40000);
					}
					switch(channel){
					case Channel::_chA:
						bsp::TimerDCHA.startPwm();
						break;
					case Channel::_chB:
						bsp::TimerDCHB.startPwm();
						break;
					case Channel::_chC:
						bsp::TimerDCHC.startPwm();
						break;
					case Channel::_chD:
						bsp::TimerDCHD.startPwm();
						break;
					}
					s_mode[static_cast<u8>(channel)] = Mode::Servo;
				}
			}
		};

		class PWM{
		public:
			PWM() = delete;
			static void setDuty(Channel channel, u16 dutyCycle) {
				if(s_mode[static_cast<u8>(channel)] != Mode::PWM){

				}
			}

		private:


		};

		class Out{
		public:
			Out() = delete;

			static bool set(Channel channel, bool state) {
				if(s_mode[static_cast<u8>(channel)] != Mode::GPIO) {
					return false;
				}


				switch(channel) {
					case Channel::_chA: DriverA = state; break;
					case Channel::_chB: DriverB = state; break;
					case Channel::_chC: DriverC = state; break;
					case Channel::_chD: DriverC = state; break;
				}
			}

		};

	private:
		static inline std::array s_mode = {Mode::uninitialised,Mode::uninitialised,Mode::uninitialised,Mode::uninitialised};

	};

}
