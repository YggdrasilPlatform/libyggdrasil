/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *  _____.___.                 .___                    .__.__      *
 *  \__  |   | ____   ____   __| _/___________    _____|__|  |     *
 *   /   |   |/ ___\ / ___\ / __ |\_  __ \__  \  /  ___/  |  |     *
 *   \____   / /_/  > /_/  > /_/ | |  | \// __ \_\___ \|  |  |__   *
 *   / ______\___  /\___  /\____ | |__|  (____  /____  >__|____/   *
 *   \/     /_____//_____/      \/            \/     \/            *
 *                         - Midgard -                             *
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
 *  @file midgard/driver/timer.cpp
 *  @ingroup yggdrasil
 *  @author Fabian Weber, Nikolaij Saegesser
 *  @brief Timer abstraction implementation for Midgard
 */

#if defined(YGGDRASIL_PERIPHERAL_DEFS) && BOARD == MIDGARD

	#include <cpp/common/attributes.hpp>
	#include <cpp/common/types.hpp>
	#include <cpp/common/utils.hpp>

	#include <c/midgard/driver/timer.h>

	#include <yggdrasil.h>

	#include <math.h>

	/* Basic tim functions */

	/**
	 * @brief Timer initialization
	 *
	 * @param tim Timer handel
	 */
	C_LINKAGE bool yggdrasil_TIM_Init(tim_t tim) {
		return true;
	}

	/**
	 * @brief Timer enable
	 *
	 * @param tim Timer handel
	 */
	C_LINKAGE void yggdrasil_TIM_Enable(tim_t tim) {
		tim.interface->Instance->CR1 = TIM_CR1_CEN;		// Enable the timer
	}

	/**
	 * @brief Timer disable
	 *
	 * @param tim Timer handel
	 */
	C_LINKAGE void yggdrasil_TIM_Disable(tim_t tim) {
		tim.interface->Instance->CR1 &= ~TIM_CR1_CEN;	// Disable the timer
	}

	/**
	 * @brief Get the counter value
	 *
	 * @param tim Timer handel
	 * @return Actual timer count
	 */
	C_LINKAGE u32 yggdrasil_TIM_GetCount(tim_t tim) {
		return tim.interface->Instance->CNT;
	}

    /**
     * @brief Set the counter value
     *
     * @param tim Timer handel
     * @param cnt New timer value
     */
	C_LINKAGE void yggdrasil_TIM_SetCount(tim_t tim, u32 cnt) {
		tim.interface->Instance->CNT = cnt;
	}

    /**
     * @brief Reset the counter value
     *
     * @param tim Timer handel
     */
	C_LINKAGE void yggdrasil_TIM_ResetCount(tim_t tim) {
		tim.interface->Instance->CNT = 0;
	}

	/**
	 * @brief Converts a duty cycle in % to an integer according to the arr register
	 *
	 * @param tim Timer handel
	 * @param dutyCycle Duty cycle in %
	 * @return Duty cycle as an integer
	 */
	static u32 dutyToInt(tim_t tim, float dutyCycle) {
		if(dutyCycle > 100) dutyCycle = 100;
		else if(dutyCycle <= 0) return 0;
		u32 arr = tim.interface->Instance->ARR;
		return static_cast<u32>(arr / 100 * dutyCycle);
	}

	/**
	 * @brief Converts a duty cycle from integer to an float in % according to the arr register
	 *
	 * @param tim Timer handel
	 * @param intDutyCycle duty cycle as an integer
	 * @return Duty cycle as a float in %
	 */
	static float intToDuty(tim_t tim, u32 intDutyCycle) {
		u32 arr = tim.interface->Instance->ARR;
		if(arr == 0) return 0;
		return static_cast<float>(intDutyCycle) / static_cast<float>(arr) * 100.0F;
	}

    /**
     * @brief Get the pwm frequency
     * @note The frequency is for all channels the same
     *
     * @param tim Timer handel
     * @return Frequency in Hz
     */
	C_LINKAGE u32 yggdrasil_TIM_GetPwmFrequency(tim_t tim) {
		auto arr = tim.interface->Instance->ARR;
		auto psc = (tim.interface->Instance->PSC + 1);
		if(psc == 0) psc = 1;

		if ((tim.interface->Instance == TIM1) ||
				(tim.interface->Instance == TIM8) ||
				(tim.interface->Instance == TIM9) ||
				(tim.interface->Instance == TIM10) ||
				(tim.interface->Instance == TIM11)) {

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
	 * @param tim Timer handel
	 * @param f_hz new frequency in hz
	 * @param resolution of the pwm, for 0 the actual value will be used
	 *
	 * @return True when the adjustment was possible, false when the parameter did not match
	 */
	C_LINKAGE bool yggdrasil_TIM_SetPwmFrequency(tim_t tim, u32 f_hz, u32 resolution) {
		u32 pclk1 = (SystemCoreClock >> APBPrescTable[(RCC->CFGR & RCC_CFGR_PPRE1) >> RCC_CFGR_PPRE1_Pos]); // Get the timer clock before prescaler for APB1
		u32 pclk2 = (SystemCoreClock >> APBPrescTable[(RCC->CFGR & RCC_CFGR_PPRE2) >> RCC_CFGR_PPRE2_Pos]); // Get the timer clock before prescaler for APB2
		u32 timerFrequency;								// Timerfrequency depending on the RCC configuration
		u32 psc = 0;
		u32 arr = 0;

		std::array<float, 4> dutyCycle;					// Save the actual duty cycle for each channel
		dutyCycle[0] = intToDuty(tim, tim.interface->Instance->CCR1);
		dutyCycle[1] = intToDuty(tim, tim.interface->Instance->CCR2);
		dutyCycle[2] = intToDuty(tim, tim.interface->Instance->CCR3);
		dutyCycle[3] = intToDuty(tim, tim.interface->Instance->CCR4);




		if(resolution){
			tim.interface->Instance->ARR = resolution;	// Set a new auto reload value
		}
		arr = tim.interface->Instance->ARR;				// Get the auto reload register

		if ((tim.interface->Instance == TIM1) ||		// Get the timerFrequency before prescaler
				(tim.interface->Instance == TIM8) ||	// this is depending on the APBx bus different
				(tim.interface->Instance == TIM9) ||
				(tim.interface->Instance == TIM10) ||
				(tim.interface->Instance == TIM11)) {
			if ((RCC->CFGR & RCC_CFGR_PPRE2) == 0) timerFrequency = pclk2;	// Pwm frequency when APB2 prescaler = 1
			else timerFrequency = 2 * pclk2;								// Pwm frequency when APB2 prescaler > 1

		}
		else {
			if ((RCC->CFGR & RCC_CFGR_PPRE1) == 0) timerFrequency = pclk1;	// Pwm frequency when APB1 prescaler = 1
			else timerFrequency = 2 * pclk1;								// Pwm frequency when APB1 prescaler > 1
		}

		if((f_hz * arr) > timerFrequency) return false; 		// Check if the timer frequency is not to low

		psc = std::round((timerFrequency / (f_hz * arr)) - 1);	// Calculate the prescaler

		if(psc > 0xFFFF) return false;						// Check if prescaler is in the possible range from u16
		else{
			tim.interface->Instance->CR1 &= ~TIM_CR1_CEN;	// Stop counter to set the new prescaler and until the new duty cycle values are set
			tim.interface->Instance->PSC = psc;				// Set the new prescaler
		}

		// Reset the stored duty cycle for each channel according to the resolution
		tim.interface->Instance->CCR1 = dutyToInt(tim, dutyCycle[0]);
		tim.interface->Instance->CCR2 = dutyToInt(tim, dutyCycle[1]);
		tim.interface->Instance->CCR3 = dutyToInt(tim, dutyCycle[2]);
		tim.interface->Instance->CCR4 = dutyToInt(tim, dutyCycle[3]);

		tim.interface->Instance->CR1 = TIM_CR1_CEN;		// Enable the timer again

		return true;
	}



	/* Channel functions */
	/**
	 * @brief Checks if the time has an pwm module
	 *
	 * @param tim Timer handel
	 * @return True or false
	 */
	static bool hasPwmModule(tim_t tim) {
		if ((tim.interface->Instance == TIM6) ||			// Checks if the timer does not have a pwm module (less to check)
				(tim.interface->Instance == TIM7) ||
				(tim.interface->Instance == TIM10) ||
				(tim.interface->Instance == TIM13) ||
				(tim.interface->Instance == TIM14)) {
			return false;
		}
		return true;
	}

	/**
	 * @brief Start PWM generation for the channel
	 * @Note A duty cycle should be set with setDuty()
	 *
	 * @param tim Timer handel
	 * @return True when successfully started, false when not
	 */
	C_LINKAGE bool yggdrasil_TIM_Channel_StartPwm(tim_t tim) {
		if(!hasPwmModule(tim)) return false;
		switch(tim.channel) {
			case 1: tim.interface->Instance->CCER |= TIM_CCER_CC1E; break;	// Enable capture compare output for channel 1
			case 2: tim.interface->Instance->CCER |= TIM_CCER_CC2E; break;	// Enable capture compare output for channel 2
			case 3: tim.interface->Instance->CCER |= TIM_CCER_CC3E; break;	// Enable capture compare output for channel 3
			case 4: tim.interface->Instance->CCER |= TIM_CCER_CC4E; break;	// Enable capture compare output for channel 4
			default: bsp::unreachable();
		}
		tim.interface->Instance->CR1 = TIM_CR1_CEN;							// Enable the counter
		return true;
	}

	/**
	 * @brief Stop PWM generation for the channel
	 * @note This function disables the counter when no PWM channel is active
	 *
	 * @param tim Timer handel
	 * @return True when successfully stopped, false when not
	 */
	C_LINKAGE bool yggdrasil_TIM_Channel_StopPwm(tim_t tim) {
		if(!hasPwmModule(tim)) return false;
		switch(tim.channel) {
			case 1: tim.interface->Instance->CCER &= ~TIM_CCER_CC1E; break;	// Disable capture compare output for channel 1
			case 2: tim.interface->Instance->CCER &= ~TIM_CCER_CC2E; break;	// Disable capture compare output for channel 2
			case 3: tim.interface->Instance->CCER &= ~TIM_CCER_CC3E; break;	// Disable capture compare output for channel 3
			case 4: tim.interface->Instance->CCER &= ~TIM_CCER_CC4E; break;	// Disable capture compare output for channel 4
			default: bsp::unreachable();
		}
		if(tim.interface->Instance->CCER == 0) tim.interface->Instance->CR1 &= ~TIM_CR1_CEN;	// Disable the counter when all pwm channels are disabled
		return true;
	}

	/**
	 * @brief Start set pwm polarity
	 *
	 * @param tim Timer handel
	 * @param highActive Set channel to high active when true
	 * @return True when successfully switched, false when not
	 */
	C_LINKAGE bool yggdrasil_TIM_Channel_SetPolarityHigh(tim_t tim,	bool highActive) {
		if(!hasPwmModule(tim)) return false;
		if(!highActive){
			switch(tim.channel) {
				case 1: tim.interface->Instance->CCER |= TIM_CCER_CC1P; break;	// Capture/Compare 1 output Polarity to low
				case 2: tim.interface->Instance->CCER |= TIM_CCER_CC2P; break;	// Capture/Compare 2 output Polarity to low
				case 3: tim.interface->Instance->CCER |= TIM_CCER_CC3P; break;	// Capture/Compare 3 output Polarity to low
				case 4: tim.interface->Instance->CCER |= TIM_CCER_CC4P; break;	// Capture/Compare 4 output Polarity to low
				default: bsp::unreachable();
			}
		}
		else {
			switch(tim.channel) {
				case 1: tim.interface->Instance->CCER &= ~TIM_CCER_CC1P; break;	// Capture/Compare 1 output Polarity to high
				case 2: tim.interface->Instance->CCER &= ~TIM_CCER_CC2P; break;	// Capture/Compare 2 output Polarity to high
				case 3: tim.interface->Instance->CCER &= ~TIM_CCER_CC3P; break;	// Capture/Compare 3 output Polarity to high
				case 4: tim.interface->Instance->CCER &= ~TIM_CCER_CC4P; break;	// Capture/Compare 4 output Polarity to high
				default: bsp::unreachable();
			}
		}

		return true;
	}

	/**
	 * @brief Set the duty cycle as a float value
	 *
	 * @param tim Timer handel
	 * @param dutyCycle Duty cycle in % [0 100]
	 */
	C_LINKAGE bool yggdrasil_TIM_Channel_SetDutyCycle(tim_t tim, float dutyCycle) {
		if(!hasPwmModule(tim)) return false;
		dutyCycle = std::abs(dutyCycle);						// Make sure that the value is positive
		if(dutyCycle > 100) dutyCycle = 100;					// Limit the duty cycle to 100
		u32 arr = tim.interface->Instance->ARR;						// Get auto reload register
		u32 ccr = 0;
		if(dutyCycle != 0) ccr = arr / 100 * dutyCycle;			// Calculate capture compare register value
		switch(tim.channel) {
			case 1: tim.interface->Instance->CCR1 = ccr; break;		// Set the duty cycle for channel 1
			case 2: tim.interface->Instance->CCR2 = ccr; break;		// Set the duty cycle for channel 2
			case 3: tim.interface->Instance->CCR3 = ccr; break;		// Set the duty cycle for channel 3
			case 4: tim.interface->Instance->CCR4 = ccr; break;		// Set the duty cycle for channel 4
			default: bsp::unreachable();
		}

		return true;
	}

	/* Profile counter functions */

	/**
	 * @brief Get the counter value transformed to a time
	 *
	 * @param tim Timer handel
	 * @param cntValue Value of the counter
	 * @return Time passed in nano seconds
	 */
	static u64 cntToNanoSeconds(tim_t tim, u32 cntValue) {
		float pclk1 = static_cast<float>(SystemCoreClock >> APBPrescTable[(RCC->CFGR & RCC_CFGR_PPRE1) >> RCC_CFGR_PPRE1_Pos]); // Get the timer clock before prescaler for APB1
		float pclk2 = static_cast<float>(SystemCoreClock >> APBPrescTable[(RCC->CFGR & RCC_CFGR_PPRE2) >> RCC_CFGR_PPRE2_Pos]); // Get the timer clock before prescaler for APB2
		float timerFrequency;

		if ((tim.interface->Instance == TIM1) ||			// Get the timerFrequency before prescaler
				(tim.interface->Instance == TIM8) ||		// this is depending on the APBx bus different
				(tim.interface->Instance == TIM9) ||
				(tim.interface->Instance == TIM10) ||
				(tim.interface->Instance == TIM11)) {
			if ((RCC->CFGR & RCC_CFGR_PPRE2) == 0) timerFrequency = pclk2;	// Timer frequency when APB2 prescaler = 1
			else timerFrequency = 2 * pclk2;								// Timer frequency when APB2 prescaler > 1

		}
		else {
			if ((RCC->CFGR & RCC_CFGR_PPRE1) == 0) timerFrequency = pclk1;	// Timer frequency when APB1 prescaler = 1
			else timerFrequency = 2 * pclk1;								// Timer frequency when APB1 prescaler > 1
		}

		return static_cast<u64>(((cntValue) / timerFrequency) * 1E9);		// Calculate the passed time in ns
	}

	/**
	 * @brief Formats the passed time in ns to a string
	 *
	 * @param passedTime Passed time in nanoseconds
	 * @return Time passed formatted as a string
	 */
	void formatToString(u64 passedTime, char *buffer, size_t size) {
		u32 s = passedTime / 1E9;
		u16 ms = static_cast<u32>(passedTime / 1E6) % 1000;
		u16 us =  static_cast<u32>(passedTime / 1E3) % 1000;
		u16 ns = passedTime % 1000;

		snprintf(buffer, size, "%lus %dms %dus %dns", s, ms, us, ns);
	}

	/**
	 * @brief Start the counter
	 *
	 * @param tim Timer handel
	 */
	C_LINKAGE void yggdrasil_Profilecounter_Start(tim_t tim) {
		tim.interface->Instance->CR1 = TIM_CR1_CEN;	// Enable the timer
	}

	/**
	 * @brief Stop the counter
	 *
	 * @param tim Timer handel
	 */
	C_LINKAGE void yggdrasil_Profilecounter_Stop(tim_t tim) {
		tim.interface->Instance->CR1 &= ~TIM_CR1_CEN;	// Disable the timer
	}

	/**
	 * @brief Reset the counter to 0
	 *
	 * @param tim Timer handel
	 */
	C_LINKAGE void yggdrasil_Profilecounter_Reset(tim_t tim) {
		tim.interface->Instance->CNT = 0;
	}

	/**
	 * @brief Get the time to an overflow
	 *
	 * @param tim Timer handel
	 * @return Time to an overflow in a u64
	 */
	C_LINKAGE u64 yggdrasil_Profilecounter_GetTimeToOverflow(tim_t tim) {
		return cntToNanoSeconds(tim, (1ULL << (tim.size * 8)) - 1);
	}

	/**
	 * @brief Get the time to an overflow
	 *
	 * @return Time to an overflow formatted as a string
	 */
	C_LINKAGE void yggdrasil_Profilecounter_GetFormattedTimeToOverflow(tim_t tim, char *buffer, size_t size) {
		formatToString(cntToNanoSeconds(tim, (1ULL << (tim.size * 8)) - 1), buffer, size);
	}

	/**
	 * @brief Get the time passed time since the start
	 *
	 * @param tim Timer handel
	 * @return Passed time in a u64
	 */
	C_LINKAGE u64 yggdrasil_Profilecounter_GetPassedTime(tim_t tim) {
		return cntToNanoSeconds(tim, tim.interface->Instance->CNT);
	}

	/**
	 * @brief Get the time passed time since the start
	 *
	 * @param tim Timer handel
	 * @return Passed time formatted as a string
	 */
	C_LINKAGE void yggdrasil_Profilecounter_GetFormattedPassedTime(tim_t tim, char *buffer, size_t size) {
		return formatToString(cntToNanoSeconds(tim, tim.interface->Instance->CNT), buffer, size);
	}


	/* Encoder functions */

	/**
	 * @brief Checks if the time has an encoder module
	 *
	 * @param tim Timer handel
	 * @return True or false
	 */
	static bool hasEncoderModule(tim_t tim) {
		if ((tim.interface->Instance == TIM1) ||		// All timer with a Encoder Module
				(tim.interface->Instance == TIM2) ||
				(tim.interface->Instance == TIM3) ||
				(tim.interface->Instance == TIM4) ||
				(tim.interface->Instance == TIM5) ||
				(tim.interface->Instance == TIM8)) {
			return true;
		}
		return false;
	}

	/**
	 * @brief Initialization function for the encoder
	 * @note Default encoder mode is 96 steps per turn
	 *
	 * @param tim Timer handel
	 * @return True when successfully enabled, false when not
	 */
	C_LINKAGE bool yggdrasil_Encoder_Init(tim_t tim) {
		if(!hasEncoderModule(tim)) return false;							// Check if the timer got a pwm modul
		tim.interface->Instance->CCER = TIM_CCER_CC1E | TIM_CCER_CC2E;		// Enable capture compare 1 and 2
		tim.interface->Instance->SMCR |= TIM_SMCR_SMS_0 | TIM_SMCR_SMS_1;		// Counter counts up/down on both TI1FP1 and TI2FP2 edges depending on the level of the other input
		tim.interface->Instance->CR1 = TIM_CR1_CEN;							// Enable the timer
		return true;
	}

	/**
	 * @brief Enable the encoder mode
	 * @note This does only work for timer with a encoder modul
	 *
	 * @param tim Timer handel
	 * @return True when successfully enabled, false when not
	 */
	C_LINKAGE bool yggdrasil_Encoder_Enable(tim_t tim) {
		if(!hasEncoderModule(tim)) return false;						// Check if the timer got a pwm modul
		tim.interface->Instance->CCER = TIM_CCER_CC1E | TIM_CCER_CC2E;	// Enable capture compare channel 1 and 2
		tim.interface->Instance->CR1 = TIM_CR1_CEN;						// Enable the timer
		return true;
	}

	/**
	 * @brief Disable the encoder mode
	 * @note This does only work for timer with a encoder modul
	 *
	 * @param tim Timer handel
	 * @return True when successfully disabled, false when not
	 */
	C_LINKAGE bool yggdrasil_Encoder_Disable(tim_t tim) {
		if(!hasEncoderModule(tim)) return false;							// Check if the timer got a pwm modul
		tim.interface->Instance->CR1 &= ~TIM_CR1_CEN;							// Disable the timer
		tim.interface->Instance->CCER &= ~(TIM_CCER_CC1E | TIM_CCER_CC2E);	// Disable capture compare channel 1 and 2
		return true;
	}

	/**
	 * @brief Get the counter value
	 * @note This does only work for timer with a encoder modul
	 *
	 * @param tim Timer handel
	 * @return Actual timer count
	 */
	C_LINKAGE u32 yggdrasil_Encoder_GetCount(tim_t tim) {
		return tim.interface->Instance->CNT;		// Read the counter value form the register
	}

	/**
	 * @brief Set the encoder counter value
	 *
	 * @param tim Timer handel
	 * @param cnt New counter value
	 */
	C_LINKAGE void yggdrasil_Encoder_SetCount(tim_t tim, u32 cnt) {
		tim.interface->Instance->CNT = cnt;		// Write the new counter value to the register
	}

	/**
	 * @brief Get the direction of the last rotation
	 * @note This bit might not be accurate while turning the encoder
	 *
	 * @param tim Timer handel
	 * @return Direction
	 */
	C_LINKAGE enum EncoderDirection yggdrasil_Encoder_GetDirection(tim_t tim) {
		return (tim.interface->Instance->CR1 & TIM_CR1_DIR) ? EncoderDirectionCounterClockwise : EncoderDirectionClockwise;
	}

	/**
	 * @brief Set the mode of the encoder (48 or 96 counts per turn)
	 *
	 * @param tim Timer handel
	 * @param mode Mode selection
	 */
	C_LINKAGE void yggdrasil_Encoder_SetMoce(tim_t tim, enum EncoderMode mode) {
		tim.interface->Instance->CR1 &= ~TIM_CR1_CEN;											// Disable the timer
		tim.interface->Instance->SMCR &= ~(TIM_SMCR_SMS_0 | TIM_SMCR_SMS_1);					// Reset the mode bits
		switch(mode) {																									// Set the new mode according to
			case EncoderMode_48StepsPerTurn: tim.interface->Instance->SMCR |= TIM_SMCR_SMS_0; break;					// Counter counts up/down on TI1FP1 edge depending on TI2FP2 level
			case EncoderMode_96StepsPerTurn: tim.interface->Instance->SMCR |= TIM_SMCR_SMS_0 | TIM_SMCR_SMS_1; break;	// Counter counts up/down on both TI1FP1 and TI2FP2 edges depending on the level of the other input
		}
		tim.interface->Instance->CR1 = TIM_CR1_CEN;
	}

#endif
