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


	/**
	 * @brief Push Pull driver containing classes to use the driver as GPIO, as PWM Module or as Servo port
	 */
	class PushPullDriver {
	public:
		PushPullDriver() = delete;

		/**
		 * @brief Timer Channels
		 */
		enum class Channel {
			A = 0,		///< Timer channel A
			B = 1,		///< Timer channel B
			C = 2,		///< Timer channel C
			D = 3,		///< Timer channel D
		};

		/**
		 * @brief Servo driver
		 * @note When using the Servo port, the PWM frequency for all channels will be set to 50Hz
		 */
		class Servo{
		public:
			Servo() = delete;

			/**
			 * @brief
			 */
			static void set(Channel channel, float percent) {
				if(checkMode(channel) == false) return;

				percent = math::clamp(percent, -100.0F, 100.0F);

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
				Servo::s_delta[enumValue(channel)] = delta;
			}


		private:
			static inline std::array s_delta 		= { 600, 600, 600, 600 };
			constexpr static inline u16 MidPosition	= 1500;
			constexpr static inline u16 TPWM		= 20000;

			static bool checkMode(Channel channel) {
				if (PushPullDriver::s_mode[static_cast<u8>(channel)] != Mode::Servo) {
					if (bsp::TimerD::getPwmFrequency() != 50) {
						if(!bsp::TimerD::setPwmFrequency(50,40000)) return false;
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
				return true;
			}
		};

		class PWM{
		public:
			PWM() = delete;

			static void setDuty(Channel channel, float dutyCycle) {
				if(PushPullDriver::s_mode[enumValue(channel)] != Mode::PWM){
					switch(channel){
					case Channel::A:
						bsp::TimerDCHA.startPwm();
						bsp::TimerDCHA.setPolarityHigh();
						break;
					case Channel::B:
						bsp::TimerDCHB.startPwm();
						bsp::TimerDCHB.setPolarityHigh();
						break;
					case Channel::C:
						bsp::TimerDCHC.startPwm();
						bsp::TimerDCHC.setPolarityHigh();
						break;
					case Channel::D:
						bsp::TimerDCHD.startPwm();
						bsp::TimerDCHD.setPolarityHigh();
						break;
					}
					PushPullDriver::s_mode[enumValue(channel)] = Mode::PWM;
				}

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

			/**
			 * @brief Set the pwm frequency and (optional) the maximal ticks within on cycle for all channels
			 * @note The actual duty cycle for all channels will be restored after the changes
			 * @note Implement a proper error handling, the function does not guarantee to be successful
			 *
			 * @param f_hz new frequency in hz
			 * @param resolution of the pwm, for 0 the actual value will be used
			 *
			 * @return True when the adjustment was possible, false when the parameter did not match
			 */
			static bool setFrequency(u32 f_hz, u16 resolution = 0) {
				for(auto mode : s_mode){
					if(mode == Mode::Servo) return false;
				}
				return bsp::TimerD::setPwmFrequency(f_hz, resolution);
			}

		    /**
		     * @brief Get the pwm frequency
		     * @note The frequency is for all channels the same
		     *
		     * @return Frequency in Hz
		     */
			static u32 getFrequency() {
				return bsp::TimerD::getPwmFrequency();
			}

		};

		class Out{
		public:
			Out() = delete;

			static void set(Channel channel, bool state) {
				if(PushPullDriver::s_mode[enumValue(channel)] != Mode::GPIO) {

					switch(channel){
					case Channel::A:
						bsp::TimerDCHA.startPwm();
						bsp::TimerDCHA.setDutyCycle(0.0F);
						break;
					case Channel::B:
						bsp::TimerDCHB.startPwm();
						bsp::TimerDCHB.setDutyCycle(0.0F);
						break;
					case Channel::C:
						bsp::TimerDCHC.startPwm();
						bsp::TimerDCHC.setDutyCycle(0.0F);
						break;
					case Channel::D:
						bsp::TimerDCHD.startPwm();
						bsp::TimerDCHD.setDutyCycle(0.0F);
						break;
					}

					PushPullDriver::s_mode[enumValue(channel)] = Mode::GPIO;
				}


				switch(channel){
				case Channel::A:
					bsp::TimerDCHA.setPolarityHigh(!state);
					break;
				case Channel::B:
					bsp::TimerDCHB.setPolarityHigh(!state);
					break;
				case Channel::C:
					bsp::TimerDCHC.setPolarityHigh(!state);
					break;
				case Channel::D:
					bsp::TimerDCHD.setPolarityHigh(!state);
					break;
				}

			}

		};

	private:

		/**
		 * @brief Modes for the single pins
		 */
		enum class Mode {
			Uninitialised = 0,		///< The channel is not initialised
			GPIO = 1,				///< The channel is used as GPIO
			PWM = 2,				///< The channel is used as PWM
			Servo = 3,				///< The channel is used as servo port
		};

		static inline std::array s_mode = { Mode::Uninitialised,Mode::Uninitialised,Mode::Uninitialised,Mode::Uninitialised };


	};

}
