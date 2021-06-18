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
  *  @file c/midgard/driver/dac.h
  *  @ingroup midgard
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief DAC abstraction implementation for Midgard
  */

#include <c/common/types.h>

#include <stm32f7xx_hal.h>

typedef struct {
	DAC_HandleTypeDef *interface;
	u8 channel;

	u16 offset;
	u16 maxValue;
} dac_t;

/**
 * @brief DAC init function
 *
 * @param dac DAC handle
 * @return True when successfully stared, false when not
 */
C_LINKAGE bool yggdrasil_DAC_Init(dac_t dac);

/**
 * @brief DAC deinit function
 *
 * @param dac DAC handle
 * @return True when successfully stopped, false when not
 */
C_LINKAGE bool yggdrasil_DAC_Deinit(dac_t dac);

/**
 * @brief Set the dac value to the channel specified in the DAC handle
 *
 * @param dac DAC handle
 * @param value DAC value
 */
C_LINKAGE void yggdrasil_DAC_Write(dac_t dac, float value);

/**
 * @brief Get the dac value from the channel specified in the DAC handle
 *
 * @param dac DAC handle
 * @return DAC value
 */
C_LINKAGE float yggdrasil_DAC_Read(dac_t dac);
