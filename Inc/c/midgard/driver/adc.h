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
  *  @file c/midgard/driver/adc.h
  *  @ingroup midgard
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief ADC abstraction implementation for Midgard
  */

#include <c/common/types.h>

#include <stm32f7xx_hal.h>

typedef struct {
	ADC_HandleTypeDef *interface;
	u8 channel;

	u16 offset;
	u16 maxValue;
} adc_t;

/**
 * @brief Get the adc value from the channel specified in the ADC handle
 *
 * @param adc ADC handle
 * @return ADC value
 */
C_LINKAGE float yggdrasil_ADC_Read(adc_t adc);
