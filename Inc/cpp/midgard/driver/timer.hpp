 /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  _____.___.                 .___                    .__.__      *
  *  \__  |   | ____   ____   __| _/___________    _____|__|  |     *
  *   /   |   |/ ___\ / ___\ / __ |\_  __ \__  \  /  ___/  |  |     *
  *   \____   / /_/  > /_/  > /_/ | |  | \// __ \_\___ \|  |  |__   *
  *   / ______\___  /\___  /\____ | |__|  (____  /____  >__|____/   *
  *   \/     /_____//_____/      \/            \/     \/            *
  *                          - Midgard -                            *
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
  *  @file cpp/midgard/driver/timer.hpp
  *  @ingroup midgard
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief Timer Channel abstraction implementation for Midgard
  */

#pragma once

#include <cpp/common/frontend/timer.hpp>

#include <string>
#include <string_view>
#include <array>

#include <cstdlib>

#include <cmsis_gcc.h>
#include <limits>
#include <cstdio>
#include <cmath>
#include <stdio.h>

namespace bsp::mid::drv {

	/**
	 * @brief Timer channel implementation for Midgard
	 * @warning Do not use this on its own!
	 *
	 * @tparam Context Timer context
	 * @tparam Channel Timer channel number
	 * @tparam Size Timer width (16 bit or 32 bit)
	 */
	template<auto Context, u8 Channel, typename Size>
	struct TimerChannel {
		static_assert(Channel >= 1 && Channel <= 4, "Channel index out of range");

		/**
		 * @brief Start PWM generation for the channel
		 * @Note A duty cycle should be set with setDuty()
		 *
		 * @return Success
		 */
		ALWAYS_INLINE bool startPwm() const noexcept {
			if(!hasPwmModule()) return false;
			switch(Channel) {
				case 1: Context->Instance->CCER |= TIM_CCER_CC1E; break;	// Enable capture compare output for channel 1
				case 2: Context->Instance->CCER |= TIM_CCER_CC2E; break;	// Enable capture compare output for channel 2
				case 3: Context->Instance->CCER |= TIM_CCER_CC3E; break;	// Enable capture compare output for channel 3
				case 4: Context->Instance->CCER |= TIM_CCER_CC4E; break;	// Enable capture compare output for channel 4
				default: bsp::unreachable();
			}
			Context->Instance->CR1 = TIM_CR1_CEN;							// Enable the counter
			return true;
		}

		/**
		 * @brief Stop PWM generation for the channel
		 * @note This function disables the counter when no PWM channel is active
		 *
		 * @return Success
		 */
		ALWAYS_INLINE bool stopPwm() const noexcept {
			if(!hasPwmModule()) return false;
			switch(Channel) {
				case 1: Context->Instance->CCER &= ~TIM_CCER_CC1E; break;	// Disable capture compare output for channel 1
				case 2: Context->Instance->CCER &= ~TIM_CCER_CC2E; break;	// Disable capture compare output for channel 2
				case 3: Context->Instance->CCER &= ~TIM_CCER_CC3E; break;	// Disable capture compare output for channel 3
				case 4: Context->Instance->CCER &= ~TIM_CCER_CC4E; break;	// Disable capture compare output for channel 4
				default: bsp::unreachable();
			}
			if(Context->Instance->CCER == 0) Context->Instance->CR1 &= ~TIM_CR1_CEN;	// Disable the counter when all pwm channels are disabled
			return true;
		}

		/**
		 * @brief Start set pwm polarity
		 *
		 * @param highActive Set channel to high active when true
		 * @return Success
		 */
		ALWAYS_INLINE bool setPolarityHigh(bool highActive = true) const noexcept {
			if(!hasPwmModule()) return false;
			if(!highActive){
				switch(Channel) {
					case 1: Context->Instance->CCER |= TIM_CCER_CC1P; break;	// Capture/Compare 1 output Polarity to low
					case 2: Context->Instance->CCER |= TIM_CCER_CC2P; break;	// Capture/Compare 2 output Polarity to low
					case 3: Context->Instance->CCER |= TIM_CCER_CC3P; break;	// Capture/Compare 3 output Polarity to low
					case 4: Context->Instance->CCER |= TIM_CCER_CC4P; break;	// Capture/Compare 4 output Polarity to low
					default: bsp::unreachable();
				}
			}
			else {
				switch(Channel) {
					case 1: Context->Instance->CCER &= ~TIM_CCER_CC1P; break;	// Capture/Compare 1 output Polarity to high
					case 2: Context->Instance->CCER &= ~TIM_CCER_CC2P; break;	// Capture/Compare 2 output Polarity to high
					case 3: Context->Instance->CCER &= ~TIM_CCER_CC3P; break;	// Capture/Compare 3 output Polarity to high
					case 4: Context->Instance->CCER &= ~TIM_CCER_CC4P; break;	// Capture/Compare 4 output Polarity to high
					default: bsp::unreachable();
				}
			}

			return true;
		}

		/**
		 * @brief Set the duty cycle as a float value
		 *
		 * @param dutyCycle Duty cycle in % [0 100]
		 * @return Success
		 */
		ALWAYS_INLINE bool setDutyCycle(float dutyCycle) const noexcept {
			if(!hasPwmModule()) return false;
			dutyCycle = std::abs(dutyCycle);						// Make sure that the value is positive
			if(dutyCycle > 100) dutyCycle = 100;					// Limit the duty cycle to 100
			Size arr = Context->Instance->ARR;						// Get auto reload register
			Size ccr = 0;
			if(dutyCycle != 0) ccr = arr / 100 * dutyCycle;			// Calculate capture compare register value
			switch(Channel) {
				case 1: Context->Instance->CCR1 = ccr; break;		// Set the duty cycle for channel 1
				case 2: Context->Instance->CCR2 = ccr; break;		// Set the duty cycle for channel 2
				case 3: Context->Instance->CCR3 = ccr; break;		// Set the duty cycle for channel 3
				case 4: Context->Instance->CCR4 = ccr; break;		// Set the duty cycle for channel 4
				default: bsp::unreachable();
			}

			return true;
		}

	private:
		/**
		 * @brief Checks if the time has an pwm module
		 *
		 * @return Success
		 */
		bool hasPwmModule() const noexcept{
			if ((Context->Instance == TIM6) ||			// Checks if the timer does not have a pwm module (less to check)
					(Context->Instance == TIM7) ||
					(Context->Instance == TIM10) ||
					(Context->Instance == TIM13) ||
					(Context->Instance == TIM14)) {
				return false;
			}
			return true;
		}

	};


	/**
	 * @brief Timer encoder implementation for Midgard
	 * @warning Do not use this on its own!
	 *
	 * @tparam Context Timer context
	 * @tparam Size Timer width (16 bit or 32 bit)
	 */
	template<auto Context, typename Size>
	struct TimerEncoder {

		/**
		 * @brief Last known turning direction of the encoder
		 */
		enum class Direction : u8 {
			Clockwise,
			CounterClockwise,
		};

		/**
		 * @brief Modes for the encoder, 48 odr 96 steps per turn are possible
		 */
		enum class Mode : u8 {
			_48StepsPerTurn,
			_96StepsPerTurn
		};

		/**
		 * @brief Enable the encoder mode
		 * @note This does only work for timer with a encoder modul
		 *
		 * @return Success
		 */
		ALWAYS_INLINE bool enable() const noexcept {
			if(!hasEncoderModule()) return false;						// Check if the timer got a pwm modul
			Context->Instance->CCER = TIM_CCER_CC1E | TIM_CCER_CC2E;	// Enable capture compare channel 1 and 2
			Context->Instance->CR1 = TIM_CR1_CEN;						// Enable the timer
			return true;
		}

		/**
		 * @brief Disable the encoder mode
		 * @note This does only work for timer with a encoder modul
		 *
		 * @return Success
		 */
		ALWAYS_INLINE bool disable() const noexcept {
			if(!hasEncoderModule()) return false;							// Check if the timer got a pwm modul
			Context->Instance->CR1 &= ~TIM_CR1_CEN;							// Disable the timer
			Context->Instance->CCER &= ~(TIM_CCER_CC1E | TIM_CCER_CC2E);	// Disable capture compare channel 1 and 2
			return true;
		}

		/**
		 * @brief Get the counter value
		 * @note This does only work for timer with a encoder modul
		 *
		 * @return Actual timer count
		 */
		ALWAYS_INLINE Size getCount() const noexcept {
			return Context->Instance->CNT;		// Read the counter value form the register
		}

		/**
		 * @brief Set the encoder counter value
		 *
		 * @param cnt New counter value
		 */
		ALWAYS_INLINE void setCount(Size cnt) const noexcept {
			Context->Instance->CNT = cnt;		// Write the new counter value to the register
		}

		/**
		 * @brief Get the direction of the last rotation
		 * @note This bit might not be accurate while turning the encoder
		 *
		 * @return Direction
		 */
		ALWAYS_INLINE Direction getDirection() const noexcept {
			return (Context->Instance->CR1 & TIM_CR1_DIR) ? Direction::CounterClockwise : Direction::Clockwise;
		}

		/**
		 * @brief Set the mode of the encoder (48 or 96 counts per turn)
		 *
		 * @param mode Mode selection
		 */
		ALWAYS_INLINE void setMode(Mode mode) const noexcept {
			Context->Instance->CR1 &= ~TIM_CR1_CEN;											// Disable the timer
			Context->Instance->SMCR &= ~(TIM_SMCR_SMS_0 | TIM_SMCR_SMS_1);					// Reset the mode bits
			switch(mode) {																						// Set the new mode according to
				case Mode::_48StepsPerTurn: Context->Instance->SMCR |= TIM_SMCR_SMS_0; break;					// Counter counts up/down on TI1FP1 edge depending on TI2FP2 level
				case Mode::_96StepsPerTurn: Context->Instance->SMCR |= TIM_SMCR_SMS_0 | TIM_SMCR_SMS_1; break;	// Counter counts up/down on both TI1FP1 and TI2FP2 edges depending on the level of the other input
			}
			Context->Instance->CR1 = TIM_CR1_CEN;											// Enable the timer
		}

		/**
		 * @brief Initialization function for the encoder
		 * @note Default encoder mode is 96 steps per turn
		 *
		 * @return Success
		 */
		ALWAYS_INLINE bool init() const noexcept {
			if(!hasEncoderModule()) return false;							// Check if the timer got a pwm modul
			Context->Instance->CCER = TIM_CCER_CC1E | TIM_CCER_CC2E;		// Enable capture compare 1 and 2
			Context->Instance->SMCR |= TIM_SMCR_SMS_0 | TIM_SMCR_SMS_1;		// Counter counts up/down on both TI1FP1 and TI2FP2 edges depending on the level of the other input
			Context->Instance->CR1 = TIM_CR1_CEN;							// Enable the timer
			return true;
		}

	private:
		/**
		 * @brief Checks if the time has an encoder module
		 *
		 * @return Success
		 */
		bool hasEncoderModule() const noexcept{
			if ((Context->Instance == TIM1) ||		// All timer with a Encoder Module
					(Context->Instance == TIM2) ||
					(Context->Instance == TIM3) ||
					(Context->Instance == TIM4) ||
					(Context->Instance == TIM5) ||
					(Context->Instance == TIM8)) {
				return true;
			}
			return false;
		}
	};

	/**
	 * @brief Profile counter implementation for Midgard
	 * @warning Do not use this on its own!
	 *
	 * @tparam Context Timer context
	 * @tparam Size Timer width (16 bit or 32 bit)
	 */
	template<auto Context, typename Size>
	struct TimerProfileCounter {


		/**
		 * @brief Start the counter
		 */
		ALWAYS_INLINE void start() const noexcept {
			Context->Instance->CR1 = TIM_CR1_CEN;	// Enable the timer
		}

		/**
		 * @brief Stop the counter
		 */
		ALWAYS_INLINE void stop() const noexcept {
			Context->Instance->CR1 &= ~TIM_CR1_CEN;	// Disable the timer
		}

		/**
		 * @brief Reset the counter to 0
		 */
		ALWAYS_INLINE void reset() const noexcept {
			Context->Instance->CNT = 0;
		}

		/**
		 * @brief Get the time to an overflow
		 *
		 * @return Time to an overflow in a u64
		 */
		u64 getTimeToOverflow() const noexcept {
			return cntToNanoSeconds(std::numeric_limits<Size>::max());
		}

		/**
		 * @brief Get the time to an overflow
		 *
		 * @return Time to an overflow formatted as a string
		 */
		std::string getFormattedTimeToOverflow() const noexcept {
			return formatToString(cntToNanoSeconds(std::numeric_limits<Size>::max()));
		}

		/**
		 * @brief Get the time passed time since the start
		 *
		 * @return Passed time in a u64
		 */
		u64 getPassedTime() const noexcept {
			return cntToNanoSeconds(Context->Instance->CNT);
		}

		/**
		 * @brief Get the time passed time since the start
		 *
		 * @return Passed time formatted as a string
		 */
		std::string getFormattedPassedTime() const noexcept {
			return formatToString(cntToNanoSeconds(Context->Instance->CNT));
		}

		/**
		 * @brief Formats the passed time in ns to a string
		 *
		 * @param passedTime Passed time in nanoseconds
		 * @return Time passed formatted as a string
		 */
		std::string formatToString(u64 passedTime) const noexcept {
			std::string buffer(0xFF, 0x00);
			u32 s = passedTime / 1E9;
			u16 ms = static_cast<u32>(passedTime / 1E6) % 1000;
			u16 us =  static_cast<u32>(passedTime / 1E3) % 1000;
			u16 ns = passedTime % 1000;

			snprintf(buffer.data(), buffer.size(), "%lus %dms %dus %dns", s, ms, us, ns);

			return buffer;
		}


	private:

		/**
		 * @brief Get the counter value transformed to a time
		 *
		 * @param cntValue Value of the counter
		 * @return Time passed in nano seconds
		 */
		u64 cntToNanoSeconds(Size cntValue) const noexcept {
			float timerFrequency;

			if ((Context->Instance == TIM1) ||			// Get the timerFrequency before prescaler
					(Context->Instance == TIM8) ||		// this is depending on the APBx bus different
					(Context->Instance == TIM9) ||
					(Context->Instance == TIM10) ||
					(Context->Instance == TIM11)) {
				float pclk2 = static_cast<float>(SystemCoreClock >> APBPrescTable[(RCC->CFGR & RCC_CFGR_PPRE2) >> RCC_CFGR_PPRE2_Pos]); // Get the timer clock before prescaler for APB2
				if ((RCC->CFGR & RCC_CFGR_PPRE2) == 0) timerFrequency = pclk2;	// Timer frequency when APB2 prescaler = 1
				else timerFrequency = 2 * pclk2;								// Timer frequency when APB2 prescaler > 1

			}
			else {
				float pclk1 = static_cast<float>(SystemCoreClock >> APBPrescTable[(RCC->CFGR & RCC_CFGR_PPRE1) >> RCC_CFGR_PPRE1_Pos]); // Get the timer clock before prescaler for APB1
				if ((RCC->CFGR & RCC_CFGR_PPRE1) == 0) timerFrequency = pclk1;	// Timer frequency when APB1 prescaler = 1
				else timerFrequency = 2 * pclk1;								// Timer frequency when APB1 prescaler > 1
			}

			return static_cast<u64>(((cntValue) / timerFrequency) * 1E9);		// Calculate the passed time in ns
		}


	};

	/**
	 * @brief Timer implementation for Midgard
	 * @warning Do not use this on its own!
	 *
	 * @tparam Context Timer context
	 * @tparam Size Timer width (16 bit or 32 bit)
	 */
	template<auto Context, typename Size>
	struct Timer {

	    /**
	     * @brief Timer channel
	     *
	     * @tparam Number Channel number
	     */
		template<u8 Number>
		static constexpr auto Channel = TimerChannel<Context, Number, Size>();

	    /**
	     * @brief Timer in encoder mode
	     */
		static constexpr auto Encoder = TimerEncoder<Context, Size>();

	    /**
	     * @brief Timer used as profile counter
	     */
		static constexpr auto ProfileCounter = TimerProfileCounter<Context, Size>();

		/**
		 * @brief Init function
		 *
		 * @return Success
		 */
		static bool init() {
			return true;
		}

		/**
		 * @brief Deinit function
		 *
		 * @return Success
		 */
		static bool deinit() {
			return true;
		}


		/**
		 * @brief Enable the counter
		 */
		static void enable() {
			Context->Instance->CR1 = TIM_CR1_CEN;	// Enable the timer
		}

		/**
		 * @brief Disable the counter
		 */
		static void disable() {
			Context->Instance->CR1 &= ~TIM_CR1_CEN;	// Disable the timer
		}


	    /**
	     * @brief Get the counter value
	     *
	     * @return Actual timer count
	     */
		static Size getCount() {
			return Context->Instance->CNT;
		}

	    /**
	     * @brief Set the counter value
	     *
	     * @param cnt New timer value
	     */
		static void setCount(Size cnt) {
			Context->Instance->CNT = cnt;
		}

	    /**
	     * @brief Get the pwm frequency
	     * @note The frequency is for all channels the same
	     *
	     * @return Frequency in Hz
	     */
		static u32 getPwmFrequency() {
			auto arr = Context->Instance->ARR;
			auto psc = (Context->Instance->PSC + 1);
			if(psc == 0) psc = 1;

			if ((Context->Instance == TIM1) ||
					(Context->Instance == TIM8) ||
					(Context->Instance == TIM9) ||
					(Context->Instance == TIM10) ||
					(Context->Instance == TIM11)) {

				u32 pclk2 = (SystemCoreClock >> APBPrescTable[(RCC->CFGR & RCC_CFGR_PPRE2) >> RCC_CFGR_PPRE2_Pos]);	// Get the timer clock before prescaler for APB1
				if ((RCC->CFGR & RCC_CFGR_PPRE2) == 0) 	return (pclk2 / psc) / arr;									// Return the pwm frequency when APB1 prescaler = 1
				else return 2 *  (pclk2 / psc) / arr;																// Return the pwm frequency when APB1 prescaler > 1

			}
			else {
				u32 pclk1 = (SystemCoreClock >> APBPrescTable[(RCC->CFGR & RCC_CFGR_PPRE1) >> RCC_CFGR_PPRE1_Pos]); // Get the timer clock before prescaler for APB2
				if ((RCC->CFGR & RCC_CFGR_PPRE1) == 0) 	return (pclk1 / psc) / arr;									// Return the pwm frequency when APB2 prescaler = 1
				else return 2 * (pclk1 / psc) / arr;																// Return the pwm frequency when APB2 prescaler > 1

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
		static bool setPwmFrequency(u32 f_hz, Size resolution = 0){
			u32 timerFrequency;							// Timerfrequency depending on the RCC configuration
			u32 psc = 0;
			Size arr = 0;

			std::array<float, 4> dutyCycle;				// Save the actual duty cycle for each channel
			dutyCycle[0] = intToDuty(Context->Instance->CCR1);
			dutyCycle[1] = intToDuty(Context->Instance->CCR2);
			dutyCycle[2] = intToDuty(Context->Instance->CCR3);
			dutyCycle[3] = intToDuty(Context->Instance->CCR4);




			if(resolution){
				Context->Instance->ARR = resolution;	// Set a new auto reload value
			}
			arr = Context->Instance->ARR;				// Get the auto reload register

			if ((Context->Instance == TIM1) ||			// Get the timerFrequency before prescaler
					(Context->Instance == TIM8) ||		// this is depending on the APBx bus different
					(Context->Instance == TIM9) ||
					(Context->Instance == TIM10) ||
					(Context->Instance == TIM11)) {
				u32 pclk2 = (SystemCoreClock >> APBPrescTable[(RCC->CFGR & RCC_CFGR_PPRE2) >> RCC_CFGR_PPRE2_Pos]); // Get the timer clock before prescaler for APB2
				if ((RCC->CFGR & RCC_CFGR_PPRE2) == 0) timerFrequency = pclk2;	// Pwm frequency when APB2 prescaler = 1
				else timerFrequency = 2 * pclk2;								// Pwm frequency when APB2 prescaler > 1

			}
			else {
				u32 pclk1 = (SystemCoreClock >> APBPrescTable[(RCC->CFGR & RCC_CFGR_PPRE1) >> RCC_CFGR_PPRE1_Pos]); // Get the timer clock before prescaler for APB1
				if ((RCC->CFGR & RCC_CFGR_PPRE1) == 0) timerFrequency = pclk1;	// Pwm frequency when APB1 prescaler = 1
				else timerFrequency = 2 * pclk1;								// Pwm frequency when APB1 prescaler > 1
			}

			if((f_hz * arr) > timerFrequency) return false; 	// Check if the timer frequency is not to low

			psc = std::round((timerFrequency / (f_hz * arr)) - 1);	// Calculate the prescaler

			if(psc > 0xFFFF) return false;				// Check if prescaler is in the possible range from u16
			else{
				Context->Instance->CR1 &= ~TIM_CR1_CEN;	// Stop counter to set the new prescaler and until the new duty cycle values are set
				Context->Instance->PSC = psc;			// Set the new prescaler
			}

			// Reset the stored duty cycle for each channel according to the resolution
			Context->Instance->CCR1 = dutyToInt(dutyCycle[0]);
			Context->Instance->CCR2 = dutyToInt(dutyCycle[1]);
			Context->Instance->CCR3 = dutyToInt(dutyCycle[2]);
			Context->Instance->CCR4 = dutyToInt(dutyCycle[3]);

			Context->Instance->CR1 = TIM_CR1_CEN;		// Enable the timer again

			return true;
		}



	private:

		/**
		 * @brief Converts a duty cycle in % to an integer according to the arr register
		 *
		 * @param dutyCycle Duty cycle in %
		 * @return Duty cycle as an integer
		 */
		static constexpr Size dutyToInt(float dutyCycle){
			if(dutyCycle > 100) dutyCycle = 100;
			else if(dutyCycle <= 0) return 0;
			Size arr = Context->Instance->ARR;
			return static_cast<Size>(arr / 100 * dutyCycle);
		}

		/**
		 * @brief Converts a duty cycle from integer to an float in % according to the arr register
		 *
		 * @param intDutyCycle duty cycle as an integer
		 * @return Duty cycle as a float in %
		 */
		static constexpr float intToDuty(Size intDutyCycle){
			Size arr = Context->Instance->ARR;
			if(arr == 0) return 0;
			return static_cast<float>(intDutyCycle) / static_cast<float>(arr) * 100.0F;
		}
	};

}
