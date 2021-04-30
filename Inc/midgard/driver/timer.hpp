/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  _____.___.                 .___                    .__.__      *
  *  \__  |   | ____   ____   __| _/___________    _____|__|  |     *
  *   /   |   |/ ___\ / ___\ / __ |\_  __ \__  \  /  ___/  |  |     *
  *   \____   / /_/  > /_/  > /_/ | |  | \// __ \_\___ \|  |  |__   *
  *   / ______\___  /\___  /\____ | |__|  (____  /____  >__|____/   *
  *   \/     /_____//_____/      \/            \/     \/            *
  *                          - Midgard -                            *
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  @file midgard/driver/uart.hpp                                  *
  *  @ingroup midgard                                               *
  *  @author Fabian Weber, Nikolaij Saegesser						*
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  @brief Timer abstraction implementation for Midgard  		    *
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

#include <common/driver/timer.hpp>

#include <string>
#include <string_view>
#include <array>

#include <cstdlib>

#include <cmsis_gcc.h>



namespace bsp::mid::drv {

	template<auto Context, u8 Channel, typename Size>
	struct TimerChannel {
		static_assert(Channel >= 1 && Channel <= 4, "Channel index out of range");

		/**
		 * @brief Start PWM generation for the channel
		 * @Note A duty cycle should be set with setDuty()
		 *
		 * @return true when successfully started, false when not
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
		 * @note Does disable the counter when no PWM channel is active
		 *
		 * @return true when successfully stopped, false when not
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
		 * @brief Set the duty cycle as a float value
		 *
		 * @param duty cycle in %
		 */
		ALWAYS_INLINE void setDutyCycle(float dutyCycle) const noexcept {
			dutyCycle = std::abs(dutyCycle);
			if(dutyCycle > 100) dutyCycle = 100;
			else if(dutyCycle < 0) dutyCycle = 0;
			Size arr = Context->Instance->ARR;
			Size ccr = 0;
			if(dutyCycle != 0) ccr = arr / 100 * dutyCycle;
			switch(Channel) {
				case 1: Context->Instance->CCR1 = ccr; break;		// Set the duty cycle for channel 1
				case 2: Context->Instance->CCR2 = ccr; break;		// Set the duty cycle for channel 2
				case 3: Context->Instance->CCR3 = ccr; break;		// Set the duty cycle for channel 3
				case 4: Context->Instance->CCR4 = ccr; break;		// Set the duty cycle for channel 4
				default: bsp::unreachable();
			}
		}

	private:
		/**
		 * @brief checks if the time has an pwm module
		 *
		 * @return true / false
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

	template<auto Context, u8 Channel, typename Size>
	struct TimerEncoder {

		/**
		 * @brief enable the encoder mode
		 * @note this does only work for timer with a encoder modul
		 *
		 * @return true when successfully enabled, false when not
		 */
		ALWAYS_INLINE bool enable() const noexcept {
			if(!hasEncoderModule()) return false;
			Context->Instance->CCER = TIM_CCER_CC1E | TIM_CCER_CC2E;
			Context->Instance->CR1 = TIM_CR1_CEN;
			return true;
		}

		/**
		 * @brief disable the encoder mode
		 * @note this does only work for timer with a encoder modul
		 *
		 * @return true when successfully disabled, false when not
		 */
		ALWAYS_INLINE bool disable() const noexcept {
			if(!hasEncoderModule()) return false;
			Context->Instance->CR1 &= ~TIM_CR1_CEN;
			Context->Instance->CCER &= ~(TIM_CCER_CC1E | TIM_CCER_CC2E);
			return true;
		}

		/**
		 * @brief disable the encoder mode
		 * @note this does only work for timer with a encoder modul
		 */
		ALWAYS_INLINE Size getCount() const noexcept {
			return Context->Instance->CNT;
		}

		/**
		 * @brief set the encoder counter value
		 *
		 * @param new counter value (16 or 32 bit depending to the timer)
		 */
		ALWAYS_INLINE void setCount(Size cnt) const noexcept {
			Context->Instance->CNT = cnt;
		}

		/**
		 * @brief get the direction of the last rotation
		 * @note this bit might not be accurate while turning the encoder
		 *
		 * @return true for ccw, false for cw
		 */
		ALWAYS_INLINE bool getRotation() const noexcept {
			return (Context->Instance->CR1 & TIM_CR1_DIR);
		}

		/**
		 * @brief set the Mode of the encoder (48 or 96 counts per turn)
		 *
		 * @param mode selection
		 */
		ALWAYS_INLINE void setMode(u8 mode = 3) const noexcept {							// TODO make a enum class for mode
			Context->Instance->CR1 &= ~TIM_CR1_CEN;											// Disable the timer
			Context->Instance->SMCR &= ~(TIM_SMCR_SMS_0 | TIM_SMCR_SMS_1);					// Reset the mode bits
			switch(mode) {																	// Set the new mode according to
				case 1: Context->Instance->SMCR |= TIM_SMCR_SMS_0; break;					// Counter counts up/down on TI1FP1 edge depending on TI2FP2 level
				case 2: Context->Instance->SMCR |= TIM_SMCR_SMS_1; break;					// Counter counts up/down on TI2FP2 edge depending on TI1FP1 level
				case 3: Context->Instance->SMCR |= TIM_SMCR_SMS_0 | TIM_SMCR_SMS_1; break;	// Counter counts up/down on both TI1FP1 and TI2FP2 edges depending on the level of the other input
			}
			Context->Instance->CR1 = TIM_CR1_CEN;											// Enable the timer
		}

		/**
		 * @brief init function for the encoder
		 * @note defualt mode init is 96 ticks per turn
		 *
		 * @return true when successfully enabled, false when not
		 */
		ALWAYS_INLINE bool init() const noexcept {
			if(!hasEncoderModule()) return false;
			Context->Instance->CCER = TIM_CCER_CC1E | TIM_CCER_CC2E;		// Enable capture compare 1 and 2
			Context->Instance->SMCR |= TIM_SMCR_SMS_0 | TIM_SMCR_SMS_1;		// Counter counts up/down on both TI1FP1 and TI2FP2 edges depending on the level of the other input
			Context->Instance->CR1 = TIM_CR1_CEN;							// Enable the timer
			return true;
		}

	private:
		/**
		 * @brief checks if the time has an encoder module
		 *
		 * @return true / false
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

	template<auto Context, typename Size>
	struct Timer {

		// TODO Add comments
		template<u8 Number>
		static constexpr auto Channel = TimerChannel<Context, Number, Size>();


		// TODO remove number
		template<u8 Number>
		static constexpr auto Encoder = TimerEncoder<Context, Number, Size>();

		/**
		 * @brief get the counter value
		 *
		 * @return counter value (16 or 32 bit depending to the timer)
		 */
		static Size getCount() {
			return Context->Instance->CNT;
		}

		/**
		 * @brief set the counter value
		 *
		 * @param new counter value (16 or 32 bit depending to the timer)
		 */
		static void setCount(Size cnt) {
			Context->Instance->CNT = cnt;
		}

		/**
		 * @brief get the pwm frequency for all channels
		 *
		 * @return frequency in hz
		 */
		static u32 getPwmFrequency() {
			auto arr = Context->Instance->ARR;
			auto psc = Context->Instance->PSC;
			if(psc == 0) psc = 1;

			if ((Context->Instance == TIM1) ||
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
		 * @brief set the pwm frequency and (optional) the maximal ticks within on cycle for all channels
		 *
		 * @param f_hz new frequency in hz
		 * @param resolution of the pwm, for 0 the actual value will be used
		 *
		 * @return true when the adjustment was possible, false when the parameter did not match
		 */
		static bool setPwmFrequency(u32 f_hz, Size resolution = 0){
			u32 pclk1 = (SystemCoreClock >> APBPrescTable[(RCC->CFGR & RCC_CFGR_PPRE1) >> RCC_CFGR_PPRE1_Pos]); // Get the timer clock before prescaler for APB1
			u32 pclk2 = (SystemCoreClock >> APBPrescTable[(RCC->CFGR & RCC_CFGR_PPRE2) >> RCC_CFGR_PPRE2_Pos]); // Get the timer clock before prescaler for APB2
			u32 timerFrequency;							// Timerfrequency depending on the RCC configuration
			u32 psc = 0;								// Note: prescaler is always 16 bit wide, but should not have an overflow
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
					(Context->Instance == TIM9) ||		// this is depending on the APBx bus different
					(Context->Instance == TIM10) ||
					(Context->Instance == TIM11)) {
				if ((RCC->CFGR & RCC_CFGR_PPRE2) == 0) timerFrequency = pclk2;	// Return the pwm frequency when APB2 prescaler = 1
				else timerFrequency = 2 * pclk2;								// Return the pwm frequency when APB2 prescaler > 1

			}
			else {
				if ((RCC->CFGR & RCC_CFGR_PPRE1) == 0) timerFrequency = pclk1;	// Return the pwm frequency when APB1 prescaler = 1
				else timerFrequency = 2 * pclk1;								// Return the pwm frequency when APB1 prescaler > 1
			}

			if(f_hz > timerFrequency) return false; 	// Check if the timer frequency is not to low

			psc = timerFrequency / (f_hz * arr);		// Calculate the prescaler

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
		 * @brief converts a duty cycle in % to an integer according to the arr register
		 *
		 * @param duty cycle in %
		 * @return duty cycle as integer
		 */
		static constexpr Size dutyToInt(float dutyCycle){
			if(dutyCycle > 100) dutyCycle = 100;
			else if(dutyCycle <= 0) return 0;
			Size arr = Context->Instance->ARR;
			return static_cast<Size>(arr / 100 * dutyCycle);
		}

		/**
		 * @brief converts a duty cycle from integer to an float in % according to the arr register
		 *
		 * @param duty cycle as integer
		 * @return duty cycle as float in %
		 */
		static constexpr float intToDuty(Size intDutyCycle){
			Size arr = Context->Instance->ARR;
			if(arr == 0) return 0;
			return static_cast<float>(intDutyCycle) / static_cast<float>(arr) * 100.0F;
		}
	};

}
