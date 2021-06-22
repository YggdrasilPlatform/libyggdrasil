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
  *  @file cpp/yggdrasil/peripherals/sink_driver.hpp
  *  @ingroup yggdrasil
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief Driver to use the sink drivers
  */

#pragma once

#include <cpp/common/attributes.hpp>
#include <cpp/common/types.hpp>
#include <cpp/common/utils.hpp>

namespace bsp::ygg::prph {


	/**
	 * @brief Sink driver containing classes to use the driver as GPIO, as PWM Module or as Servo port
	 */
	class SinkDriver {
	public:
		SinkDriver() = delete;

		/**
		 * @brief Initialization function
		 *
		 * @return always true
		 */
		static bool init() {
			return true;
		}

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
		class Servo {
		public:
			Servo() = delete;

			/**
			 * @brief Set the servo arm rotation in percent relative to its maximal value
			 * @note The needed high period of pwm signal to reach maximal magnitude can
			 * be configured with the setDeltaHighTime() function (This is servo specific)
			 * @warning If the system clock is not 216MHz the function might not be able to set the pwm frequency to 50Hz
			 *
			 * @param channel Channel which should be changed
			 * @param percent Servo arm rotation in percent from -100% to 100%
			 */
			static void set(Channel channel, float percent) {
				if(checkMode(channel) == false) return;				// Chech if the channel is configured as a servo channel

				percent = math::clamp(percent, -100.0F, 100.0F);

				float dutyCycle = ((MidPosition + ((Servo::s_delta[enumValue(channel)] / 100.0F) * percent)) / TPWM) * 100.0F;	// get the high time in ms and calculate the duty cycle

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
			 * @brief FUnction to set the high time of the pwm pulse
			 *
			 * @param channel Channel which should be changed
			 * @param delta High time of the pwm pulse in ms
			 */
			static void setDeltaHighTime(Channel channel, u16 delta) {
				Servo::s_delta[enumValue(channel)] = delta;
			}


		private:
			static inline std::array s_delta 		= { 600, 600, 600, 600 };		// Delta value for each channel in ms
			constexpr static inline u16 MidPosition	= 1500;							// 1.5ms high time pulse which represents 0° rotation (minimal is MidPosition - Delta, maximal is MidPosition + Delta)
			constexpr static inline u16 TPWM		= 20000;						// Period of the pwm frequency in ms

			/**
			 * @brief Checks if the channel is in servo mode
			 * @note Configures the timer pwm frequency to 50Hz
			 *
			 * @param channel Channel which should be configured
			 * @return True when successful, false when not (this will come from a system clock frequency which is to low)
			 */
			static bool checkMode(Channel channel) {
				if (SinkDriver::s_mode[static_cast<u8>(channel)] != Mode::Servo) {
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

					SinkDriver::s_mode[enumValue(channel)] = Mode::Servo;
				}
				return true;
			}
		};

		/**
		 * @brief Pwm driver
		 * @note When using the Servo port, the PWM frequency for all channels will be set to 50Hz
		 * @warning Changing the pwm frequency will not be possible when one channel is used as servo port
		 */
		class PWM{
		public:
			PWM() = delete;

			/*
			 * @brief Set the duty cycle
			 *
			 * @param channel Channel which should be changed
			 * @param dutyCycle Duty cycle
			 */
			static void setDuty(Channel channel, float dutyCycle) {
				if(SinkDriver::s_mode[enumValue(channel)] != Mode::PWM){
					// Set to high active state and start the pwm for the used channel
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
					SinkDriver::s_mode[enumValue(channel)] = Mode::PWM;
				}

				// Set the duty cycle for the used channel
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
			 * @warning When one channel is used as servo port, the frequency can not be changed
			 *
			 * @param f_hz new frequency in hz
			 * @param resolution of the pwm, for 0 the actual value will be used
			 *
			 * @return True when the adjustment was possible, false when the parameter did not match
			 */
			static bool setFrequency(u32 frequency, u16 resolution = 0) {
				for(auto mode : s_mode){
					if(mode == Mode::Servo) return false;
				}
				return bsp::TimerD::setPwmFrequency(frequency, resolution);
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


		/**
		 * @brief GPIO driver
		 */
		class Out{
		public:
			Out() = delete;

			/**
			 * @brief set the sink driver pin state
			 *
			 * @param channel Channel to set
			 * @param state Pin state
			 */
			static void set(Channel channel, bool state) {
				if(SinkDriver::s_mode[enumValue(channel)] != Mode::GPIO) {

					// Enable the pwm and set the duty cycle to 0
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

					SinkDriver::s_mode[enumValue(channel)] = Mode::GPIO;
				}

				// Set the pwm polarity according to the state. Since the duty cycle is 0 this action will result in a always low
				// or always high. A duty of 100% usually is not really 100%
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
