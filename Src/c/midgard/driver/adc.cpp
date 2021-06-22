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
  *  @file midgard/driver/adc.cpp
  *  @ingroup yggdrasil
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief ADC abstraction implementation for Midgard
  */

#include <yggdrasil.h>

#if BOARD == MIDGARD

	#include <cpp/common/attributes.hpp>
	#include <cpp/common/types.hpp>
	#include <cpp/common/utils.hpp>

	#include <c/midgard/driver/adc.h>

	#include <math.h>

	bool yggdrasil_ADC_Init(adc_t adc) {
		return true;
	}

	bool yggdrasil_ADC_Deinit(adc_t adc) {
		return true;
	}

	static u32 getHALChannel(u8 index) {
		switch (index) {
			case 0:  return ADC_CHANNEL_0;
			case 1:  return ADC_CHANNEL_1;
			case 2:  return ADC_CHANNEL_2;
			case 3:  return ADC_CHANNEL_3;
			case 4:  return ADC_CHANNEL_4;
			case 5:  return ADC_CHANNEL_5;
			case 6:  return ADC_CHANNEL_6;
			case 7:  return ADC_CHANNEL_7;
			case 8:  return ADC_CHANNEL_8;
			case 9:  return ADC_CHANNEL_9;
			case 10: return ADC_CHANNEL_10;
			case 11: return ADC_CHANNEL_11;
			case 12: return ADC_CHANNEL_12;
			case 13: return ADC_CHANNEL_13;
			case 14: return ADC_CHANNEL_14;
			case 15: return ADC_CHANNEL_15;
			case 16: return ADC_CHANNEL_16;
			case 17: return ADC_CHANNEL_17;
			case 18: return ADC_CHANNEL_18;
			default: bsp::unreachable();
		}
	}

	float yggdrasil_ADC_Read(adc_t adc) {
		ADC_ChannelConfTypeDef channelConfig = { 0 };

		channelConfig.Channel = getHALChannel(adc.channel);
		channelConfig.Rank = ADC_REGULAR_RANK_1;
		channelConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;

		HAL_ADC_ConfigChannel(adc.interface, &channelConfig);

		HAL_ADC_Start(adc.interface);
		HAL_ADC_PollForConversion(adc.interface, HAL_MAX_DELAY);

		return fmax((float)(HAL_ADC_GetValue(adc.interface)) - adc.offset, 0.0F) / adc.maxValue;
	}

#endif
