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
  *  @file c/midgard/driver/gpio.h
  *  @ingroup midgard
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief GPIO Pin abstraction implementation for Midgard
  */

#include <c/common/types.h>

#include <stm32f7xx_hal.h>

#define LOW_ACTIVE true
#define HIGH_ACTIVE false

typedef GPIO_TypeDef* port_t;
typedef u8 pin_t;

typedef struct {
	port_t port;
	pin_t pin;
	bool lowActive;
} gpio_t;

/**
 * @brief GPIO initialization
 *
 * @param gpio GPIO handle
 */
C_LINKAGE bool yggdrasil_GPIO_Init(gpio_t gpio);

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

/**
 * @brief Get multiple GPIO states
 *
 * @param gpio GPIO handle
 * @param from Start bit number
 * @param to End bit number
 * @return GPIO state
 */
C_LINKAGE u16 yggdrasil_GPIO_GetMultiple(port_t port, u8 from, u8 to);

/**
 * @brief Set multiple GPIO states
 *
 * @param gpio GPIO handle
 * @param from Start bit number
 * @param to End bit number
 * @value GPIO state
 */
C_LINKAGE void yggdrasil_GPIO_SetMultiple(port_t port, u8 from, u8 to, u16 value);
