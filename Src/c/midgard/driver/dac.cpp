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
  *  @file midgard/driver/dac.cpp
  *  @ingroup yggdrasil
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief DAC abstraction implementation for Midgard
  */

#if BOARD == MIDGARD

	#include <cpp/common/attributes.hpp>
	#include <cpp/common/types.hpp>
	#include <cpp/common/utils.hpp>

	#include <c/midgard/driver/dac.h>

	#include <yggdrasil.h>

	#include <math.h>

	bool yggdrasil_DAC_Init(dac_t adc) {
		return true;
	}

	bool yggdrasil_DAC_Deinit(dac_t adc) {
		return true;
	}

	static u32 getHALChannel(u8 index) {
		switch (index) {
			case 1:  return DAC_CHANNEL_1;
			case 2:  return DAC_CHANNEL_2;
			default: bsp::unreachable();
		}
	}

	C_LINKAGE void yggdrasil_DAC_Write(dac_t dac, float value) {
		u32 channel = getHALChannel(dac.channel);

		HAL_DAC_SetValue(dac.interface, channel, DAC_ALIGN_12B_R, (u32)(fmax(value * dac.maxValue - dac.offset, 0.0F)));
		HAL_DAC_Start(dac.interface, channel);
	}

	C_LINKAGE float yggdrasil_DAC_Read(dac_t dac) {
		u32 channel = getHALChannel(dac.channel);

		return ((float)fmax(HAL_DAC_GetValue(dac.interface, channel) + dac.offset, 0)) / dac.maxValue;
	}

#endif
