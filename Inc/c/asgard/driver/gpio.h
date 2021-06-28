 /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  _____.___.                 .___                    .__.__      *
  *  \__  |   | ____   ____   __| _/___________    _____|__|  |     *
  *   /   |   |/ ___\ / ___\ / __ |\_  __ \__  \  /  ___/  |  |     *
  *   \____   / /_/  > /_/  > /_/ | |  | \// __ \_\___ \|  |  |__   *
  *   / ______\___  /\___  /\____ | |__|  (____  /____  >__|____/   *
  *   \/     /_____//_____/      \/            \/     \/            *
  *                          - Asgard -                             *
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
  *  @file c/asgard/driver/gpio.h
  *  @ingroup asgard
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief GPIO Pin abstraction implementation for Asgard
  */

#include <c/common/types.h>

#define LOW_ACTIVE true
#define HIGH_ACTIVE false

/**
 * @brief GPIO handle type
 */
typedef struct {
	u8 pinNumber;
	bool lowActive;
} gpio_t;

/**
 * @brief GPIO initialization
 *
 * @param gpio GPIO handle
 * @return Success
 */
extern "C" bool yggdrasil_GPIO_Init(gpio_t gpio);

/**
 * @brief GPIO deinitialization
 *
 * @param gpio GPIO handle
 * @return Success
 */
C_LINKAGE bool yggdrasil_GPIO_Deinit(gpio_t gpio);

/**
 * @brief Turn pin into an output
 *
 * @param gpio GPIO handle
 * @return Success
 */
C_LINKAGE bool yggdrasil_GPIO_MakeOutput(gpio_t gpio);

/**
 * @brief Turn pin into an input
 *
 * @param gpio GPIO handle
 * @return Success
 */
C_LINKAGE bool yggdrasil_GPIO_MakeInput(gpio_t gpio);

/**
 * @brief Get GPIO state
 *
 * @param gpio GPIO handle
 * @return GPIO state
 */
C_LINKAGE bool yggdrasil_GPIO_Get(gpio_t gpio);

/**
 * @brief Set GPIO state
 *
 * @param gpio GPIO handle
 * @param state GPIO state
 */
C_LINKAGE void yggdrasil_GPIO_Set(gpio_t gpio, bool state);

/**
 * @brief Toggle GPIO
 *
 * @param gpio GPIO handle
 */
C_LINKAGE void yggdrasil_GPIO_Toggle(gpio_t gpio);
