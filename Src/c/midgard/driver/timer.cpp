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

#if BOARD == MIDGARD

	#include <cpp/common/attributes.hpp>
	#include <cpp/common/types.hpp>
	#include <cpp/common/utils.hpp>

	#include <c/midgard/driver/timer.h>

	#include <yggdrasil.h>

	#include <math.h>

	/* Basic tim functions */

	C_LINKAGE bool yggdrasil_TIM_Init(tim_t tim) {
		return true;
	}

	C_LINKAGE bool yggdrasil_TIM_Deinit(tim_t tim) {
		return true;
	}

	C_LINKAGE void yggdrasil_TIM_Enable(tim_t tim) {
		tim.interface->Instance->CR1 = TIM_CR1_CEN;		// Enable the timer
	}

	C_LINKAGE void yggdrasil_TIM_Disable(tim_t tim) {
		tim.interface->Instance->CR1 &= ~TIM_CR1_CEN;	// Disable the timer
	}

	C_LINKAGE u32 yggdrasil_TIM_GetCount(tim_t tim) {
		return tim.interface->Instance->CNT;
	}

	C_LINKAGE void yggdrasil_TIM_SetCount(tim_t tim, u32 cnt) {
		tim.interface->Instance->CNT = cnt;
	}

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

	C_LINKAGE bool yggdrasil_TIM_Channel_StartPwm(tim_channel_t channel) {
		if(!hasPwmModule(channel.timer)) return false;
		switch(channel.channel) {
			case 1: channel.timer.interface->Instance->CCER |= TIM_CCER_CC1E; break;	// Enable capture compare output for channel 1
			case 2: channel.timer.interface->Instance->CCER |= TIM_CCER_CC2E; break;	// Enable capture compare output for channel 2
			case 3: channel.timer.interface->Instance->CCER |= TIM_CCER_CC3E; break;	// Enable capture compare output for channel 3
			case 4: channel.timer.interface->Instance->CCER |= TIM_CCER_CC4E; break;	// Enable capture compare output for channel 4
			default: bsp::unreachable();
		}
		channel.timer.interface->Instance->CR1 = TIM_CR1_CEN;							// Enable the counter
		return true;
	}

	C_LINKAGE bool yggdrasil_TIM_Channel_StopPwm(tim_channel_t channel) {
		if(!hasPwmModule(channel.timer)) return false;
		switch(channel.channel) {
			case 1: channel.timer.interface->Instance->CCER &= ~TIM_CCER_CC1E; break;	// Disable capture compare output for channel 1
			case 2: channel.timer.interface->Instance->CCER &= ~TIM_CCER_CC2E; break;	// Disable capture compare output for channel 2
			case 3: channel.timer.interface->Instance->CCER &= ~TIM_CCER_CC3E; break;	// Disable capture compare output for channel 3
			case 4: channel.timer.interface->Instance->CCER &= ~TIM_CCER_CC4E; break;	// Disable capture compare output for channel 4
			default: bsp::unreachable();
		}
		if(channel.timer.interface->Instance->CCER == 0) channel.timer.interface->Instance->CR1 &= ~TIM_CR1_CEN;	// Disable the counter when all pwm channels are disabled
		return true;
	}

	C_LINKAGE bool yggdrasil_TIM_Channel_SetPolarityHigh(tim_channel_t channel,	bool highActive) {
		if(!hasPwmModule(channel.timer)) return false;
		if(!highActive){
			switch(channel.channel) {
				case 1: channel.timer.interface->Instance->CCER |= TIM_CCER_CC1P; break;	// Capture/Compare 1 output Polarity to low
				case 2: channel.timer.interface->Instance->CCER |= TIM_CCER_CC2P; break;	// Capture/Compare 2 output Polarity to low
				case 3: channel.timer.interface->Instance->CCER |= TIM_CCER_CC3P; break;	// Capture/Compare 3 output Polarity to low
				case 4: channel.timer.interface->Instance->CCER |= TIM_CCER_CC4P; break;	// Capture/Compare 4 output Polarity to low
				default: bsp::unreachable();
			}
		}
		else {
			switch(channel.channel) {
				case 1: channel.timer.interface->Instance->CCER &= ~TIM_CCER_CC1P; break;	// Capture/Compare 1 output Polarity to high
				case 2: channel.timer.interface->Instance->CCER &= ~TIM_CCER_CC2P; break;	// Capture/Compare 2 output Polarity to high
				case 3: channel.timer.interface->Instance->CCER &= ~TIM_CCER_CC3P; break;	// Capture/Compare 3 output Polarity to high
				case 4: channel.timer.interface->Instance->CCER &= ~TIM_CCER_CC4P; break;	// Capture/Compare 4 output Polarity to high
				default: bsp::unreachable();
			}
		}

		return true;
	}

	C_LINKAGE bool yggdrasil_TIM_Channel_SetDutyCycle(tim_channel_t channel, float dutyCycle) {
		if(!hasPwmModule(channel.timer)) return false;
		dutyCycle = std::abs(dutyCycle);						// Make sure that the value is positive
		if(dutyCycle > 100) dutyCycle = 100;					// Limit the duty cycle to 100
		u32 arr = channel.timer.interface->Instance->ARR;						// Get auto reload register
		u32 ccr = 0;
		if(dutyCycle != 0) ccr = arr / 100 * dutyCycle;			// Calculate capture compare register value
		switch(channel.channel) {
			case 1: channel.timer.interface->Instance->CCR1 = ccr; break;		// Set the duty cycle for channel 1
			case 2: channel.timer.interface->Instance->CCR2 = ccr; break;		// Set the duty cycle for channel 2
			case 3: channel.timer.interface->Instance->CCR3 = ccr; break;		// Set the duty cycle for channel 3
			case 4: channel.timer.interface->Instance->CCR4 = ccr; break;		// Set the duty cycle for channel 4
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
	static void formatToString(u64 passedTime, char *buffer, size_t size) {
		u32 s = passedTime / 1E9;
		u16 ms = static_cast<u32>(passedTime / 1E6) % 1000;
		u16 us =  static_cast<u32>(passedTime / 1E3) % 1000;
		u16 ns = passedTime % 1000;

		snprintf(buffer, size, "%lus %dms %dus %dns", s, ms, us, ns);
	}

	C_LINKAGE void yggdrasil_ProfileCounter_Start(tim_t tim) {
		tim.interface->Instance->CR1 = TIM_CR1_CEN;	// Enable the timer
	}

	C_LINKAGE void yggdrasil_ProfileCounter_Stop(tim_t tim) {
		tim.interface->Instance->CR1 &= ~TIM_CR1_CEN;	// Disable the timer
	}

	C_LINKAGE void yggdrasil_ProfileCounter_Reset(tim_t tim) {
		tim.interface->Instance->CNT = 0;
	}

	C_LINKAGE u64 yggdrasil_ProfileCounter_GetTimeToOverflow(tim_t tim) {
		return cntToNanoSeconds(tim, (1ULL << (tim.size * 8)) - 1);
	}

	C_LINKAGE void yggdrasil_ProfileCounter_GetFormattedTimeToOverflow(tim_t tim, char *buffer, size_t size) {
		formatToString(cntToNanoSeconds(tim, (1ULL << (tim.size * 8)) - 1), buffer, size);
	}

	C_LINKAGE u64 yggdrasil_ProfileCounter_GetPassedTime(tim_t tim) {
		return cntToNanoSeconds(tim, tim.interface->Instance->CNT);
	}

	C_LINKAGE void yggdrasil_ProfileCounter_GetFormattedPassedTime(tim_t tim, char *buffer, size_t size) {
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

	C_LINKAGE bool yggdrasil_Encoder_Init(tim_t tim) {
		if(!hasEncoderModule(tim)) return false;							// Check if the timer got a pwm modul
		tim.interface->Instance->CCER = TIM_CCER_CC1E | TIM_CCER_CC2E;		// Enable capture compare 1 and 2
		tim.interface->Instance->SMCR |= TIM_SMCR_SMS_0 | TIM_SMCR_SMS_1;		// Counter counts up/down on both TI1FP1 and TI2FP2 edges depending on the level of the other input
		tim.interface->Instance->CR1 = TIM_CR1_CEN;							// Enable the timer
		return true;
	}

	C_LINKAGE bool yggdrasil_Encoder_Enable(tim_t tim) {
		if(!hasEncoderModule(tim)) return false;						// Check if the timer got a pwm modul
		tim.interface->Instance->CCER = TIM_CCER_CC1E | TIM_CCER_CC2E;	// Enable capture compare channel 1 and 2
		tim.interface->Instance->CR1 = TIM_CR1_CEN;						// Enable the timer
		return true;
	}

	C_LINKAGE bool yggdrasil_Encoder_Disable(tim_t tim) {
		if(!hasEncoderModule(tim)) return false;							// Check if the timer got a pwm modul
		tim.interface->Instance->CR1 &= ~TIM_CR1_CEN;							// Disable the timer
		tim.interface->Instance->CCER &= ~(TIM_CCER_CC1E | TIM_CCER_CC2E);	// Disable capture compare channel 1 and 2
		return true;
	}

	C_LINKAGE u32 yggdrasil_Encoder_GetCount(tim_t tim) {
		return tim.interface->Instance->CNT;		// Read the counter value form the register
	}

	C_LINKAGE void yggdrasil_Encoder_SetCount(tim_t tim, u32 cnt) {
		tim.interface->Instance->CNT = cnt;		// Write the new counter value to the register
	}

	C_LINKAGE enum EncoderDirection yggdrasil_Encoder_GetDirection(tim_t tim) {
		return (tim.interface->Instance->CR1 & TIM_CR1_DIR) ? EncoderDirection_CounterClockwise : EncoderDirection_Clockwise;
	}


	C_LINKAGE void yggdrasil_Encoder_SetMode(tim_t tim, enum EncoderMode mode) {
		tim.interface->Instance->CR1 &= ~TIM_CR1_CEN;											// Disable the timer
		tim.interface->Instance->SMCR &= ~(TIM_SMCR_SMS_0 | TIM_SMCR_SMS_1);					// Reset the mode bits
		switch(mode) {																									// Set the new mode according to
			case EncoderMode_48StepsPerTurn: tim.interface->Instance->SMCR |= TIM_SMCR_SMS_0; break;					// Counter counts up/down on TI1FP1 edge depending on TI2FP2 level
			case EncoderMode_96StepsPerTurn: tim.interface->Instance->SMCR |= TIM_SMCR_SMS_0 | TIM_SMCR_SMS_1; break;	// Counter counts up/down on both TI1FP1 and TI2FP2 edges depending on the level of the other input
		}
		tim.interface->Instance->CR1 = TIM_CR1_CEN;
	}

#endif
