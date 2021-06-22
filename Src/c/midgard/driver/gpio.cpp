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
  *  @file midgard/driver/gpio.cpp
  *  @ingroup yggdrasil
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief GPIO Pin abstraction implementation for Midgard
  */

#include <yggdrasil.h>

#if BOARD == MIDGARD

	#include <cpp/common/attributes.hpp>
	#include <cpp/common/types.hpp>
	#include <cpp/common/utils.hpp>

	#include <c/midgard/driver/gpio.h>

	C_LINKAGE bool yggdrasil_GPIO_Init(gpio_t gpio){
		return true;
	}

	C_LINKAGE bool yggdrasil_GPIO_Deinit(gpio_t gpio){
		return true;
	}

	C_LINKAGE bool yggdrasil_GPIO_Get(gpio_t gpio) {
		bool state = gpio.port->IDR & (1 << gpio.pin);

		return gpio.lowActive ? !state : !!state;
	}

	C_LINKAGE void yggdrasil_GPIO_Set(gpio_t gpio, bool state) {
		state = gpio.lowActive ? !state : state;

		if (state)
			gpio.port->ODR |= (1 << gpio.pin);
		else
			gpio.port->ODR &= ~(1 << gpio.pin);
	}

	C_LINKAGE void yggdrasil_GPIO_Toggle(gpio_t gpio) {
		yggdrasil_GPIO_Set(gpio, !yggdrasil_GPIO_Get(gpio));
	}

	C_LINKAGE u16 yggdrasil_GPIO_GetMultiple(port_t port, u8 from, u8 to) {
		u32 mask = ((1ULL << (u64)(to - from + 1)) - 1) << from;

		return (port->IDR & mask) >> from;
	}

	C_LINKAGE void yggdrasil_GPIO_SetMultiple(port_t port, u8 from, u8 to, u16 value) {
		u32 mask = ((1ULL << (u64)(to - from + 1)) - 1) << from;

		port->ODR = (port->ODR & ~mask) | (((u32)value << from) & mask);
	}

#endif
