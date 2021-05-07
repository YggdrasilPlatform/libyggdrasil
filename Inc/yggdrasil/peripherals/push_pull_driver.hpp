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
  *  @file yggdrasil/peripherals/push_pull_driver.hpp
  *  @ingroup yggdrasil
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief Driver to use the IX4310T push-pull drivers
  */

#pragma once

#include <common/attributes.hpp>
#include <common/types.hpp>
#include <common/utils.hpp>

namespace bsp::ygg::prph {


	class PushPullDriver {
	public:
		PushPullDriver() = delete;

		/**
		 * @brief
		 */
		enum class Mode {
			Uninitialised = 0,
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

			static void init(Channel channel, float delta = 600){
				checkMode(channel);
				Servo::s_delta[enumValue(channel)] = delta;
			}

			static void set(Channel channel, float percent) {
				checkMode(channel);

				if(percent > 100) percent = 100;
				else if(percent < -100) percent = -100;

				float dutyCycle = ((MidPosition + ((Servo::s_delta[enumValue(channel)] / 100.0F) * percent)) / TPWM) * 100.0F;

				switch(channel){
				case Channel::A:
					bsp::TimerDCHA.setDutyCycle(dutyCycle);
					break;
				case Channel::B:
					bsp::TimerDCHB.setDutyCycle(dutyCycle);
					break;
				case Channel::C:
					bsp::TimerDCHC.setDutyCycle(dutyCycle);
					break;
				case Channel::D:
					bsp::TimerDCHD.setDutyCycle(dutyCycle);
					break;
				}


			}

			static void setDeltaHighTime(Channel channel, float delta) {
				Servo::s_delta[static_cast<u8>(channel)] = delta;
			}


		private:
			static inline std::array s_delta 		= { 600, 600, 600, 600 };
			constexpr static inline u16 MidPosition	= 1500;
			constexpr static inline u16 TPWM		= 20000;

			static void checkMode(Channel channel) {
				if (PushPullDriver::s_mode[static_cast<u8>(channel)] != Mode::Servo) {
					if (bsp::TimerD::getPwmFrequency() != 50) {
						bsp::TimerD::setPwmFrequency(50,40000);
					}

					switch(channel){
						case Channel::A:
							bsp::TimerDCHA.startPwm();
							break;
						case Channel::B:
							bsp::TimerDCHB.startPwm();
							break;
						case Channel::C:
							bsp::TimerDCHC.startPwm();
							break;
						case Channel::D:
							bsp::TimerDCHD.startPwm();
							break;
					}

					PushPullDriver::s_mode[enumValue(channel)] = Mode::Servo;
				}
			}
		};

		class PWM{
		public:
			PWM() = delete;
			static void setDuty(Channel channel, u16 dutyCycle) {
				if(PushPullDriver::s_mode[enumValue(channel)] != Mode::PWM){

				}
			}

		private:


		};

		class Out{
		public:
			Out() = delete;

			static bool set(Channel channel, bool state) {
				if(PushPullDriver::s_mode[enumValue(channel)] != Mode::GPIO) {
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
		static inline std::array s_mode = { Mode::Uninitialised,Mode::Uninitialised,Mode::Uninitialised,Mode::Uninitialised };

	};

}
